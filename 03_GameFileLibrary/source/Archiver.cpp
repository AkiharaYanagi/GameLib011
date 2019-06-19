//=================================================================================================
//
// ファイルアーカイバ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Archiver.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//------------------------------------------
	//	定数
	//------------------------------------------
	//アーカイブファイル名
	const TCHAR Archiver::m_archiveFileName[] = TEXT("archive.dat");

	//アーカイブ作成のため読み込むディレクトリ名
	const TCHAR Archiver::m_archiveDirName[] = TEXT("archive/");

	//アーカイブ作成のため読み込むファイル名条件
	const TCHAR Archiver::m_searchCondition[] = TEXT("archive/*.*");

	//ファイルマッピングの名前
	const TCHAR Archiver::m_mapName[] = TEXT("mapName");

	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	Archiver::P_Archiver	Archiver::m_inst;

	//------------------------------------------

	//コンストラクタ
	Archiver::Archiver ()
		: m_hFile ( nullptr ), m_archiveHeader ( nullptr ), m_hMap ( nullptr )
		, m_pFile ( nullptr ), m_fileNum ( 0 )
	{
	}

	//デストラクタ
	Archiver::~Archiver ()
	{
		Close ();
		if ( m_archiveHeader ) { delete[] m_archiveHeader; m_archiveHeader = nullptr; }
	}

	//アーカイブファイル作成
	void Archiver::Make ()
	{
		WIN32_FIND_DATA fileData;

		DWORD fileNum = 0;	//ファイル個数
		DWORD fileSize = 0;		//各ファイルサイズ
		DWORD fileTotalSize = 0;	//総ファイルサイズ

		//カレントディレクトリの取得
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//バイナリで書出用ファイルを開く
		HANDLE hWriteFile = CreateFile ( m_archiveFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );

		//-------------------------------------------------------------------------
		//ヘッダの作成
		//-------------------------------------------------------------------------
		//個数の取得
		HANDLE hFile = ::FindFirstFile ( m_searchCondition, &fileData );
		while ( true )
		{
			//次のファイルを取得
			if ( FindNextFile ( hFile, &fileData ) )
			{
				//ディレクトリはとばす(../一つ上のディレクトリなど)論理演算でチェックする
//				if ( fileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				//システムファイル(Thumbs.dbなど)はとばす
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }
				
				TCHAR fileName[MAX_PATH];		//ファイル名
				_tcscpy_s ( fileName, TEXT("archive/") );
				_tcscat_s ( fileName, fileData.cFileName );
				fileSize = fileData.nFileSizeLow;	//4Gbyteサイズ以上は扱わない
				
#if	1
				tostringstream toss;
				toss << fileName << TEXT(", オフセット: ") << fileTotalSize << TEXT(", ファイルサイズ: ") << fileSize << std::endl;
//				OutputDebugString ( toss.str().c_str () );
#endif	//0
				//個数のカウント
				++fileNum;
			}
			else	//次のファイルが取得できなかったとき
			{
				if ( GetLastError () == ERROR_NO_MORE_FILES ) {}	//列挙終了
				else {}		//エラー終了
				break;
			}
		}
		FindClose ( hFile );

		DWORD numberOfBytesWritten = 0;
		WriteFile ( hWriteFile, &fileNum, sizeof(DWORD), &numberOfBytesWritten, nullptr );

		tostringstream tossDebug;
		tossDebug << TEXT("アーカイブ　ファイル個数 = ") << fileNum << std::endl;
//		OutputDebugString ( tossDebug.str().c_str () );


		//ファイル名、オフセット、ファイルサイズを取得
		hFile = FindFirstFile ( m_searchCondition, &fileData );
		while ( 1 )
		{
			//次のファイルを取得
			if ( FindNextFile ( hFile, &fileData ) )
			{
				//ディレクトリはとばす
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
					tstring str ( fileData.cFileName );
					tostringstream toss;
					toss << TEXT("ディレクトリ: ") << str << TEXT(", ファイルサイズ: ") << fileData.nFileSizeLow << std::endl;
//					OutputDebugString ( toss.str().c_str () );
					continue; 
				}

				//システムファイル(Thumbs.dbなど)はとばす
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM )
				{
					tstring str ( fileData.cFileName );
					tostringstream toss;
					toss << TEXT("システムファイル: ") << str << TEXT(", ファイルサイズ: ") << fileData.nFileSizeLow << std::endl;
//					OutputDebugString ( toss.str().c_str () );
					continue; 
				}

				TCHAR fileName[MAX_PATH];		//ファイル名
				_tcscpy_s ( fileName, TEXT("archive/") );
				_tcscat_s ( fileName, fileData.cFileName );
				fileSize = fileData.nFileSizeLow;	//4Gbyteサイズ以上は扱わない
				
#if	1
				tostringstream toss;
				toss << fileName << TEXT(", オフセット: ") << fileTotalSize << TEXT(", ファイルサイズ: ") << fileSize << std::endl;
//				OutputDebugString ( toss.str().c_str () );
#endif	//0

				DWORD numberOfBytesWritten = 0;
				WriteFile ( hWriteFile, fileName, sizeof(fileName), &numberOfBytesWritten, nullptr );
				WriteFile ( hWriteFile, &fileTotalSize, sizeof(DWORD), &numberOfBytesWritten, nullptr );
				WriteFile ( hWriteFile, &fileSize, sizeof(DWORD), &numberOfBytesWritten, nullptr );

				//次のオフセット位置
				fileTotalSize += fileSize;
			}
			else	//次のファイルが取得できなかったとき
			{
				if ( GetLastError () == ERROR_NO_MORE_FILES ) {}	//列挙終了
				else {}		//エラー終了
				break;
			}
		}
		FindClose ( hFile );


		//-------------------------------------------------------------------------
		//実データ書出
		//-------------------------------------------------------------------------
		hFile = FindFirstFile ( m_searchCondition, &fileData );
		while ( 1 )
		{
			//次のファイルを取得
			if ( FindNextFile ( hFile, &fileData ) )
			{
				//ディレクトリはとばす
//				if ( fileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				//システムファイル(Thumbs.dbなど)はとばす
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }

				fileSize = fileData.nFileSizeLow;	//4Gbyteサイズ以上は扱わない
				
#if	0
				TCHAR fileName[MAX_PATH];		//ファイル名
				_tcscpy_s ( fileName, TEXT("archive/") );
				_tcscat_s ( fileName, fileData.cFileName );
				HANDLE hReadFile = CreateFile ( fileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
#endif	//0
				tstring fileName ( m_archiveDirName );
				fileName.append ( fileData.cFileName );

				HANDLE hReadFile = CreateFile ( fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );

				//ファイルハンドルからサイズ分読込
				BYTE* buf = new BYTE [ fileSize ];
				DWORD numberOfBytesRead = 0;
				ReadFile ( hReadFile, buf, fileSize, &numberOfBytesRead, nullptr );

				//ファイルにサイズ分書出
				DWORD numberOfBytesWritten = 0;
				WriteFile ( hWriteFile, buf, fileSize, &numberOfBytesWritten, nullptr );
				delete[] buf;

				CloseHandle ( hReadFile );

#if	0
				tostringstream toss0;
				toss0 << "read = " << numberOfBytesRead << ", write = " << numberOfBytesWritten << std::endl;
				OutputDebugString ( toss0.str().c_str () );
#endif	//0
			}
			else	//次のファイルが取得できなかったとき
			{
				if ( GetLastError () == ERROR_NO_MORE_FILES ) {}	//列挙終了
				else {}		//エラー終了
				break;
			}
		}
		FindClose ( hFile );

		CloseHandle ( hWriteFile );
	}


	//アーカイブファイル読込
	void Archiver::Open ()
	{
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		m_hFile = ::CreateFile ( m_archiveFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD erorr = GetLastError();

		//ファイル数を得る
		DWORD dwFileNum = 0;
		DWORD numberOfBytesRead = 0;
		bool bRet = ::ReadFile ( m_hFile, &dwFileNum, sizeof ( DWORD ), &numberOfBytesRead, nullptr );

		//ヘッダを個数分得る
		if ( m_archiveHeader ) { return; }
		m_archiveHeader = new ARCHIVE_HEADER_SEARCH [ dwFileNum ];

		for ( DWORD i = 0; i < dwFileNum; ++i )
		{
			ARCHIVE_HEADER temp;
			ReadFile ( m_hFile, &temp, sizeof ( ARCHIVE_HEADER ), &numberOfBytesRead, nullptr );
			m_archiveHeader[i].fileName.assign ( temp.fileName );
			m_archiveHeader[i].align.offset = temp.align.offset;
			m_archiveHeader[i].align.fileSize = temp.align.fileSize;

			m_map.insert ( ARCHIVE_MAP::value_type ( m_archiveHeader[i].fileName, &m_archiveHeader[i].align ) );
		}

		m_fileNum = dwFileNum;

		//ファイルマッピング
		//
		// ※ 名前を付けると複数起動時に同名のマッピングでアクセス違反になるので無名にする
		//
//		m_hMap = CreateFileMapping ( m_hFile, nullptr, PAGE_READONLY, 0, 0, m_mapName );
		m_hMap = CreateFileMapping ( m_hFile, nullptr, PAGE_READONLY, 0, 0, nullptr );
		if ( m_hMap == nullptr )
		{
			////DebugOutTrace::instance()->DebugOutf( TEXT("ファイルマッピングに失敗") );
			return;
		}
		m_pFile = MapViewOfFile ( m_hMap, FILE_MAP_READ, 0, 0, 0 );
	}


	//アーカイブファイル閉
	void Archiver::Close ()
	{
		if ( m_hMap ) { CloseHandle ( m_hMap ); m_hMap = nullptr; }
		if ( m_hFile ) { CloseHandle ( m_hFile ); m_hFile = nullptr; }
	}



	//元のファイル名からアーカイブ内のファイルポインタを得る
	ARCHIVE_FILE_USE Archiver::GetFilePointer ( LPCTSTR fileName ) 
	{
		ARCHIVE_FILE_USE ret = { nullptr, 0 };
//		if ( m_fileBuf ) { return ret; }
		
		//検索
		tstring str ( m_archiveDirName );
		str.append ( fileName );
		if ( m_map.find ( str ) == m_map.end() ) 
		{
			////DebugOutTrace::instance()->DebugOutf ( TEXT("%s, アーカイブの中に対象のファイルが見つかりませんでした\n"), fileName );
			return ret; 
		}

		//mapからポインタ配置情報を取得
		ARCHIVE_ALIGN* align = m_map [ str ];

		//データ開始位置
		DWORD startData = sizeof ( DWORD ) + sizeof ( ARCHIVE_HEADER ) * m_fileNum;

		ret.filePointer = (LPBYTE)m_pFile + startData + align->offset;
		ret.fileSize = align->fileSize;

		return ret;

#if	0
		m_fileBuf = new BYTE [ align->fileSize ];

		SetFilePointer ( m_hFile, startData + align->offset, nullptr, FILE_BEGIN );
		DWORD numberOfBytesRead = 0;
		ReadFile ( m_hFile, m_fileBuf, align->fileSize, &numberOfBytesRead, nullptr );

		ret.filePointer = m_fileBuf;
		ret.fileSize = align->fileSize;
		return ret;
#endif	//0
	}


}	//namespace GAME


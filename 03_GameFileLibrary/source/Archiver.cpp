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
	const TCHAR Archiver::ARCHIVE_FILE_NAME[] = _T("archive.dat");

	//アーカイブ作成のため読み込むディレクトリ名
	const TCHAR Archiver::ARCHIVE_DIR_NAME[] = _T("archive\\");

	//アーカイブ作成のため読み込むファイル名条件
	const TCHAR Archiver::SEARCH_CONDITION[] = _T("archive\\*.*");

	//ファイルマッピングの名前
	const TCHAR Archiver::MAP_NAME[] = _T("mapName");

	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	Archiver::P_Archiver	Archiver::m_inst;

	//------------------------------------------

	//コンストラクタ
	Archiver::Archiver ()
		: m_hMap ( nullptr ), m_pFile ( nullptr ), m_fileNum ( 0 )
	{
	}

	//デストラクタ
	Archiver::~Archiver ()
	{
		Close ();
	}

	//アーカイブファイル閉
	void Archiver::Close ()
	{
		if ( m_hMap ) { CloseHandle ( m_hMap ); m_hMap = nullptr; }
	}




	//@todo 再起によるサブディレクトリの検索を追加する




	//アーカイブファイル作成
	void Archiver::Make ()
	{
		//カレントディレクトリの取得
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//バイナリで書出用ファイルを開く
		HANDLE hWriteFile = CreateFile ( ARCHIVE_FILE_NAME, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD numberOfBytesWritten = 0;

		//-------------------------------------------------------------------------
		//	ヘッダの作成
		//-------------------------------------------------------------------------

		//サブディレクトリを含む検索でファイルリストを作成する
		Find ( SEARCH_CONDITION );

		//ファイル個数を書出
		DWORD nFile = m_vFilename.size();
		::WriteFile ( hWriteFile, & nFile, sizeof ( DWORD ), & numberOfBytesWritten, nullptr );

		//-------------------------------------------------------------------------
		//	ファイル名、ファイルサイズ(オフセット)を取得
		//-------------------------------------------------------------------------
#if 0
		WIN32_FIND_DATA findData;
		HANDLE hFind = FindFirstFile ( SEARCH_CONDITION, & findData );
		while ( T )
		{
			//次のファイルを取得
			if ( FindNextFile ( hFind, &findData ) )
			{
				//ディレクトリはとばす
				if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
					tstring str ( findData.cFileName );
					tostringstream toss;
					toss << _T("ディレクトリ: ") << str << _T(", ファイルサイズ: ") << findData.nFileSizeLow << std::endl;
//					OutputDebugString ( toss.str().c_str () );
					continue; 
				}

				//システムファイル(Thumbs.dbなど)はとばす
				if ( findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM )
				{
					tstring str ( findData.cFileName );
					tostringstream toss;
					toss << _T("システムファイル: ") << str << _T(", ファイルサイズ: ") << findData.nFileSizeLow << std::endl;
//					OutputDebugString ( toss.str().c_str () );
					continue; 
				}

				TCHAR fileName[MAX_PATH];		//ファイル名
				_tcscpy_s ( fileName, _T("archive/") );
				_tcscat_s ( fileName, findData.cFileName );
				fileSize = findData.nFileSizeLow;	//4Gbyteサイズ以上は扱わない
				
#if	1
				tostringstream toss;
				toss << fileName << _T(", オフセット: ") << fileTotalSize << _T(", ファイルサイズ: ") << fileSize << std::endl;
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
		FindClose ( hFind );
#endif // 0


		//@todo ヘッダの書き込みと読込の型の違いを修正



		//対象ファイルすべてに対してループ
		for ( ACV_H_SRC acvSrc : m_vFilename )
		{
			//アーカイブファイル(.dat)に書出
			DWORD nWrtn = 0;
			TCHAR fn [ MAX_PATH ];
			_tcscpy_s ( fn, MAX_PATH, acvSrc.fileName.c_str () );
			::WriteFile ( hWriteFile, fn, sizeof ( fn ), &nWrtn, nullptr );
			::WriteFile ( hWriteFile, & acvSrc.align.offset, sizeof ( DWORD ), &nWrtn, nullptr );
			::WriteFile ( hWriteFile, & acvSrc.align.fileSize, sizeof ( DWORD ), &nWrtn, nullptr );
		}



		//-------------------------------------------------------------------------
		//ファイル実データ書出
		//-------------------------------------------------------------------------
#if 0
		hFind = FindFirstFile ( SEARCH_CONDITION, &findData );
		while ( T )
		{
			//次のファイルを取得
			if ( FindNextFile ( hFind, &findData ) )
			{
				//ディレクトリはとばす
				if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				//システムファイル(Thumbs.dbなど)はとばす
				if ( findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }

				fileSize = findData.nFileSizeLow;	//4Gbyteサイズ以上は扱わない

				//ファイル読込
#if	0
				TCHAR fileName[MAX_PATH];		//ファイル名
				_tcscpy_s ( fileName, _T("archive/") );
				_tcscat_s ( fileName, fileData.cFileName );
				HANDLE hReadFile = CreateFile ( fileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
#endif	//0
				tstring fileName ( ARCHIVE_DIR_NAME );
				fileName.append ( findData.cFileName );
				HANDLE hReadFile = ::CreateFile ( fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );

				//ファイルハンドルからサイズ分読込
//				BYTE* buf = new BYTE [ fileSize ];
				unique_ptr < BYTE[] > buf = make_unique < BYTE[] > ( fileSize );
				DWORD numberOfBytesRead = 0;
				ReadFile ( hReadFile, buf.get (), fileSize, &numberOfBytesRead, nullptr );

				//ファイルにサイズ分書出
				DWORD numberOfBytesWritten = 0;
				WriteFile ( hWriteFile, buf.get (), fileSize, &numberOfBytesWritten, nullptr );
//				delete[] buf;

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
		FindClose ( hFind );
#endif // 0

		//対象ファイルすべてに対してループ
		for ( ACV_H_SRC acvSrc : m_vFilename )
		{
			//一時読込
			HANDLE hReadFile = ::CreateFile ( acvSrc.fileName.c_str (), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
			unique_ptr < BYTE[] > buf = make_unique < BYTE[] > ( acvSrc.align.fileSize );
			DWORD nRead = 0;
			::ReadFile ( hReadFile, buf.get (), acvSrc.align.fileSize, & nRead, nullptr );

			//アーカイブファイル(.dat)に書出
			DWORD nWrtn = 0;
			::WriteFile ( hWriteFile, buf.get (), acvSrc.align.fileSize, & nWrtn, nullptr );
		}

		CloseHandle ( hWriteFile );
	}


	//アーカイブファイル読込
	void Archiver::Open ()
	{
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

//		m_hFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		HANDLE hFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD erorr = GetLastError();

		//ファイル数を得る
		DWORD dwFileNum = 0;
		DWORD numberOfBytesRead = 0;
		bool bRet = ::ReadFile ( hFile, & dwFileNum, sizeof ( DWORD ), & numberOfBytesRead, nullptr );

		//ヘッダを個数分得る
#if 0
		if ( m_archiveHeader ) { return; }
		m_archiveHeader = new ARCHIVE_HEADER_SEARCH [ dwFileNum ];
#endif // 0
		unique_ptr < ACV_H_SRC [] > hAcv ( new ACV_H_SRC [ dwFileNum ] );

		for ( DWORD i = 0; i < dwFileNum; ++ i )
		{
			ARCHIVE_HEADER tempAcvHd;
			::ReadFile ( hFile, & tempAcvHd, sizeof ( ARCHIVE_HEADER ), & numberOfBytesRead, nullptr );
			hAcv [i].fileName.assign ( tempAcvHd.fileName );
			hAcv [i].align.offset = tempAcvHd.align.offset;
			hAcv [i].align.fileSize = tempAcvHd.align.fileSize;

			m_map.insert ( ARCHIVE_MAP::value_type ( hAcv [i].fileName, & (hAcv [i].align ) ) );
		}

		m_fileNum = dwFileNum;

		//ファイルマッピング
		//@info 名前を付けると複数起動時に同名のマッピングでアクセス違反になるので無名にする
//		m_hMap = CreateFileMapping ( m_hFile, nullptr, PAGE_READONLY, 0, 0, m_mapName );
		m_hMap = CreateFileMapping ( hFile, nullptr, PAGE_READONLY, 0, 0, nullptr );
		if ( m_hMap == nullptr )
		{
			////TRACE_F( _T("ファイルマッピングに失敗") );
			return;
		}
		m_pFile = ::MapViewOfFile ( m_hMap, FILE_MAP_READ, 0, 0, 0 );
	}




	//元のファイル名からアーカイブ内のファイルポインタを得る
	ACV_FL_USE Archiver::GetFilePointer ( LPCTSTR fileName )
	{
		ACV_FL_USE ret = { nullptr, 0 };
		
		//検索
		tstring str ( ARCHIVE_DIR_NAME );
		str.append ( fileName );
		if ( m_map.find ( str ) == m_map.end() ) 
		{
			TRACE_F ( _T("%s, アーカイブの中に対象のファイルが見つかりませんでした\n"), fileName );
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



	void Archiver::Find ( LPCTSTR path )
	{
		//ファイル情報
		WIN32_FIND_DATA findData;

		//引数のパスから最初のファイルを検索
		HANDLE hFind = ::FindFirstFile ( path, & findData );

		DWORD fileNum = 0;	//ファイル個数
		DWORD fileTotalSize = 0;	//総ファイルサイズ

		//列挙後、条件("*.*")を除きディレクトリ文字列にする
		TRACE_F ( _T ( "Find( %s )\n" ), path );
		tstring tstr_path ( path );
		tstring tstr_cond ( _T ( "*.*" ) );
		size_t nSize = tstr_path.find_last_of ( _T ( "\\" ) ) + 1;
		tstring tstr_dir = tstr_path.substr ( 0, tstr_path.length () - tstr_cond.length () );
		TRACE_F ( _T ( "dir = %s \n" ), tstr_dir );

		//以降のファイル
		do
		{
			//システムファイル(Thumbs.dbなど)はとばす
			if ( findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }

			//ディレクトリは再帰する
			if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) 
			{
				if ( _tcscmp ( _T ( "." ), findData.cFileName ) == 0 ) { continue; }
				if ( _tcscmp ( _T ( ".." ), findData.cFileName ) == 0 ) { continue; }

				tstring bsbs ( _T ( "\\" ) );
				tstring a = tstr_dir.substr ( 0, tstr_dir.length () - bsbs.length () );
				size_t i_dir = a.find_last_of ( _T ( "\\" ) ) + 1;
				tstring name = a.substr ( i_dir, a.length() - i_dir );
				if ( _tcscmp ( name.c_str (), findData.cFileName ) == 0 ){ continue; }
				TRACE_F ( _T ( "ディレクトリ\n" ), path );

				TCHAR subpath [ MAX_PATH ];
				_stprintf_s ( subpath, MAX_PATH, _T ( "%s%s\\*.*" ), tstr_dir.c_str (), findData.cFileName );
				Find ( subpath );
			}
			else
			{
				TCHAR filename [ MAX_PATH ];		//ファイル名
				_stprintf_s ( filename, MAX_PATH, _T("%s%s"), tstr_dir.c_str (), findData.cFileName );

				TRACE_F ( _T ( "filename = %s\n" ), filename );

				ACV_H_SRC acv;
				acv.fileName = filename;
				acv.align.fileSize = findData.nFileSizeLow;
				acv.align.offset = fileTotalSize;
				
				//保存
				m_vFilename.push_back ( acv );

				//ファイルのオフセット計算
				fileTotalSize += findData.nFileSizeLow;
			}
		} while ( FindNextFile ( hFind, & findData ) );

		::FindClose ( hFind );
	}


}	//namespace GAME


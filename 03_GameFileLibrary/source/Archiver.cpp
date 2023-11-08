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
		: m_hMap ( nullptr ), m_pFile ( nullptr )
		, m_current_offset ( 0 )
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
		if ( m_hMap ) { ::UnmapViewOfFile ( m_hMap ); m_hMap = nullptr; }
	}


	//アーカイブファイル作成
	void Archiver::Make ()
	{
		//カレントディレクトリの取得
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );
//		TRACE_F ( _T ( "Make(): %s\n" ), path );

		//バイナリで書出用ファイルを開く
		HANDLE hWriteFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD numberOfBytesWritten = 0;
		
		//-------------------------------------------------------------------------
		//	対象ファイルリストと個数
		//-------------------------------------------------------------------------
		//サブディレクトリを含む検索でファイルリストを作成する
		//@info ! 再帰のため、現在オフセット位置は外側に置く
		m_current_offset = 0;
		Find ( SEARCH_CONDITION );

		//ファイル個数を書出
		DWORD nFile = m_vFilename.size();
		::WriteFile ( hWriteFile, & nFile, sizeof ( DWORD ), & numberOfBytesWritten, nullptr );

		//-------------------------------------------------------------------------
		//	ヘッダの作成
		//-------------------------------------------------------------------------
		//	ファイル名、ファイルサイズ(オフセット)を取得

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

//			TRACE_F ( _T ( "%s: offset = %d, size = %d\n" ), fn, acvSrc.align.offset, acvSrc.align.fileSize );
		}

		//-------------------------------------------------------------------------
		//ファイル実データ書出
		//-------------------------------------------------------------------------

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

			::CloseHandle ( hReadFile );
		}

		::CloseHandle ( hWriteFile );
	}


	//アーカイブファイル読込
	void Archiver::Open ()
	{
		//カレントディレクトリの取得
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );
//		TRACE_F ( _T ( "Open(): %s\n" ), path );

		HANDLE hFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD error = ::GetLastError();
		if ( ERROR_SUCCESS != error )
		{
			TRACE_F ( _T ( "Error : %d\n" ), error );
			return;
		}

		//ファイル数を得る
		DWORD dwFileNum = 0;
		DWORD numberOfBytesRead = 0;
		bool bRet = ::ReadFile ( hFile, & dwFileNum, sizeof ( DWORD ), & numberOfBytesRead, nullptr );

		//ヘッダを個数分得る
		unique_ptr < ACV_H_SRC [] > hAcv ( new ACV_H_SRC [ dwFileNum ] );

		for ( DWORD i = 0; i < dwFileNum; ++ i )
		{
			ARCHIVE_HEADER tempAcvHd;
			::ReadFile ( hFile, & tempAcvHd, sizeof ( ARCHIVE_HEADER ), & numberOfBytesRead, nullptr );
			hAcv [i].fileName.assign ( tempAcvHd.fileName );
			hAcv [i].align.offset = tempAcvHd.align.offset;
			hAcv [i].align.fileSize = tempAcvHd.align.fileSize;

//			TRACE_F ( _T ( "%s: offset = %d, size = %d\n" ), hAcv [ i ].fileName, hAcv [ i ].align.offset, hAcv[i].align.fileSize );
			m_map.insert ( ARCHIVE_MAP::value_type ( hAcv [i].fileName, hAcv [i].align ) );
		}

		//ファイルマッピング
		//@info 名前を付けると複数起動時に同名のマッピングでアクセス違反になるので無名にする
		//	ファイルマッピングは別プロセスで共通メモリにアクセスする手法
//		m_hMap = CreateFileMapping ( m_hFile, nullptr, PAGE_READONLY, 0, 0, m_mapName );
		m_hMap = ::CreateFileMapping ( hFile, nullptr, PAGE_READONLY, 0, 0, nullptr );
		if ( m_hMap == nullptr )
		{
			////TRACE_F( _T("ファイルマッピングに失敗") );
			return;
		}
		m_pFile = ::MapViewOfFile ( m_hMap, FILE_MAP_READ, 0, 0, 0 );

		::CloseHandle ( hFile );
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
		ARCHIVE_ALIGN align = m_map [ str ];


		//データ開始位置
//		size_t nFile = m_vFilename.size ();
		//--------------------------------------------------------------------------------
		//@info ! ReleaseモードではMake()を通らないため、m_vFileName.size()に個数が記録されない
		//--------------------------------------------------------------------------------
		size_t nFile = m_map.size ();
		DWORD startData = sizeof ( DWORD ) + sizeof ( ARCHIVE_HEADER ) * nFile;

		//(LPVOID)では位置計算ができないので(LPBYTE)にする
//		ret.filePointer = (LPVOID)m_pFile + startData + align.offset;
		ret.filePointer = (LPBYTE)m_pFile + startData + align.offset;
		ret.fileSize = align.fileSize;

		return ret;
	}


	void Archiver::Find ( LPCTSTR path )
	{
		//ファイル情報
		WIN32_FIND_DATA findData;

		//引数のパスから最初のファイルを検索
		HANDLE hFind = ::FindFirstFile ( path, & findData );

		//列挙後、条件("*.*")を除きディレクトリ文字列にする
//		TRACE_F ( _T ( "Find( %s )\n" ), path );
		tstring tstr_path ( path );
		tstring tstr_cond ( _T ( "*.*" ) );
		size_t nSize = tstr_path.find_last_of ( _T ( "\\" ) ) + 1;
		tstring tstr_dir = tstr_path.substr ( 0, tstr_path.length () - tstr_cond.length () );
//		TRACE_F ( _T ( "dir = %s \n" ), tstr_dir );

		//@info 現在オフセット位置は関数の外側に置く
//		DWORD	all_offset = 0;

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
//				TRACE_F ( _T ( "ディレクトリ\n" ), path );

				TCHAR subpath [ MAX_PATH ];
				_stprintf_s ( subpath, MAX_PATH, _T ( "%s%s\\*.*" ), tstr_dir.c_str (), findData.cFileName );
				Find ( subpath );
			}
			else
			{
				TCHAR filename [ MAX_PATH ];		//ファイル名
				_stprintf_s ( filename, MAX_PATH, _T("%s%s"), tstr_dir.c_str (), findData.cFileName );

//				TRACE_F ( _T ( "filename = %s\n" ), filename );

				ACV_H_SRC acv;
				acv.fileName = filename;
				acv.align.fileSize = findData.nFileSizeLow;
//				acv.align.offset = all_offset;
				acv.align.offset = m_current_offset;

				//保存
				m_vFilename.push_back ( acv );

				//ファイルのオフセット計算
				m_current_offset += findData.nFileSizeLow;
			}
		} while ( FindNextFile ( hFind, & findData ) );

		::FindClose ( hFind );
	}


}	//namespace GAME


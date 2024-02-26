//=================================================================================================
//
// SoundArchiver ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "SoundArchiver.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//@info 読み込むディレクトリをSEとBGMに分け、SEはバッファを複数、BGMはバッファを単一で持つ
	//IDはSE，BGM共通で監理, 呼び出しからのID指定は別enumで行う

	//------------------------------------------
	//	定数
	//------------------------------------------
	//作成するサウンドアーカイブファイル名
	LPCTSTR SoundArchiver::m_archiveFileName = _T("sound.dat");


	//アーカイブ作成のため読み込むディレクトリ名
	LPCTSTR SoundArchiver::m_archiveDirName = _T ( "Sound/" );

	//アーカイブ作成のため読み込むファイル名条件
	LPCTSTR SoundArchiver::m_searchCondition = _T ( "Sound/*.*" );


	//SE アーカイブ作成のため読み込むディレクトリ名
	LPCTSTR SoundArchiver::m_archiveDirName_SE = _T ( "SE/" );

	//SE アーカイブ作成のため読み込むファイル名条件
	LPCTSTR SoundArchiver::m_searchCondition_SE = _T ( "SE/*.*" );

	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	SoundArchiver::P_SoundArchiver		SoundArchiver::m_inst;

	//------------------------------------------
	//コンストラクタ
	SoundArchiver::SoundArchiver ()
//		: m_hFile ( nullptr ) //, m_count ( 0 )
		: m_nBGM ( 0 ), m_nSE ( 0 )
	{
	}

	//デストラクタ
	SoundArchiver::~SoundArchiver ()
	{
	}

	//作成
	void SoundArchiver::Make ()
	{
		//DBGOUT_FL_F ( _T ("SoundArchiver::Make()\n") );

		//カレントディレクトリの取得
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//バイナリで書出用ファイルを開く
		HANDLE hWriteFile = CreateFile ( m_archiveFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );


		//ファイル個数を列挙
		m_nBGM = CountFileNum ( m_searchCondition );
		m_nSE = CountFileNum ( m_searchCondition_SE );

		//各ファイル個数を書出
		::WriteFile ( hWriteFile, & m_nBGM, sizeof ( DWORD ), nullptr, nullptr );
		::WriteFile ( hWriteFile, & m_nSE, sizeof ( DWORD ), nullptr, nullptr );



#if 0
		//ファイル列挙
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( m_searchCondition, &fileData );	//ディレクトリ指定("sound/*.*")

		//個数を数え上げ
		while ( T )
		{
			//次ファイルを取得
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//ディレクトリは飛ばす
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//システムファイル(Thumbs.dbなど)は飛ばす
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				++ m_count;
			}
			//次ファイルが取得できなかったとき
			else
			{
				break;
			}
		}
		FindClose ( hFileList );
#endif // 0

#if 0
		//ファイル列挙
//		m_count = CountFileNum ( m_searchCondition );
		UINT count = CountFileNum ( m_searchCondition );

		//ファイル個数を記録
		::WriteFile ( hWriteFile, & count, sizeof ( DWORD ), nullptr, nullptr );


		//再列挙
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( m_searchCondition, &fileData );	//ディレクトリ指定("sound/*.*")

		//書出
		while ( T )
		{
			//次ファイルを取得
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//ディレクトリは飛ばす
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//システムファイル(Thumbs.dbなど)は飛ばす
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				//DBGOUT_FL_F ( _T ( "Filename=\"%s\"\n" ), fileData.cFileName );

				//ファイルサイズ
				DWORD fileSize = fileData.nFileSizeLow;	//4Gbyte未満のみ
				DWORD numberOfBytesWritten = 0;

				::WriteFile ( hWriteFile, &fileSize, sizeof ( DWORD ), &numberOfBytesWritten, nullptr );

				//ディレクトリ指定
				tstring filename ( m_archiveDirName );
				filename.append ( fileData.cFileName );

				//ファイル読込
				HANDLE hReadFile = CreateFile ( filename.c_str(), GENERIC_READ, 0, nullptr, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
				
				std::unique_ptr < BYTE[] > buf = std::make_unique < BYTE[] > ( fileSize );
				DWORD numberOfByteRead = 0;
				::ReadFile ( hReadFile, buf.get(), fileSize, &numberOfByteRead, nullptr );

				::CloseHandle ( hReadFile );

				//アーカイブにサイズ分書出
				::WriteFile ( hWriteFile, buf.get(), fileSize, &numberOfBytesWritten, nullptr );
				
//				++m_count;
			}
			//次ファイルが取得できなかったとき
			else 
			{
				break;
			}
		}
#endif // 0

		///BGM
		_Make ( hWriteFile, m_archiveDirName, m_searchCondition );

		//SE
		_Make ( hWriteFile, m_archiveDirName_SE, m_searchCondition_SE );


		//終了
		CloseHandle ( hWriteFile );
	}

	void SoundArchiver::_Make ( HANDLE hWriteFile, LPCTSTR dirname, LPCTSTR condition )
	{
		//再列挙
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( condition, &fileData );	//ディレクトリ指定("sound/*.*")

		//書出
		while ( T )
		{
			//次ファイルを取得
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//ディレクトリは飛ばす
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//システムファイル(Thumbs.dbなど)は飛ばす
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				//DBGOUT_FL_F ( _T ( "Filename=\"%s\"\n" ), fileData.cFileName );

				//ファイルサイズ書込
				DWORD fileSize = fileData.nFileSizeLow;	//4Gbyte未満のみ
				DWORD numberOfBytesWritten = 0;
				::WriteFile ( hWriteFile, &fileSize, sizeof ( DWORD ), &numberOfBytesWritten, nullptr );

				//バッファにファイルデータ読込
				tstring filename ( dirname );			
				filename.append ( fileData.cFileName );	//ファイルパス作成
				HANDLE hReadFile = CreateFile ( filename.c_str(), GENERIC_READ, 0, nullptr, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
				
				std::unique_ptr < BYTE[] > buf = std::make_unique < BYTE[] > ( fileSize );
				DWORD numberOfByteRead = 0;
				::ReadFile ( hReadFile, buf.get(), fileSize, &numberOfByteRead, nullptr );

				::CloseHandle ( hReadFile );

				//アーカイブにサイズ分書出
				::WriteFile ( hWriteFile, buf.get(), fileSize, &numberOfBytesWritten, nullptr );
			}
			//次ファイルが取得できなかったとき
			else 
			{
				break;
			}
		}
		//終了
		FindClose ( hFileList );
	}


	//条件のファイル数え上げ
	UINT SoundArchiver::CountFileNum ( LPCTSTR condition )
	{
		UINT ret = 0;

		//ファイル列挙( OpenHandle )
		WIN32_FIND_DATA		fileData;
		//ディレクトリ指定("sound/*.*")
		HANDLE hFileList = ::FindFirstFile ( condition, & fileData );

		//個数を数え上げ
		while ( T )
		{
			//次ファイルを取得
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//ディレクトリは飛ばす
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//システムファイル(Thumbs.dbなど)は飛ばす
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				++ ret;
			}
			//次ファイルが取得できなかったとき
			else
			{
				break;
			}
		}
		::FindClose ( hFileList );

		return ret;
	}


	//開
	void SoundArchiver::Open ()
	{
		//DBGOUT_FL_F ( _T ( "サウンドアーカイバ読込開始\n" ) );
		//ファイル読込
		HANDLE hFile = CreateFile ( m_archiveFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, nullptr );

//		TCHAR cur [ 255 ] = _T("filepath");
//		::GetCurrentDirectory ( 255, cur );

		//ファイル個数合計を読込
		::ReadFile ( hFile, & m_nBGM, sizeof ( DWORD ), nullptr, nullptr );
		::ReadFile ( hFile, & m_nSE, sizeof ( DWORD ), nullptr, nullptr );
		UINT count = m_nBGM + m_nSE;

		//各ファイル読込
		//DBGOUT_FL_F ( _T ( "count = %d\n" ), m_count );
		for ( UINT i = 0; i < count; ++i )
		{
			DWORD numberOfByteRead = 0;
			DWORD fileSize = 0;
			::ReadFile ( hFile, &fileSize, sizeof ( DWORD ), &numberOfByteRead, nullptr );
			std::unique_ptr < BYTE [] > buf = std::make_unique < BYTE [] > ( fileSize );
			::ReadFile ( hFile, buf.get(), fileSize, &numberOfByteRead, nullptr );
			
			//サウンドバッファを作成 (SEは複数再生のためバッファ数を指定)
			//BGM
			if ( i < m_nBGM )
			{
				DxSound::instance ()->LoadWaveFromMemEx ( 1, (HPSTR)buf.get(), fileSize, m_volume );
			}
			//SE
			else
			{
				DxSound::instance ()->LoadWaveFromMemEx ( 8, (HPSTR)buf.get(), fileSize, m_volume );
			}
		}

		//閉じる
		CloseHandle ( hFile );
	}

	//------------------------------------------------------------------
	//再生
	void SoundArchiver::Play_BGM ( UINT BGM_ID )
	{
		DxSound::instance()->Play ( BGM_ID );
	}

	//ループ再生
	void SoundArchiver::Play_Loop_BGM ( UINT BGM_ID )
	{
		DxSound::instance()->PlayLoop ( BGM_ID );
	}

	//停止
	void SoundArchiver::Stop_BGM ( UINT BGM_ID )
	{
		DxSound::instance()->Stop ( BGM_ID );
	}

	//再生
	void SoundArchiver::Play_SE ( UINT SE_ID )
	{
		//@info リリースモード時にMake()を通らないため、m_nBGMはファイルから読み込む
		//BGMの数だけオフセットして指定
		DxSound::instance()->Play ( m_nBGM + SE_ID );
	}



}	//namespace GAME


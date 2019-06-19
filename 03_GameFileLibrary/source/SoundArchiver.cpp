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

	//------------------------------------------
	//	定数
	//------------------------------------------
	//アーカイブファイル名
	const TCHAR SoundArchiver::m_archiveFileName[] = TEXT("sound.dat");

	//アーカイブ作成のため読み込むディレクトリ名
	const TCHAR SoundArchiver::m_archiveDirName[] = TEXT("sound/");

	//アーカイブ作成のため読み込むファイル名条件
	const TCHAR SoundArchiver::m_searchCondition[] = TEXT("sound/*.*");

	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	SoundArchiver::P_SoundArchiver		SoundArchiver::m_inst;

	//------------------------------------------
	//コンストラクタ
	SoundArchiver::SoundArchiver () : m_hFile ( nullptr ), m_count ( 0 )
	{
	}

	//デストラクタ
	SoundArchiver::~SoundArchiver ()
	{
	}

	//作成
	void SoundArchiver::Make ()
	{
		//カレントディレクトリの取得
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//バイナリで書出用ファイルを開く
		HANDLE hWriteFile = CreateFile ( m_archiveFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );

		//ファイル列挙
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( m_searchCondition, &fileData );	//ディレクトリ指定("sound/*.*")

		while ( 1 )
		{
			//次ファイルを取得
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//ディレクトリは飛ばす
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//システムファイル(Thumbs.dbなど)は飛ばす
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				//ファイルサイズ
				DWORD fileSize = fileData.nFileSizeLow;	//4Gbyte未満のみ
				DWORD numberOfBytesWritten = 0;

				::WriteFile ( hWriteFile, &fileSize, sizeof ( DWORD ), &numberOfBytesWritten, nullptr );

				//ディレクトリ指定
				LPTSTR filename = new TCHAR [ sizeof ( m_archiveDirName ) + sizeof ( fileData.cFileName ) ];
				::lstrcpy ( filename, m_archiveDirName );
				::lstrcat ( filename, fileData.cFileName );

				//ファイル読込
				HANDLE hReadFile = CreateFile ( filename, GENERIC_READ, 0, nullptr, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
				
				BYTE* buf = new BYTE [ fileSize ];
				DWORD numberOfByteRead = 0;
				::ReadFile ( hReadFile, buf, fileSize, &numberOfByteRead, nullptr );

				::CloseHandle ( hReadFile );

				//ファイルにサイズ分書出
				::WriteFile ( hWriteFile, buf, fileSize, &numberOfBytesWritten, nullptr );
				
				delete[] buf;
				delete[] filename;
				
				++m_count;
			}
			//次ファイルが取得できなかったとき
			else 
			{
				break;
			}
		}

		//終了
		FindClose ( hFileList );
		CloseHandle ( hWriteFile );
	}

	//開
	void SoundArchiver::Open ()
	{
		//ファイル読込
		m_hFile = CreateFile ( m_archiveFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, nullptr );

		for ( UINT i = 0; i < m_count; ++i )
		{
			DWORD numberOfByteRead = 0;
			DWORD fileSize = 0;
			::ReadFile ( m_hFile, &fileSize, sizeof ( DWORD ), &numberOfByteRead, nullptr );
			BYTE* buf = new BYTE [ fileSize ];
			::ReadFile ( m_hFile, buf, fileSize, &numberOfByteRead, nullptr );

			DxSound::instance ()->LoadWaveFromMem_Renew ( (HPSTR)buf, fileSize );

			delete[] buf;
		}
	}

	//閉
	void SoundArchiver::Close ()
	{
		if ( m_hFile ) { CloseHandle ( m_hFile ); m_hFile = nullptr; }
	}

	//再生
	void SoundArchiver::Play ( UINT id )
	{
		DxSound::instance()->Play_Renew ( id );
	}

	//ループ再生
	void SoundArchiver::PlayLoop ( UINT id )
	{
		DxSound::instance()->PlayLoop ( id );
	}

	//停止
	void SoundArchiver::Stop ( UINT id )
	{
		DxSound::instance()->Stop ( id );
	}



}	//namespace GAME


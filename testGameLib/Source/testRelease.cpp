//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TestRelease.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Test::Test ()
	{
		m_grp = std::make_shared < GrpAcv > ();
		m_grp->AddTexture ( _T ( "test_title.png" ) );
		AddpTask ( m_grp );
//		GRPLST_INSERT_MAIN ( m_grp );

		m_grpFromFile = std::make_shared < GrpFl > ();
		m_grpFromFile->AddTexture ( _T ( "test_title.png" ) );
		AddpTask ( m_grpFromFile );
//		GRPLST_INSERT_MAIN ( m_grpFromFile );
	}

	Test::~Test ()
	{
	}

	void Test::Load ()
	{
//		SOUND->Play_Loop_BGM ( 0 );

		LPCTSTR filename = _T ( "test_title.png" );

#if 0
		//アーカイバテスト
		ACV_FL_USE acv_fl = Archiver::instance ()->GetFilePointer ( filename );

		TX tx;
		DX3D->CreateTextureFromMem ( acv_fl.filePointer, acv_fl.fileSize, & tx );

		P_TxBs pTxBs = std::make_shared < TxBs > ();
		pTxBs->SetTexture ( tx );
		P_GrpApTx pGrpApTx = std::make_shared < GrpApTx > ();
		pGrpApTx->SetpTexture ( pTxBs );
		AddpTask ( pGrpApTx );
		GRPLST_INSERT_MAIN ( pGrpApTx );
#endif // 0


#if 0
		//ファイル情報
		WIN32_FIND_DATA findData;

		//引数のパスから最初のファイルを検索
		HANDLE hFind = ::FindFirstFile ( filename, & findData );
		::FindClose ( hFind );
		DWORD filesize = findData.nFileSizeLow;

		//ファイルオープン
		HANDLE hReadFile = ::CreateFile ( filename, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		std::unique_ptr < BYTE [] > buf = std::make_unique < BYTE [] > ( filesize );
		DWORD nRead = 0;
		::ReadFile ( hReadFile, buf.get (), filesize, & nRead, nullptr );
		::CloseHandle ( hReadFile );


		//メモリからテクスチャ作成
		TX lpTexture;
		DX3D->CreateTextureFromMem ( buf.get (), filesize, & lpTexture );

		P_TxBs pTxBs = std::make_shared < TxBs > ();
		pTxBs->SetTexture ( lpTexture );
		P_GrpApTx pGrpApTx = std::make_shared < GrpApTx > ();
		pGrpApTx->SetpTexture ( pTxBs );
		AddpTask ( pGrpApTx );
		GRPLST_INSERT_MAIN ( pGrpApTx );
#endif // 0

#if 0
		//マッピングテスト
		//ファイル情報
		WIN32_FIND_DATA findData;

		//引数のパスから最初のファイルを検索
		HANDLE hFind = ::FindFirstFile ( filename, & findData );
		::FindClose ( hFind );
		DWORD filesize = findData.nFileSizeLow;

		//ファイルオープン
		HANDLE hReadFile = ::CreateFile ( filename, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		std::unique_ptr < BYTE [] > buf = std::make_unique < BYTE [] > ( filesize );
		DWORD nRead = 0;
		::ReadFile ( hReadFile, buf.get (), filesize, & nRead, nullptr );

		//ファイルマッピング
		HANDLE hMap = ::CreateFileMapping ( hReadFile, nullptr, PAGE_READONLY, 0, 0, nullptr );
		LPVOID pStartMap = ::MapViewOfFile ( hMap, FILE_MAP_READ, 0, 0, 0 );

		//ファイルクローズ
		::CloseHandle ( hReadFile );


		//メモリからテクスチャ作成
		TX lpTexture;
		DX3D->CreateTextureFromMem ( pStartMap, filesize, & lpTexture );

		P_TxBs pTxBs = std::make_shared < TxBs > ();
		pTxBs->SetTexture ( lpTexture );
		P_GrpApTx pGrpApTx = std::make_shared < GrpApTx > ();
		pGrpApTx->SetpTexture ( pTxBs );
		AddpTask ( pGrpApTx );
		GRPLST_INSERT_MAIN ( pGrpApTx );
#endif // 0

		//アーカイブファイルテスト
		LPCTSTR ARCHIVE_FILE_NAME = _T ( "archive.dat" );
		HANDLE hFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD error = ::GetLastError ();
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
		std::unique_ptr < ACV_H_SRC [] > hAcv ( new ACV_H_SRC [ dwFileNum ] );

		for ( DWORD i = 0; i < dwFileNum; ++ i )
		{
			ARCHIVE_HEADER tempAcvHd;
			::ReadFile ( hFile, & tempAcvHd, sizeof ( ARCHIVE_HEADER ), & numberOfBytesRead, nullptr );
			hAcv [ i ].fileName.assign ( tempAcvHd.fileName );
			hAcv [ i ].align.offset = tempAcvHd.align.offset;
			hAcv [ i ].align.fileSize = tempAcvHd.align.fileSize;

//			TRACE_F ( _T ( "%s: offset = %d, size = %d\n" ), hAcv [ i ].fileName, hAcv [ i ].align.offset, hAcv [ i ].align.fileSize );
//			m_map.insert ( ARCHIVE_MAP::value_type ( hAcv [ i ].fileName, hAcv [ i ].align ) );
		}

		//ファイルマッピング
		HANDLE hMap = ::CreateFileMapping ( hFile, nullptr, PAGE_READONLY, 0, 0, nullptr );
		LPVOID pStartMap = ::MapViewOfFile ( hMap, FILE_MAP_READ, 0, 0, 0 );

		//ファイルクローズ
		::CloseHandle ( hFile );

		ACV_FL_USE acv_fl = Archiver::instance ()->GetFilePointer ( filename );



		//データ開始位置
		size_t nFile = dwFileNum;
		DWORD startData = sizeof ( DWORD ) + sizeof ( ARCHIVE_HEADER ) * nFile;

		DWORD offset = hAcv [ 3 ].align.offset;
		DWORD filesize = hAcv [ 3 ].align.fileSize;
		LPVOID pointer = (LPBYTE)pStartMap + startData + offset;
		TRACE_F ( _T ( "%d,%d\n" ), acv_fl.filePointer, acv_fl.fileSize );
		TRACE_F ( _T ( "%d,%d\n" ), pointer, filesize );

		//メモリからテクスチャ作成
		TX lpTexture;
//		DX3D->CreateTextureFromMem ( pointer, filesize, & lpTexture );
		DX3D->CreateTextureFromMem ( acv_fl.filePointer, acv_fl.fileSize, & lpTexture );

		P_TxBs pTxBs = std::make_shared < TxBs > ();
		pTxBs->SetTexture ( lpTexture );
		P_GrpApTx pGrpApTx = std::make_shared < GrpApTx > ();
		pGrpApTx->SetpTexture ( pTxBs );
		AddpTask ( pGrpApTx );
		GRPLST_INSERT_MAIN ( pGrpApTx );


		TASK_VEC::Load ();
	}


}	//namespace GAME


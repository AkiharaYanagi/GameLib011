//=================================================================================================
//
// ゲームテクスチャ	実装
//
//=================================================================================================


//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameTexture.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------------------------------------------------------------------
	//	GameTextureBase
	//-------------------------------------------------------------------------------------------------
	GameTextureBase::GameTextureBase () : 
		m_lpTexture ( nullptr ), m_color ( 0xffffffff ), m_textureIndex ( 0 )
	{
	}

	GameTextureBase::~GameTextureBase ()
	{
	}


	//-------------------------------------------------------------------------------------------------
	//	GameTextureFromFile
	//		直接ファイルから名前を指定してテクスチャを作成し管理する
	//-------------------------------------------------------------------------------------------------
	GameTextureFromFile::GameTextureFromFile () : m_lpTexture ( nullptr ), m_strFilename ( _T("") )
	{
	}

	GameTextureFromFile::~GameTextureFromFile ()
	{
		Rele ();
	}

	void GameTextureFromFile::Load ()
	{
		//ファイル名の指定が無いときは何もしない
		if ( m_strFilename.compare ( _T("") ) == 0 ) { return; }

		TCHAR curDir [ MAX_PATH ];
		::GetCurrentDirectory( MAX_PATH, curDir );
		////DebugOutTrace::instance()->DebugOutf ( curDir );
		////DebugOutTrace::instance()->DebugOutf ( _T(": %s : ") , m_strFilename.c_str() );

		//ファイル読込
		HRESULT hr = D3DXCreateTextureFromFile ( Dx3D::instance ()->GetDevice(), m_strFilename.c_str(), &m_lpTexture );
		if ( FAILED ( hr ) ) { DXTRACE ( hr, TEXT("テクスチャ読込の失敗") ); }

		//テクスチャの設定
		GameTextureBase::SetTexture ( m_lpTexture );
	}

	void GameTextureFromFile::Rele ()
	{
		RELEASE ( m_lpTexture );
	}

	void GameTextureFromFile::Reset ()
	{
		Rele ();
		Load ();
	}


	//-------------------------------------------------------------------------------------------------
	//	GameTextureFromArchive
	//		archive.dat内のファイル名を指定してテクスチャを作成し管理する
	//		Debugモード時にはarchiveディレクトリ内のファイルを指定する
	//-------------------------------------------------------------------------------------------------
	GameTextureFromArchive::GameTextureFromArchive () :  m_lpTexture ( nullptr ), m_strFileName ( _T("") )
	{
	}

	GameTextureFromArchive::~GameTextureFromArchive ()
	{
		Rele ();
	}

	void GameTextureFromArchive::Load ()
	{
		//ファイル名の指定が無いときは何もしない
		if ( m_strFileName.compare ( _T("") ) == 0 ) { return; }

		//アーカイブからファイルを取得
		ARCHIVE_FILE_USE file = Archiver::instance()->GetFilePointer ( m_strFileName.c_str() );
		if ( file.filePointer == nullptr )
		{
			////DebugOutTrace::instance()->DebugOutf ( TEXT("アーカイブにファイルが見つかりませんでした\n") );
			return;
		}

		TCHAR curDir [ MAX_PATH ];
		::GetCurrentDirectory( MAX_PATH, curDir );
//		TRACE->DebugOutf ( curDir );
		////DebugOutTrace::instance()->DebugOutf ( _T(": %s : ") , m_strFileName.c_str() );

		//メモリからテクスチャの作成
#if 0
		HRESULT hr = D3DXCreateTextureFromFileInMemory ( Dx3D::instance ()->GetDevice(), file.filePointer, file.fileSize, & m_lpTexture );
		if ( FAILED ( hr ) )
		{ 
			DXTRACE ( hr, TEXT("アーカイバ利用：テクスチャ読込の失敗") ); 
			return;
		}
#endif // 0
		DX3D->CreateTextureFromMem ( file.filePointer, file.fileSize, & m_lpTexture );

		TRACE_F ( m_strFileName.c_str() );
		TRACE_F ( _T(" : テクスチャ作成　成功\n") );

		//テクスチャの設定
		GameTextureBase::SetTexture ( m_lpTexture );
	}

	void GameTextureFromArchive::Rele ()
	{
		RELEASE ( m_lpTexture );
	}

	void GameTextureFromArchive::Reset ()
	{
		Rele ();
		Load ();
	}


	//-------------------------------------------------------------------------------------------------
	//	GameTextureFromMemory
	//		アーカイブ等のメモリ上からテクスチャを作成し管理する
	//-------------------------------------------------------------------------------------------------
	GameTextureFromMemory::GameTextureFromMemory ( LPCVOID pSrcData, UINT SrcDataSize ) :  m_lpTexture ( nullptr )
	{
		//メモリ上のデータからテクスチャに変換
		HRESULT hr = D3DXCreateTextureFromFileInMemory ( Dx3D::instance ()->GetDevice(), pSrcData, SrcDataSize, &m_lpTexture );
		if ( FAILED ( hr ) ) { DXTRACE ( hr, TEXT("スクリプトアーカイバ利用：テクスチャ読込の失敗") ); }

		//テクスチャの設定
		GameTextureBase::SetTexture ( m_lpTexture );
	}

	GameTextureFromMemory::~GameTextureFromMemory ()
	{
		Rele ();
	}

	void GameTextureFromMemory::Load ()
	{
	}

	void GameTextureFromMemory::Rele ()
	{
		RELEASE ( m_lpTexture );
	}

	void GameTextureFromMemory::Reset ()
	{
		Rele ();
		Load ();
	}


}	//namespace GAME


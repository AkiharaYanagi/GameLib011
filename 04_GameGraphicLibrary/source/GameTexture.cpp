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
		m_lpTexture ( nullptr ), m_textureIndex ( 0 )
	{
	}

	GameTextureBase::~GameTextureBase ()
	{
	}

	USIZE GameTextureBase::GetSize () const
	{
		USIZE ret = { 0, 0 };

		if ( m_lpTexture )
		{
			D3DSURFACE_DESC dc;
			m_lpTexture->GetLevelDesc ( 0, & dc );
			ret.w = dc.Width;
			ret.h = dc.Height;
		}
		return ret;
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
			////TRACE_F ( TEXT("アーカイブにファイルが見つかりませんでした\n") );
			return;
		}

		DX3D->CreateTextureFromMem ( file.filePointer, file.fileSize, & m_lpTexture );

		TRACE_F ( _T("%s : テクスチャ作成　成功\n") , m_strFileName.c_str());

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


	//-------------------------------------------------------------------------------------------------
	//ゲームテクスチャ　フロムストリング
	//		文字列から生成されるゲームテクスチャ
	//-------------------------------------------------------------------------------------------------
	TxStr::GameTextureFromString ()
		: m_fontSize ( 40 ), m_penSize ( 1 )
		, m_quality ( 2 )
		, m_fillColor ( 0xff8080fful ), m_edgeColor ( 0x80fffffful )
		, m_fontName ( _T ( "MSゴシック" ) )
	{
	}

	TxStr::~GameTextureFromString ()
	{
	}

	void TxStr::Load ()
	{
		//文字列からテクスチャを作成
		OLF->SetParam ( m_fontSize, m_penSize, m_quality );
		OLF->SetFontFace ( m_fontName );
		TX tx = OLF_MAKE_STRTX ( m_str.c_str (), m_fillColor, m_edgeColor );
		TxBs::SetTexture ( tx );
	}

	void TxStr::Rele ()
	{
		RELEASE ( GetTexture () );
	}

	void TxStr::Reset ()
	{
		Rele ();
		Load ();
	}

	void TxStr::SetStr ( LPCTSTR str )
	{
		m_str.assign ( str );
	}

	void TxStr::SetParam ( int fontSize, int penSize, int quolity )
	{
		m_fontSize = fontSize;
		m_penSize = penSize;
		m_quality = quolity;
	}

	void TxStr::SetFontFace ( LPCTSTR fontname )
	{
		_tcscpy_s ( m_fontName, fontname );
	}

	void TxStr::SetColor ( DWORD fill, DWORD edge )
	{
		m_fillColor = fill;
		m_edgeColor = edge;
	}


}	//namespace GAME


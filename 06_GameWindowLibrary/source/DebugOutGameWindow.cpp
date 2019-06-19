//=================================================================================================
//
// ゲーム画面へのデバッグテキスト表示
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugOutGameWindow.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//static実体
	unique_ptr < DebugOutGameWindow > DebugOutGameWindow::m_inst = nullptr;

	//コンストラクタ
	DebugOutGameWindow::DebugOutGameWindow ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_texture[i] = nullptr;
			m_tstr[i] = _T("");
		}
	}
 
	//デストラクタ
	DebugOutGameWindow::~DebugOutGameWindow ()
	{
		Rele ();
	}
	
	//インスタンス生成
	void DebugOutGameWindow::Create ()
	{
		assert ( ! m_inst );		//既に存在していたらassert
		m_inst = unique_ptr < DebugOutGameWindow > ( new DebugOutGameWindow () );
	}


	//読込
	void DebugOutGameWindow::Load ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_vertex[i].Load ();		//頂点バッファの作成
		}

//		m_tstr.assign ( TEXT("DebugOutGameWindow::Init _  ()") );
//		GameText::instance()->MakeStrTexture ( m_tstr, m_texture, m_vertex );
	}

	void DebugOutGameWindow::Rele ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}
	}

	void DebugOutGameWindow::Reset ( LPDIRECT3DDEVICE9 d3dDevice )
	{
		Rele ();
		Load ();
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			GameText::instance()->MakeStrTexture ( m_tstr[i], m_texture[i], m_vertex[i] );
		}
	}

	void DebugOutGameWindow::Move ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_vertex[i].ApplyPos ();
			m_vertex[i].SetVertexBuffer ();
		}
	}

	void DebugOutGameWindow::DrawVertex ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			//文字列が空なら何もしないで返す
			if ( ! m_tstr[i].compare ( TEXT("") ) ) { continue; }

			//描画
			m_vertex[i].DrawVertex ( m_texture[i] );
		}
	}


	//文字列設定
	void DebugOutGameWindow::SetStr ( UINT index, LPCTSTR lpctstr )
	{
		//現在の文字列と比較して異なる場合新たにテクスチャを作成
		if ( m_tstr[index].compare ( lpctstr ) )
		{
			m_tstr[index].assign ( lpctstr );
			GameText::instance()->MakeStrTexture ( m_tstr[index], m_texture[index], m_vertex[index] );
		}
	}

	void DebugOutGameWindow::SetStr ( UINT index, tstring& tstr )
	{
		//現在の文字列と比較して異なる場合新たにテクスチャを作成
		if ( m_tstr[index].compare ( tstr.c_str() ) )
		{
			m_tstr[index] = tstr;
			GameText::instance()->MakeStrTexture ( m_tstr[index], m_texture[index], m_vertex[index] );
		}
	}


	void DebugOutGameWindow::DebugOutf ( UINT index, LPCTSTR format, ... )
	{
		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット

		//Unicode（ワイド文字）対応　_vsc w printf() / マルチバイト文字対応 _vscprintf()
		int size = _vsctprintf ( format, args ) + 1;		//'\0'を最後につけたサイズを得る
		TCHAR* buf = new TCHAR[size];		//バッファを確保
		//Unicode（ワイド文字）対応　vs w printf_s() / マルチバイト文字対応 vswprintf_s()
		_vstprintf_s ( buf, size, format, args );	//バッファに書き込み

		//テキストの設定
		SetStr ( index, buf );

		va_end ( args );
		delete[] buf;
	}

	void DebugOutGameWindow::Off ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}
	}


}	//namespace GAME


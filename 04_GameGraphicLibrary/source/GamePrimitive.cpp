//=================================================================================================
//
// ゲームプリミティブオブジェクト　クラス　ヘッダ
//		頂点処理のグラフィックを扱うオブジェクト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GamePrimitive.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GamePrimitive::GamePrimitive ()
		: m_valid ( true ), m_vertex ( make_shared < DxVertex > () )
	{
	}

	GamePrimitive::GamePrimitive ( P_Vertex vertex )
		: m_valid ( true ), m_vertex ( make_shared < DxVertex > () )
	{
		assert ( vertex != nullptr );
		m_vertex = vertex;
	}

	GamePrimitive::~GamePrimitive ()
	{
		 m_vertex->Rele();
	}

	void GamePrimitive::Load ()
	{
		m_vertex->Load ();
	}

	void GamePrimitive::Rele ()
	{
		m_vertex->Rele ();
	}

	void GamePrimitive::Reset ()
	{
		m_vertex->Reset ();
	}

	void GamePrimitive::Move ()
	{
		m_vertex->Move ();
	}

	//引数：テクスチャなし
	void GamePrimitive::DrawVertex ()
	{
		if ( ! GetValid() )	{ return; }	//非有効時には何もしない
		m_vertex->DrawVertex ( nullptr );
	}

	//引数：テクスチャあり
	void GamePrimitive::DrawVertex ( TX& texture )
	{
		if ( ! GetValid() )	{ return; }	//非有効時には何もしない
		m_vertex->DrawVertex ( texture );
	}


	//-------------------------------------------------------------------------------------------------
	GamePrimitiveRect::GamePrimitiveRect ()
	{
		m_vertex = make_shared < DxVertex4 > ();
		GameParticularPrimitive::SetVertex ( m_vertex );
		m_vertex->SetRect ( 50, 50, 100, 200 );
	}

	GamePrimitiveRect::~GamePrimitiveRect ()
	{
	}


	//-------------------------------------------------------------------------------------------------
	GamePrimitive4::GamePrimitive4 ()
	{
		m_vertex = make_shared < DxVertexFree4 > ();
		GamePrimitive::SetVertex ( m_vertex );
		m_vertex->SetPoint ( 0, VEC2 ( 200,  50 ) );
		m_vertex->SetPoint ( 1, VEC2 ( 220, 120 ) );
		m_vertex->SetPoint ( 2, VEC2 (  80,  40 ) );
		m_vertex->SetPoint ( 3, VEC2 (  40, 140 ) );
	}

	GamePrimitive4::~GamePrimitive4 ()
	{
	}


	//-------------------------------------------------------------------------------------------------
	GamePrimitiveLine::GamePrimitiveLine ()
	{
		m_vertex = make_shared < DxVertexLine > ();
		GamePrimitive::SetVertex ( m_vertex );
		m_vertex->SetPoint ( VEC2 ( 100, 50 ), VEC2 ( 50, 100 ) );
	}

	GamePrimitiveLine::~GamePrimitiveLine ()
	{
	}


	//-------------------------------------------------------------------------------------------------
	GamePrimitiveTriangle::GamePrimitiveTriangle ()
	{
		m_vertex = make_shared < DxVertex3 > ();
		GamePrimitive::SetVertex ( m_vertex );
		m_vertex->SetTriangle ( 0, 0, 10, D3DX_PI );
	}

	GamePrimitiveTriangle::~GamePrimitiveTriangle ()
	{
	}


	//-------------------------------------------------------------------------------------------------
	GamePrimitiveText::GamePrimitiveText () : m_texture ( nullptr )
	{
	}

	GamePrimitiveText::~GamePrimitiveText ()
	{
		Rele ();
	}

	void GamePrimitiveText::Load ()
	{
//		m_tstr.assign ( TEXT("GamePrimitiveText::GamePrimitiveText () ") );
//		GameText::instance()->MakeStrTexture ( m_tstr, m_texture, GetVertex4 () );
		GamePrimitiveRect::Load ();
	}

	void GamePrimitiveText::Rele ()
	{
		RELEASE ( m_texture );
		GamePrimitiveRect::Rele ();
	}

	void GamePrimitiveText::Reset ()
	{
		Rele ();
		Init ();
		GamePrimitiveRect::Reset ();
		GameText::instance()->MakeStrTexture ( m_tstr, m_texture, *GetpVertex4 () );
	}

	void GamePrimitiveText::DrawVertex ()
	{
		GamePrimitiveRect::DrawVertex ( m_texture );
//		GamePrimitiveRect::DrawVertex ();
	}

	void GamePrimitiveText::SetStr ( tstring& tstr )
	{
		//現在の文字列と比較して異なる場合新たにテクスチャを作成
		if ( m_tstr.compare ( tstr.c_str() ) )
		{
			m_tstr = tstr;
			GameText::instance()->MakeStrTexture ( m_tstr, m_texture, *GetpVertex4 () );
		}
	}

	void GamePrimitiveText::SetStr ( LPCTSTR lpctstr )
	{
		//現在の文字列と比較して異なる場合新たにテクスチャを作成
		if ( m_tstr.compare ( lpctstr ) )
		{
			m_tstr.assign ( lpctstr );
//			GameText::instance()->SetFontSize ( m_fontSize );
			GameText::instance()->MakeStrTexture ( m_tstr, m_texture, *GetpVertex4 () );
		}
	}

	void GamePrimitiveText::SetStrf ( LPCTSTR format, ... )
	{
		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット

		//Unicode（ワイド文字）対応　_vsc w printf() / マルチバイト文字対応 _vscprintf()
		int size = _vsctprintf ( format, args ) + 1;		//'\0'を最後につけたサイズを得る
		TCHAR* buf = new TCHAR[size];		//バッファを確保
		//Unicode（ワイド文字）対応　vs w printf_s() / マルチバイト文字対応 vswprintf_s()
		_vstprintf_s ( buf, size, format, args );	//バッファに書き込み

		//テキストの設定
		SetStr ( buf );

		va_end ( args );
		delete[] buf;
	}

	//-------------------------------------------------------------------------------------------------
	_GamePrimitivePoliLine::_GamePrimitivePoliLine ()
	{
//		GamePrimitive::SetVertex ( &m_vertex );
		m_vertex = make_shared < _DxPoliVertex > ();
		GamePrimitive::SetVertex ( m_vertex );
#if	0
		m_vertex->SetPos ( 0, 300, 250, 0 );
		m_vertex->SetPos ( 1, 250, 300, 0 );
		m_vertex->SetPos ( 2, 200,  50, 0 );
		m_vertex->SetPos ( 3, 200, 150, 0 );
		m_vertex->SetPos ( 4, 100, 250, 0 );
		m_vertex->SetPos ( 5, 150, 300, 0 );
#endif	//0

		m_vertex->SetColor ( 0, 0xffff0000 );
		m_vertex->SetColor ( 1, 0xff00ff00 );
		m_vertex->SetColor ( 2, 0xff0000ff );
		m_vertex->SetColor ( 3, 0xff00ffff );
		m_vertex->SetColor ( 4, 0xffff00ff );
		m_vertex->SetColor ( 5, 0xffffff00 );

		m_vertex->ApplyPos ();
	}

	_GamePrimitivePoliLine::~_GamePrimitivePoliLine ()
	{
	}

	void _GamePrimitivePoliLine::Load ()
	{
//		m_vertex->CreateVertexBuffer ();
		GamePrimitive::Load ();
	}


	//-------------------------------------------------------------------------------------------------
	GamePrimitivePoliLine::GamePrimitivePoliLine ()
	{
//		GamePrimitive::SetVertex ( &m_vertex );
		m_vertex = make_shared < DxPoliVertex > ();
		GamePrimitive::SetVertex ( m_vertex );

#if	0
		//点の個数を設定
		m_vertex->SetMaxVec ( 10 );

		//点の位置を設定
		m_vertex->SetVec ( 0, D3DXVECTOR2 ( 0, 200 ) );
		m_vertex->SetVec ( 1, D3DXVECTOR2 ( 50, 100 ) );
		m_vertex->SetVec ( 2, D3DXVECTOR2 ( 100, 200 ) );
		m_vertex->SetVec ( 3, D3DXVECTOR2 ( 150, 100 ) );
		m_vertex->SetVec ( 4, D3DXVECTOR2 ( 200, 200 ) );
		m_vertex->SetVec ( 5, D3DXVECTOR2 ( 250, 100 ) );
		m_vertex->SetVec ( 6, D3DXVECTOR2 ( 300, 200 ) );
		m_vertex->SetVec ( 7, D3DXVECTOR2 ( 350, 100 ) );
		m_vertex->SetVec ( 8, D3DXVECTOR2 ( 400, 200 ) );
		m_vertex->SetVec ( 9, D3DXVECTOR2 ( 450, 100 ) );
#endif	//0
	}

	GamePrimitivePoliLine::~GamePrimitivePoliLine ()
	{
	}

	void GamePrimitivePoliLine::Load ()
	{
		GamePrimitive::Load ();
	}


}	//namespace GAME


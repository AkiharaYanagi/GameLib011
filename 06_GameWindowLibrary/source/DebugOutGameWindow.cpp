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

	//--------------------------------------------------
	//シングルトンパターン
	//static実体
	DBGO_WND::P_DBG_WND		DBGO_WND::m_inst = nullptr;

	//コンストラクタ
	DebugOutGameWindow::DebugOutGameWindow ()
		: m_bTime ( true )
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_texture[i] = nullptr;
			m_tstr[i] = _T("");
		}

		for ( UINT i = 0; i < DebugVertexNum; ++ i )
		{
			m_vpVx.push_back ( make_shared < Vx_Rect > () );
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
		m_inst = DBGO_WND::P_DBG_WND ( new DBGO_WND () );
	}
	//--------------------------------------------------

	//読込
	void DebugOutGameWindow::Load ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_vertex[i].Load ();		//頂点バッファの作成
			m_vertex[i].SetPos ( 0, 20.f * i );
		}
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			GameText::Inst()->MakeStrTexture ( m_tstr[i], m_texture[i], m_vertex[i] );
		}
//		m_tstr.assign ( TEXT("DebugOutGameWindow::Init _  ()") );
//		GameText::instance()->MakeStrTexture ( m_tstr, m_texture, m_vertex );


		tstring testStr = _T ( "Test String" );
		m_testVx.Load ();
		m_testVx.SetPos ( 100, 400 );
		m_testVx.SetAllColor ( 0xffff0000 );
		GameText::Inst ()->MakeStrTexture ( testStr, m_testTx, m_testVx );


		UINT index = 0;
		float pos_x = 50;
		DWORD delta = 0;
		for ( P_VxRct pVx : m_vpVx )
		{
			pVx->Load ();
			pVx->SetPos ( pos_x, 130 );
			pos_x += 12;
			delta = ++ index * 255 / DebugVertexNum;
			pVx->SetAllColor ( 0xff00ffffL | delta << 16 );
		}
	}

	void DebugOutGameWindow::Rele ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}


		m_testVx.Rele ();
		for ( P_VxRct pVx : m_vpVx ) { pVx->Rele (); }
	}

	void DebugOutGameWindow::Reset ( D3DDEV d3dDevice )
	{
		Rele ();
		Load ();
	}

	void DebugOutGameWindow::Move ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_vertex[i].ApplyPos ();
			m_vertex[i].SetVertexBuffer ();
		}

//		m_testVx.SetPos ( VEC2 ( 500, 300 ) );
//		m_testVx.ApplyPos ();

		m_testVx.Move ();

		char ch = 32;
		for ( P_VxRct pVx : m_vpVx )
		{
			pVx->Move (); 
		}
	}

	void DebugOutGameWindow::DrawVertex ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			//文字列が空なら何もしないで返す
			if ( ! m_tstr[i].compare ( _T("") ) ) { continue; }

			//４頂点にテクスチャ描画
			m_vertex[i].DrawVertex ( m_texture[i] );
		}


//		m_testVx.DrawVertex ( m_testTx );

		//固定表示 : 稼働時間[F]
		if ( m_bTime )
		{
			for ( P_VxRct pVx : m_vpVx )
			{
				pVx->DrawVertex ( GameText::Inst()->GetAsciiTx () );
			}
		}
	}


	//文字列設定
	void DebugOutGameWindow::SetStr ( UINT index, LPCTSTR lpctstr )
	{
		//現在の文字列と比較して同じ場合何もしない
		if ( ! m_tstr [ index ].compare ( lpctstr ) ) { return; }

		//新たにテクスチャを作成
		m_tstr[index].assign ( lpctstr );
		GameText::Inst()->MakeStrTexture ( m_tstr[index], m_texture[index], m_vertex[index] );

#if 0
		OutlineFont::Inst ()->SetParam ( 40, 1, 1 );
//			OutlineFont::Inst ()->SetFontFace ( _T ( "メイリオ" ) );

		m_texture[index] = OutlineFont::Inst ()->Make ( m_tstr [ index ].c_str (), 0xffffffff, 0xffffffff );
		POINT size = OutlineFont::Inst ()->GetSize ();

		m_vertex [ index ].SetSize ( 1.f * size.x, 1.f * size.y );
		m_vertex [ index ].ApplyPos ();
#endif // 0
	}

	void DebugOutGameWindow::SetStr ( UINT index, tstring& tstr )
	{
		SetStr ( index, tstr.c_str () );
	}
	void DebugOutGameWindow::SetStr ( UINT index, UP_TSTR pstr )
	{
		SetStr ( index, pstr.get () );
	}


	void DebugOutGameWindow::DebugOutf ( UINT index, LPCTSTR format, ... )
	{
		//文字列フォーマット
		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		//テキストの設定
		SetStr ( index, p.get () );
	}

	//-------------------------------------------------------------------------
	//固定表示 : 稼働時間[F]
	void DebugOutGameWindow::DebugOutWnd_Time ( LPCTSTR format, ... )
	{
		va_list args;
		va_start ( args, format );	//文字列の先頭ポインタをセット
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );


		//先頭が空の文字列のとき何もしない
		LPTCH tch = p.get ();
		if ( p [ 0 ] == '\0' ) { return; }

		//文字列サイズの取得
		UINT old_size = m_vpVx.size ();
		UINT size = Size ( p.get () );
		if ( size < old_size )
		{
			m_vpVx.resize ( size );
		}
		else if ( old_size < size )
		{
			m_vpVx.resize ( size );
			for ( UINT i = size - old_size; i < size; ++ i )
			{
				m_vpVx [ i ] = make_shared < Vx_Rect > ();
				m_vpVx [ i ]->Load ();
			}

			UINT init_index = 0;
			float pos_x = 50;
			DWORD delta = 0;
			for ( P_VxRct pVx : m_vpVx )
			{
				pVx->SetPos ( pos_x, 130 );
				pos_x += 12;
				delta = ++ init_index * 255 / DebugVertexNum;
				pVx->SetAllColor ( 0xff00ffffL | delta << 16 );
			}
		}

		//テクスチャサイズと位置の取得
		USIZE ch = GameText::Inst ()->GetCharTxSize ();
		USIZE all = GameText::Inst ()->GetAsciiTxSize ();
		float u = ch.w / (float)all.w;
		float v = ch.h / (float)all.h;

		UINT index = 0;
		while ( index < size )
		{
			UINT code = GameText::Inst()->GetCode ( tch + index );
			VEC2 pos = GameText::Inst ()->GetChToPos ( code );
			float x = pos.x / (float)all.w;
			float y = pos.y / (float)all.h;
			
			P_VxRct pVx = m_vpVx [ index ];
			pVx->SetTxUVWH ( x, y, u, v );
			pVx->SetSize ( 1.f * ch.w, 1.f * ch.h );
			
			++ index;
		}
	}

	void DebugOutGameWindow::Off ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}
	}

	//文字列サイズの取得
	UINT DebugOutGameWindow::Size ( LPCTSTR lpctstr ) const
	{
		UINT ret = 0;
		TCHAR t = *lpctstr;

		try
		{
			while ( t != '\0' )
			{
				t = *( lpctstr + ( ret ++ ) );
			}
		}
		catch ( ... )
		{
			return 0;
		}

		return ret;
	}

}	//namespace GAME


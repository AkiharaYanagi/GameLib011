//=================================================================================================
//
// ゲーム画面へのデバッグテキスト表示
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugOutGameWindow.h"
#include "GameText.h"


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
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_texture [ i ] = nullptr;
			m_tstr [ i ] = _T ( "" );
		}

		m_frame.SetPos ( VEC2 ( 0, 0 ) );
		m_FPS.SetPos ( VEC2 ( 200, 0 ) );
		m_drawTime.SetPos ( VEC2 ( 500, 0 ) );
		m_moveTime.SetPos ( VEC2 ( 500, 20 ) );

		m_test.SetPos ( VEC2 ( 0, 300 ) );
		m_test.SetStr ( _T ( "ConstDebugOut_ASCII" ) );

		m_frame_asc.SetPos ( VEC2 ( 0, 50 ) );
		m_frame_asc.SetStr ( _T ( "m_frame_asc" ) );
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
			m_vertex [ i ].Load ();		//頂点バッファの作成
			m_vertex [ i ].SetPos ( 0, 20.f * i );
		}
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			GameText::Inst ()->MakeStrTexture ( m_tstr [ i ], m_texture [ i ], m_vertex [ i ] );
		}

		m_frame.Load ();
		m_FPS.Load ();
		m_moveTime.Load ();
		m_drawTime.Load ();

		m_test.Load ();
		m_frame_asc.Load ();
	}

	void DebugOutGameWindow::Rele ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture [ i ] );
			m_vertex [ i ].Rele ();
		}
		m_frame.Rele ();
		m_FPS.Rele ();
		m_moveTime.Rele ();
		m_drawTime.Rele ();

		m_test.Rele ();
		m_frame_asc.Rele ();
	}

	void DebugOutGameWindow::Reset ( D3DDEV d3dDevice )
	{
		Rele ();
		Load ();
	}

	void DebugOutGameWindow::Move ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i ) { m_vertex [ i ].Move (); }
		m_frame.Move ();
		m_FPS.Move ();
		m_moveTime.Move ();
		m_drawTime.Move ();


		if ( WND_UTL::AscKey ( VK_F9 ) )
		{
			m_frame_asc.ToggleValid ();
		}

		m_test.Move ();
		m_frame_asc.Move ();
	}

	void DebugOutGameWindow::DrawVertex ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			//文字列が空なら何もしないで返す
			if ( ! m_tstr [ i ].compare ( _T ( "" ) ) ) { continue; }

			//４頂点にテクスチャ描画
			m_vertex [ i ].DrawVertex ( m_texture [ i ] );
		}

		m_frame.Draw ();
		m_FPS.Draw ();
		m_moveTime.Draw ();
		m_drawTime.Draw ();

		m_test.Draw ();
		m_frame_asc.Draw ();
	}


	//文字列設定
	void DebugOutGameWindow::SetStr ( UINT index, LPCTSTR lpctstr )
	{
		//現在の文字列と比較して同じ場合何もしない
		if ( ! m_tstr [ index ].compare ( lpctstr ) ) { return; }

		//新たにテクスチャを作成
		m_tstr [ index ].assign ( lpctstr );
		GameText::Inst ()->MakeStrTexture ( m_tstr [ index ], m_texture [ index ], m_vertex [ index ] );

#if 0
		OutlineFont::Inst ()->SetParam ( 40, 1, 1 );
		//			OutlineFont::Inst ()->SetFontFace ( _T ( "メイリオ" ) );

		m_texture [ index ] = OutlineFont::Inst ()->Make ( m_tstr [ index ].c_str (), 0xffffffff, 0xffffffff );
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

		m_frame.SetStr ( std::move ( p ) );
	}

	//固定表示 : FPS
	void DebugOutGameWindow::DebugOutWnd_FPS ( LPCTSTR format, ... )
	{
		va_list args;
		va_start ( args, format );	//文字列の先頭ポインタをセット
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		m_FPS.SetStr ( std::move ( p ) );
	}

	//固定表示 : MoveTime[ms]
	void DebugOutGameWindow::DebugOutWnd_MoveTime ( LPCTSTR format, ... )
	{
		//可変長引数による文字列フォーマット
		va_list args;
		va_start ( args, format );	//文字列の先頭ポインタをセット
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		m_moveTime.SetStr ( std::move ( p ) );
	}

	//固定表示 : DrawTime[ms]
	void DebugOutGameWindow::DebugOutWnd_DrawTime ( LPCTSTR format, ... )
	{
		//可変長引数による文字列フォーマット
		va_list args;
		va_start ( args, format );	//文字列の先頭ポインタをセット
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		m_drawTime.SetStr ( std::move ( p ) );
	}


	//固定表示 : DrawTime[ms]
	void DebugOutGameWindow::DebugOutWnd_Frame ( UINT frame )
	{
		UP_TSTR p = Format::GetFormatStr ( _T ( "Frame:%d" ), frame );
		m_frame_asc.SetStr ( std::move ( p ) );
	}

	//-------------------------------------------------------------------------
	void DebugOutGameWindow::Off ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture [ i ] );
			m_vertex [ i ].Rele ();
		}
	}

	void DebugOutGameWindow::DebugOutWnd ( UP_TSTR up_tstr, VP_VxRct& vpVpRct )
	{
		//先頭が空の文字列のとき何もしない
		LPTCH tch = up_tstr.get ();
		if ( up_tstr [ 0 ] == '\0' ) { return; }

		//文字列サイズの取得
		UINT old_size = vpVpRct.size ();
		UINT size = STR_UTL::Size ( up_tstr.get () );
		if ( size < old_size )
		{
			vpVpRct.resize ( size );
		}
		else if ( old_size < size )
		{
			vpVpRct.resize ( size );
			for ( UINT i = size - old_size; i < size; ++ i )
			{
				vpVpRct [ i ] = make_shared < Vx_Rect > ();
				vpVpRct [ i ]->Load ();
			}

			float pos_x = 0.f;
			for ( P_VxRct pVx : vpVpRct )
			{
				pVx->SetPos ( pos_x, 0 );
				pos_x += 12;
				pVx->SetAllColor ( 0xffffffffL );
			}
		}

		//テクスチャサイズと位置の取得
		USIZE ch = GameText::Inst ()->GetCharTxSize ();
		USIZE all = GameText::Inst ()->GetAsciiTxSize ();
		float u = ch.w / (float)all.w;
		float v = ch.h / (float)all.h;

		for ( UINT i = 0; i < size; ++ i )
		{
			UINT code = GameText::Inst ()->GetCode ( tch + i );
			VEC2 pos = GameText::Inst ()->GetChToPos ( code );
			float x = pos.x / (float)all.w;
			float y = pos.y / (float)all.h;

			P_VxRct pVx = vpVpRct [ i ];
			pVx->SetTxUVWH ( x, y, u, v );
			pVx->SetSize ( 1.f * ch.w, 1.f * ch.h );
		}
	}



	//=====================================================
	//固定表示
	ConstDebugOut::ConstDebugOut ()
		: m_valid ( T )
	{
		m_vx.SetAllZ ( 0 );
		m_vx.SetPos ( 600, 0 );
		m_vx.SetSize ( 200, 16 );
		m_vx.SetAllColor ( 0xff00ffffL );

		m_tx.SetStr ( _T ( "GameTextureFromString" ) );
		m_tx.SetParam ( 20, 1, 2 );
	}

	ConstDebugOut::~ConstDebugOut ()
	{
		Rele ();
	}

	void ConstDebugOut::Load ()
	{
		m_vx.Load ();
		m_tx.Load ();
	}

	void ConstDebugOut::Rele ()
	{
		m_vx.Rele ();
		m_tx.Rele ();
	}

	void ConstDebugOut::Reset ()
	{
		Rele ();
		Load ();
	}

	void ConstDebugOut::Move ()
	{
		m_vx.Move ();
	}

	void ConstDebugOut::Draw ()
	{
		if ( ! m_valid ) { return; }
		m_vx.DrawVertex ( m_tx.GetTexture () );
	}

	void ConstDebugOut::SetStr ( UP_TSTR upctstr )
	{
		m_tx.SetStr ( upctstr.get () );
		if ( 0 == _tcscmp ( upctstr.get (), _T ( "" ) ) ) { return; }

		m_tx.Load ();

		D3DSURFACE_DESC dc;
		m_tx.GetTexture ()->GetLevelDesc ( 0, & dc );
		m_vx.SetSize ( 1.f * dc.Width, 1.f * dc.Height );
	}

	void ConstDebugOut::SetPos ( VEC2 v )
	{
		m_vx.SetPos ( v );
	}


	//=====================================================
	//固定表示 ASCII文字別テクスチャ

	const UINT ConstDebugOut_ASCII::SIZE = 255;

	ConstDebugOut_ASCII::ConstDebugOut_ASCII ()
		: m_valid ( T )
	{
		mvp_vx.resize ( SIZE );	
		for ( UINT i = 0; i < SIZE; ++ i )
		{
			mvp_vx [ i ] = make_shared < Vx_Rect > ();
			mvp_vx [ i ]->SetAllZ ( 0 );
			mvp_vx [ i ]->SetPos ( 20 + 20.f * i, 400 );
			mvp_vx [ i ]->SetSize ( 20, 16 );
			mvp_vx [ i ]->SetAllColor ( 0xff00ffffL );
		}
	}

	ConstDebugOut_ASCII::~ConstDebugOut_ASCII ()
	{
		Rele ();
	}

	void ConstDebugOut_ASCII::Load ()
	{
		for ( P_VxRct p : mvp_vx ) { p->Load (); }
	}

	void ConstDebugOut_ASCII::Rele ()
	{
		for ( P_VxRct p : mvp_vx ) { p->Rele (); }
	}

	void ConstDebugOut_ASCII::Reset ()
	{
		for ( P_VxRct p : mvp_vx ) { p->Reset (); }
	}

	void ConstDebugOut_ASCII::Move ()
	{
		for ( P_VxRct p : mvp_vx ) { p->Move (); }
	}

	void ConstDebugOut_ASCII::Draw ()
	{
		if ( ! m_valid ) { return; }

		//文字列変換
		size_t str_size = m_tstr.size ();
		int converted = 0;
		vector < char > v_ch;
		v_ch.resize ( str_size );

		UINT i = 0;
		for ( TCHAR tch : m_tstr )
		{
			wctomb_s ( & converted, & v_ch [ i ], 1, m_tstr [ i ] );
			++ i;
		}

		UINT i_c = 0;
		for ( char c : v_ch )
		{
			mvp_vx [ i_c ++ ]->DrawVertex ( GameText::Inst()->GetAsciiTx ( c ) );
		}
	}

	void ConstDebugOut_ASCII::SetStr ( UP_TSTR upctstr )
	{
		m_tstr.assign ( upctstr.get () );
	}

	void ConstDebugOut_ASCII::SetStr ( LPCTSTR lpctstr )
	{
		m_tstr.assign ( lpctstr );
	}

	void ConstDebugOut_ASCII::SetPos ( VEC2 v )
	{
		UINT i = 0;
		for ( P_VxRct p : mvp_vx ) { p->SetPos ( v.x + i++ * 20.f, v.y ); }
	}


}	//namespace GAME


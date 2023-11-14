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
		m_moveTime.SetPos ( VEC2 ( 500, 0 ) );
		m_drawTime.SetPos ( VEC2 ( 500, 20 ) );
		m_sleepTime.SetPos ( VEC2 ( 500, 40 ) );
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
		m_sleepTime.Load ();
		m_moveTime.Load ();
		m_drawTime.Load ();
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
		m_sleepTime.Rele ();
		m_moveTime.Rele ();
		m_drawTime.Rele ();
	}

	void DebugOutGameWindow::Reset ( D3DDEV d3dDevice )
	{
		Rele ();
		Load ();
	}

	void DebugOutGameWindow::Move ()
	{
		//手動 Move ()
		for ( UINT i = 0; i < DebugTextNum; ++i ) { m_vertex [ i ].Move (); }

		//F8キーでFPS関連デバッグ表示切替
		if ( WND_UTL::AscKey ( VK_F8 ) )
		{
			m_frame.ToggleValid (); 
			m_FPS.ToggleValid ();
			m_moveTime.ToggleValid ();
			m_drawTime.ToggleValid ();
			m_sleepTime.ToggleValid ();
		}

		m_frame.Move ();
		m_FPS.Move ();
		m_moveTime.Move ();
		m_drawTime.Move ();
		m_sleepTime.Move ();
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
		m_sleepTime.Draw ();
		m_moveTime.Draw ();
		m_drawTime.Draw ();
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

	//固定表示 : DrawTime[ms]
	void DebugOutGameWindow::DebugOutWnd_Frame ( UINT frame )
	{
		UP_TSTR p = Format::GetFormatStr ( _T ( "Frame:%d" ), frame );
		m_frame.SetStr ( std::move ( p ) );
	}

	//固定表示 : FPS
	void DebugOutGameWindow::DebugOutWnd_FPS ( UINT FPS )
	{
		UP_TSTR p = Format::GetFormatStr ( _T ( "FPS:%d" ), FPS );
		m_FPS.SetStr ( std::move ( p ) );
	}

	//固定表示 : 休眠時間[ms]
	void DebugOutGameWindow::DebugOutWnd_SleepTime ( float sleepTile )
	{
		UP_TSTR p = Format::GetFormatStr ( _T ( "SleepTime = %05.2f [ms/F]" ), sleepTile );
		m_sleepTime.SetStr ( std::move ( p ) );
	}

	//固定表示 : 動作時間[ms]
	void DebugOutGameWindow::DebugOutWnd_MoveTime ( float moveTime )
	{
		UP_TSTR p = Format::GetFormatStr ( _T ( "MoveTime  = %05.2f [ms/F]" ), moveTime );
		m_moveTime.SetStr ( std::move ( p ) );
	}

	//固定表示 : 描画時間[ms]
	void DebugOutGameWindow::DebugOutWnd_DrawTime ( float drawTime )
	{
		UP_TSTR p = Format::GetFormatStr ( _T ( "DrawTime  = %05.2f [ms/F]" ), drawTime );
		m_drawTime.SetStr ( std::move ( p ) );
	}

	//-------------------------------------------------------------------------
#if 0
	void DebugOutGameWindow::Off ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture [ i ] );
			m_vertex [ i ].Rele ();
		}
	}
#endif // 0

	void DebugOutGameWindow::Off ()
	{
		m_frame.Off ();
		m_FPS.Off ();
		m_sleepTime.Off ();
		m_moveTime.Off ();
		m_drawTime.Off ();
	}

	void DebugOutGameWindow::On ()
	{
		m_frame.On ();
		m_FPS.On ();
		m_sleepTime.On ();
		m_moveTime.On ();
		m_drawTime.On ();
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
				vpVpRct [ i ] = std::make_shared < Vx_Rect > ();
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
			UINT code = STR_UTL::GetCode ( tch + i );
			VEC2 pos = GameText::Inst ()->GetChToPos ( code );
			float x = pos.x / (float)all.w;
			float y = pos.y / (float)all.h;

			P_VxRct pVx = vpVpRct [ i ];
			pVx->SetTxUVWH ( x, y, u, v );
			pVx->SetSize ( 1.f * ch.w, 1.f * ch.h );
		}
	}


	//=====================================================
	//固定表示 ASCII文字別テクスチャ

	const UINT ConstDebugOut_ASCII::SIZE = 64;

	ConstDebugOut_ASCII::ConstDebugOut_ASCII ()
		: m_valid ( T )
	{
		mvp_vx.resize ( SIZE );	
		for ( UINT i = 0; i < SIZE; ++ i )
		{
			mvp_vx [ i ] = std::make_shared < Vx_Rect > ();
			P_VxRct p = mvp_vx [ i ];
			p->SetAllZ ( 0 );
			p->SetPos ( 20 + 20.f * i, 400 );
			p->SetSize ( 20, 16 );
			p->SetAllColor ( 0xff00ffffL );
			p->SetUpdate ( F );	//毎回のMove()内で頂点位置を更新しない
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

		//テクスチャを指定して描画
		UINT i_c = 0;
		for ( char c : m_str )
		{
			P_VxRct p = mvp_vx [ i_c ];
			TX tx = GameText::Inst ()->GetAsciiTx ( c );
			p->DrawVertex ( tx );
			++ i_c;
		}
	}

	void ConstDebugOut_ASCII::SetStr ( UP_TSTR upctstr )
	{
		SetStr ( upctstr.get () );
	}

	void ConstDebugOut_ASCII::SetStr ( LPCTSTR lpctstr )
	{
		m_tstr.assign ( lpctstr );

		//文字列変換
		size_t str_size = m_tstr.size ();
		std::unique_ptr < char[] > ary_ch = std::make_unique < char[] > ( str_size );

		vector < char > v_ch;
		v_ch.resize ( str_size );

		int converted = 0;
		UINT i = 0;
		for ( TCHAR tch : m_tstr )
		{
			wctomb_s ( & converted, & v_ch [ i ], 1, m_tstr [ i ] );
			wctomb_s ( & converted, & ary_ch [ i ], 1, m_tstr [ i ] );
			++ i;
		}
		m_str.assign ( ary_ch.get (), str_size );


		//テクスチャを指定して	サイズ取得
		float dx = 0;	//補正位置
		for ( UINT i_c = 0; i_c < str_size; ++ i_c )
		{
			P_VxRct p = mvp_vx [ i_c ];
			TX tx = GameText::Inst ()->GetAsciiTx ( ary_ch [ i_c ] );
			USIZE us = Dx_UTL::TxSize ( tx );
			LONG w = GameText::Inst ()->GetAsciiW ( ary_ch [ i_c ] );

			p->SetSize ( 1.f * us.w, 1.f * us.h );
			p->SetPos ( m_pos.x + dx, m_pos.y );
			p->ApplyPos ();
			p->WriteVertexBuffer ();

			dx += w;	//次の頂点位置はテクスチャではなく文字から取得する
		}
	}

	void ConstDebugOut_ASCII::SetPos ( VEC2 v )
	{
		m_pos = v;
	}


}	//namespace GAME


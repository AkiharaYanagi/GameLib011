//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "testInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Test::Test ()
	{
		for ( int i = 0; i < 24; ++ i )
		{
			m_vp_rect.push_back ( make_shared < PrmRect > () );
			m_vp_rect [ i ]->SetZ ( 0.5f );
			m_vp_rect [ i ]->SetSize ( VEC2 ( 20.f, 20.f ) );
			m_vp_rect [ i ]->SetPos ( VEC2 ( 120.f + i * 20, 120.f ) );
			m_vp_rect [ i ]->SetAllColor ( 0xFF404040 );
			AddpTask ( m_vp_rect [ i ] );
			GRPLST_INSERT_MAIN ( m_vp_rect [ i ] );
		}
#if 0

		OutlineFont::Inst ()->SetFontFace ( _T ( "メイリオ" ) );
		OutlineFont::Inst ()->SetParam ( 80, 1, 3 );

		m_grpStr = make_shared < GrpStr > ();
		m_grpStr->SetStr ( _T ( "m_grpStr" ) );
		m_grpStr->SetPos ( 100, 200 );
		m_grpStr->SetZ ( 0.1f );
		AddpTask ( m_grpStr );
		GRPLST_INSERT_MAIN ( m_grpStr );
#endif // 0

#if 0
		m_grpApTx = make_shared < GrpApTx > ();
		P_TxStr txstr = make_shared < TxStr > ();
		txstr->SetStr ( _T ( "test" ) );
		m_grpApTx->SetpTexture ( txstr );
		m_grpApTx->SetPos ( 100, 300 );
//		AddpTask ( m_grpApTx );
#endif // 0

#if 0
		m_ascii = make_shared < GrpApTx > ();
		m_ascii->SetPos ( 100, 400 );
		
		m_tx = make_shared < TxBs > ();
//		m_tx->SetTexture ( GameText::Inst ()->GetAsciiTx ( L'A' ) );
		m_tx->SetTexture ( GameText::Inst ()->GetAsciiTx ( L'Z' ) );
//		m_tx->SetTexture ( GameText::Inst ()->GetAsciiTx () );
		m_ascii->SetpTexture ( m_tx );
		AddpTask ( m_ascii );
		GRPLST_INSERT_MAIN ( m_ascii );

		m_grpAcv = make_shared < GrpAcv > ();
		m_grpAcv->AddTexture ( _T ( "test_title.png" ) );
		//		m_grpAcv->AddTexture ( _T ( "Demo_Attack.png" ) );
		AddpTask ( m_grpAcv );
		GRPLST_INSERT_MAIN ( m_grpAcv );
#endif // 0

		m_grpAcv = make_shared < GrpAcv > ();
//		m_grpAcv->SetZ ( 0.25f );
		m_grpAcv->SetPos ( VEC2 ( 50, 50 ) );
		m_grpAcv->AddTexture ( _T ( "shadow.png" ) );
//		m_grpAcv->AddTexture ( _T ( "ftgmain_bg.bmp" ) );
		m_grpAcv->Load ();
		AddpTask ( m_grpAcv );
		GRPLST_INSERT_MAIN ( m_grpAcv );


		m_rect0 = make_shared < PrmRect > ();
		m_rect0->SetZ ( 0.1f );
		m_rect0->SetSize ( 600, 400 );
		m_rect0->SetPos ( 200, 50 );
		m_rect0->SetAllColor ( 0x800000ff );
		AddpTask ( m_rect0 );
		GRPLST_INSERT_MAIN ( m_rect0 );

		m_rect1 = make_shared < PrmRect > ();
		m_rect1->SetZ ( 0.2f );
		m_rect1->SetSize ( 1000, 300 );
		m_rect1->SetPos ( 100, 130 );
		m_rect1->SetAllColor ( 0x80ff0000 );
		AddpTask ( m_rect1 );
		GRPLST_INSERT_MAIN ( m_rect1 );

		m_rect2 = make_shared < PrmRect > ();
		m_rect2->SetZ ( 0.3f );
		m_rect2->SetSize ( 600, 300 );
		m_rect2->SetPos ( 130, 80 );
		m_rect2->SetAllColor ( 0x8000ff00 );
		AddpTask ( m_rect2 );
		GRPLST_INSERT_MAIN ( m_rect2 );
	}

	Test::~Test ()
	{
	}

	void Test::Move ()
	{
#if 0
		DBGOUT_WND_F ( 0, _T ( "%d" ), DXINP->GetJoyAxisY ( 0 ) );
//		DBGOUT_WND_F ( 1, _T ( "%d" ), DXINP->IsAxisUp ( 0 ) );
		DBGOUT_WND_F ( 1, _T ( "%d" ), DXINP->GetPov ( 0 ) );
		DBGOUT_WND_F ( 3, _T ( "up:%d" ), CFG_IS_KEY ( _P1_UP ) ? 1 : 0 );

		//リセット
		for ( int i = 0; i < 24; ++ i )
		{
			m_vp_rect [ i ]->SetAllColor ( 0xFF404040 );
		}
		
		//各種判定
		Check ( _P1_UP );
		Check ( _P1_DOWN );
		Check ( _P1_LEFT );
		Check ( _P1_RIGHT );
		Check ( _P1_BTN0 );
		Check ( _P1_BTN1 );
		Check ( _P1_BTN2 );
		Check ( _P1_BTN3 );
		Check ( _P1_BTN4 );
		Check ( _P1_BTN5 );
		Check ( _P1_BTN6 );
		Check ( _P1_BTN7 );

		Check ( _P2_UP );
		Check ( _P2_DOWN );
		Check ( _P2_LEFT );
		Check ( _P2_RIGHT );
		Check ( _P2_BTN0 );
		Check ( _P2_BTN1 );
		Check ( _P2_BTN2 );
		Check ( _P2_BTN3 );
		Check ( _P2_BTN4 );
		Check ( _P2_BTN5 );
		Check ( _P2_BTN6 );
		Check ( _P2_BTN7 );

#endif // 0

		if ( CFG_IS_KEY ( _P1_BTN0 ) )
		{
			SOUND->Play_BGM ( 0 );
		}
		if ( CFG_IS_KEY ( _P1_BTN1 ) )
		{
			SOUND->Stop_BGM ( 0 );
		}

		if ( CFG_IS_KEY ( _P1_BTN2 ) )
		{
			SOUND->Play_SE ( 0 );
		}

		if ( CFG_IS_KEY ( _P1_BTN3 ) )
		{
			SOUND->Play_SE ( 1 );
		}



		TASK_VEC::Move ();
	}

	void Test::Check ( GAME_USE_KEY key )
	{
		if ( CFG_IS_KEY ( key ) )
		{
			m_vp_rect [ key ]->SetAllColor ( 0xffffffff );
		}
	}



}	//namespace GAME


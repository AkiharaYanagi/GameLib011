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
			m_vp_rect [ i ]->SetSize ( VEC2 ( 20.f, 20.f ) );
			m_vp_rect [ i ]->SetPos ( VEC2 ( 120.f + i * 20, 120.f ) );
			m_vp_rect [ i ]->SetAllColor ( 0xFF404040 );
			AddpTask ( m_vp_rect [ i ] );
			GRPLST_INSERT_MAIN ( m_vp_rect [ i ] );
		}

		OutlineFont::Inst ()->SetFontFace ( _T ( "メイリオ" ) );
		OutlineFont::Inst ()->SetParam ( 80, 1, 3 );

		m_grpStr = make_shared < GrpStr > ();
		m_grpStr->SetStr ( _T ( "m_grpStr" ) );
		m_grpStr->SetPos ( 100, 200 );
		m_grpStr->SetZ ( 0.1f );
		AddpTask ( m_grpStr );
		GRPLST_INSERT_MAIN ( m_grpStr );

#if 0
		m_grpApTx = make_shared < GrpApTx > ();
		P_TxStr txstr = make_shared < TxStr > ();
		txstr->SetStr ( _T ( "test" ) );
		m_grpApTx->SetpTexture ( txstr );
		m_grpApTx->SetPos ( 100, 300 );
//		AddpTask ( m_grpApTx );
#endif // 0
	}

	Test::~Test ()
	{
	}

	void Test::Move ()
	{
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


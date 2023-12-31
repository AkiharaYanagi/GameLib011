//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TestFade.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TestFade::TestFade ()
	{
		m_grp = make_shared < GrpAcv > ();
		m_grp->AddTexture ( _T ( "dot_ver0.png" ) );
		m_grp->AddObject ();
		AddpTask ( m_grp );

#if 0
		m_grp->SetFade ( 1000, 0x00ffffff, 0xffffffff );
//		m_grp->SetFade ( 1000, 0x00000000UL, 0xff000000UL );
//		m_grp->SetFade ( 1000, 0xff000000UL, 0x00000000UL );
#endif // 0


		PVP_Object pvpOb = m_grp->GetpvpObject ();
		P_Object pOb = ( *pvpOb ) [ 0 ];
//		pOb->SetFade ( 1000,0x00000000UL, 0xffffffff );

		( *pvpOb ) [ 1 ]->SetPos ( VEC2 ( 100, 100 ) );

		m_grp->FadeChangeOb ( 1000, 0, 1 );

	}

	TestFade::~TestFade ()
	{
	}

	void TestFade::Move ()
	{
		if ( DXINP->IsMouseButton ( DXINP->MOUSE_LEFT ) )
		{
			m_grp->EndFade ( 0xffffffff );
		}

		m_grp->Move ();
//		TASK_VEC::Move ();
	}

	void TestFade::Draw ()
	{
		m_grp->Draw ();
//		TASK_VEC::Move ();
	}

}	//namespace GAME


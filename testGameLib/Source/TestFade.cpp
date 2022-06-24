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
		m_grp->AddTexture ( _T ( "test_od.png" ) );
		AddpTask ( m_grp );

#if 0
		PVP_Object pvpOb = m_grp->GetpvpObject ();
		P_Object pOb = ( *pvpOb ) [ 0 ];
		pOb->SetColor ( 0x80000080 );
#endif // 0

		m_grp->SetFade ( 1000, 0x00ffffff, 0xffffffff );
//		m_grp->SetFade ( 1000, 0x00000000UL, 0xff000000UL );
//		m_grp->SetFade ( 1000, 0xff000000UL, 0x00000000UL );

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


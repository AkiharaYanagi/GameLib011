//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "testGrpLst.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-----------------------------------------------------------------
	Scene0::Scene0 ()
	{
		TRACE_F ( _T ( "Scene0:コンストラクタ\n" ) );
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "test_FtgMain.png" ) );
		AddpTask ( m_bg );

	}
	Scene0::~Scene0 ()
	{
		TRACE_F ( _T ( "Scene0:デストラクタ\n" ) );
	}
	void Scene0::Load ()
	{
		TRACE_F ( _T ( "Scene0:Load\n" ) );
		//		AddpTask ( GRPLST_NEW () );
		//		GRPLST_INSERT ( m_bg );

		TASK_VEC::Load ();
	}
	void Scene0::Move ()
	{
		TASK_VEC::Move ();
	}

	P_GameScene Scene0::Transit ()
	{
		if ( PUSH_KEY ( P1_BUTTON1 ) )
		{
			TRACE_F ( _T ( "Scene1:Transit\n\n" ) );
			return make_shared < Scene1 > ();
		}
		return shared_from_this ();
	}


	//-----------------------------------------------------------------
	Scene1::Scene1 ()
	{
		TRACE_F ( _T ( "Scene1:コンストラクタ\n" ) );
		m_bg1 = make_shared < GrpAcv > ();
		m_bg1->AddTexture ( _T ( "ftgmain_bg.png" ) );
		AddpTask ( m_bg1 );
	}
	Scene1::~Scene1 ()
	{
		TRACE_F ( _T ( "Scene1:デストラクタ\n" ) );
	}
	void Scene1::Load ()
	{
		TRACE_F ( _T ( "Scene1:Load\n" ) );
//		AddpTask ( GRPLST_NEW () );
//		GRPLST_INSERT ( m_bg1 );

		TASK_VEC::Load ();
	}
	void Scene1::Move ()
	{
		TASK_VEC::Move ();
	}

	P_GameScene Scene1::Transit ()
	{
		return shared_from_this ();
	}


	//-----------------------------------------------------------------
	TestGrpLst::TestGrpLst ()
	{
		m_SceneManager = make_shared < GameSceneManager > ();
		shared_ptr < Scene0 > p = make_shared < Scene0 > ();
		m_SceneManager->SetScene ( p );

		AddpTask ( m_SceneManager );
	}

	TestGrpLst::~TestGrpLst ()
	{
	}

}	//namespace GAME


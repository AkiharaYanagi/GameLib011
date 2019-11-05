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
	TestGrpLst::TestGrpLst ()
	{
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T("test_FtgMain.png") );


		m_SceneManager.SetScene ( make_shared < Scene0 > () );
	}

	TestGrpLst::~TestGrpLst ()
	{
	}

	void TestGrpLst::Load ()
	{
		AddpTask ( GRPLST_NEW () );
		GRPLST_INSERT ( m_bg );

		TASK_VEC::Load ();
	}

}	//namespace GAME


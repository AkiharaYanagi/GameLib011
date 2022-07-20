//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "testStretch.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TestStretch::TestStretch()
	{
		TASK_VEC::AddpTask ( GRPLST_MAKE () );

		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T("test_title.png") );
		GRPLST_INSERT ( m_bg );

		m_rect = make_shared < PrmRect > ();
		m_rect->SetSize ( 1200, 900 );
		m_rect->SetColor ( 0, 0xff0000ff );
		m_rect->SetColor ( 1, 0xff00ff00 );
		m_rect->SetColor ( 2, 0xffff0000 );
		m_rect->SetColor ( 3, 0xffff00ff );
//		AddpTask ( m_rect );
	}

	TestStretch::~TestStretch()
	{
	}

	void TestStretch::Move ()
	{
		if ( PUSH_KEY ( P1_BUTTON1 ) )
		{
			GRPLST_ERASE ( m_bg );
		}
		
		TASK_VEC::Move ();
	}


}	//namespace GAME


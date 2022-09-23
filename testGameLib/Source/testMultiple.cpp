//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "testMultiple.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Test::Test ()
	{
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "Test\\B\\test_od.png" ) );
		AddpTask ( m_bg );


		m_Multi = make_shared < GrpAcv > ();
		m_Multi->AddTexture ( _T ( "Test\\testMultiple.png" ) );
		AddpTask ( m_Multi );

		m_rect = make_shared < PrmTx > ();
		m_rect->SetFileName ( _T ( "pantsu_shade.png" ) );
//		m_rect->SetFileName ( _T ( "testMultiple.png" ) );
		m_rect->SetMultiple ( true );
//		m_rect->SetColor ( 2, 0xff0000ff );
//		m_rect->SetColor ( 2, 0x000000ff );
//		m_rect->SetAllColor ( 0x00ffffff );
//		m_rect->SetAllColor ( 0xffffffff );
		m_rect->SetColor ( 0x80ffffff );
		m_rect->SetPos ( 180, -150 );
		m_rect->SetSize ( 600, 1000 );
		AddpTask ( m_rect );


		m_clr = 0x80ffffff;
	}

	Test::~Test ()
	{
	}

	void Test::Move ()
	{
		if ( IS_KEY ( P1_RIGHT ) )
		{
			m_rect->SetPos ( m_rect->GetPos () + VEC2 ( 10, 0 ) );
		}
		if ( IS_KEY ( P1_LEFT ) )
		{
			m_rect->SetPos ( m_rect->GetPos () + VEC2 ( -10, 0 ) );
		}

		if ( IS_KEY ( P1_UP ) )
		{
			m_clr.a += 0.01f;
			if ( m_clr.a > 1.f ) { m_clr.a = 1.f; }
			m_rect->SetColor ( m_clr );
		}
		if ( IS_KEY ( P1_DOWN ) )
		{
			m_clr.a -= 0.01f;
			if ( m_clr.a < 0.f ) { m_clr.a = 0.f; }
			m_rect->SetColor ( m_clr );
		}

//		m_rect->Move ();
		TASK_VEC::Move ();
	}



}	//namespace GAME


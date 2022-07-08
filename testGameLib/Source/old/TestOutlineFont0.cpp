//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TestOutlineFont0.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TestOutlineFont::TestOutlineFont ()
	{
		//---------------------------------------------
		//Sceneの最初一回のみ、GrpLstをゲームタスクに設定
//		AddpTask ( GRPLST_NEW () );
		//---------------------------------------------
//		m_rect = make_shared < PrmRect > ();
//		m_rect->SetRect ( 100, 100, 100, 100 );
//		GameTaskVector::AddpTask ( m_rect );
//		GRPLST_INSERT ( m_rect );

		m_str = make_shared < Str > ();
		GameTaskVector::AddpTask ( m_str );

		m_grpTx = make_shared < GrpApTx > ();
		AddpTask ( m_grpTx );
	}

	TestOutlineFont::~TestOutlineFont ()
	{
	}

	void TestOutlineFont::Load ()
	{
//		OutlineFont::Inst ()->Set ( 100, 3, 3 );
		OutlineFont::Inst ()->Set ( 100, 2, 1 );
		OutlineFont::Inst ()->SetFontFace ( _T ( "メイリオ" ) );
		m_str->SetStr ( _T ( "abcdefghijklmnopqrstuvwxyz.,!?" ) );
//		m_str->SetStr ( _T ( "あいうえお、。" ) );
		m_str->Off ();
		m_str->SetPitch ( 1200 );


		m_tx.SetTexture (GameText::Inst()->GetAsciiTx ());
		m_grpTx->SetpTexture ( &m_tx );



		GameTaskVector::Load ();
	}

	void TestOutlineFont::Init ()
	{
		GameTaskVector::Init ();
	}

	void TestOutlineFont::Move ()
	{
		DBGOUT_WND->SetPos ( 0, 0, 200 );
		DBGOUT_WND_F ( 0, _T ( "abcdefghijklmnopqrstuvwxyz.,!?" ) );
//		DBGOUT_WND_F ( 0, _T ( "あいうえお、。" ) );

		if ( PUSH_KEY ( P1_BUTTON1 ) )
		{
			m_str->Stream ();
		}

		if ( PUSH_KEY ( P1_BUTTON2 ) )
		{
			m_str->Off ();
		}

		GameTaskVector::Move ();
	}

	void TestOutlineFont::DrawVertex ()
	{
		GameTaskVector::DrawVertex ();
	}

}	//namespace GAME


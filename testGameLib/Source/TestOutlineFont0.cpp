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
		: m_tx ( nullptr )
	{
	}

	TestOutlineFont::~TestOutlineFont ()
	{
		RELEASE ( m_tx );
	}

	void TestOutlineFont::Load ()
	{
		m_vtx.Load ();
	}

	void TestOutlineFont::Init ()
	{
		OutlineFont::Inst ()->Set ( 600, 10, 2 );
		m_tx = OutlineFont::Inst ()->Make ( _T("鸞"), 0xff4080ff, 0x8080ffff );
		POINT size = OutlineFont::Inst ()->GetSize ();
		m_vtx.SetRect ( 100, 200, 1.f * size.x, 1.f * size.y );
	}

	void TestOutlineFont::Move ()
	{
		m_vtx.Move ();
	}

	void TestOutlineFont::DrawVertex ()
	{
		m_vtx.DrawVertex ( m_tx );
	}

}	//namespace GAME


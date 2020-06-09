//=================================================================================================
//
//	文字列
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameString.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	GameString::GameString ()
		: m_tx ( nullptr )
	{
		m_str.clear ();
	}

	GameString::~GameString ()
	{
		RELEASE ( m_tx );
	}

	void GameString::Load ()
	{
//		m_vtx.Load ();
		GameTaskVector::Load ();
	}

	void GameString::Init ()
	{
//		m_tx = OutlineFont::Inst ()->Make ( _T("鸞"), 0xff4080ff, 0x8080ffff );
//		POINT size = OutlineFont::Inst ()->GetSize ();
//		m_vtx.SetRect ( 100, 200, 1.f * size.x, 1.f * size.y );

		GameTaskVector::Init ();
	}

	void GameString::Move ()
	{
//		m_vtx.Move ();
		for ( UINT i = 0; i < m_str.length (); ++ i )
		{
			m_vecVtx[i]->Move ();
		}
		GameTaskVector::Move ();
	}

	void GameString::DrawVertex ()
	{
//		m_vtx.DrawVertex ( m_tx );
		for ( UINT i = 0; i < m_str.length (); ++ i )
		{
			m_vecVtx[i]->DrawVertex ( m_vecTx [ i ] );
		}
		GameTaskVector::DrawVertex ();
	}


	void GameString::SetStr ( tstring str )
	{
		m_str = str;
		m_vecTx.resize ( m_str.length () );
		m_vecVtx.resize ( m_str.length () );

		float pos_x = 0;
		float pos_y = 0;
		float nextOrigin = 0;
		for ( UINT i = 0; i < m_str.length (); ++ i )
		{
			m_vecTx [ i ] = OutlineFont::Inst()->Make ( m_str.c_str () + i, 0xfff0f0f0, 0xff6060d0 );
			POINT size = OutlineFont::Inst ()->GetSize ();
			POINT grif_pos = OutlineFont::Inst ()->GetPos ();
			int gmCellIncX = OutlineFont::Inst ()->GetGmCellIncX ();

			m_vecVtx[i] = make_shared < DxVertex4 > ();
			m_vecVtx[i]->Load ();
			m_vecVtx[i]->SetRect ( pos_x + grif_pos.x, pos_y + grif_pos.y, 1.f * size.x, 1.f * size.y );
			pos_x += gmCellIncX;
		}
	}


}	//namespace GAME


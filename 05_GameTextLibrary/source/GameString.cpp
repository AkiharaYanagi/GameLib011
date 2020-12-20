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
		: m_tx ( nullptr ), m_fillColor ( 0xffc0c0c0 ), m_edgeColor ( 0xffffffff )
		, m_stream ( F ), m_pitch ( 1000 ), m_timer ( 0 ), m_index ( 0 ), m_count ( 0 )
	{
		m_str.clear ();
	}

	GameString::~GameString ()
	{
		RELEASE ( m_tx );
	}

	void GameString::Move ()
	{
		for ( UINT i = 0; i < m_str.length (); ++ i )
		{
			m_vecVtx[i]->Move ();
		}

		//Stream
		if ( m_stream )
		{
			//目標位置までの計算
			m_timer += m_pitch;
			m_index = m_timer / 1000;
			++ m_index;

			//サイズ内での表示開始
			size_t size = m_vecVtx.size ();
			if ( m_count < size )
			{
				//初回のみ即表示
				if ( 0 == m_count )
				{
					m_vecVtx[m_count]->SetValid ( T );
					++ m_count;
				}
				else
				{
					//pitchによって最大値を超えてしまうときの補正
					if ( m_index > size )
					{
						m_index = size;
					}
					//現在値から目標値まで表示開始
					for ( UINT i = m_count; i < m_index; ++ i )
					{
						m_vecVtx[i]->SetValid ( T );
					}
					//現在値の更新
					m_count = m_index;
				}
			}
			else
			{
				m_timer = 0;
				m_count = 0;
				m_index = 0;
			}
		}

		GameTaskVector::Move ();
	}

	void GameString::DrawVertex ()
	{
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
			m_vecTx [ i ] = OutlineFont::Inst()->Make ( m_str.c_str () + i, m_edgeColor, m_fillColor );
			POINT size = OutlineFont::Inst ()->GetSize ();
			POINT grif_pos = OutlineFont::Inst ()->GetPos ();
			int gmCellIncX = OutlineFont::Inst ()->GetGmCellIncX ();

			m_vecVtx[i] = make_shared < DxVertex4 > ();
			m_vecVtx[i]->Load ();
			m_vecVtx[i]->SetRect ( pos_x + grif_pos.x, pos_y + grif_pos.y, 1.f * size.x, 1.f * size.y );
			pos_x += gmCellIncX;
		}
	}

	void GameString::SetPos ( VEC2 v )
	{
		float pos_x = v.x;
		for ( UINT i = 0; i < m_str.length (); ++ i )
		{
			m_vecTx[i] = OutlineFont::Inst ()->Make ( m_str.c_str () + i, m_edgeColor, m_fillColor );
			POINT size = OutlineFont::Inst ()->GetSize ();
			POINT grif_pos = OutlineFont::Inst ()->GetPos ();
			int gmCellIncX = OutlineFont::Inst ()->GetGmCellIncX ();

			m_vecVtx[i]->SetRect ( pos_x + grif_pos.x, v.y + grif_pos.y, 1.f * size.x, 1.f * size.y );
			pos_x += gmCellIncX;
		}
	}

	void GameString::On ()
	{
		for ( P_Vx4 p : m_vecVtx )
		{
			p->SetValid ( T );
		}
		m_stream = F;
	}

	void GameString::Off ()
	{
		for ( P_Vx4 p : m_vecVtx )
		{
			p->SetValid ( F );
		}
		m_timer = 0;
		m_count = 0;
		m_index = 0;
		m_stream = F;
	}

	void GameString::Stream ()
	{
		m_stream = T;
	}


}	//namespace GAME


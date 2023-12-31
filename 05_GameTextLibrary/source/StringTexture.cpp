//=================================================================================================
//
//	文字列をまとめたテクスチャ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "StringTexture.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	StringTexture::StringTexture ()
		: m_fillColor ( 0xffc0c0c0 ), m_edgeColor ( 0xffffffff )
	{
	}

	StringTexture::~StringTexture ()
	{
	}

	void StringTexture::SetStr ( tstring str )
	{
		m_str = str;
#if 0

		m_vecTx.resize ( m_str.length () );

		float pos_x = 0;
		float pos_y = 0;
		float nextOrigin = 0;
		for ( UINT i = 0; i < m_str.length (); ++ i )
		{
			m_vecTx [ i ] = OutlineFont::Inst()->Make ( m_str.c_str () + i, m_edgeColor, m_fillColor );
			POINT size = OutlineFont::Inst ()->GetSize ();
			POINT grif_pos = OutlineFont::Inst ()->GetPos ();
			int gmCellIncX = OutlineFont::Inst ()->GetGmCellIncX ();

			m_vecVtx[i] = std::make_shared < DxVertexRect > ();
			m_vecVtx[i]->Load ();
			m_vecVtx[i]->SetRect ( pos_x + grif_pos.x, pos_y + grif_pos.y, 1.f * size.x, 1.f * size.y );
			pos_x += gmCellIncX;
		}
#endif // 0
	}


}	//namespace GAME


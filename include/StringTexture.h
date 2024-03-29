//=================================================================================================
//
//	文字列をまとめたテクスチャ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "Dx3D.h"
#include "DxVertex.h"
#include "GameTexture.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class StringTexture
	{
		tstring		m_str;
		std::vector < TX >	m_vecTx;

		//テクスチャの位置 (矩形)
		//	( u + w	, v		),
		//	( u + w	, v + h	),
		//	( u		, v		),
		//	( u		, v + h	),
		float		m_u;
		float		m_v;
		float		m_w;
		float		m_h;

		DWORD		m_fillColor;
		DWORD		m_edgeColor;

	public:
		StringTexture ();
		StringTexture ( const StringTexture & rhs ) = delete;
		~StringTexture ();

		void Move ();
		void SetStr ( tstring str );

		void On ();
		void Off ();
		void Stream ();

		void SetFillColor ( DWORD fillColor ) { m_fillColor = fillColor; }
		void SetEdgeColor ( DWORD edgeColor ) { m_edgeColor = edgeColor; }

	};


}	//namespace GAME


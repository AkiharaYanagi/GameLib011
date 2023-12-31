//=================================================================================================
//
// FRECT　ヘッダファイル
//
//		floatの矩形を定義
//
//=================================================================================================

#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Const.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	typedef struct _FRECT
	{
		float		x;
		float		y;
		float		w;
		float		h;
	} FRECT, *PFRECT;

	bool OverlapFRect ( FRECT frect0, FRECT frect1 )
	{
		float t0 = frect0.y;
		float l0 = frect0.x;
		float b0 = frect0.y + frect0.h;
		float r0 = frect0.x + frect0.w;
		float t1 = frect1.y;
		float l1 = frect1.x;
		float b1 = frect1.y + frect1.h;
		float r1 = frect1.x + frect1.w;
		return ( (t0 <= b1) && (b0 >= t1) && (l0 <= r1) && (r0 >= l1) );
	}

}	//namespace GAME



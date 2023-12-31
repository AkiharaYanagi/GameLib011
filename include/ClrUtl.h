//=================================================================================================
//
//	カラーユーティリティ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//色範囲(Routate)
	enum CLR_RTT
	{
		R_UP,
		R_DN,
		G_UP,
		G_DN,
		B_UP,
		B_DN,
	};

	class ClrUtl
	{
		//色範囲
		CLR_RTT			m_clrRtt;

		//変化方向
		bool			m_vec;	// T:Up, F:Down


	public:
		ClrUtl ();
		ClrUtl ( const ClrUtl & rhs ) = delete;
		~ClrUtl ();

		//色取得
		DWORD RndColor () const;
		DWORD RotateColor ( DWORD color, DWORD delta );

		//色相遷移の計算
		//引数 ( c0:対象, c1:最大値, c2:最小値 )
		void CalcColor ( DWORD& c_trg, DWORD& c_max, DWORD& c_min, DWORD delta );

		void RTT_NXT ( CLR_RTT& clr_rtt ) const;

		//彩度固定ランダム
		DWORD SaturationRnd ( DWORD color ) const;

		//３種比較
		DWORD Max ( DWORD dw0, DWORD dw1, DWORD dw2 ) const;
		DWORD Min ( DWORD dw0, DWORD dw1, DWORD dw2 ) const;

		DWORD SetRGB ( DWORD r, DWORD g, DWORD b ) const
		{
			return 0xff000000 | r << 16 | g << 8 | b;
		}

		//Alphaのみ０にする
		_CLR Alpha0 ( _CLR clr ) { return _CLR ( clr.r, clr.g, clr.b, 0 ); }
	};


}	//namespace GAME


//=================================================================================================
//
// Rect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Rect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//ゼロで初期化する
	void ZeroRect ( RECT & rect )
	{
		rect.top = 0;
		rect.left = 0;
		rect.right = 0;
		rect.bottom = 0;
	}

	//空枠(すべて0)かどうか
	bool IsZeroRect ( const RECT & rect )
	{
		return ( rect.top == 0 ) && ( rect.bottom == 0 ) && ( rect.left == 0 ) && ( rect.right == 0 );
	}

	//矩形の値を設定する
	void SetRect ( RECT & rect, LONG left, LONG top, LONG right, LONG bottom )
	{
		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;
	}

	//矩形をrhsからlhsにコピーする
	void CopyRect ( RECT & lhs, const RECT & rhs )
	{
		lhs.left	= rhs.left;
		lhs.top		= rhs.top;
		lhs.right	= rhs.right;	
		lhs.bottom	= rhs.bottom;
	}

	//枠配列をゼロ初期化する
	void ZeroVecRect ( PV_RECT pvRect )
	{
		for ( RECT & rect : * pvRect ) { ZeroRect ( rect ); }
	}


	//-------------------------------------
	//重なり判定
	//点と矩形の重なり判定
	bool OverlapPoint ( const VEC2 & pt, const RECT & rect )
	{
		if ( rect.left <= pt.x && pt.x <= rect.right )
		{
			if ( rect.top <= pt.y && pt.y <= rect.bottom )
			{
				return T;
			}
		}
		return F;
	}


	//矩形２つで重なり判定
	bool OverlapRect ( const RECT & rect1, const RECT & rect2 )
	{
		LONG t1 = rect1.top;
		LONG l1 = rect1.left;
		LONG b1 = rect1.bottom;
		LONG r1 = rect1.right;
		LONG t2 = rect2.top;
		LONG l2 = rect2.left;
		LONG b2 = rect2.bottom;
		LONG r2 = rect2.right;

		//いずれかの大きさが０だったら判定しない
		if ( ( b1 - t1 ) == 0 || ( r1 - l1 ) == 0 || ( b2 - t2 ) == 0 || ( r2 - l2 ) == 0 ) { return false; }
		
		//上下と左右で重なり条件をすべて満たしていたらtrue
		return ( (t1 <= b2) && (b1 >= t2) && (l1 <= r2) && (r1 >= l2) );
	}

	//枠配列に行う重なり判定
	bool OverlapAryRect ( PV_RECT pvRect1, PV_RECT pvRect2 )
	{
		UINT i1 = 0;
		for ( RECT r1 : * pvRect1 )
		{
			if ( IsZeroRect ( r1 ) ) { continue; }
			UINT i2 = 0;
			for ( RECT r2 : * pvRect2 )
			{
				if ( IsZeroRect ( r2 ) ) { continue; }
				if ( OverlapRect ( r1, r2 ) ) { return true; }
			}
			++ i1;
		}
		return false;
	}


	//枠重なり部分の中心位置を取得
	VEC2 GetOverlayCenterRects ( const RECT & rect1, const RECT & rect2 )
	{
		//戻値
		VEC2 ret = VEC2 ( 0, 0 );
		
		//====================================================
		//横方向(x)

		//-------------------------------------------------------
		//				:     (l1 < l2)		:	(l2 < l1)		:
		//-------------------------------------------------------
		// (r1 < r2)	: [A] l1,l2,r1,r2	: [C] l2,l1,r1,r2	:
		//-------------------------------------------------------
		// (r2 < r1)	: [B] l1,l2,r2,r1	: [D] l2,l1,r2,r1	:
		//-------------------------------------------------------

		//[A] 【1〔2 】〕	//[C] 〔2【1 】〕
		//[B] 【1〔2 〕】	//[D] 〔2【1 〕】


		//重なり前提
		//[-] 【1】〔2〕
		//[-] 〔2〕【1】

		if ( rect1.left < rect2.left )
		{
			if ( rect1.right < rect2.right )
			{
				ret.x = rect2.left + ( rect1.right - rect2.left ) * 0.5f;	//[A]
			}
			else
			{
				ret.x = rect2.left + ( rect2.right - rect2.left ) * 0.5f;	//[B]
			}
		}
		else
		{
			if ( rect1.right < rect2.right )
			{
				ret.x = rect1.left + ( rect1.right - rect1.left ) * 0.5f;	//[D]
			}
			else
			{
				ret.x = rect1.left + ( rect2.right - rect1.left ) * 0.5f;	//[C]
			}
		}

		//====================================================
		//縦方向(y)
		if ( rect1.top < rect2.top )
		{
			if ( rect1.bottom < rect2.bottom )
			{
				ret.y = rect2.top + ( rect1.bottom - rect2.top ) * 0.5f;	//[A]
			}
			else
			{
				ret.y = rect2.top + ( rect2.bottom - rect2.top ) * 0.5f;	//[B]
			}
		}
		else
		{
			if ( rect1.bottom < rect2.bottom )
			{
				ret.y = rect1.top + ( rect1.bottom - rect1.top ) * 0.5f;	//[D]
			}
			else
			{
				ret.y = rect1.top + ( rect2.bottom - rect1.top ) * 0.5f;	//[C]
			}
		}

		return ret;
	}

	//枠配列に行う重なり判定(重なりの中心付き)
	bool OverlapAryRect_Center ( PV_RECT pvRect1, PV_RECT pvRect2, VEC2 & center )
	{
		UINT i1 = 0;
		for ( RECT r1 : * pvRect1 )
		{
			if ( IsZeroRect ( r1 ) ) { continue; }
			UINT i2 = 0;
			for ( RECT r2 : * pvRect2 )
			{
				if ( IsZeroRect ( r2 ) ) { continue; }
				if ( OverlapRect ( r1, r2 ) )
				{
					center = GetOverlayCenterRects ( r1, r2 );
					return true; 
				}
			}
		}
		return false;
	}


}	//namespace GAME


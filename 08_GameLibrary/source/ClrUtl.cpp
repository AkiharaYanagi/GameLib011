//=================================================================================================
//
//	カラーユーティリティ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ClrUtl.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	ClrUtl::ClrUtl ()
	{
		//ランダム値初期化
		srand ( timeGetTime () );
	}

	ClrUtl::~ClrUtl ()
	{
	}

	DWORD ClrUtl::RndColor () const
	{
		DWORD ret = 0x0;

		DWORD r = rand () % 256;
		DWORD g = rand () % 256;
		DWORD b = rand () % 256;

		ret = 0xff000000 | r << 16 | g << 8 | b;
//		DBGOUT_WND_F ( 1, _T ( "rgb = %0x %0x %0x, color = %x" ), r, g, b, ret );
		return ret;
	}

	//色相変更
	DWORD ClrUtl::RotateColor ( DWORD color, DWORD delta )
	{
		DWORD ret = 0x0;

		DWORD r = ( 0x00ff0000 & color ) >> 16;
		DWORD g = ( 0x0000ff00 & color ) >> 8;
		DWORD b = ( 0x000000ff & color );

#if 0
		/*rgb*/ if (r > g && g > b) { CalcColor ( r, g, b, delta ); }
		/*rbg*/ if (r > b && b > g) { CalcColor ( r, b, g, delta ); }
		/*grb*/ if (g > r && r > b) { CalcColor ( g, r, b, delta ); }
		/*gbr*/ if (g > b && b > r) { CalcColor ( g, b, r, delta ); }
		/*brg*/ if (b > r && r > g) { CalcColor ( b, r, g, delta ); }
		/*bgr*/ if (b > g && g > r) { CalcColor ( b, g, r, delta ); }
#endif // 0
		switch (m_clrRtt)
		{
		case R_UP: CalcColor ( r, g, b, delta ); break;	//0->3
		case R_DN: CalcColor ( r, b, g, delta ); break;	//1->2
		case G_UP: CalcColor ( g, b, r, delta ); break;	//2->5
		case G_DN: CalcColor ( g, r, b, delta ); break;	//3->4
		case B_UP: CalcColor ( b, r, g, delta ); break;	//4->1
		case B_DN: CalcColor ( b, g, r, delta ); break;	//5->0
		}

		ret = SetRGB ( r, g, b );
//		DBGOUT_WND_F ( 1, _T ( "rgb = %0x %0x %0x, color = %x" ), r, g, b, color );
//		DBGOUT_WND_F ( 2, _T ( "rgb = %0d %0d %0d, color = %x" ), r, g, b, color );

		return ret;
	}

	void ClrUtl::CalcColor ( DWORD& c_trg, DWORD& c_max, DWORD& c_min, DWORD delta )
	{
		if (m_vec)	//増加時
		{
			if (c_trg + delta < c_max)	//単純増加
			{
				c_trg += delta;
			}
			else //折返し
			{
				int d = delta - ( c_max - c_trg );
				c_trg = c_max;
				c_max -= d;
				RTT_NXT ( m_clrRtt );
				m_vec = F;
			}
		}
		else //減少時
		{
			if (c_trg > c_min + delta) //単純減少
			{
				c_trg -= delta;
			}
			else //折返し
			{
				int d = delta - ( c_trg - c_min );
				c_trg = c_min;
				c_min += d;
				RTT_NXT ( m_clrRtt );
				m_vec = T;
			}
		}

	}

	void ClrUtl::RTT_NXT ( CLR_RTT& clr_rtt ) const
	{
		switch (clr_rtt)
		{
		case R_UP: clr_rtt = G_DN; break;	//0->3
		case R_DN: clr_rtt = G_UP; break;	//1->2
		case G_UP: clr_rtt = B_DN; break;	//2->5
		case G_DN: clr_rtt = B_UP; break;	//3->4
		case B_UP: clr_rtt = R_DN; break;	//4->1
		case B_DN: clr_rtt = R_UP; break;	//5->0
		}
	}


	DWORD ClrUtl::SaturationRnd ( DWORD color ) const
	{
		DWORD r = ( 0x00ff0000 & color ) >> 16;
		DWORD g = ( 0x0000ff00 & color ) >> 8;
		DWORD b = ( 0x000000ff & color );

		//最大値と最小値は固定で、中間値をその間のいずれかにする
		DWORD max = Max ( r, g, b );
		DWORD min = Min ( r, g, b );
		DWORD med = min + ( rand () % ( max - min ) );	//median

		DWORD ret = 0x0;
		switch (rand () % 6)
		{
		case 0: ret = SetRGB ( max, min, med ); break;
		case 1: ret = SetRGB ( max, med, min ); break;
		case 2: ret = SetRGB ( min, max, med ); break;
		case 3: ret = SetRGB ( min, med, max ); break;
		case 4: ret = SetRGB ( med, max, min ); break;
		case 5: ret = SetRGB ( med, min, max ); break;
		}

//		DBGOUT_WND_F ( 2, _T ( "rgb = %0d %0d %0d, color = %x" ), r, g, b, ret );
		return ret;
	}

	DWORD ClrUtl::Max ( DWORD dw0, DWORD dw1, DWORD dw2 ) const
	{
		if (dw0 > dw1)
		{
			if (dw0 > dw2) { return dw0; }
			else { return dw2; }
		}
		else
		{
			if (dw1 > dw2) { return dw1; }
			else { return dw2; }
		}
		return dw0;
	}
	DWORD ClrUtl::Min ( DWORD dw0, DWORD dw1, DWORD dw2 ) const
	{
		if (dw0 < dw1)
		{
			if (dw0 < dw2) { return dw0; }
			else { return dw2; }
		}
		else
		{
			if (dw1 < dw2) { return dw1; }
			else { return dw2; }
		}
		return dw0;
	}


}	//namespace GAME


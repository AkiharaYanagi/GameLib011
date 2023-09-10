//=================================================================================================
//
//	文字列ユーティリティ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "STR_UTL.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//文字列サイズの取得
	UINT STR_UTL::Size ( LPCTSTR lpctstr )
	{
		UINT ret = 0;
		TCHAR t = *lpctstr;

		try
		{
			while ( t != '\0' )
			{
				t = *( lpctstr + ( ret ++ ) );
			}
		}
		catch ( ... )
		{
			return 0;
		}

		return ret;
	}

	//テクスチャ用
	//2のべき乗補完 ( 1 〜 65536 )
	LONG STR_UTL::Power ( LONG ln )
	{
		const long LMT = 65536;
		long pw = 2;
		while ( pw <= LMT )
		{
			if ( ln <= pw ) { return pw; }
			pw *= 2;
		}
		return 1;	//範囲外は１
	}


}	//namespace GAME


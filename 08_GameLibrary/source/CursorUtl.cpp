//=================================================================================================
//
//	カーソルユーティリティ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CursorUtl.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//カーソル位置を取得
	POINT CursorUtl::GetCursor () { POINT p; ::GetCursorPos ( & p ); return p; }

	//カーソルのクライアント位置を取得
	POINT CursorUtl::GetCursorCltPos ()
	{
		POINT p;
		GetCursorPos ( & p );
		::ScreenToClient ( HWnd::Get (), & p );
		return p;
	};

	//カーソル位置にウィンドウサイズ補正をかける
	POINT CursorUtl::GetWndRev ()
	{
		POINT pt = GetCursorCltPos ();
		UINT window_w = AppSettingFile::Inst ()->GetWindowW ();
		UINT window_h = AppSettingFile::Inst ()->GetWindowH ();
		pt.x = (LONG)( 1.f * pt.x * GAME_WINDOW_WIDTH / window_w );
		pt.y = (LONG)( 1.f * pt.y * GAME_WINDOW_HEIGHT / window_h );
		return pt;
	}

	//RECTと位置判定
	bool CursorUtl::IsHover ( RECT rect )
	{
		POINT pt = { 0, 0 };
		
		//フルスクリーン時は直接カーソル位置を参照
		if ( AppSettingFile::Inst ()->GetbFullscreen () )
		{
//			::GetCursorPos ( & pt );
			pt = GetCursorCltPos ();
		}
		else
		{
			pt = GetWndRev ();
		}


		if ( rect.left <= pt.x && pt.x < rect.right )
		{
			if ( rect.top <= pt.y && pt.y < rect.bottom )
			{
				return true;
			}
		}
		return false;
	}

	bool CursorUtl::IsHover ( VEC2 pos, POINT size )
	{
		LONG bx = (LONG)pos.x;
		LONG bw = (LONG)size.x;
		LONG by = (LONG)pos.y;
		LONG bh = (LONG)size.y;
		RECT rect = { bx, by, bx + bw, by + bh };
		return IsHover ( rect );
	}

	bool CursorUtl::IsHover ( VEC2 pos, VEC2 size )
	{
		return IsHover ( pos.x, pos.y, size.x, size.y );
	}

	bool CursorUtl::IsHover ( float x, float y, float w, float h )
	{
		LONG bx = (LONG)x;
		LONG bw = (LONG)w;
		LONG by = (LONG)y;
		LONG bh = (LONG)h;
		RECT rect = { bx, by, bx + bw, by + bh };
		return IsHover ( rect );
	}

}	//namespace GAME


//=================================================================================================
//
//	カーソルユーティリティ
//		GameLibConst.h
//		ゲームサイズ( GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT )を基準として、
//		表示サイズを補正してカーソルの位置を計算する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameWindowLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CursorUtl
	{
		CursorUtl () = delete;	//staticクラスとして実体化禁止
	public:
		CursorUtl ( const CursorUtl & rhs ) = delete;
		~CursorUtl () = delete;

		//カーソル位置を取得
		static POINT GetCursor ();

		//カーソルのクライアント位置を取得
		static POINT GetCursorCltPos ();

		//カーソル位置にウィンドウサイズ補正をかける
		static POINT GetWndRev ();
		
		//RECTと位置判定
		static bool IsHover ( RECT rect );
		static bool IsHover ( VEC2 pos, POINT size );
		static bool IsHover ( VEC2 pos, VEC2 size );
		static bool IsHover ( float x, float y, float w, float h );
	};


}	//namespace GAME


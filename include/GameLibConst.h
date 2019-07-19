//=================================================================================================
//
// GameLibConst ファイル
//		ライブラリ内共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
#include <iostream>
#include <tchar.h>

//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------
	
	//ウィンドウサイズ
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 960;

	//プレイヤーID
	enum PLAYER_ID
	{
		PLAYER_ID_1 = 1,
		PLAYER_ID_2 = 2,
		_PLAYER_NUM,	//人数
	};

	//プレイヤ種類
	enum PLAYER_MODE
	{
		MODE_PLAYER,
		MODE_CPU,
		MODE_NETWORK,
	};

	//描画Z位置
	constexpr float Z_BG  = 0.1f;
	constexpr float Z_EFB = 0.6f;
	constexpr float Z_CH  = 0.6f;
	constexpr float Z_EFF = 0.6f;
	constexpr float Z_SYS = 0.6f;

}


//=================================================================================================
//
// GameConst ファイル
//		ゲーム内共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------
	
	//キャラ名
	enum CHARA_NAME
	{
		CHARA_SONIA,
		CHARA_ORFLOAT,
		CHARA_NAME_NUM,
	};

	//入力
	enum COMMAND
	{
		NO_COMPLETE = 0xFFFFFFFF
	};

	//キャラ定数
	enum CONST_CHARA
	{
		NUM_RECT = 8,	//判定枠配列の保持サイズ
	};

	//枠表示(色)
	enum RECT_COLOR
	{
		RECT_COLOR_C = 0x400000ff,
		RECT_COLOR_A = 0x40ff0000,
		RECT_COLOR_H = 0x4000ff00,
		RECT_COLOR_O = 0x40ffff00,
	};

	//割合
	enum PERCENTAGE
	{
		CENT = 100,
	};

	//CPU_INPUT
	enum CPU_INPUT
	{
		CPU_INPUT_GAMEKEY_NUM = 20,
	};
	
	//基本アクション 列挙型定義
	enum BASIC_ACTION
	{
		BA_STAND, BA_POISED, BA_CLANG, BA_AVOID, BA_DOTTY, BA_DAMAGED, BA_DOWN, BA_WIN,
		BASIC_ACTION_NUM,
	};

	//アクション属性
	enum ACTION_CATEGORY 
	{
		AC_STAND, AC_MOVE, AC_DASH, AC_ATTACK_L, AC_ATTACK_M, AC_ATTACK_H, 
		AC_POISED, AC_CLANG, AC_AVOID, AC_DOTTY, AC_DAMAGED, AC_DEMO, AC_OTHER, 
		ACTION_CATEGORY_NUM
	};

	//打合結果 (左右)
	enum CLANG_DECISION_LR
	{
		CD_EQUAL,
		CD_LEFT,
		CD_RIGHT,
		CD_OFF, 
	};

	//打合結果 (勝負)
	enum CLANG_DECISION_WL
	{
		CD_DRAW,
		CD_WIN,
		CD_LOSE,
	};

	//初期位置
	enum PLAYER_BASE_PT
	{
		GAME_WIDTH = 2048,
		GAME_HEIGHT = 1024,

		BG_SIZE_X = 2048,
		BG_SIZE_Y = 1024,
		BG_POS_X = 0 - ( 2048 - 1280 ) / 2,
		BG_POS_Y = 0 - ( 1024 - 960 ) / 2,

		PLAYER_BASE_Y = 750,

		PLAYER_1_BASE_X = GAME_WIDTH / 2 - WINDOW_WIDTH / 2 + 200,
		PLAYER_1_BASE_Y = 750,
		PLAYER_2_BASE_X = GAME_WIDTH / 2 + WINDOW_WIDTH / 2 - 200,
		PLAYER_2_BASE_Y = 750,

		GRP_PLAYER1_X = 0,
		GRP_PLAYER1_Y = 14,
		GRP_PLAYER2_X = WINDOW_WIDTH - 64 -0,
		GRP_PLAYER2_Y = 14,

		GAUGE_WIDTH = 480,
		GAUGE_HEIGHT = 40,
		LIFE_GAUGE_X = 100,
		LIFE_GAUGE_Y = 40,

		FIELD_BASE_X = 0,
		FIELD_WIDTH = 2048,
		FIELD_EDGE = 64,

		LIFE_MAX = 1000,

		HITSTOP_TIME = 15,
	};

}


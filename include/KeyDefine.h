//=================================================================================================
//
//	入力キー定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//プレイヤごとの入力
	enum _PLAYER_INPUT
	{
		PLY_UP,
		PLY_DOWN,
		PLY_LEFT,
		PLY_RIGHT,
		PLY_BTN0,
		PLY_BTN1,
		PLY_BTN2,
		PLY_BTN3,
		PLY_BTN4,
		PLY_BTN5,
		PLY_BTN6,
		PLY_BTN7,
		PLY_INPUT_NUM
	};

	//ゲーム使用キー
	enum GAME_USE_KEY
	{
		_P1_UP,
		_P1_DOWN,
		_P1_LEFT,
		_P1_RIGHT,
		_P1_BTN0,
		_P1_BTN1,
		_P1_BTN2,
		_P1_BTN3,
		_P1_BTN4,
		_P1_BTN5,
		_P1_BTN6,
		_P1_BTN7,

		_P2_UP,
		_P2_DOWN,
		_P2_LEFT,
		_P2_RIGHT,
		_P2_BTN0,
		_P2_BTN1,
		_P2_BTN2,
		_P2_BTN3,
		_P2_BTN4,
		_P2_BTN5,
		_P2_BTN6,
		_P2_BTN7,

		GAME_USE_KEY_NUM,	//ゲーム使用キーの数
	};


	//デバイス種類
	enum _GAME_DEVICE_TYPE
	{
		_KEYBOARD,
		_JOYSTICK,
		_MOUSE, 
		_NODEVICE,
	};


	//ジョイスティック内の入力種類
	enum JOY_INPUT_TYPE
	{
		JIT_AXIS,
		JIT_POINT_OF_VIEW,
		JIT_BUTTON,
		JIT_NO_DATA,
	};


	//レバー
	enum LEVER
	{
		LVR_UP,
		LVR_DOWN,
		LVR_LEFT,
		LVR_RIGHT,
	};


}	//namespace GAME


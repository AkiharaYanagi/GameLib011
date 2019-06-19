//-------------------------------------------------------------------------------------------------
//	キーコンフィグ設定ファイル利用クラス
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "DxInput.h"
#include <fstream>

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//プレイヤごとの使用キー
	enum INPUT
	{
		UP, 
		DOWN, 
		LEFT, 
		RIGHT, 
		BUTTON1, 
		BUTTON2, 
		BUTTON3, 
		BUTTON4,
		INPUT_NUM
	};

	//ゲーム使用キー
	enum KEY_NAME
	{
		P1_UP, 
		P1_DOWN, 
		P1_LEFT, 
		P1_RIGHT, 
		P1_BUTTON1, 
		P1_BUTTON2, 
		P1_BUTTON3, 
		P1_BUTTON4, 

		P2_UP, 
		P2_DOWN, 
		P2_LEFT, 
		P2_RIGHT, 
		P2_BUTTON1, 
		P2_BUTTON2, 
		P2_BUTTON3, 
		P2_BUTTON4, 

		KEY_NAME_NUM,	//ゲーム使用キーの数
	};

	//プレイヤと入力
	static const KEY_NAME	PL_IP_KEY [ _PLAYER_NUM ][ INPUT_NUM ] = 
	{
		  { P1_UP, P1_DOWN, P1_LEFT, P1_RIGHT, P1_BUTTON1, P1_BUTTON2, P1_BUTTON3, P1_BUTTON4, }
		, { P2_UP, P2_DOWN, P2_LEFT, P2_RIGHT, P2_BUTTON1, P2_BUTTON2, P2_BUTTON3, P2_BUTTON4, }
	};

	//デバイスキー
	enum GAME_DEVICE_TYPE
	{
		KEYBOARD,
		JOYSTICK,
		NODEVICE,
	};

	//キー設定
	struct KEY_CONFIG
	{
		GAME_DEVICE_TYPE	m_type;		//デバイスの種類
		int					m_num;		//デバイス番号
		int					m_key;		//キー番号
	};

	enum JOYSTICK_KEY
	{
        NUM_JOYSTICK_BUTTON = 128,					 //ジョイスティックのボタンの数
        JOYSTICK_UP = NUM_JOYSTICK_BUTTON + 1,       //レバー上
        JOYSTICK_DOWN = NUM_JOYSTICK_BUTTON + 2,     //レバー下
        JOYSTICK_LEFT = NUM_JOYSTICK_BUTTON + 3,     //レバー左
        JOYSTICK_RIGHT = NUM_JOYSTICK_BUTTON + 4,    //レバー右
        JOYSTICK_NEUTRAL = NUM_JOYSTICK_BUTTON + 5,    //未入力
	};


	//キー入力
	class KeyInput
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_KeyInput = unique_ptr < KeyInput >;
		static P_KeyInput		m_inst;
		KeyInput();
		KeyInput( const KeyInput& rhs );
	public:
		~KeyInput();
		static void Create () { if ( ! m_inst ) { m_inst = P_KeyInput ( new KeyInput () ); } }
		static P_KeyInput & instance () { return m_inst; }
	//--------------------------------------------------

	private:
		//キーコンフィグデータ
		struct KEY_CONFIG		m_keyconfig[KEY_NAME_NUM];

	public:
		void Reset();	//再設定
		void Load();	//データの読込
		void Update();	//更新

		//ゲームキー
		bool IsKey ( KEY_NAME key );		//押した状態かどうか(このフレームのみ)
		bool OffKey ( KEY_NAME key )		//離した状態かどうか(このフレームのみ)
		{ return ( ! IsKey ( key ) ); }

		bool PushKey ( KEY_NAME key );		//押した瞬間かどうか(前回off 今回on)
		bool ReleaseKey ( KEY_NAME key );	//離した瞬間かどうか(前回on 今回off)

	};
	
//シングルトンアクセス用
#define KEY_INPUT KeyInput::instance()
#define IS_KEY KeyInput::instance()->IsKey 
#define OFF_KEY KeyInput::instance()->OffKey 
#define PUSH_KEY KeyInput::instance()->PushKey 
#define RELE_KEY KeyInput::instance()->ReleaseKey 

}


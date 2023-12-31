//=================================================================================================
//
//	デバイスインプット
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "DxInput.h"
#include "KeyDefine.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-----------------------------------------------------------
	//ジョイスティックの入力定義
	class JoystickInput
	{
		DWORD		m_joystickID;		//ジョイスティックID
		JOY_INPUT_TYPE		m_type;		//入力種類
		DWORD		m_buttonID;		//ボタン
		LEVER		m_lever;		//レバー

	public:
		JoystickInput ();
		JoystickInput ( const JoystickInput & rhs )	//コピー可能
		{
			m_joystickID = rhs.m_joystickID;
			m_type = rhs.m_type;
			m_buttonID = rhs.m_buttonID;
			m_lever = rhs.m_lever;
		}
		~JoystickInput () {}

		void Set ( DWORD joy_id, JOY_INPUT_TYPE type, DWORD btn_id, LEVER lvr );
		DWORD GetID () const { return m_joystickID; }
		JOY_INPUT_TYPE GetInputType () const { return m_type; }
		DWORD GetButtonID () const { return m_buttonID; }
		LEVER GetLever () const { return m_lever; }
	};



	//-----------------------------------------------------------
	//ゲーム内におけるデバイスの入力定義
	class DeviceInput
	{
		//デバイスタイプ
		_GAME_DEVICE_TYPE	m_dvc_type;

		//各デバイス入力
		DWORD				m_keyboardInput;	//キーボード
		JoystickInput		m_joystickInput;	//ジョイスティック

	public:
		DeviceInput ();
		DeviceInput ( const DeviceInput & rhs );	//コピー可能
		~DeviceInput ();

		void SetKey ( _GAME_DEVICE_TYPE	dvc_type, DWORD key );
		void SetJoy ( JoystickInput ji );

		_GAME_DEVICE_TYPE GetType () const { return m_dvc_type; }
		DWORD GetKey () const { return m_keyboardInput; }
		JoystickInput GetJoy () const { return m_joystickInput; }
	};




}	//namespace GAME


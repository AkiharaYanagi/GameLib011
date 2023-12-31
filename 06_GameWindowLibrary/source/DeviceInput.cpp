//=================================================================================================
//
//	デバイスインプット
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DeviceInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-----------------------------------------------------------
	JoystickInput::JoystickInput ()
		: m_joystickID ( 0 ), m_type ( JOY_INPUT_TYPE::JIT_AXIS ), m_buttonID ( 0 ), m_lever ( LEVER::LVR_UP )
	{
	}

	void JoystickInput::Set ( DWORD joy_id, JOY_INPUT_TYPE type, DWORD btn_id, LEVER lvr )
	{
		m_joystickID = joy_id;
		m_type = type;
		m_buttonID = btn_id;
		m_lever = lvr;
	}

	//-----------------------------------------------------------
	DeviceInput::DeviceInput ()
		: m_dvc_type ( _GAME_DEVICE_TYPE::_NODEVICE ), m_keyboardInput ( DIK_Z )
	{
	}

	DeviceInput::DeviceInput ( const DeviceInput & rhs )
	{
		m_dvc_type = rhs.m_dvc_type;
		m_keyboardInput = rhs.m_keyboardInput;
		m_joystickInput = rhs.m_joystickInput;
	}

	DeviceInput::~DeviceInput ()
	{
	}

	void DeviceInput::SetKey ( _GAME_DEVICE_TYPE dvc_type, DWORD key )
	{
		m_dvc_type = dvc_type;
		m_keyboardInput = key;
	}

	void DeviceInput::SetJoy ( JoystickInput ji )
	{
		m_dvc_type = _GAME_DEVICE_TYPE::_JOYSTICK;
		m_joystickInput = ji;
	}



}	//namespace GAME


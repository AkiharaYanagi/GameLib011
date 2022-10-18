//=================================================================================================
//
//	キーコンフィグ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "KeyConfig.h"
#include "DeviceInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	//	シングルトン　インスタンス
	KeyConfig::P_KeyConfig		KeyConfig::m_inst;

	KeyConfig::KeyConfig ()
	{
		m_deviceInput [ _P1_UP		 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_UP );
		m_deviceInput [ _P1_DOWN	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_DOWN );
		m_deviceInput [ _P1_LEFT	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_LEFT );
		m_deviceInput [ _P1_RIGHT	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_RIGHT );
		m_deviceInput [ _P1_BTN0	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_A );
		m_deviceInput [ _P1_BTN1	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_S );
		m_deviceInput [ _P1_BTN2	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_D );
		m_deviceInput [ _P1_BTN3	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_F );
		m_deviceInput [ _P1_BTN4	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_COMMA );
		m_deviceInput [ _P1_BTN5	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_PERIOD );
		m_deviceInput [ _P1_BTN6	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_SLASH );
		m_deviceInput [ _P1_BTN7	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_BACKSLASH );

		m_deviceInput [ _P2_UP		 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_HOME );
		m_deviceInput [ _P2_DOWN	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_END );
		m_deviceInput [ _P2_LEFT	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_DELETE );
		m_deviceInput [ _P2_RIGHT	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_PGUP );
		m_deviceInput [ _P2_BTN0	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_A );
		m_deviceInput [ _P2_BTN1	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_S );
		m_deviceInput [ _P2_BTN2	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_D );
		m_deviceInput [ _P2_BTN3	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_F );
		m_deviceInput [ _P2_BTN4	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_L );
		m_deviceInput [ _P2_BTN5	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_SEMICOLON );
		m_deviceInput [ _P2_BTN6	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_COLON );
		m_deviceInput [ _P2_BTN7	 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_RBRACKET );
	}

	KeyConfig::~KeyConfig ()
	{
	}
	//------------------------------------------


	void KeyConfig::Load ()
	{
		//設定ファイル読込
		fstream fs ( _T ( "keyConfig.dat" ), ios::in, ios::binary );

		//エラーのとき
		if ( fs.fail () )
		{
			//新規ファイルの作成

			return;
		}

		//test union

		union 
		{
			uint32_t	b4;
			uint16_t	b2 [ 2 ];
			uint8_t		b1 [ 4 ];
		} bytes;

		bytes.b4 = 0x12345678;




		//各キーに対して対応デバイス入力を読込
		for ( int i = 0; i < GAME_USE_KEY_NUM; ++ i )
		{
			DeviceInput di;

			const size_t BUF_SIZE = 4;
			char buf [ BUF_SIZE ];
			fs.read ( buf, BUF_SIZE );
			_GAME_DEVICE_TYPE type = (_GAME_DEVICE_TYPE)*buf;

			DWORD key = 0;
			DWORD joystickID = 0;
			JOY_INPUT_TYPE joytype = JOY_INPUT_TYPE::JIT_AXIS;
			DWORD buttonID = 0;
			LEVER lvr = LEVER::LVR_UP;

			JoystickInput ji;

			switch ( type )
			{
			case _KEYBOARD:
				int i;
				fs.read ( (char*)&i, BUF_SIZE );
				key = i;
				di.SetKey ( _KEYBOARD, key );
			break;

			case _JOYSTICK:
				fs.read ( buf, BUF_SIZE );
				joystickID = (DWORD)buf;
				fs.read ( buf, BUF_SIZE );
				joytype = (JOY_INPUT_TYPE)(int)buf;
				fs.read ( buf, BUF_SIZE );
				buttonID = (DWORD)buf;
				fs.read ( buf, BUF_SIZE );
				lvr = (LEVER)(int)buf;

				ji.Set ( joystickID, joytype, buttonID, lvr );
				di.SetJoy ( ji );
			break;
			}

			m_deviceInput [ i ] = di;	//代入OK
		}
	}

	bool KeyConfig::IsKey ( GAME_USE_KEY key ) const
	{
		bool ret = false;
		DeviceInput di = m_deviceInput [ key ];

		_GAME_DEVICE_TYPE type = di.GetType ();
		switch ( type )
		{
		case _JOYSTICK: ret = IsJoy ( di.GetJoy () ); break;
		case _KEYBOARD: ret = IsKeyboard ( di.GetKey () ); break;
		}
		return ret;
	}


	bool KeyConfig::IsJoy ( JoystickInput ji ) const
	{
		DWORD id = ji.GetID ();
		JOY_INPUT_TYPE type = ji.GetInputType ();
		switch ( type )
		{
		case JIT_AXIS:
		break;

		case JIT_POINT_OF_VIEW:
			return DxInput::instance ()->IsPovUp ( id );
			break;

		case JIT_BUTTON:
			break;
		}
		return false;
	}

	bool KeyConfig::IsKeyboard ( DWORD key ) const
	{
		return DxInput::instance ()->IsOneKeyboard ( key );
	}


}	//namespace GAME


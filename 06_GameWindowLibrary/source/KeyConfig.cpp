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
		SetInitial ();
	}

	KeyConfig::~KeyConfig ()
	{
	}
	//------------------------------------------


	void KeyConfig::Load ()
	{
		//設定ファイル読込
		std::fstream fs ( _T("keyConfig.dat"), std::ios::in, std::ios::binary );

		//エラーのとき
		if ( fs.fail () )
		{
			//新規ファイルの作成
			SetInitial ();
			Save ();
			return;
		}

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
				joystickID = (DWORD)*buf;
				fs.read ( buf, BUF_SIZE );
				joytype = (JOY_INPUT_TYPE)(int)*buf;
				fs.read ( buf, BUF_SIZE );
				buttonID = (DWORD)*buf;
				fs.read ( buf, BUF_SIZE );
				lvr = (LEVER)(int)*buf;

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
		case _KEYBOARD: ret = Is_Keyboard ( di.GetKey () ); break;
		}
		return ret;
	}

	bool KeyConfig::OffKey ( GAME_USE_KEY key ) const
	{
		return ! IsKey ( key );
	}

	bool KeyConfig::PushKey ( GAME_USE_KEY key ) const
	{
		bool ret = false;
		DeviceInput di = m_deviceInput [ key ];

		_GAME_DEVICE_TYPE type = di.GetType ();
		switch ( type )
		{
		case _JOYSTICK: ret = PushJoy ( di.GetJoy () ); break;
		case _KEYBOARD: ret = Push_Keyboard ( di.GetKey () ); break;
		}
		return ret;
	}

	bool KeyConfig::ReleKey ( GAME_USE_KEY key ) const
	{
		bool ret = false;
		return ret;
	}


	//----------------------------------------------------------------------------------
	//初期化
	void KeyConfig::SetInitial ()
	{
		m_deviceInput [ _P1_UP ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_UP );
		m_deviceInput [ _P1_DOWN ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_DOWN );
		m_deviceInput [ _P1_LEFT ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_LEFT );
		m_deviceInput [ _P1_RIGHT ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_RIGHT );
		m_deviceInput [ _P1_BTN0 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_A );
		m_deviceInput [ _P1_BTN1 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_S );
		m_deviceInput [ _P1_BTN2 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_D );
		m_deviceInput [ _P1_BTN3 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_F );
		m_deviceInput [ _P1_BTN4 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_COMMA );
		m_deviceInput [ _P1_BTN5 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_PERIOD );
		m_deviceInput [ _P1_BTN6 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_SLASH );
		m_deviceInput [ _P1_BTN7 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_BACKSLASH );

		m_deviceInput [ _P2_UP ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_HOME );
		m_deviceInput [ _P2_DOWN ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_END );
		m_deviceInput [ _P2_LEFT ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_DELETE );
		m_deviceInput [ _P2_RIGHT ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_PGUP );
		m_deviceInput [ _P2_BTN0 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_A );
		m_deviceInput [ _P2_BTN1 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_S );
		m_deviceInput [ _P2_BTN2 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_D );
		m_deviceInput [ _P2_BTN3 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_F );
		m_deviceInput [ _P2_BTN4 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_L );
		m_deviceInput [ _P2_BTN5 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_SEMICOLON );
		m_deviceInput [ _P2_BTN6 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_COLON );
		m_deviceInput [ _P2_BTN7 ].SetKey ( _GAME_DEVICE_TYPE::_KEYBOARD, DIK_RBRACKET );
	}

	void KeyConfig::Save ()
	{
		std::fstream fs ( _T ( "keyConfig.dat" ), std::ios::out, std::ios::binary );
			 
		for ( int i = 0; i < GAME_USE_KEY_NUM; ++ i )
		{
			DeviceInput di = m_deviceInput [ i ];
			_GAME_DEVICE_TYPE type = di.GetType ();
			fs.write ( (char*)type, sizeof (_GAME_DEVICE_TYPE) );

			switch ( type )
			{
			case _KEYBOARD:
				fs.write ( (char*)di.GetKey (), sizeof ( DWORD ) );
			break;
	
			case _JOYSTICK:
				JoystickInput ji = di.GetJoy ();
				DWORD id = ji.GetID ();
				fs.write ( (char*)id, sizeof ( DWORD ) );
				JOY_INPUT_TYPE joytype = ji.GetInputType ();
				fs.write ( (char*)joytype, sizeof ( JOY_INPUT_TYPE ) );
				DWORD btn = ji.GetButtonID ();
				fs.write ( (char*)btn, sizeof ( DWORD ) );
				LEVER lvr = ji.GetLever ();
				fs.write ( (char*)lvr, sizeof ( LEVER ) );
				break;
			}
		}
	}


	//----------------------------------------------------------------------------------
	//押された状態かどうか
	bool KeyConfig::IsJoy ( JoystickInput ji ) const
	{
		DWORD id = ji.GetID ();
		JOY_INPUT_TYPE type = ji.GetInputType ();
		switch ( type )
		{
		case JIT_AXIS: return Is_Axis_Lvr ( id, ji.GetLever () ); break;
		case JIT_POINT_OF_VIEW: return Is_POV_Lvr ( id, ji.GetLever () ); break;
		case JIT_BUTTON: return DXINP->IsJoyButton ( id, ji.GetButtonID () ); break;
		}
		return false;
	}

	bool KeyConfig::Is_Axis_Lvr ( DWORD ID, LEVER lvr ) const
	{
		bool ret = false;
		switch ( lvr )
		{
		case LEVER::LVR_UP:		ret = DXINP->IsAxisUp ( ID );		break;
		case LEVER::LVR_DOWN:	ret = DXINP->IsAxisDown ( ID );		break;
		case LEVER::LVR_LEFT:	ret = DXINP->IsAxisLeft ( ID );		break;
		case LEVER::LVR_RIGHT:	ret = DXINP->IsAxisRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Is_POV_Lvr ( DWORD ID, LEVER lvr ) const
	{
		bool ret = false;
		switch ( lvr )
		{
		case LEVER::LVR_UP:		ret = DXINP->IsPovUp ( ID );	break;
		case LEVER::LVR_DOWN:	ret = DXINP->IsPovDown ( ID );	break;
		case LEVER::LVR_LEFT:	ret = DXINP->IsPovLeft ( ID );	break;
		case LEVER::LVR_RIGHT:	ret = DXINP->IsPovRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Is_Keyboard ( DWORD key ) const
	{
		return DxInput::instance ()->IsOneKeyboard ( key );
	}

	//----------------------------------------------------------------------------------
	//押された瞬間かどうか
	bool KeyConfig::PushJoy ( JoystickInput ji ) const
	{
		DWORD id = ji.GetID ();
		JOY_INPUT_TYPE type = ji.GetInputType ();
		switch ( type )
		{
		case JIT_AXIS: return Push_Axis_Lvr ( id, ji.GetLever () ); break;
		case JIT_POINT_OF_VIEW: return Push_POV_Lvr ( id, ji.GetLever () ); break;
		case JIT_BUTTON: return DXINP->PushJoyButton ( id, ji.GetButtonID () ); break;
		}
		return false;
	}

	bool KeyConfig::Push_Axis_Lvr ( DWORD ID, LEVER lvr ) const
	{
		bool ret = false;
		switch ( lvr )
		{
		case LEVER::LVR_UP:		ret = DXINP->PushAxisUp ( ID );		break;
		case LEVER::LVR_DOWN:	ret = DXINP->PushAxisDown ( ID );		break;
		case LEVER::LVR_LEFT:	ret = DXINP->PushAxisLeft ( ID );		break;
		case LEVER::LVR_RIGHT:	ret = DXINP->PushAxisRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Push_POV_Lvr ( DWORD ID, LEVER lvr ) const
	{
		bool ret = false;
		switch ( lvr )
		{
		case LEVER::LVR_UP:		ret = DXINP->PushPovUp ( ID );	break;
		case LEVER::LVR_DOWN:	ret = DXINP->PushPovDown ( ID );	break;
		case LEVER::LVR_LEFT:	ret = DXINP->PushPovLeft ( ID );	break;
		case LEVER::LVR_RIGHT:	ret = DXINP->PushPovRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Push_Keyboard ( DWORD key ) const
	{
		return DxInput::instance ()->PushOneKeyboard ( key );
	}

	//----------------------------------------------------------------------------------


}	//namespace GAME


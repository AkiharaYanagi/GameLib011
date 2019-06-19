//=================================================================================================
//
// キーコンフィグ利用クラス　ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "KeyInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------------------------------------------------------------------
	//	定数
	//-------------------------------------------------------------------------------------------------

	//キーコンフィグ 設定ファイルにおけるデフォルトのバイナリデータ
	//[1P] : Pad0_UP, Pad0_DOWN, Pad0_LEFT, Pad0_RIGHT, Pad0_key3, Pad0_key4, Pad0_key1, Pad0_key0, 
	//[2P] : Home, End, Delete, PageDown, A, S, D, F,
	const unsigned char data[] =
	{
		0x01, 0x00, 0x81, 0x01, 0x00, 0x82, 0x01, 0x00, 0x83, 0x01, 0x00, 0x84, 0x01, 0x00, 0x03, 0x01,
		0x00, 0x04, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0xC7, 0x00, 0xCF, 0x00, 0xD3, 0x00, 0xD1,
		0x00, 0x1E, 0x00, 0x1F, 0x00, 0x20, 0x00, 0x21, 0x02,
	};

	//------------------------------------------
	//	Static実体
	//------------------------------------------
	//	シングルトン　インスタンス
	KeyInput::P_KeyInput	KeyInput::m_inst;

	//-------------------------------------------------------------------------------------------------

	//コンストラクタ
	KeyInput::KeyInput()
	{
		//DirectInput(キーボード、ジョイスティックの利用)
		DxInput::Create();
		Load();
	}
	
	//デストラクタ
	KeyInput::~KeyInput()
	{
		DxInput::Destroy();
	}

	//再設定
	void KeyInput::Reset()
	{
		if ( DxInput::instance() )
		{
			DxInput::instance()->Reset();
		}
	}

	//ファイル読込
	void KeyInput::Load()
	{
		std::fstream fstrm( TEXT("keyconfig.dat"), std::ios::in, std::ios::binary );

		if ( fstrm.fail() )
		{
			//新規ファイルの作成
			std::fstream f ( "keyconfig.dat", std::ios::out, std::ios::binary );
			if ( ! f.fail () )
			{
				for ( UINT i = 0; i < sizeof ( data ); i++ )
				{
					f.write ( (char*)&data[i], sizeof ( unsigned char ) );
				}
			}
			f.close ();
			Load ();
			fstrm.close ();
			return;
		}

		//バイナリ読込
		for ( int k = P1_UP; k < KEY_NAME_NUM; k++ )
		{
			BYTE bType = 0;
			BYTE bNum = 0;
			BYTE bKey = 0;

			fstrm.read( (char*)&bType, sizeof(BYTE) );
			m_keyconfig[k].m_type = (GAME_DEVICE_TYPE)bType;

			switch ( bType )
			{
			case JOYSTICK:
				fstrm.read( (char*)&bNum, sizeof(BYTE) );
				m_keyconfig[k].m_num = (DWORD)bNum;
				fstrm.read( (char*)&bKey, sizeof(BYTE) );
				m_keyconfig[k].m_key = (DWORD)bKey;
				break;
			case KEYBOARD:
				m_keyconfig[k].m_num = 0;
				fstrm.read( (char*)&bKey, sizeof(BYTE) );
				m_keyconfig[k].m_key = (DWORD)bKey;
				break;
			default:
				m_keyconfig[k].m_num = 0;
				m_keyconfig[k].m_key = 0;
				continue;
			}
		}

		////DebugOutTrace::instance()->DebugOutf(TEXT(" ...OK\n"));
		fstrm.close();
	}

	//状態の更新
	void KeyInput::Update()
	{
		if ( DxInput::instance() )
		{
			DxInput::instance()->Update ();	//入力の更新
		}
	}

	//押した状態かどうか(このフレームのみ)
	bool KeyInput::IsKey( KEY_NAME key )
	{
		if ( m_keyconfig[key].m_type == JOYSTICK )
		{
			//ジョイスティックボタンとXY軸で分岐する
			switch ( m_keyconfig[key].m_key )
			{
			case JOYSTICK_UP:       //レバー上
				return DxInput::instance()->IsJoyUp( m_keyconfig[key].m_num );
			case JOYSTICK_DOWN:     //レバー下
				return DxInput::instance()->IsJoyDown( m_keyconfig[key].m_num );
			case JOYSTICK_LEFT:     //レバー左
				return DxInput::instance()->IsJoyLeft( m_keyconfig[key].m_num );
			case JOYSTICK_RIGHT:    //レバー右
				return DxInput::instance()->IsJoyRight( m_keyconfig[key].m_num );
			default:				//その他ボタン
				return DxInput::instance()->IsOneJoystick( m_keyconfig[key].m_num, m_keyconfig[key].m_key );
			}
		}
		else if ( m_keyconfig[key].m_type == KEYBOARD )
		{
			return DxInput::instance()->IsOneKeyboard( m_keyconfig[key].m_key );
		}
		return false;
	}
	
	//キーが押された瞬間かどうか(前回off 今回on)
	bool KeyInput::PushKey( KEY_NAME key )
	{
		if ( m_keyconfig[key].m_type == JOYSTICK )
		{
			//ジョイスティックボタンとXY軸で分岐する
			switch ( m_keyconfig[key].m_key )
			{
			case JOYSTICK_UP:       //レバー上
				return ( DxInput::instance()->PushJoyUp( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_DOWN:     //レバー下
				return ( DxInput::instance()->PushJoyDown( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_LEFT:     //レバー左
				return ( DxInput::instance()->PushJoyLeft( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_RIGHT:    //レバー右
				return ( DxInput::instance()->PushJoyRight( m_keyconfig[key].m_num ) ) ? true: false;
			default:				//その他ボタン
				return DxInput::instance()->PushOneJoystick( m_keyconfig[key].m_num, m_keyconfig[key].m_key );
			}
		}
		else if ( m_keyconfig[key].m_type == KEYBOARD )
		{
			return DxInput::instance()->PushOneKeyboard( m_keyconfig[key].m_key );
		}
		return false;
	}


	//キーが離された瞬間かどうか(前回on 今回off)
	bool KeyInput::ReleaseKey( KEY_NAME key )
	{
		if ( m_keyconfig[key].m_type == JOYSTICK )
		{
			//ジョイスティックボタンとXY軸で分岐する
			switch ( m_keyconfig[key].m_key )
			{
			case JOYSTICK_UP:       //レバー上
				return ( DxInput::instance()->ReleaseJoyUp( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_DOWN:     //レバー下
				return ( DxInput::instance()->ReleaseJoyDown( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_LEFT:     //レバー左
				return ( DxInput::instance()->ReleaseJoyLeft( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_RIGHT:    //レバー右
				return ( DxInput::instance()->ReleaseJoyRight( m_keyconfig[key].m_num ) ) ? true: false;
			default:				//その他ボタン
				return DxInput::instance()->ReleaseOneJoystick( m_keyconfig[key].m_num, m_keyconfig[key].m_key );
			}
		}
		else if ( m_keyconfig[key].m_type == KEYBOARD )
		{
			return DxInput::instance()->ReleaseOneKeyboard( m_keyconfig[key].m_key );
		}
		return false;
	}


}	//namespace GAME


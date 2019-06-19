//=================================================================================================
//
// �L�[�R���t�B�O���p�N���X�@�\�[�X�R�[�h
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "KeyInput.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------------------------------------------------------------------
	//	�萔
	//-------------------------------------------------------------------------------------------------

	//�L�[�R���t�B�O �ݒ�t�@�C���ɂ�����f�t�H���g�̃o�C�i���f�[�^
	//[1P] : Pad0_UP, Pad0_DOWN, Pad0_LEFT, Pad0_RIGHT, Pad0_key3, Pad0_key4, Pad0_key1, Pad0_key0, 
	//[2P] : Home, End, Delete, PageDown, A, S, D, F,
	const unsigned char data[] =
	{
		0x01, 0x00, 0x81, 0x01, 0x00, 0x82, 0x01, 0x00, 0x83, 0x01, 0x00, 0x84, 0x01, 0x00, 0x03, 0x01,
		0x00, 0x04, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0xC7, 0x00, 0xCF, 0x00, 0xD3, 0x00, 0xD1,
		0x00, 0x1E, 0x00, 0x1F, 0x00, 0x20, 0x00, 0x21, 0x02,
	};

	//------------------------------------------
	//	Static����
	//------------------------------------------
	//	�V���O���g���@�C���X�^���X
	KeyInput::P_KeyInput	KeyInput::m_inst;

	//-------------------------------------------------------------------------------------------------

	//�R���X�g���N�^
	KeyInput::KeyInput()
	{
		//DirectInput(�L�[�{�[�h�A�W���C�X�e�B�b�N�̗��p)
		DxInput::Create();
		Load();
	}
	
	//�f�X�g���N�^
	KeyInput::~KeyInput()
	{
		DxInput::Destroy();
	}

	//�Đݒ�
	void KeyInput::Reset()
	{
		if ( DxInput::instance() )
		{
			DxInput::instance()->Reset();
		}
	}

	//�t�@�C���Ǎ�
	void KeyInput::Load()
	{
		std::fstream fstrm( TEXT("keyconfig.dat"), std::ios::in, std::ios::binary );

		if ( fstrm.fail() )
		{
			//�V�K�t�@�C���̍쐬
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

		//�o�C�i���Ǎ�
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

	//��Ԃ̍X�V
	void KeyInput::Update()
	{
		if ( DxInput::instance() )
		{
			DxInput::instance()->Update ();	//���͂̍X�V
		}
	}

	//��������Ԃ��ǂ���(���̃t���[���̂�)
	bool KeyInput::IsKey( KEY_NAME key )
	{
		if ( m_keyconfig[key].m_type == JOYSTICK )
		{
			//�W���C�X�e�B�b�N�{�^����XY���ŕ��򂷂�
			switch ( m_keyconfig[key].m_key )
			{
			case JOYSTICK_UP:       //���o�[��
				return DxInput::instance()->IsJoyUp( m_keyconfig[key].m_num );
			case JOYSTICK_DOWN:     //���o�[��
				return DxInput::instance()->IsJoyDown( m_keyconfig[key].m_num );
			case JOYSTICK_LEFT:     //���o�[��
				return DxInput::instance()->IsJoyLeft( m_keyconfig[key].m_num );
			case JOYSTICK_RIGHT:    //���o�[�E
				return DxInput::instance()->IsJoyRight( m_keyconfig[key].m_num );
			default:				//���̑��{�^��
				return DxInput::instance()->IsOneJoystick( m_keyconfig[key].m_num, m_keyconfig[key].m_key );
			}
		}
		else if ( m_keyconfig[key].m_type == KEYBOARD )
		{
			return DxInput::instance()->IsOneKeyboard( m_keyconfig[key].m_key );
		}
		return false;
	}
	
	//�L�[�������ꂽ�u�Ԃ��ǂ���(�O��off ����on)
	bool KeyInput::PushKey( KEY_NAME key )
	{
		if ( m_keyconfig[key].m_type == JOYSTICK )
		{
			//�W���C�X�e�B�b�N�{�^����XY���ŕ��򂷂�
			switch ( m_keyconfig[key].m_key )
			{
			case JOYSTICK_UP:       //���o�[��
				return ( DxInput::instance()->PushJoyUp( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_DOWN:     //���o�[��
				return ( DxInput::instance()->PushJoyDown( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_LEFT:     //���o�[��
				return ( DxInput::instance()->PushJoyLeft( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_RIGHT:    //���o�[�E
				return ( DxInput::instance()->PushJoyRight( m_keyconfig[key].m_num ) ) ? true: false;
			default:				//���̑��{�^��
				return DxInput::instance()->PushOneJoystick( m_keyconfig[key].m_num, m_keyconfig[key].m_key );
			}
		}
		else if ( m_keyconfig[key].m_type == KEYBOARD )
		{
			return DxInput::instance()->PushOneKeyboard( m_keyconfig[key].m_key );
		}
		return false;
	}


	//�L�[�������ꂽ�u�Ԃ��ǂ���(�O��on ����off)
	bool KeyInput::ReleaseKey( KEY_NAME key )
	{
		if ( m_keyconfig[key].m_type == JOYSTICK )
		{
			//�W���C�X�e�B�b�N�{�^����XY���ŕ��򂷂�
			switch ( m_keyconfig[key].m_key )
			{
			case JOYSTICK_UP:       //���o�[��
				return ( DxInput::instance()->ReleaseJoyUp( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_DOWN:     //���o�[��
				return ( DxInput::instance()->ReleaseJoyDown( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_LEFT:     //���o�[��
				return ( DxInput::instance()->ReleaseJoyLeft( m_keyconfig[key].m_num ) ) ? true: false;
			case JOYSTICK_RIGHT:    //���o�[�E
				return ( DxInput::instance()->ReleaseJoyRight( m_keyconfig[key].m_num ) ) ? true: false;
			default:				//���̑��{�^��
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


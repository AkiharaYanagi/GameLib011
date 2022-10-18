//=================================================================================================
//
// Direct Input �ɂ��W���C�X�e�B�b�N�̊Ǘ��@�N���X
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"
#include <dinput.h>		//DirectInput

#include "DebugManager.h"
#include "HWnd.h"

//-------------------------------------------------------------------------------------------------
// ���C�u�����̃����N
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dinput8.lib")

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//�萔�錾
	//------------------------------------------
	const int INPUT_DEVICE_NUM = 16;	//�f�o�C�X�̍ő吔(Windows�ŃW���C�X�e�B�b�N�̈�����͈�)

	//--------------------------------------------------------
	// Direct Input �ɂ��W���C�X�e�B�b�N�̊Ǘ��@�N���X
	//--------------------------------------------------------
	class DxJoystick
	{
		LPDIRECTINPUT8			m_lpDI;			//DirectInput�I�u�W�F�N�g
		LPDIRECTINPUTDEVICE8	m_lpDIDevice[INPUT_DEVICE_NUM];		//�񋓂����f�o�C�X
		DIDEVCAPS				m_diDevCaps[INPUT_DEVICE_NUM];		//�W���C�X�e�B�b�N�̔\��

		DIJOYSTATE				m_dijs[INPUT_DEVICE_NUM];			//�W���C�X�e�B�b�N���
		DIJOYSTATE				m_preDijs[INPUT_DEVICE_NUM];		//���O�̃W���C�X�e�B�b�N���

		//DirectInput�ϐ�
		DWORD	m_dwJoyMaxCount;	//������W���C�X�e�B�b�N�̍ő吔
		DWORD	m_dwJoyCount;		//�W���C�X�e�B�b�N�̎���(��Ƀf�o�C�X�z��̓Y����)

		//DirectInput�R�[���o�b�N�֐�
		static BOOL CALLBACK EnumJoystickCallback ( const DIDEVICEINSTANCE* lpddi, LPVOID lpContext );
		static BOOL CALLBACK EnumAxisCallback ( LPCDIDEVICEOBJECTINSTANCE lpddi, LPVOID lpvRef );

	public:
		DxJoystick();
		DxJoystick( const DxJoystick& rhs ) = delete;
		~DxJoystick();

		void Init( LPDIRECTINPUT8 lpDI );		//������
		void Rele();	//���

		//�w�肵���{�^����������Ă����Ԃ�
		bool IsButton( int nDevice, int nButton );
		//�w�肵���{�^���������ꂽ�u�Ԃ�
		bool PushButton( int nDevice, int nButton );
		//�w�肵���{�^���������ꂽ�u�Ԃ�
		bool ReleaseButton( int nDevice, int nButton );

		//���̏�Ԃ�Ԃ�
		LONG GetJoyAxisX( int nDevice ) { return m_dijs[nDevice].lX; }
		LONG GetJoyAxisY( int nDevice ) { return m_dijs[nDevice].lY; }

		//POV�̏�Ԃ�Ԃ�( �ォ�� 0, 9000, 18000, 27000 )
		DWORD GetPov ( int nDevice ) { return m_dijs [ nDevice ].rgdwPOV [ 0 ]; }
		bool IsPovUp	( int nDevice ) { return 0		== m_dijs [ nDevice ].rgdwPOV [ 0 ]; }
		bool IsPovRight	( int nDevice ) { return 9000	== m_dijs [ nDevice ].rgdwPOV [ 0 ]; }
		bool IsPovDown	( int nDevice ) { return 18000	== m_dijs [ nDevice ].rgdwPOV [ 0 ]; }
		bool IsPovLeft	( int nDevice ) { return 27000	== m_dijs [ nDevice ].rgdwPOV [ 0 ]; }

		//��������Ԃ̔���
		bool IsJoyUp	( int nDevice ) { return ( m_dijs[nDevice].lY <= -500 ) ? true: false; }
		bool IsJoyDown	( int nDevice ) { return ( m_dijs[nDevice].lY >=  500 ) ? true: false; }
		bool IsJoyLeft	( int nDevice ) { return ( m_dijs[nDevice].lX <= -500 ) ? true: false; }
		bool IsJoyRight ( int nDevice ) { return ( m_dijs[nDevice].lX >=  500 ) ? true: false; }

		//�O�t���[���̏��
		bool IsPreJoyUp		( int nDevice ) { return ( m_preDijs[nDevice].lY <= -500 ) ? true: false; }
		bool IsPreJoyDown	( int nDevice ) { return ( m_preDijs[nDevice].lY >=  500 ) ? true: false; }
		bool IsPreJoyLeft	( int nDevice ) { return ( m_preDijs[nDevice].lX <= -500 ) ? true: false; }
		bool IsPreJoyRight	( int nDevice ) { return ( m_preDijs[nDevice].lX >=  500 ) ? true: false; }

		//�������u�Ԃ̔���(�O��off ����on)
		bool PushJoyUp	 ( int nDevice ) { return ( ! IsPreJoyUp(nDevice)    && IsJoyUp(nDevice)    ) ? true: false; }
		bool PushJoyDown ( int nDevice ) { return ( ! IsPreJoyDown(nDevice)  && IsJoyDown(nDevice)  ) ? true: false; }
		bool PushJoyLeft ( int nDevice ) { return ( ! IsPreJoyLeft(nDevice)  && IsJoyLeft(nDevice)  ) ? true: false; }
		bool PushJoyRight( int nDevice ) { return ( ! IsPreJoyRight(nDevice) && IsJoyRight(nDevice) ) ? true: false; }

		//�������u�Ԃ̔���(�O��on ����off)
		bool ReleaseJoyUp   ( int nDevice ) { return ( IsPreJoyUp(nDevice)    && ! IsJoyUp(nDevice)    ) ? true: false; }
		bool ReleaseJoyDown ( int nDevice ) { return ( IsPreJoyDown(nDevice)  && ! IsJoyDown(nDevice)  ) ? true: false; }
		bool ReleaseJoyLeft ( int nDevice ) { return ( IsPreJoyLeft(nDevice)  && ! IsJoyLeft(nDevice)  ) ? true: false; }
		bool ReleaseJoyRight( int nDevice ) { return ( IsPreJoyRight(nDevice) && ! IsJoyRight(nDevice) ) ? true: false; }

		//	���݃W���C�X�e�B�b�N����Ԃ��֐�
		DWORD GetJoyCount(void){ return m_dwJoyCount; }

		//�Q�[�����p
		//��Ԃ̍X�V
		void Update();
	};


}	//namespace GAME


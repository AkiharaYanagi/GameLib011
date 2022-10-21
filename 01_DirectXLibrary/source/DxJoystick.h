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
		bool IsButton( int id, int nButton );
		//�w�肵���{�^���������ꂽ�u�Ԃ�
		bool PushButton( int id, int nButton );
		//�w�肵���{�^���������ꂽ�u�Ԃ�
		bool ReleaseButton( int id, int nButton );

		//���̏�Ԃ�Ԃ�
		LONG GetJoyAxisX( int id ) { return m_dijs[id].lX; }
		LONG GetJoyAxisY( int id ) { return m_dijs[id].lY; }

		//POV�̏�Ԃ�Ԃ�( �ォ�� 0, 9000, 18000, 27000 )
		//���΂߂��P��̒l�����̂Ŕ͈͂Ŏw�肷��
		DWORD GetPov ( int id );
		bool IsPovUp	( int id );
		bool IsPovRight	( int id );
		bool IsPovDown	( int id );
		bool IsPovLeft	( int id );

		//Axis:��������Ԃ̔���
		bool IsAxisUp	( int id ) 
		{ return ( m_dijs[id].lY <= -500 ) ? true: false; }
		bool IsAxisDown	( int id ) { return ( m_dijs[id].lY >=  500 ) ? true: false; }
		bool IsAxisLeft	( int id ) { return ( m_dijs[id].lX <= -500 ) ? true: false; }
		bool IsAxisRight ( int id ) { return ( m_dijs[id].lX >=  500 ) ? true: false; }

		//�O�t���[���̏��
		bool IsPreAxisUp	( int id ) { return ( m_preDijs[id].lY <= -500 ) ? true: false; }
		bool IsPreAxisDown	( int id ) { return ( m_preDijs[id].lY >=  500 ) ? true: false; }
		bool IsPreAxisLeft	( int id ) { return ( m_preDijs[id].lX <= -500 ) ? true: false; }
		bool IsPreAxisRight	( int id ) { return ( m_preDijs[id].lX >=  500 ) ? true: false; }

		//�������u�Ԃ̔���(�O��off ����on)
		bool PushAxisUp		( int id ) { return ( ! IsPreAxisUp(id)    && IsAxisUp(id)    ) ? true: false; }
		bool PushAxisDown	( int id ) { return ( ! IsPreAxisDown(id)  && IsAxisDown(id)  ) ? true: false; }
		bool PushAxisLeft	( int id ) { return ( ! IsPreAxisLeft(id)  && IsAxisLeft(id)  ) ? true: false; }
		bool PushAxisRight	( int id ) { return ( ! IsPreAxisRight(id) && IsAxisRight(id) ) ? true: false; }

		//�������u�Ԃ̔���(�O��on ����off)
		bool ReleAxisUp   ( int id ) { return ( IsPreAxisUp(id)    && ! IsAxisUp(id)    ) ? true: false; }
		bool ReleAxisDown ( int id ) { return ( IsPreAxisDown(id)  && ! IsAxisDown(id)  ) ? true: false; }
		bool ReleAxisLeft ( int id ) { return ( IsPreAxisLeft(id)  && ! IsAxisLeft(id)  ) ? true: false; }
		bool ReleAxisRight( int id ) { return ( IsPreAxisRight(id) && ! IsAxisRight(id) ) ? true: false; }

		//	���݃W���C�X�e�B�b�N����Ԃ��֐�
		DWORD GetJoyCount(void){ return m_dwJoyCount; }

		//�Q�[�����p
		//��Ԃ̍X�V
		void Update();
	};


}	//namespace GAME


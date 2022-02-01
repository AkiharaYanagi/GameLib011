//=================================================================================================
//
// DirectInput �̎���
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DxInput.h"

//-------------------------------------------------------------------------------------------------
// ���C�u���������݂̂ŎQ�Ƃ���w�b�_�t�@�C��
//-------------------------------------------------------------------------------------------------
#include "DxJoystick.h"			//�W���C�X�e�B�b�N
#include "DxKeyboard.h"			//�L�[�{�[�h
#include "DxMouse.h"			//�}�E�X

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//	�V���O���g���@�C���X�^���X
	//-------------------------------------------------------------------------------------------------
	DxInput::P_DxInput		DxInput::m_inst = nullptr;

	//-------------------------------------------------------------------------------------------------
	//	�V���O���g���@�C���X�^���X����
	//-------------------------------------------------------------------------------------------------
	void DxInput::Create ()
	{
		assert ( ! m_inst );
//		m_inst = new DxInput;
//		if ( ! m_inst ) { m_inst = make_unique < DxInput > (); }
		if ( ! m_inst ) { m_inst = P_DxInput ( new DxInput () ); }
	}
#if 0


	//-------------------------------------------------------------------------------------------------
	//	�V���O���g���@�C���X�^���X�j��
	//-------------------------------------------------------------------------------------------------
	void DxInput::Destroy ()
	{
//		if ( m_inst ) { delete m_inst; }
//		m_inst = nullptr;
		m_inst.reset ();
	}
#endif // 0


	//-------------------------------------------------------------------------------------------------
	//	�R���X�g���N�^
	//-------------------------------------------------------------------------------------------------
	DxInput::DxInput ()
		: m_lpDI ( nullptr ), m_joystick ( nullptr ), m_keyboard ( nullptr ), m_mouse ( nullptr )
	{
		m_joystick = make_unique < DxJoystick > ();
		m_keyboard = make_unique < DxKeyboard > ();
		m_mouse = make_unique < DxMouse > ();

		Init ();		//������
	}

	//-------------------------------------------------------------------------------------------------
	//	�f�X�g���N�^
	//-------------------------------------------------------------------------------------------------
	DxInput::~DxInput ()
	{
		Rele ();	//���
#if 0
		if ( m_joystick ) { delete m_joystick; }
		m_joystick = nullptr;
		if ( m_keyboard ) { delete m_keyboard; }
		m_keyboard = nullptr;
		if ( m_mouse ) { delete m_mouse; }
		m_mouse = nullptr;
#endif // 0
	}


	//-------------------------------------------------------------------------------------------------
	//	DirectInput ������
	//-------------------------------------------------------------------------------------------------
	void DxInput::Init()
	{
		HRESULT hr;
		HINSTANCE hInstance = GetModuleHandle(nullptr);

		//DirectInput�I�u�W�F�N�g�̍쐬
#if	0
		hr = DirectInput8Create (	hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, 
									reinterpret_cast<LPVOID*>(&m_lpDI), nullptr );
		DXTRACE_RETURN_FLASE( hr, TEXT("DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s") );
#else
		::CoInitialize(nullptr);		//COM�̏�����
		//COM�I�u�W�F�N�g�Ƃ��Đ�������Ƃ�CoInitialize(nullptr)���ĂԕK�v������B�I�����ɂ�CoUninitialize()�B
		hr = ::CoCreateInstance( CLSID_DirectInput8, nullptr, CLSCTX_ALL, IID_IDirectInput8,
									reinterpret_cast<LPVOID*>(&m_lpDI) );
		if ( FAILED(hr) ) DXTRACE( hr, TEXT("COM�ɂ��DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s") );

		hr = m_lpDI->Initialize( hInstance, DIRECTINPUT_VERSION );
		if ( FAILED(hr) ) DXTRACE( hr, TEXT("DirectInput�I�u�W�F�N�g�̏������Ɏ��s") );
#endif	//0

		m_joystick->Init ( m_lpDI );	//	�W���C�X�e�B�b�N
		m_keyboard->Init ( m_lpDI );	//	�L�[�{�[�h
		m_mouse->Init ( m_lpDI );		//	�}�E�X
	}

	//-------------------------------------------------------------------------------------------------
	//	DirectInput ���
	//-------------------------------------------------------------------------------------------------
	void DxInput::Rele()
	{
		m_keyboard->Rele ();	//�L�[�{�[�h
		m_joystick->Rele ();	//�W���C�X�e�B�b�N
		m_mouse->Rele ();		//�}�E�X
		RELEASE ( m_lpDI );		//DirectInput�̉��
		::CoUninitialize ();	//COM�̉��
	}

	//-------------------------------------------------------------------------------------------------
	//	DirectInput �Đݒ�
	//-------------------------------------------------------------------------------------------------
	void DxInput::Reset()
	{
		Rele();
		Init();
	}

	//-------------------------------------------------------------------------------------------------
	//	�t���[�����̍X�V
	//-------------------------------------------------------------------------------------------------
	void DxInput::Update()
	{
		m_keyboard->Update();		//�L�[�{�[�h�f�o�C�X
		m_joystick->Update();		//�W���C�X�e�B�b�N
		m_mouse->Update();			//�}�E�X
	}


	//---------------------------------------------------------------------------
	//	�L�[�{�[�h
	//---------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//	�L�[�{�[�h�ŉ�����Ă����Ԃ��ǂ������擾����
	//	�����Fkey �L�[�{�[�h�̔z��萔
	//	�ߒl�F�Ώۂ̃L�[��������Ă����ԂȂ�true, �����łȂ����false
	//-------------------------------------------------------------------------------------------------
	bool DxInput::IsOneKeyboard ( int key ) const
	{
		return m_keyboard->IsKey( key );
	}

	//-------------------------------------------------------------------------------------------------
	//	�L�[�{�[�h�������ꂽ�u�Ԃ��ǂ������擾���� (1�t���[���O��false ���� ���݃t���[����true)
	//	�����Fkey �L�[�{�[�h�̔z��萔
	//	�ߒl�F�Ώۂ̃L�[�������ꂽ�u�ԂȂ�true, �����łȂ����false
	//-------------------------------------------------------------------------------------------------
	bool DxInput::PushOneKeyboard ( int key ) const
	{
		return m_keyboard->PushKey( key );
	}

	//-------------------------------------------------------------------------------------------------
	//	�L�[�{�[�h�������ꂽ�u�Ԃ��ǂ������擾���� (1�t���[���O��true ���� ���݃t���[����false)
	//	�����Fkey �L�[�{�[�h�̔z��萔
	//	�ߒl�F�Ώۂ̃L�[�������ꂽ�u�ԂȂ�true, �����łȂ����false
	//-------------------------------------------------------------------------------------------------
	bool DxInput::ReleaseOneKeyboard ( int key ) const
	{
		return m_keyboard->ReleaseKey( key );
	}


	//---------------------------------------------------------------------------
	//	�W���C�X�e�B�b�N
	//---------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//	�W���C�X�e�B�b�N(�L�[)�ŉ�����Ă����Ԃ��ǂ������擾����
	//	�����Fnum �f�o�C�X�ԍ�, key �L�[�ԍ�
	//-------------------------------------------------------------------------------------------------
	bool DxInput::IsOneJoystick( int num, int key ) const
	{
		return m_joystick->IsJoyKey( num, key );
	}
	//	�W���C�X�e�B�b�N(XY)�ŉ�����Ă����Ԃ��ǂ������擾����
	bool DxInput::IsJoyUp( int nDevice ) const { return m_joystick->IsJoyUp(nDevice); }
	bool DxInput::IsJoyDown( int nDevice ) const { return m_joystick->IsJoyDown(nDevice); }
	bool DxInput::IsJoyLeft( int nDevice ) const { return m_joystick->IsJoyLeft(nDevice); }
	bool DxInput::IsJoyRight( int nDevice ) const { return m_joystick->IsJoyRight(nDevice); }


	//-------------------------------------------------------------------------------------------------
	//	�W���C�X�e�B�b�N(�L�[)�ŉ����ꂽ�u�Ԃ��ǂ������擾����
	//	�����Fnum �f�o�C�X�ԍ�, key �L�[�ԍ�
	//-------------------------------------------------------------------------------------------------
	bool DxInput::PushOneJoystick( int num, int key ) const
	{
		return m_joystick->PushJoyKey( num, key );
	}
	//	�W���C�X�e�B�b�N(XY)�ŉ����ꂽ�u�Ԃ��ǂ������擾����
	bool DxInput::PushJoyUp( int nDevice ) const { return m_joystick->PushJoyUp(nDevice); }
	bool DxInput::PushJoyDown( int nDevice ) const { return m_joystick->PushJoyDown(nDevice); }
	bool DxInput::PushJoyLeft( int nDevice ) const { return m_joystick->PushJoyLeft(nDevice); }
	bool DxInput::PushJoyRight( int nDevice ) const { return m_joystick->PushJoyRight(nDevice); }


	//-------------------------------------------------------------------------------------------------
	//	�W���C�X�e�B�b�N(�L�[)�ŗ����ꂽ�u�Ԃ��ǂ������擾����
	//	�����Fnum �f�o�C�X�ԍ�, key �L�[�ԍ�
	//-------------------------------------------------------------------------------------------------
	bool DxInput::ReleaseOneJoystick( int num, int key ) const
	{
		return m_joystick->ReleaseJoyKey( num, key );
	}
	//	�W���C�X�e�B�b�N(XY)�ŗ����ꂽ�u�Ԃ��ǂ������擾����
	bool DxInput::ReleaseJoyUp( int nDevice ) const { return m_joystick->ReleaseJoyUp(nDevice); }
	bool DxInput::ReleaseJoyDown( int nDevice ) const { return m_joystick->ReleaseJoyDown(nDevice); }
	bool DxInput::ReleaseJoyLeft( int nDevice ) const { return m_joystick->ReleaseJoyLeft(nDevice); }
	bool DxInput::ReleaseJoyRight( int nDevice ) const { return m_joystick->ReleaseJoyRight(nDevice); }


	//���̏�Ԃ�Ԃ�
	LONG DxInput::GetJoyAxisX( int nDevice ) const { return m_joystick->GetJoyAxisX( nDevice ); }
	LONG DxInput::GetJoyAxisY( int nDevice ) const { return m_joystick->GetJoyAxisY( nDevice ); }


	//---------------------------------------------------------------------------
	//	�}�E�X
	//---------------------------------------------------------------------------
	bool DxInput::IsMouseButton ( MOUSE_BUTTON n ) const
	{
		return m_mouse->IsButton ( n ); 
	}

	bool DxInput::UpMouseButton ( MOUSE_BUTTON n ) const
	{
		return m_mouse->UpButton ( n ); 
	}

	POINT DxInput::GetMouseDelta () const
	{
		return m_mouse->GetMouseDelta (); 
	}

	POINT DxInput::GetMousePoint () const
	{
		//�}�E�X�ʒu�̎擾
		POINT cursorPt;
		::GetCursorPos ( &cursorPt );
		::ScreenToClient ( HWnd::Get(), &cursorPt );
		return cursorPt; 
	}

	bool DxInput::IsMouseInside ( LONG x, LONG y, LONG w, LONG h ) const
	{
		//�}�E�X�ʒu�̎擾
		POINT cursorPt = GetMousePoint ();
		if (	x <= cursorPt.x 
			&&	cursorPt.x <= x + w
			&&	y <= cursorPt.y 
			&&	cursorPt.y <= y + h )
		{
			return true;
		}
		return false; 
	}


}	//namespace GAME


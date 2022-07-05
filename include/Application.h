//=================================================================================================
//
// �A�v���P�[�V�����w�b�_
//
//�@windows�A�v���P�[�V�����ɂ����鏉�����ƃ��b�Z�[�W�̏���
//	�`��X���b�h����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"		//�f�o�b�O�\��
#include "DirectX_Library.h"	//DirectX���p
#include "HWnd.h"				//�E�B���h�E�n���h���I�u�W�F�N�g�̗��p
#include "GameMainBase.h"		//�Q�[�����C�����
#include "AppSettingFile.h"		//�ݒ�t�@�C��

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//���C�u�������N���X�錾
	//		���C�u�����������ŗp����N���X
	//		�w�b�_�t�@�C���ɃC���N���[�h���Ȃ����߂ɃN���X�錾�����s��
	//-------------------------------------------------------------------------------------------------
	class FrameControl;

	//���\�[�X��
	struct ResourceName
	{
		LPCTSTR windowClassName;	//�E�B���h�E�N���X��
		LPCTSTR mutexText;			//�~���[�e�b�N�X������
		LPCTSTR TitleBar;			//�^�C�g���o�[������
		LPCTSTR ICON_ID;			//�A�C�R��ID
	};

	//-------------------------------------------------------------------------------------------------
	//�A�v���P�[�V�����Ǘ��N���X
	//-------------------------------------------------------------------------------------------------
	class Application : public enable_shared_from_this < Application >
	{
		//�E�B���h�E������
		ResourceName		m_rcName;		//���\�[�X��
		HWND				m_hWnd;			//�E�B���h�E�n���h��
		static shared_ptr < Application >	m_pThis;		//�ÓIthis�|�C���^
		static bool			m_init;			//�������t���O(HWND�ƃA�N�e�B�u�E�B���h�E���b�Z�[�W�̊֌W�ŕK�v)

		bool _WinInit ( HINSTANCE hInst );	// �E�B���h�E�̏�����
		static LRESULT CALLBACK WinProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );		//�E�B���h�E�v���V�[�W��

		//���C�u�����������ŗp����N���X
		//		�w�b�_�ł̓|�C���^�����Ő錾���A�\�[�X�t�@�C���őΏۃw�b�_���C���N���[�h����
		unique_ptr < FrameControl > m_pFrameControl;
		
		//���d�N���h�~�̂��߂̃~���[�e�b�N�X�n���h��
		HANDLE				m_hMutex;
#if 0
		//�`��X���b�h
		static UINT WINAPI DrawThread ( void* vdParam );
		bool				m_bPermi;		//�X���b�h���t���O
		bool				m_bActive;		//�X���b�h�ғ��t���O
#endif // 0

		//------------------------------------------------------------------------
		//�ݒ�t�@�C��
//		AppSettingFile	m_settingFile;

//		bool		m_InitFromCursorPos;


	public:
		Application ( ResourceName rcName );
		Application ( const Application & rhs ) = delete;
		~Application ();

		//Windows�A�v���P�[�V�����̏�����
		bool AppInit ( HINSTANCE hInst );

		//�^�X�N�̈ꊇ����
		void Load ();		//�Ǎ�
		void Rele ();		//���
		void Init ();		//������

		//���DirectX�֘A�̍Đݒ� �v���V�[�W������Ăяo������static�錾������
		static void Reset ();

		//windows���C�����[�v
		void MainLoop ( MSG* pMsg );

		//�Q�[�����C���I�u�W�F�N�g�̐ݒ�
		//FrameControl�̋L�q�����邽�߁A�w�b�_�ɂ͋L�q���Ȃ�
		//(include��x�������̂��\�[�X�R�[�h���ł̂ݗp����)
		void SetGameMain ( UP_GameMainBase pGameMain );

		//�X���b�h�ғ��t���O�擾
//		bool IsActive() { return m_bActive; }

		//�f�o�b�O�\�������ׂ�ON
		static void FullDebugMode ();

	private:
		POINT GetWindowInitPos ();
		POINT GetWindowInitSize ();
	};


}	//namespace GAME


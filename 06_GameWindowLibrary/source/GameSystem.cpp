//=================================================================================================
//
// �Q�[���V�X�e���@�N���X��`
//
//		�Q�[�����e�̑O�ɏ��������K�v�ɂȂ�A�v���P�[�V�����⃉�C�u�����Ƃ̘A�����L�q����B
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameSystem.h"
#include "DebugOutGameWindow.h"
#include "AppSettingFile.h"
#include "GameGraphicList.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//static����
	bool GameSystem::m_bDispTimer = false;


	//�e��V���O���g���̃N���G�C�g�Ȃ�1��݂̂̏�����
	void GameSystem::SystemLoad ()
	{
		//�ݒ肩��E�B���h�E��Ԃ̎擾
		UINT window_w = AppSettingFile::Inst ()->GetWindowW ();
		UINT window_h = AppSettingFile::Inst ()->GetWindowH ();
		bool bFullScreen = AppSettingFile::Inst ()->GetbFullscreen ();
		int displayNum = AppSettingFile::Inst ()->GetDisplayNum ();

		// Direct3D�̏�����
		Dx3D::Create ();
		Dx3D::instance()->SetWindowSize ( window_w, window_h );
		Dx3D::instance()->SetFullscreen ( bFullScreen );
		Dx3D::instance ()->SetDisplayNum ( displayNum );
		Dx3D::instance()->Load ();

		//Graphic�z��̏�����
		GameGraphicList::Create ();

		//�Q�[���e�L�X�g������
		GameText::Create();
		GameText::Inst()->Load ( Dx3D::instance()->GetDevice() );

		OutlineFont::Create ();
		OutlineFont::Inst ()->Load ( Dx3D::instance ()->GetDevice () );

#if	0
		//�Q�[���e�L�X�g�t�@�C��������
		TextFile::Create ();
		TextFile::instance()->Load();
#endif	//0
	
		//�Q�[����ʃf�o�b�O�\���̏�����
		DebugOutGameWindow::Create ();
		DebugOutGameWindow::Inst()->Load ();

		//�T�E���h�̐���
		DxSound::Create ();
		DxSound::instance()->Load();

		//�L�[���͂̏�����
		KeyInput::Create();

		//�A�[�J�C�o�̏�����
		Archiver::Create ();
#if	_DEBUG
		Archiver::instance()->Make ();		//�f�o�b�O���̂݃A�[�J�C�u�t�@�C���𐶐�����
#endif	//_DEBUG
		Archiver::instance()->Open ();		//�A�[�J�C�u�t�@�C���̓Ǎ�

		//�T�E���h�A�[�J�C�o�̏�����
		SoundArchiver::Create ();
#if	_DEBUG
		SoundArchiver::instance()->Make ();		//�f�o�b�O���̂݃A�[�J�C�u�t�@�C���𐶐�����
#endif	//_DEBUG
		SoundArchiver::instance()->Open ();		//�A�[�J�C�u�t�@�C���̓Ǎ�
	}


	//�Ǎ�
	void GameSystem::Load ()
	{
		//�Q�[�����C���̓Ǎ�
		assert ( m_pGameMain );
		m_pGameMain->Load ();
	}


	//���
	void GameSystem::Rele ()
	{
//�@���@�f�X�g���N�^�Ŕh���N���X�̉��z�֐����ĂԂƁA���N���X�̉��z�֐����Ă΂��
//�@�@�@���̂��Ƃ��A�������z�֐��̂Ƃ���Purecall�ƂȂ�\��������̂Œ��ӁB
//		���@�f�X�g���N�^�ŉ��z�֐����Ă΂Ȃ�
//ex.		if ( m_pGameMain ) m_pGameMain->Rele ();		//�Q�[���I�u�W�F�N�g�̉��
//		���@�����Ă���|�C���^�̉��z�֐����ĂԂ̂ł͂Ȃ��A
//			�����̃f�X�g���N�^�Ŏ����̏I�������֐����Ă�
	}


	//�Đݒ�
	void GameSystem::Reset()
	{
		//DirectX�֘A�̍Đݒ�
		Dx3D::instance()->Reset();
		D3DDEV dev = Dx3D::instance ()->GetDevice ();
		GameText::Inst()->Reset ( dev );
		OutlineFont::Inst ()->Reset ( dev );
		DebugOutGameWindow::Inst()->Reset( dev );
		KeyInput::instance()->Reset ();
		GRPLST_RESET ();

		if ( m_pGameMain ) { m_pGameMain->Reset(); }
	}


	//������
	void GameSystem::Init ()
	{
		//�Q�[�����C���̏�����
		assert ( m_pGameMain );
		m_pGameMain->Init ();
	}

	
	//�t���[��������
	void GameSystem::Move ()
	{
		DxSound::instance ()->Move ();	//�T�E���h�̍X�V
		KeyInput::instance()->Update ();	//���͂̍X�V

#ifdef	_DEBUG
#endif	// _DEBUG

		//----------------------------------------------
		// 'T'�L�[�Ń^�C�}�[�\���ؑ�
		static int time = 0;
		if( ::GetAsyncKeyState('T') & 0x0001 )
		{
			m_bDispTimer ^= true;
			DBGOUT_WND->SetbDispTime ( m_bDispTimer );
		}
		if( m_bDispTimer )
		{
			DBGOUT_WND->DebugOutWnd_Time ( _T ( "time = %d" ), time );
		}
		else
		{
			DBGOUT_WND->SetbDispTime ( false );
			DBGOUT_WND->DebugOutWnd_Time ( _T ( "" ) );
		}

		//----------------------------------------------
		// 'W'�L�[�ŃX�^�[�g/�X�g�b�v�̃g�O���ؑ�
		static bool bStop = false;
		if( ::GetAsyncKeyState('W') & 0x0001 )
		{
			bStop ^= true; 
		}
		//----------------------------------------------
		// �X�g�b�v���A'Q'�L�[�� 1 �t���[�����i�܂���
		if( ! bStop || ::GetAsyncKeyState('Q') & 0x0001 )
		{
			assert ( m_pGameMain );
			m_pGameMain->Move ();		//�t���[�����̓���
			++ time;
		}
		//----------------------------------------------

		//�Q�[����ʂɂ�����f�o�b�O�\���̓���
		DebugOutGameWindow::Inst()->Move ();
#if	0
		TextFile::instance()->Move ();
#endif	//0
	}


	//�`��
	void GameSystem::Draw()
	{
		assert ( m_pGameMain );

		Dx3D::instance()->BeginScene ();	//�`��J�n
		{
			//�X�v���C�g�`��
			Dx3D::instance()->BeginSprite ();	//�X�v���C�g�`��J�n
			{
				m_pGameMain->Draw ();	//�Q�[�����C���`��
			}
			Dx3D::instance()->EndSprite ();		//�X�v���C�g�`��I��

			//���_�`��
			m_pGameMain->DrawVertex ();			//�Q�[�����C���ȉ��̃^�X�N�ɂ�钸�_�`��

			DebugOutGameWindow::Inst()->DrawVertex ();	//�Q�[����ʏ�̃f�o�b�O�\��
		}
		Dx3D::instance()->EndScene ();		//�`��I��
	}


	//���C���I�u�W�F�N�g�̐ݒ�
	void GameSystem::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = ::move ( pGameMain ); 

#if 0
		//Graphic�z����Q�[�����C���ɐݒ�
		P_TASK_VEC pGrpAry = GrpAry::instance()->GetpInstance ();
		m_pGameMain->AddpTask ( pGrpAry );
//		TRACE_F(_T("GameSystem::SetGameMain\n"));
#endif // 0
	}

	void GameSystem::FullDebugMode ()
	{
		m_bDispTimer = T;
	}

	void GameSystem::NoDebugMode ()
	{
		m_bDispTimer = F;
	}


}	//namespace GAME


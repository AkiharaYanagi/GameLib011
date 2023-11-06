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
//	bool GameSystem::m_bDispTimer = true;
	bool GameSystem::m_bMakeArchive = true;


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
		GRPLST_CREATE ();

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

		//�L�[���͂̏�����
		DxInput::Create ();		//DirectInput(�L�[�{�[�h�A�W���C�X�e�B�b�N�̗��p)
		KeyInput::Create();
		KeyConfig::Create ();

		//�O���t�B�b�N�t�@�C���A�[�J�C�o�̏�����
		Archiver::Create ();
#if	_DEBUG
		//�f�o�b�O�� ���� �t���OON �̂݃A�[�J�C�u�t�@�C���𐶐�����
		if ( m_bMakeArchive )
		{
			Archiver::instance()->Make ();
		}
#endif	//_DEBUG
		Archiver::instance()->Open ();		//�A�[�J�C�u�t�@�C���̓Ǎ�


		//�T�E���h�̐���
		DxSound::Create ();
		DxSound::instance()->Load();

		//�T�E���h�A�[�J�C�o�̏�����
		SoundArchiver::Create ();
#if	_DEBUG
		//�f�o�b�O�� ���� �t���OON �̂݃A�[�J�C�u�t�@�C���𐶐�����
		if ( m_bMakeArchive )
		{
			SoundArchiver::instance ()->Make ();
		}
#endif	//_DEBUG
		SoundArchiver::instance()->Open ();		//�A�[�J�C�u�t�@�C���̓Ǎ�
	}


	//�Ǎ�
	void GameSystem::Load ()
	{
		//�Q�[�����C���̓Ǎ�
		assert ( m_pGameMain );
		m_pGameMain->Load ();
		GRPLST_LOAD ();
		KeyConfig::instance ()->Load ();
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

		//���ʃO���t�B�b�N���X�g
//		GRPLST_RELE ();

		if ( m_pGameMain ) { m_pGameMain->Rele (); }
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
		DxInput::instance ()->Reset ();
		GRPLST_RESET ();

		if ( m_pGameMain ) { m_pGameMain->Reset(); }
	}


	//������
	void GameSystem::Init ()
	{
		//�Q�[�����C���̏�����
		assert ( m_pGameMain );
		m_pGameMain->Init ();
//		GRPLST_INIT ();
	}

	
	//�t���[��������
	void GameSystem::Move ()
	{
		DxSound::instance ()->Move ();	//�T�E���h�̍X�V
		DxInput::instance ()->Update ();	//���͂̍X�V

		//----------------------------------------------
		//�ғ��t���[����
		static UINT frame_time = 0;
		DBGOUT_WND->DebugOutWnd_Frame ( frame_time );

		//----------------------------------------------
		// 'W'�L�[�ŃX�^�[�g/�X�g�b�v�̃g�O���ؑ�
		static bool bStop = false;
		if( WND_UTL::AscKey ( 'W' ) )
		{
			bStop ^= true; 
		}
		//----------------------------------------------
		// �X�g�b�v���A'Q'�L�[�� 1 �t���[�����i�܂���
		if( ! bStop || WND_UTL::AscKey ( 'Q' ) )
		{
			//�t���[�����̓���	
			m_pGameMain->Move ();

			//�Q�[����ʂɂ�����f�o�b�O�\���̓���
			DBGOUT_WND->Move ();
#if	0
			TextFile::instance()->Move ();
#endif	//0
			
			++ frame_time;
		}
		//----------------------------------------------
#ifdef	_DEBUG
#else	// _DEBUG
		
		//�t���[�����̓���	
		m_pGameMain->Move ();

#endif	// _DEBUG

	}


	//�`��
	void GameSystem::Draw()
	{
		assert ( m_pGameMain );

		Dx3D::instance()->BeginScene ();	//�`��J�n
		{

			//@todo �X�v���C�g�ƒ��_�����킹�āAZ�叇�ŕ`�悷��

#if 0
			//�X�v���C�g�`��
			Dx3D::instance()->BeginSprite ();	//�X�v���C�g�`��J�n
			{
//				m_pGameMain->Draw ();	//�Q�[�����C���`��
				GRPLST_DRAW ();
			}
			Dx3D::instance()->EndSprite ();		//�X�v���C�g�`��I��


			//@info �X�v���C�g�ƒ��_�̕`�揇�Ԃɒ���

			//���_�`��
//			m_pGameMain->DrawVertex ();			//�Q�[�����C���ȉ��̃^�X�N�ɂ�钸�_�`��
			GRPLST_DRAW_VERTEX ();
#endif // 0
			GRPLST_DRAW ();


			DBGOUT_WND->DrawVertex ();	//�Q�[����ʏ�̃f�o�b�O�\��
		}
		Dx3D::instance()->EndScene ();		//�`��I��
	}


	//���C���I�u�W�F�N�g�̐ݒ�
	void GameSystem::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = ::move ( pGameMain ); 
	}


}	//namespace GAME


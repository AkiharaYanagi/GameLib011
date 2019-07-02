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
#include "SettingFile.h"
#include "GameGraphicArray.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//�V���O���g���̃N���G�C�g�Ȃ�1��݂̂̏�����
	void GameSystem::SystemLoad ()
	{
		//�ݒ肩��E�B���h�E�T�C�Y�̎擾
		UINT window_x = SettingFile::instance ()->GetWindowX ();
		UINT window_y = SettingFile::instance ()->GetWindowY ();

		// Direct3D�̏�����
		Dx3D::Create ();
		Dx3D::instance()->SetWindowSize ( window_x, window_y );
		Dx3D::instance()->Load ();

		//Graphic�z��̏�����
		GameGraphicArray::Create ();
		
		//�Q�[���e�L�X�g������
		GameText::Create();
		GameText::instance()->Load ( Dx3D::instance()->GetDevice() );
#if	0
		//�Q�[���e�L�X�g�t�@�C��������
		TextFile::Create ();
		TextFile::instance()->Load();
#endif	//0
	
		//�Q�[����ʃf�o�b�O�\���̏�����
		DebugOutGameWindow::Create ();
		DebugOutGameWindow::instance()->Load ();

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
		//DirectX�̍Đݒ�
		Dx3D::instance()->Reset();
		GameText::instance()->Reset ( Dx3D::instance()->GetDevice() );
		DebugOutGameWindow::instance()->Reset( Dx3D::instance()->GetDevice() );
		KeyInput::instance()->Reset ();

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

		assert ( m_pGameMain );
		m_pGameMain->Move ();		//�t���[�����̓���

		//�Q�[����ʂɂ�����f�o�b�O�\���̓���
		DebugOutGameWindow::instance()->Move ();
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

			DebugOutGameWindow::instance()->DrawVertex ();	//�Q�[����ʏ�̃f�o�b�O�\��
		}
		Dx3D::instance()->EndScene ();		//�`��I��
	}


	//���C���I�u�W�F�N�g�̐ݒ�
	void GameSystem::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = ::move ( pGameMain ); 

		//Graphic�z����Q�[�����C���ɐݒ�
		P_TASK_VEC pGrpAry = GrpAry::instance()->GetpInstance ();
		m_pGameMain->AddpTask ( pGrpAry );
	}


}	//namespace GAME


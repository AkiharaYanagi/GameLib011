//=================================================================================================
//
// �Q�[���V�[�� �\�[�X�t�@�C��
//		�J�ڎ��Ƀf�[�^�̔j���������ԑJ��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameScene.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//------------------------------------------------------------------
	//	�Q�[���V�[��
	//------------------------------------------------------------------
	//�w�b�_�̂�


	//------------------------------------------------------------------
	//	�Q�[���V�[���}�l�[�W��
	//------------------------------------------------------------------
	GameSceneManager::GameSceneManager ()
		: m_pScene ( nullptr )
	{
	}

	GameSceneManager::~GameSceneManager ()
	{
	}

	void GameSceneManager::Load ()
	{
		if ( m_pScene ) { m_pScene->Load (); }
		GameTaskVector::Load ();
	}

	void GameSceneManager::Rele ()
	{
		if ( m_pScene ) { m_pScene->Rele (); }
		GameTaskVector::Rele ();
	}

	void GameSceneManager::Reset ()
	{
		if ( m_pScene ) { m_pScene->Reset (); }
		GameTaskVector::Reset ();
	}

	void GameSceneManager::Init ()
	{
		if ( m_pScene ) { m_pScene->Init (); }
		GameTaskVector::Init ();
	}

	void GameSceneManager::Move ()
	{
		Transit ();	//�J�ڏ����m�F

		if ( m_pScene ) { m_pScene->Move (); }
		GameTaskVector::Move ();
	}

	void GameSceneManager::Draw ()
	{
		if ( m_pScene ) { m_pScene->Draw (); }
		GameTaskVector::Draw ();
	}

	void GameSceneManager::DrawVertex ()
	{
		if ( m_pScene ) { m_pScene->DrawVertex (); }
		GameTaskVector::DrawVertex ();
	}

	void GameSceneManager::Transit ()
	{
		if ( ! m_pScene ) { return; }

		shared_ptr < GameScene > next = m_pScene->Transit ();		//Transit()���Ŏw�肵���J�ڐ�A�܂���this���Ԃ�
		if ( next != m_pScene )	//�ȑO�ƈقȂ�ꍇ
		{
			//�p�����[�^�̈ڏ�
			next->SetpParam ( m_pScene->GetpParam () );

			//�V�K�V�[����ݒ�
			m_pScene = next;
			m_pScene->ParamInit ();
			m_pScene->Load ();
			m_pScene->Init ();
		}
	}


}	//namespace GAME


//=================================================================================================
//
// �Q�[���V�X�e���@�w�b�_
//
//					�Q�[�����e�̑O�ɕK�v�ɂȂ�A�v���P�[�V�����⃉�C�u�����Ƃ̘A�����L�q����B
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DirectX_Library.h"
#include "GameTextLibrary.h"
#include "KeyInput.h"
#include "Archiver.h"
#include "SoundArchiver.h"
#include "GameMainBase.h"
#include "KeyConfig.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------------------------------------------------------------------
	//	�Q�[�����̃��C�u�����g�p�Ȃ�
	//-------------------------------------------------------------------------------------------------
	class GameSystem
	{
		UP_GameMainBase		m_pGameMain;	//�Q�[���̃��C���I�u�W�F�N�g�|�C���^

		//@info �O���t�B�b�N�͓���Move()���Q�[�����C���̌�ōs�����߁A�ʂŕێ�����
		P_Task	m_grpList;	//���ʃO���t�B�b�N���X�g�̃^�X�N�|�C���^

	public:
		GameSystem () : m_pGameMain ( nullptr ) {}
		GameSystem ( const GameSystem& rhs ) = delete;
		~GameSystem () { Rele(); }

		void SystemLoad ();		//�V���O���g���̃N���G�C�g�ȂǏ�����

		void Load ();	//�Ǎ�
		void Rele ();	//���
		void Reset();	//�Đݒ�
		void Init ();	//������
		void Move ();	//�t���[��������
		void Draw ();	//�`��

		//���C���I�u�W�F�N�g�̐ݒ�
		void SetGameMain ( UP_GameMainBase pGameMain );


	private:
		static bool m_bDispTimer;
		static bool m_bMakeArchive;

	public:
		//-----------------------------
		//	static ���ݒ�
		//-----------------------------
		
		//�f�o�b�O�\�������ׂ�ON
		static void FullDebugMode () { m_bDispTimer = T; }

		//�f�o�b�O�\�������ׂ�ON
		static void NoDebugMode () { m_bDispTimer = F; }
		
		//�A�[�J�C�u���쐬���ēǂݍ���
		static void SetFlag_MakeArchive ( bool b ) { m_bMakeArchive = b; }
	};


}	//namespace GAME


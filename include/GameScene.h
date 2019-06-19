//=================================================================================================
//
// �Q�[���V�[���@�w�b�_
//		�J�ڎ��Ƀf�[�^�̐����Ɣj���������ԑJ��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "GameTask.h"
#include "GameParam.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------------
	//	�Q�[���V�[��
	//		TaskArray���p�����A�ċA�I�Ƀ^�X�N�������ł���悤�ɂ���GameState
	//		�E���ʂ̃f�[�^�������Ĉڍ�����P��
	//		�E�V�[���̈ړ����ɃI�u�W�F�N�g�̑S�J���A�S�m��
	//		��this�̎擾�̂��߁Aenable_shared_from_this < GameScene >�𑽏d�p��
	//		shared_from_this��p����̂�unique_ptr�ɂ͂��Ȃ�
	//------------------------------------------------------------------
	class GameScene : public GameTaskVector, public enable_shared_from_this < GameScene >
	{
		//�V�[�����ʃp�����[�^
		P_GameParam		m_pParam;

	public:
//		GameScene () : m_pParam ( nullptr ) {}
		GameScene () {}
		GameScene ( const GameScene& rhs ) = delete;
		~GameScene () = default;

		//�p�����[�^��p�����������C���^�[�t�F�[�X
		//�p�����[�^�̎擾�̂��Ƃ̌ďo1��ۏ�
		//Load()�Ƃ͈قȂ�f�o�C�X���Z�b�g�ł��Ă΂�Ȃ�
		//Init()�͕�����Ă΂��\��������
		virtual void ParamInit () = 0;

		//�J�ڏ���
		//��{�̖ߒl��return this;
		//�����ŏ������m�F���A�J�ڎ��͑J�ڐ�̃I�u�W�F�N�g��
		//	make_shared < GameScene > () ���ĕԂ�
		virtual shared_ptr < GameScene > Transit () = 0;

		//�V�[�����ʃp�����[�^
		void SetpParam ( P_GameParam && pParam ) { m_pParam = pParam; }
		P_GameParam GetpParam () { return m_pParam; }
	};

	using P_GameScene = shared_ptr < GameScene >;


	//------------------------------------------------------------------
	//	�Q�[���V�[���}�l�[�W��
	//------------------------------------------------------------------
	class GameSceneManager : public GameTaskVector
	{
		P_GameScene		m_pScene;

	public:
		GameSceneManager ();
		GameSceneManager ( const GameSceneManager & rhs ) = delete;
		virtual ~GameSceneManager ();

		void Load();		//�Ǎ�
		void Rele();		//���
		void Reset ();

		void Init();		//������
		void Move ();
		void Draw ();
		void DrawVertex ();

		//�V�[���̐ݒ�
		void SetScene ( P_GameScene p ) { m_pScene = p; }
//		P_GameScene GetScene () { return m_pScene; }

		//�J��
		virtual void Transit ();
	};

	using SCENE_MGR = GameSceneManager;


}	//namespace GAME


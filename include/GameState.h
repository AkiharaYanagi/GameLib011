//=================================================================================================
//
// �Q�[���X�e�[�g�@�w�b�_
//		��ԑJ��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "GameTask.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//�Q�[���X�e�[�g
	//-------------------------------------------------------------------------------------------------
	//	�Q�[���̏�Ԃ�����
	//	Transit()�ŔC�ӂ̑J�ڏ����𒲂ׁA���̏�Ԃ�������this��Ԃ�
	//-------------------------------------------------------------------------------------------------
	class GameState	: public GameTaskVector
	{
		GameState*			m_next;			//���̏��
		bool				m_change;		//��x�J�ڂ�����this��Ԃ��悤�ɖ߂�

	public:
		GameState ();
		GameState ( const GameState& rhs ) = delete;
		~GameState ();

		//�J�ڐ���w��
		void SetNext ( GameState* p ) 
		{
			m_change = true; 
			m_next = p; 
		}

		//�J�ڔ���
		virtual GameState* Transit () 
		{
			if ( m_change )
			{
				m_change = false;
				return m_next;
			}
			return this; 
		}
	};

	//�Q�[����ԑJ�ڊǗ�
	//-------------------------------------------------------------------------------------------------
	//	�Q�[���^�X�N����������̉����Ď��s����
	//	Move()����Transit()�����s
	//	Transit()�őJ�ڂ���Ƃ��ɈȑO�̃^�X�N��j��
	//-------------------------------------------------------------------------------------------------
	class GameStateManager : public GameTaskVector
	{
		GameState*		m_state;	//���݂̃X�e�[�g

	public:
		GameStateManager ();
		GameStateManager ( const GameStateManager& rhs ) = delete;
		virtual ~GameStateManager ();

		void Init ();
		void Rele ();
		void Load ();
		void Reset ();
		void Move ();
#if 0
		void Draw ();
		void DrawVertex ();
#endif // 0

		void SetState ( GameState* p ) { m_state = p; }
		GameState* GetState () { return m_state; }

		void Transit ();
	};


//======================================================================================


	//�Q�[���X�e�[�g
	class _GameState	// : public GameTask
	{
		_GameState*			m_next;
		bool				m_change;		//��x�J�ڂ�����this��Ԃ��悤�ɖ߂�

	public:
		_GameState () : m_next(nullptr), m_change(false) {}
		_GameState ( const _GameState& rhs ) = delete;
		~_GameState () {}

		//�J�ڐ���w��
		void SetNext ( _GameState* p ) 
		{
			m_change = true; 
			m_next = p; 
		}

		//����̑J�ڃ`�F�b�N
		virtual _GameState* Transit () 
		{
			_GameState* ret = this;
			
			if ( m_change )		//�J�ڐ悪�w�肳��Ă����ꍇ
			{
				ret = m_next;
				m_next = this;		//this��Ԃ��悤�ɖ߂�
				m_change = false;
			}
			return ret; 
		}
	};

	//�Q�[���X�e�[�g�}�l�[�W��
	//-------------------------------------------------------------------------------------------------
	//	���łɎ��̉����Ă���Q�[���^�X�N�ɑJ�ڂ���
	//	Move()����Transit()�����s
	//	Transit()�őJ�ڂ���Ƃ��ɈȑO�̃^�X�N��j�����Ȃ�
	//-------------------------------------------------------------------------------------------------
	class _GameStateManager : public GameTask
	{
		_GameState*		m_state;

	public:
		_GameStateManager () : m_state (nullptr) {}
		_GameStateManager ( const _GameStateManager& rhs ) = delete;
		~_GameStateManager () {}

		void SetState ( _GameState* p ) { m_state = p; }
		_GameState* GetState () { return m_state; }

		void Transit ();
	};


	//�Q�[���X�e�[�g(�I�[�g)
	//�����Ŏ��̏�Ԃ̑J�ڏ����ƑJ�ڐ���w�肷��
	class _GameStateTransit : public _GameState
	{
	public:
		virtual _GameStateTransit* Transit() = 0;
	};

	//�Q�[���X�e�[�g�}�l�[�W��(�g�����W�b�g)
	class _GameStateTransitManager : public _GameStateManager
	{
	public:
	};


}	//namespace GAME


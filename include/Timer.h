//=================================================================================================
//
// Timer �w�b�_�t�@�C��
//		GameTask��̃J�E���g�A�b�v�^�C�}
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameStructureLibrary.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Timer : public GameTask
	{
		bool	m_active;
		UINT	m_time;
		UINT	m_targetTime;

	public:
		Timer ();
		Timer ( UINT targetTime );	//�ڕW����
		Timer ( const Timer & rhs ) = delete;
		~Timer ();

		//@info Task�^�����A�蓮��Move()�݂̂𖈃t���[���s����AddpTask()�̕K�v�͂Ȃ�
		void Move ();

		//�����
		bool IsActive () const { return m_active; }

		//�ŏI���(���l�ɂȂ����烊�Z�b�g�����̂�( 1 + m_time )�Ŕ��肷��)
		bool IsLast () const { return (m_targetTime == 1 + m_time); }

		void SetTime ( UINT i ) { m_time = 0; }
		UINT GetTime () const { return m_time; }
		
		//�ڕW����
		void SetTargetTime ( UINT time ) { m_targetTime = time; }
		UINT GetTargetTime () const { return m_targetTime; }

		//0����X�^�[�g
		void Start () { m_time = 0; m_active = true; }
		
		//�O��̑�������X�^�[�g
		void ReStart () { m_active = true; }

		//�X�g�b�v
		void Stop () { m_active = false; }

		//�N���A
		void Reset () { m_time = 0; m_active = false; }
	};

	using P_Timer = shared_ptr < Timer >;


}	//namespace GAME



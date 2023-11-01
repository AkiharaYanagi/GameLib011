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
	//============================
	//	t = 0 ����J�n
	//	active����++;
	//	targetTime���ɏI������t = 0�ɖ߂�Adeactive
	//
	//============================

	class Timer : public GameTask
	{
		bool	m_active;
		UINT	m_time;
		UINT	m_targetTime;
		UINT	m_wait;

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

		void SetTime ( UINT i ) { m_time = i; }
		UINT GetTime () const { return m_time; }
		
		//�ڕW����
		void SetTargetTime ( UINT time ) { m_targetTime = time; }
		UINT GetTargetTime () const { return m_targetTime; }

		//0����X�^�[�g
		void Start () { m_time = 0; m_active = true; }

		//wait�������ҋ@���Ă���X�^�[�g
		void WaitStart ( UINT wait );
		
		//�O��̑�������X�^�[�g
		void ReStart () { m_active = true; }

		//�X�g�b�v(�ꎞ��~(�J�E���g�͕ۑ�))
		void Stop () { m_active = false; }

		//�N���A
		void Clear () { m_time = 0; m_active = false; }
	};

	using P_Timer = shared_ptr < Timer >;
	using VP_Timer = vector < P_Timer >;
	using PVP_Timer = shared_ptr < VP_Timer >;


}	//namespace GAME



//=================================================================================================
//
// GrpEf �w�b�_�t�@�C��
//	�L�������m�ɂ��ʒu�␳��p����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Const.h"
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GrpEf : public GrpAcv
	{
		UINT	m_timer;
		VEC2	m_base;
		VEC2	m_pos;
		VEC2	m_startScaling;		//�J�n
		VEC2	m_targetScaling;	//�ڕW
		VEC2	m_vec;
		VEC2	m_vel;
		VEC2	m_acc;
		V_VEC2	m_vPosMatrix;		//�����}�g���b�N�X�g�p���̕␳�ʒu
		VEC2	m_dispBase;

	public:
		//�����F�O������̉�ʕ␳��
		GrpEf ();
		GrpEf ( const GrpEf & rhs ) = delete;
		~GrpEf ();

		void Load ();
		void Move ();

		void On ();

		//�L�����ʒu�ɂ���ʕ␳
		void SetpDispBase ( VEC2 v ) { m_dispBase = v; }

		void SetBase ( VEC2 vec ) { m_base = vec; }
		void SetPos ( VEC2 vec ) { m_pos = vec; }

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }

		//�����I�u�W�F�N�g
		void AddObject () 
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
			GrpAcv::AddObject ();
		}
		
		void SetPosMatrix ( UINT i, VEC2 pos )
		{
			m_vPosMatrix[i] = pos;
		}

		//�v�Z��̍ŏI�ʒu���擾
		VEC2 GetCalcPos ( UINT i )
		{
			//��ʒu + �␳�ʒu + �O���␳�ʒu + �ʈʒu
			return m_base + m_pos + m_dispBase + m_vPosMatrix[i];

		}

		//�C���f�b�N�X�Ŏw�肵���e�N�X�`���Œ��S��ݒ肷��
		void SetCenterOfTexture ( UINT index );
	};

	using P_GrpEf = shared_ptr < GrpEf >;


}	//namespace GAME



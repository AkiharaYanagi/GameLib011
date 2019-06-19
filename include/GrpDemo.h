//=================================================================================================
//
// GrpDemo �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GrpDemo : public GrpAcv
	{
		UINT		m_timer;
		VEC2		m_startScaling;		//�J�n
		VEC2		m_targetScaling;	//�ڕW
		VEC2		m_vec;
		VEC2		m_vel;
		VEC2		m_acc;

		VEC2		m_secondVel;	//��2���x

	public:
		GrpDemo ();
		GrpDemo ( const GrpDemo& rhs ) = delete;
		~GrpDemo ();

		void Init ();
		void Move ();

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetAcc ( VEC2 vec ) { m_acc = vec; }
		void SetSecondVel ( VEC2 vec ) { m_secondVel = vec; }
	};


}	//namespace GAME



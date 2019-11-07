//=================================================================================================
//
//	Behavior �w�b�_�t�@�C��
//		�C���[�W�ƃV�[�N�G���X�̃Z�b�g
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Sequence.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Behavior
	{
		PVP_TxBs	m_pvpTxBs;		//�C���[�W�z��
		PVP_Sqc		m_seq;			//�V�[�N�G���X�z��

	public:
		Behavior ();
		Behavior ( const Behavior & rhs ) = delete;
		~Behavior ();
	};

	using P_Behavior = shared_ptr < Behavior >;


}	//namespace GAME


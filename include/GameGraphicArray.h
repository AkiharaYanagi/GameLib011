//=================================================================================================
//
// GameGraphicArray �w�b�_�t�@�C��
//		Z�l��p���ă\�[�g����GameGpraphic�̔z��
//		�I�u�W�F�N�g��ێ����ăV���O���g������ݒ肷��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
//--------------------------------------
//		�yZ�l(0.0f�`0.9f)�z
//		Z_BG	0.1f	�w�i
//		Z_EFB	0.4f	�G�t�F�N�g��
//		Z_CH	0.5f	�L������{�ʒu
//		Z_EF	0.6f	�G�t�F�N�g�O
//		Z_SYS	0.9f	�V�X�e���\��
//--------------------------------------

	//@todo Ef�֘A�Ő����Ɣj����������ɂ킽��̂�List�̌���

//�N���X
	class GameGraphicArray
	{
	//---------------------------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using _GrpAry = GameGraphicArray;
		using _P_GrpAry = unique_ptr < _GrpAry >;
		static _P_GrpAry		m_inst;		//�V���O���g���C���X�^���X
		GameGraphicArray ();		//private �R���X�g���N�^�Œʏ�̎��̉��͋֎~
	public:
		~GameGraphicArray () {}		//�f�X�g���N�^��unique_ptr�̂���public
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpAry ( new _GrpAry () ); } }
		static _P_GrpAry & instance () { return m_inst; }	//�C���X�^���X�擾
	//---------------------------------------------------------------------
	
	private:
		P_TASK_VEC		m_pTaskVec;		//�匳�ƂȂ�^�X�N�x�N�^

	public:
		//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
		void InsertByZ ( P_GrpBs pTask );

		//�Ώۃ^�X�N����O
		void Erase ( P_Task pTask ) { m_pTaskVec->EraseTask ( pTask ); }

		//�Ώۃ^�X�N�z��̃|�C���^
		P_TASK_VEC GetpInstance () { return m_pTaskVec; }
	};


	using GrpAry = GameGraphicArray;
	using UP_GrpAry = unique_ptr < GrpAry >;
#define		GRPARY_INSERT	GrpAry::instance()->InsertByZ
#define		GRPARY_ERASE	GrpAry::instance()->Erase

}	//namespace GAME



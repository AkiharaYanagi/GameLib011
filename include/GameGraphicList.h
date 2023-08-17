//=================================================================================================
//
// ��GameGraphicList
//		�O���t�B�b�N�\���̑O���S�̂œ��ꂷ��
//		Z�l��p���ă\�[�g����GameGpraphic�̃��X�g�̃|�C���^��ێ�����
//		�I�u�W�F�N�g�̏��L�𒴂��ēo�^����O���t�B�b�N�̃��X�g
//		�y�V���O���g���z��p���ăO���[�o������A�N�Z�X����
//		GameSystem�����̂������A�e�ʃQ�[���^�X�N��o�^����
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
	class GameGraphicList
	{
	//---------------------------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using _GrpLst = GameGraphicList;
		using _P_GrpLst = unique_ptr < _GrpLst >;
		static _P_GrpLst	m_inst;		//�V���O���g���C���X�^���X
		GameGraphicList ();		//private �R���X�g���N�^�Œʏ�̎��̉��͋֎~
	public:
		~GameGraphicList () {}		//�f�X�g���N�^��unique_ptr�̂���public
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpLst ( new _GrpLst () ); } }
		static _P_GrpLst & Inst () { return m_inst; }	//�C���X�^���X�擾
	//---------------------------------------------------------------------
	
	private:
		P_TASK_LST		m_pGrpTaskList;		//�匳�ƂȂ�^�X�N���X�g

	public:
		//@info ���p�O��NewTaskList()���蓮�ŌĂ�
		//�Ώۃ^�X�N���X�g��V�݂��ĕԂ�
		P_TASK_LST NewTaskList ();

		//�Ώۃ^�X�N���X�g��ݒ�
//		void SetpTaskList ( P_TASK_LST p ) { m_pGrpTaskList = p; }

		//�Ώۃ^�X�N���X�g���擾
		P_TASK_LST GetpTaskList () { return m_pGrpTaskList; }

		//�Đݒ��Ɏ蓮�ŏ�����
		void Load ();
		void Init ();

		//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
		//�`��Z�ʒu(��:1.f �` 0.0f:�O) "GameGraphicConst.h"�� Z_BG �ȂǂŒ萔���錾���Ă���
		void InsertByZ ( P_GrpCr pTask );

		//�Ώۃ^�X�N����O
		void Erase ( P_Task pTask ) { m_pGrpTaskList->EraseTask ( pTask ); }

		//�Đݒ�
		void Reset ();

		//�S����
		void Clear ();
	};

	using GrpLst = GameGraphicList;
	using UP_GrpLst = unique_ptr < GrpLst >;

#define		GRPLST_CREATE	GrpLst::Create
#define		GRPLST_MAKE		GrpLst::Inst()->NewTaskList
#define		GRPLST_INSERT	GrpLst::Inst()->InsertByZ
#define		GRPLST_ERASE	GrpLst::Inst()->Erase
#define		GRPLST_RESET	GrpLst::Inst()->Reset
#define		GRPLST_CLEAR	GrpLst::Inst()->Clear
#define		GRPLST_LOAD		GrpLst::Inst()->Load
#define		GRPLST_INIT		GrpLst::Inst()->Init

}	//namespace GAME



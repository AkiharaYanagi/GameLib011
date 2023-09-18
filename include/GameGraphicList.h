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
		~GameGraphicList ();	//�f�X�g���N�^��unique_ptr�̂���public
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpLst ( new _GrpLst () ); } }
		static _P_GrpLst & Inst () { return m_inst; }	//�C���X�^���X�擾
	//---------------------------------------------------------------------
	
	private:
		PLP_GrpCr		ml_GrpMain;		//�O���t�B�b�N ���C�� ���X�g
		PLP_GrpCr		ml_GrpSys;		//�O���t�B�b�N �V�X�e�� ���X�g

//		bool			m_pause;		//�ꎞ��~

	public:

		void Load ();
		void Rele ();
		void Reset ();
		void Init ();

		//@info ����̓^�X�N���X�g���ōs��
		void Move ();

		//�`��
		void Draw ();
		void DrawVertex ();

		//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
		//�`��Z�ʒu(��:1.f �` 0.0f:�O) "GameGraphicConst.h"�� Z_BG �ȂǂŒ萔���錾���Ă���
		void InsertByZ_Main ( P_GrpCr pGrpCr );
		void InsertByZ_Sys ( P_GrpCr pGrpCr );

		//�Ώۃ^�X�N����O
		void Remove_Main ( P_GrpCr p ) { ml_GrpMain->remove ( p ); }
		void Erase_Sys ( P_GrpCr p ) { ml_GrpMain->remove ( p ); }

		//�Ώۃ^�X�N���X�g���擾
		PLP_GrpCr GetpGrpList_Main () { return ml_GrpMain; }
		PLP_GrpCr GetpGrpList_Sys () { return ml_GrpSys; }

		//�S����
		void Clear ();
		void Clear_Main ();
		void Clear_Sys ();

		//�ꎞ��~ (Move()�͍s��Ȃ����ADraw()�͍s��)
//		void Pause ( bool b ) { m_pause = b; }

	private:
		//�}��
		void InsertByZ ( PLP_GrpCr plp_grp, P_GrpCr pGrpCr );
	};

	using GrpLst = GameGraphicList;
	using UP_GrpLst = unique_ptr < GrpLst >;


#define		GRPLST_CREATE	GrpLst::Create

#define		GRPLST_RESET	GrpLst::Inst()->Reset
#define		GRPLST_LOAD		GrpLst::Inst()->Load
#define		GRPLST_RELE		GrpLst::Inst()->Rele
#define		GRPLST_INIT		GrpLst::Inst()->Init
#define		GRPLST_MOVE		GrpLst::Inst()->Move
#define		GRPLST_DRAW		GrpLst::Inst()->Draw
#define		GRPLST_DRAW_VERTEX		GrpLst::Inst()->DrawVertex

#define		GRPLST_INSERT_MAIN	GrpLst::Inst()->InsertByZ_Main
#define		GRPLST_INSERT_SYS	GrpLst::Inst()->InsertByZ_Sys

#define		GRPLST_REMOVE_MAIN	GrpLst::Inst()->Remove_Main
#define		GRPLST_REMOVE_SYS	GrpLst::Inst()->Remove_Sys

#define		GRPLST_CLEAR	GrpLst::Inst()->Clear
#define		GRPLST_CLEAR_MAIN	GrpLst::Inst()->Clear
#define		GRPLST_CLEAR_SUB	GrpLst::Inst()->Clear

#define		GRPLST_PAUSE	GrpLst::Inst()->Pause

}	//namespace GAME



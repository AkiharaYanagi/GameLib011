//=================================================================================================
//
// GameGraphicArray �w�b�_�t�@�C��
//
//	Z�l��p���ă\�[�g����GameGpraphic�̔z��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "../Const.h"
#include "GameTask.h"
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GameGraphicArray : public GameTaskVector
	{
	//---------------------------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using _GrpAry = GameGraphicArray;
		using _P_GrpAry = unique_ptr < _GrpAry >;
		static _P_GrpAry		m_inst;		//�V���O���g���C���X�^���X
		GameGraphicArray () {}		//private �R���X�g���N�^�Œʏ�̎��̉��͋֎~
	public:
		~GameGraphicArray () {}		//�f�X�g���N�^��unique_ptr�̂���public
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpAry ( new _GrpAry () ); } }
		static _P_GrpAry & instance () { return m_inst; }	//�C���X�^���X�擾
	//---------------------------------------------------------------------
	public:

		//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
		void InsertByZ ( P_GrpBs pTask );
	};


	using GrpAry = GameGraphicArray;
	using P_GrpAry = unique_ptr < GrpAry >;


}	//namespace GAME



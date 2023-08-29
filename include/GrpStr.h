//=================================================================================================
//
// GrpStr �w�b�_�t�@�C��
//	�P���ȕ�����̃O���t�B�b�N
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
	//�����񂩂琶�������Q�[���e�N�X�`��
	class GameTextureFromString : public TxBs
	{
		tstring		m_str;

	public:
		GameTextureFromString ();
		GameTextureFromString ( const GameTextureFromString& rhs ) = delete;
		~GameTextureFromString ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR str );
	};

	using TxStr = GameTextureFromString;
	using P_TxStr = shared_ptr < TxStr >;


	//-------------------------------------
	class GrpStr : public GrpApTx
	{
		P_TxStr		m_tx;

	public:
		GrpStr ();
		GrpStr ( const GrpStr & rhs ) = delete;
		~GrpStr ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR str );
	};

	using P_GrpStr = shared_ptr < GrpStr >;


}	//namespace GAME



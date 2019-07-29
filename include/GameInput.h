//=================================================================================================
//
// GameInput �w�b�_�t�@�C��
//	1�t���[���ɂ�����L�[���͂��Q�[�����͂ɕϊ�����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameLibConst.h"
#include "KeyInput.h"
#include "GameKey.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameInput
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
		using P_GameInput = unique_ptr < GameInput >;
		static P_GameInput m_inst;
		GameInput ();
		GameInput ( const GameInput & rhs ) = delete;
	public:
		~GameInput () = default;
		static P_GameInput & instance () { return m_inst; }
		static void Create () { if ( ! m_inst ) { m_inst = P_GameInput ( new GameInput () ); } }
	//--------------------------------------------------

		GameKey Get ( PLAYER_ID player_id, bool dirRight );
	};

#define		INPUT_GAMEKEY	GameInput::instance()->Get


}	//namespace GAME


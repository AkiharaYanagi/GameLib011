//=================================================================================================
//
// GameInput ヘッダファイル
//	1フレームにおけるキー入力をゲーム入力に変換する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameLibConst.h"
#include "KeyInput.h"
#include "GameKey.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameInput
	{
	//--------------------------------------------------
	//シングルトンパターン
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



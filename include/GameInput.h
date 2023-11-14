//=================================================================================================
//
// GameInput ヘッダファイル
//	ゲーム1フレームにおけるキー入力を
//	格闘ゲームにおける１ｐ２ｐの向きに修正して入力データに変換する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameLibConst.h"
#include "KeyInput.h"
#include "_GameKey.h"
#include "_GameKeyCommand.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameInput
	{
	//--------------------------------------------------
	//シングルトンパターン
		using P_GameInput = std::unique_ptr < GameInput >;
		static P_GameInput m_inst;
		GameInput ();
		GameInput ( const GameInput & rhs ) = delete;
	public:
		~GameInput () = default;
		static P_GameInput & instance () { return m_inst; }
		static void Create () { if ( ! m_inst ) { m_inst = P_GameInput ( new GameInput () ); } }
	//--------------------------------------------------

		_GameKey Get ( PLAYER_ID player_id, bool dirRight );
	};

#define		INPUT_GAMEKEY	GameInput::instance()->Get


}	//namespace GAME



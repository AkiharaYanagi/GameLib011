//------------------------------------------------------------------
//
// _GameKeyCommand ヘッダ
//	コマンド判定用の１フレーム毎の入力データ
//		ゲーム上の記録データ(_GameKey)と異なる点は、
//		レバーは１つにまとめ、判定用にWILDや否定のフラグなどを持つ
//
//------------------------------------------------------------------
// ◆判定は7種類
// 
//	[__] 押し続けた状態
//	[--] 離し続けた状態		
//	[-_] 押した瞬間		
//	[_-] 離した瞬間		
//	[**] どの状態でも	
//	[*_] 現在のみ押した状態
//	[*-] 現在のみ離した状態
// 
//------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <map>
using namespace std;
#include "DebugLibrary.h"

#include "_GameKey.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _GameKeyCommand
	{
	public:
		//入力状態
		enum GAME_KEY_STATE
		{
			GAME_KEY_OFF,		// 押し続けた状態
			GAME_KEY_ON,		// 離し続けた状態
			GAME_KEY_PUSH,		// 押した瞬間
			GAME_KEY_RELE,		// 離した瞬間
			GAME_KEY_WILD,		// どの状態でも
			GAME_KEY_IS,		// 現在のみ押した状態
			GAME_KEY_NIS,		// 現在のみ離した状態
		};

		//レバー方向(10キー)をenumに置換
		enum GAME_KEY_LVR_CMD
		{
			LVR_CMD_1 = 0,
			LVR_CMD_2 = 1,
			LVR_CMD_3 = 2,
			LVR_CMD_6 = 3,
			LVR_CMD_9 = 4,
			LVR_CMD_8 = 5,
			LVR_CMD_7 = 6,
			LVR_CMD_4 = 7,
		};

	private:
		GAME_KEY_STATE m_Lvr [ _GameKey::LVR_NUM ];		//レバー状態
		GAME_KEY_STATE m_Btn [ _GameKey::BTN_NUM ];		//ボタン状態
		bool	m_bNot;		//否定

	public:
		_GameKeyCommand ();
		_GameKeyCommand ( const _GameKeyCommand & rhs );	//コピー可能
		~_GameKeyCommand ();

		//比較
		bool CompareTarget ( _GameKey gameKeyData ) const;

		//向き指定の比較
		//thisの状態がチェックするコマンド条件、引数がプレイヤ入力
		//引数：コマンド成立条件となるゲームキー状態, キャラクタ向き(右正)
		//戻値：適合したらtrue、それ以外はfalse
		bool CompareTarget ( _GameKey gameKeyData, bool dirRight ) const;

		//-----------------------------------------------------------------
		//レバー(方向指定)
		void SetLvr ( UINT index, GAME_KEY_STATE state ) { m_Lvr[index] = state; }
		void SetaLvr ( GAME_KEY_STATE state_ary [] );
		GAME_KEY_STATE GetLvr ( UINT index ) const { return m_Lvr[index]; }

#if 0
//		int IdLvr = 0;		//現在レバーインデックス
		//レバー(1方向)
//		GAME_KEY_LVR_CMD GetKeyLvrCmd () const;
		bool IsKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const;
		bool PushKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const;
#endif // 0

		//ボタン
		void SetBtn ( UINT index, GAME_KEY_STATE state ) { m_Btn[index] = state; }
		void SetaBtn ( GAME_KEY_STATE state_ary [] );
		GAME_KEY_STATE GetButton ( UINT index ) const { return m_Btn[index]; }

		//否定のフラグ
		void SetNot ( bool b ) { m_bNot = b; }
		bool GetNot () const { return m_bNot; }
		//-----------------------------------------------------------------

#if 0
	private:
		//内部利用関数
		//Is == ( 現在押されている状態 ( ON || PUSH ) )
		bool Is ( _GameKey::GAME_KEY_LEVER lvr ) const;
		bool IsNeutral () const;
		bool Is2E () const;
		bool Is6E () const;
		bool Is8E () const;
		bool Is4E () const;
#endif // 0
	};


	using V_GAME_KEY_CMD = vector < _GameKeyCommand >;
	using KEY_ST = _GameKeyCommand::GAME_KEY_STATE;


}	//namespace GAME


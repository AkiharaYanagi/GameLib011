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

		//レバーを１つにまとめる
		enum GAME_KEY_LVR_CMD
		{
			LVR_CMD_N = 0,	//入力なし

			LVR_CMD_1 = 1,
			LVR_CMD_2 = 2,
			LVR_CMD_3 = 3,
			LVR_CMD_6 = 4,
			LVR_CMD_9 = 5,
			LVR_CMD_8 = 6,
			LVR_CMD_7 = 7,
			LVR_CMD_4 = 8,

			LVR_CMD_2E = 9,		//下要素
			LVR_CMD_6E = 10,	//右要素
			LVR_CMD_8E = 11,	//上要素
			LVR_CMD_4E = 12,	//左要素
		};

	private:
		//レバー状態
		GAME_KEY_STATE m_Lvr [ _GameKey::_LVR_NUM ];

		//現在レバーインデックス
		int IdLvr = 0;

		//ボタン状態
		GAME_KEY_STATE m_Btn [ _GameKey::_BTN_NUM ];

		//否定
		bool	m_bNot;

	public:
		_GameKeyCommand ();
		_GameKeyCommand ( const _GameKeyCommand & rhs );
		~_GameKeyCommand ();

		//比較
		//thisの状態がチェックするコマンド条件、引数がプレイヤ入力
		//引数：コマンド成立条件となるゲームキー状態, キャラクタ向き(右正)
		//戻値：適合したらtrue、それ以外はfalse
		bool CompareTarget ( _GameKey gameKeyData, bool dirRight ) const
		{
			return false;
		}

		bool CompareTarget ( _GameKey gameKeyData ) const;


		//レバー(方向指定)
		void SetLvr ( UINT index, GAME_KEY_STATE state ) { m_Lvr[index] = state; }
		GAME_KEY_STATE GetLvr ( UINT index ) const { return m_Lvr[index]; }

		//レバー(1方向)
//		GAME_KEY_LVR_CMD GetKeyLvrCmd () const;
		bool IsKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const;
		bool PushKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const;


		//ボタン
		void SetBtn ( UINT index, GAME_KEY_STATE state ) { m_Btn[index] = state; }
		GAME_KEY_STATE GetButton ( UINT index ) const { return m_Btn[index]; }

		//否定のフラグ
		void SetNot ( bool b ) { m_bNot = b; }
		bool GetNot () const { return m_bNot; }

	private:
		//内部利用関数
		//Is == ( 現在押されている状態 ( ON || PUSH ) )
		bool Is ( _GameKey::GAME_KEY_LEVER lvr ) const;
		bool IsNeutral () const;
		bool Is2E () const;
		bool Is6E () const;
		bool Is8E () const;
		bool Is4E () const;
	};

	using V_GAME_KEY_CMD = vector < _GameKeyCommand >;


}	//namespace GAME


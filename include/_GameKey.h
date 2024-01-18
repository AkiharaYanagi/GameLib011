//------------------------------------------------------------------
//	ゲーム入力キー
//------------------------------------------------------------------
// ◆ゲームメインにおける1フレーム中のキー入力状態(レバー, ボタン)
// ◆8方向レバー(Lever)、ボタン４つ(Button)を表す
// ◆レバー別方向も同時押しに対応する
//
//------------------------------------------------------------------
//	【Lever】
// [7] [8] [9]
//
// [4] [_] [6]
//				【Button】
// [1] [2] [3]	,[0], [1], [2], [3]
//------------------------------------------------------------------
//
// ◆データとして現在フレーム、前フレーム情報を持つ
// (..., -2, [-1, 0], 2, 3, ...)[F]
//
//------------------------------------------------------------------
//
// レバーアイコン表示順は12369874(テンキー表示で１から反時計回り)
// レバーにも瞬間の状態を記述
//
// 『入力状態を持つクラス』と『コマンドの１フレーム条件のクラス』を分割する
// コマンドとして「否定」フラグ→「指定のゲームキー状態でなくなったとき」
//-------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <map>
#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _GameKey
	{
	public:
		//方向キー
		enum GAME_KEY_LEVER
		{
			LVR_1 = 0,
			LVR_2 = 1,
			LVR_3 = 2,
			LVR_6 = 3,
			LVR_9 = 4,
			LVR_8 = 5,
			LVR_7 = 6,
			LVR_4 = 7,
		};
		static const int LVR_NUM = 8;

		//ボタン
		enum GAME_KEY_BUTTON
		{
			BTN_0 = 0,
			BTN_1 = 1,
			BTN_2 = 2,
			BTN_3 = 3,
			BTN_4 = 4,
			BTN_5 = 5,
			BTN_6 = 6,
			BTN_7 = 7,
		};
		static const int BTN_NUM = 8;

	private:
		bool Lvr [ LVR_NUM ]	 = { false };	//レバー状態
		bool PreLvr [ LVR_NUM ] = { false };	//前レバー状態
		bool Btn [ BTN_NUM ]	 = { false };	//ボタン状態
		bool PreBtn [ BTN_NUM ] = { false };	//前ボタン状態

	public:
		_GameKey ();
		_GameKey ( const _GameKey & rhs );
		~_GameKey ();

		//更新(今回のキーを前回に保存する)
//		void Update ();
		//前回のキーを今回に保存する)
		void ReservePrevious ( const _GameKey gkPrev );

		bool GetLvr ( UINT index ) const { return Lvr[index]; }
		void SetLvr ( UINT index, bool b ) { Lvr[index] = b; }
		void SetLvrOff ();
		bool GetPreLvr ( UINT index ) const { return PreLvr[index]; }
		void SetPreLvr ( UINT index, bool b ) { PreLvr[index] = b; }

		bool GetBtn ( UINT index ) const { return Btn[index]; }
		void SetBtn ( UINT index, bool b ) { Btn[index] = b; }
		bool GetPreBtn ( UINT index ) const { return PreBtn[index]; }
		void SetPreBtn ( UINT index, bool b ) { PreBtn[index] = b; }
	};

	using V_GAME_KEY = std::vector < _GameKey >;


}	//namespace GAME


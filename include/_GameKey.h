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
using namespace std;
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
		static const int LVR_NUM;
		enum _tagLvr { _LVR_NUM = 8 };

		//ボタン
		static const int BTN_NUM = 4;
		enum _tagBtn { _BTN_NUM = 4 };

	private:
		bool Lvr [ _LVR_NUM ]	 = { false };	//レバー状態
		bool PreLvr [ _LVR_NUM ] = { false };	//前レバー状態
		bool Btn [ _BTN_NUM ]	 = { false };	//ボタン状態
		bool PreBtn [ _BTN_NUM ] = { false };	//前ボタン状態

	public:
		_GameKey ();
		_GameKey ( const _GameKey & rhs );
		~_GameKey ();

		//今回のキーを前回に保存する
		void Update ();

		bool GetLvr ( UINT index ) { return Lvr[index]; }
		void SetLvr ( UINT index, bool b ) { Lvr[index] = b; }
		bool GetPreLvr ( UINT index ) { return PreLvr[index]; }
		void SetPreLvr ( UINT index, bool b ) { PreLvr[index] = b; }

		bool GetBtn ( UINT index ) { return Lvr[index]; }
		void SetBtn ( UINT index, bool b ) { Btn[index] = b; }
		bool GetPreBtn ( UINT index ) { return PreLvr[index]; }
		void SetPreBtn ( UINT index, bool b ) { PreBtn[index] = b; }
	};

	using V_GAME_KEY = vector < _GameKey >;


}	//namespace GAME


﻿//=================================================================================================
//
//	ネットワークコモン
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
//==============================================================================
//		定数
//==============================================================================
	enum GAME_NET_MODE
	{
		SINGLE,
		DOUBLE_1P_CPU,
		DOUBLE_1P_2P,
		DOUBLE_CPU_CPU,
		NETWORK_SERVER_1P,
		NETWORK_SERVER_2P,
		NETWORK_CLIENT_1P,
		NETWORK_CLIENT_2P,
		GAME_MODE_NUM,
	};

	//転送用データ
	struct NET_GAME_INPUT
	{
		UINT frame;		//記録フレーム
		byte btIsKey;	//キーを押した状態
		byte btPushKey;	//キーを押した瞬間(前回false,今回true)
		bool end;		//終了フラグ
	};


}	//namespace GAME


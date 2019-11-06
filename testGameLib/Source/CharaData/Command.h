//=================================================================================================
//
// Command ヘッダファイル
//	ゲーム入力キーの配列を特定の組み合わせで保持する
//	実際に入力されたものの記録と、スクリプト分岐の条件に用いる
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Const.h"
#include "Game.h"
#include "GameKey.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Command
	{
		tstring			m_name;			//名前
		V_GAME_KEY		m_vecGameKey;	//キー配列
		UINT			m_limitTime;	//入力受付時間

	public:
		Command ();
		Command ( const Command & rhs ) = delete;	//コピー禁止
		~Command ();

		//比較
		bool Compare ( const V_GAME_KEY & vecGameKey, bool dirRight );

		//名前
		tstring GetName () const { return m_name; }
		void SetName ( tstring name ) { m_name.assign ( name ); }

		//キー配列
//		V_GAME_KEY * GetpVecGameKey () { return & m_vecGameKey; }
		void AddGameKey ( GameKey key ) { m_vecGameKey.push_back ( key ); }

		//入力受付時間
		UINT GetLimitTime () const { return m_limitTime; }
		void SetLimitTime ( UINT limitTime ) { m_limitTime = limitTime; }
	};

	using WP_Command = weak_ptr < Command >;
	using P_Command = shared_ptr < Command >;
	using VP_Command = vector < P_Command >;

}	//namespace GAME



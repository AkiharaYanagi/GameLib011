//=================================================================================================
//
//	Action ヘッダファイル
//		スクリプトの一連、固有の値を追加
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
#include "Sequence.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//==================================================================================
	//	◆アクション属性
	//		STAND, MOVE, DASH, ATTACK_L, ATTACK_M, ATTACK_H, CLANG, AVOID, DOTTY, DAMAGED, DEMO, OTHER
	//
	//==================================================================================

	//================================================================
	//	アクション		各フレームのスクリプトリストを持つ
	//		┣[]スクリプト
	//		┣次アクション
	//		┣消費バランス値
	//		┣アクション属性
	//================================================================
	
	class Action : public Sequence
	{
		tstring			m_name;		//名前
		UINT			m_cost;		//消費コスト
		ACTION_CATEGORY	m_category;		//アクション属性

	public:
		Action ();
		Action ( const Action & rhs ) = delete;
		~Action ();

		//名前
		void SetName ( tstring name ) { m_name.assign ( name ); }
		tstring GetName () const { return m_name; }

		//アクション属性
		ACTION_CATEGORY GetCategory () const { return m_category; }
		void SetCategory ( ACTION_CATEGORY category ) { m_category = category; }

		int GetBalance () { return 0; }
};

	using P_Action = shared_ptr < Action >;
	using VP_Action = vector < P_Action >;
	using PVP_Action = shared_ptr < VP_Action >;


}	//namespace GAME



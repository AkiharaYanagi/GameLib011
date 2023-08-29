//=================================================================================================
//
// GrpStr ヘッダファイル
//	単純な文字列のグラフィック
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//文字列から生成されるゲームテクスチャ
	class GameTextureFromString : public TxBs
	{
		tstring		m_str;

	public:
		GameTextureFromString ();
		GameTextureFromString ( const GameTextureFromString& rhs ) = delete;
		~GameTextureFromString ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR str );
	};

	using TxStr = GameTextureFromString;
	using P_TxStr = shared_ptr < TxStr >;


	//-------------------------------------
	class GrpStr : public GrpApTx
	{
		P_TxStr		m_tx;

	public:
		GrpStr ();
		GrpStr ( const GrpStr & rhs ) = delete;
		~GrpStr ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR str );
	};

	using P_GrpStr = shared_ptr < GrpStr >;


}	//namespace GAME



//=================================================================================================
//
// GameGraphicArray ヘッダファイル
//
//	Z値を用いてソートするGameGpraphicの配列
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "../Const.h"
#include "GameTask.h"
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GameGraphicArray : public GameTaskVector
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using _GrpAry = GameGraphicArray;
		using _P_GrpAry = unique_ptr < _GrpAry >;
		static _P_GrpAry		m_inst;		//シングルトンインスタンス
		GameGraphicArray () {}		//private コンストラクタで通常の実体化は禁止
	public:
		~GameGraphicArray () {}		//デストラクタはunique_ptrのためpublic
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpAry ( new _GrpAry () ); } }
		static _P_GrpAry & instance () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------
	public:

		//Z値で降順ソートされた位置に挿入
		void InsertByZ ( P_GrpBs pTask );
	};


	using GrpAry = GameGraphicArray;
	using P_GrpAry = unique_ptr < GrpAry >;


}	//namespace GAME



//=================================================================================================
//
// GameGraphicArray ヘッダファイル
//		Z値を用いてソートするGameGpraphicの配列
//		オブジェクトを保持してシングルトンから設定する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
//--------------------------------------
//		【Z値(0.0f～0.9f)】
//		Z_BG	0.1f	背景
//		Z_EFB	0.4f	エフェクト後
//		Z_CH	0.5f	キャラ基本位置
//		Z_EF	0.6f	エフェクト前
//		Z_SYS	0.9f	システム表示
//--------------------------------------

	//@todo Ef関連で生成と破棄が多数回にわたるのでListの検討

//クラス
	class GameGraphicArray
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using _GrpAry = GameGraphicArray;
		using _P_GrpAry = unique_ptr < _GrpAry >;
		static _P_GrpAry		m_inst;		//シングルトンインスタンス
		GameGraphicArray ();		//private コンストラクタで通常の実体化は禁止
	public:
		~GameGraphicArray () {}		//デストラクタはunique_ptrのためpublic
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpAry ( new _GrpAry () ); } }
		static _P_GrpAry & instance () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------
	
	private:
		P_TASK_VEC		m_pTaskVec;		//大元となるタスクベクタ

	public:
		//Z値で降順ソートされた位置に挿入
		void InsertByZ ( P_GrpBs pTask );

		//対象タスクを取外
		void Erase ( P_Task pTask ) { m_pTaskVec->EraseTask ( pTask ); }

		//対象タスク配列のポインタ
		P_TASK_VEC GetpInstance () { return m_pTaskVec; }
	};


	using GrpAry = GameGraphicArray;
	using UP_GrpAry = unique_ptr < GrpAry >;
#define		GRPARY_INSERT	GrpAry::instance()->InsertByZ
#define		GRPARY_ERASE	GrpAry::instance()->Erase

}	//namespace GAME



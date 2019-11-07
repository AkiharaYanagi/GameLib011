//=================================================================================================
//
// GameGraphicArray ヘッダファイル
//		Z値を用いてソートするGameGpraphicの配列
//		【シングルトン】グローバルかつ単一なオブジェクトを保持
//		シーンをまたぐときにリセット
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
		P_TASK_VEC GetpTaskVec () { return m_pTaskVec; }

		//再設定
		void Reset ();

		//全消去
		void Clear ();
	};


	using GrpAry = GameGraphicArray;
	using UP_GrpAry = unique_ptr < GrpAry >;

#define		GRPARY_INSERT	GrpAry::instance()->InsertByZ
#define		GRPARY_ERASE	GrpAry::instance()->Erase
#define		GRPARY_RESET	GrpAry::instance()->Reset
#define		GRPARY_CLEAR	GrpAry::instance()->Clear

}	//namespace GAME



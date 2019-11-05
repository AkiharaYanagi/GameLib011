//=================================================================================================
//
// GameGraphicList ヘッダファイル
//		Z値を用いてソートするGameGpraphicのリストのポインタを保持する
//		【シングルトン】を用いてグローバルからアクセスする
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
	class GameGraphicList
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using _GrpLst = GameGraphicList;
		using _P_GrpLst = unique_ptr < _GrpLst >;
		static _P_GrpLst	m_inst;		//シングルトンインスタンス
		GameGraphicList ();		//private コンストラクタで通常の実体化は禁止
	public:
		~GameGraphicList () {}		//デストラクタはunique_ptrのためpublic
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpLst ( new _GrpLst () ); } }
		static _P_GrpLst & Inst () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------
	
	private:
		P_TASK_LST		m_pTaskList;		//大元となるタスクリスト

	public:
		//対象タスクリストを新設して返す
		P_TASK_LST NewTaskList ();

		//対象タスクリストを設定
		void SetpTaskList ( P_TASK_LST p ) { m_pTaskList = p; }

		//対象タスクリストを取得
		P_TASK_LST GetpTaskList () { return m_pTaskList; }

		//Z値で降順ソートされた位置に挿入
		void InsertByZ ( P_GrpBs pTask );

		//対象タスクを取外
		void Erase ( P_Task pTask ) { m_pTaskList->EraseTask ( pTask ); }

		//再設定
		void Reset ();

		//全消去
		void Clear ();
	};

	using GrpLst = GameGraphicList;
	using UP_GrpLst = unique_ptr < GrpLst >;

#define		GRPLST_NEW		GrpLst::Inst()->NewTaskList
#define		GRPLST_INSERT	GrpLst::Inst()->InsertByZ
#define		GRPLST_ERASE	GrpLst::Inst()->Erase
#define		GRPLST_RESET	GrpLst::Inst()->Reset
#define		GRPLST_CLEAR	GrpLst::Inst()->Clear

}	//namespace GAME



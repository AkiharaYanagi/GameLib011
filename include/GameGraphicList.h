//=================================================================================================
//
// ◆GameGraphicList
//		グラフィック表示の前後を全体で統一する
//		Z値を用いてソートするGameGpraphicのリストのポインタを保持する
//		オブジェクトの所有を超えて登録するグラフィックのリスト
//		【シングルトン】を用いてグローバルからアクセスする
//		GameSystemが実体を持ち、各位ゲームタスクを登録する
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

//		P_TASK_LST		m_pGrpTaskList;		//大元となるタスクリスト

		list < P_GrpCr >	m_GrpLst;		//グラフィック メイン リスト
		list < P_GrpCr >	m_GrpSysLst;		//グラフィック システム リスト

		bool			m_pause;			//一時停止


	public:
		//@info 利用前にNewTaskList()を手動で呼ぶ
		//対象タスクリストを新設して返す
		P_TASK_LST NewTaskList ();

		//対象タスクリストを設定
//		void SetpTaskList ( P_TASK_LST p ) { m_pGrpTaskList = p; }

		//対象タスクリストを取得
//		P_TASK_LST GetpTaskList () { return m_pGrpTaskList; }

		void MakeList ();

		//再設定後に手動で初期化
		void Load ();
		void Init ();

		void Move ();

		void Draw ();
		void DrawVertex ();

		//Z値で降順ソートされた位置に挿入
		//描画Z位置(後:1.f ～ 0.0f:前) "GameGraphicConst.h"に Z_BG などで定数が宣言してある
		void InsertByZ ( P_GrpCr pTask );

		//対象タスクを取外
		void Erase ( P_Task pTask ) { m_pGrpTaskList->EraseTask ( pTask ); }

		//再設定
		void Reset ();

		//全消去
		void Clear ();

		//一時停止 (Move()は行わないが、Draw()は行う)
		void Pause ( bool b ) { m_pause = b; }
	};

	using GrpLst = GameGraphicList;
	using UP_GrpLst = unique_ptr < GrpLst >;

#define		GRPLST_CREATE	GrpLst::Create
#define		GRPLST_MAKE		GrpLst::Inst()->MakeList
#define		GRPLST_INSERT	GrpLst::Inst()->InsertByZ
#define		GRPLST_ERASE	GrpLst::Inst()->Erase
#define		GRPLST_RESET	GrpLst::Inst()->Reset
#define		GRPLST_CLEAR	GrpLst::Inst()->Clear
#define		GRPLST_LOAD		GrpLst::Inst()->Load
#define		GRPLST_INIT		GrpLst::Inst()->Init
#define		GRPLST_MOVE		GrpLst::Inst()->Move
#define		GRPLST_DRAW		GrpLst::Inst()->Draw
#define		GRPLST_DRAW_VERTEX		GrpLst::Inst()->DrawVertex
#define		GRPLST_PAUSE	GrpLst::Inst()->Pause

}	//namespace GAME



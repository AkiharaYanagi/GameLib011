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
		~GameGraphicList ();	//デストラクタはunique_ptrのためpublic
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpLst ( new _GrpLst () ); } }
		static _P_GrpLst & Inst () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------
	
	private:
		PLP_GrpCr		ml_GrpMain;		//グラフィック メイン リスト
		PLP_GrpCr		ml_GrpSys;		//グラフィック システム リスト

//		bool			m_pause;		//一時停止

	public:

		void Load ();
		void Rele ();
		void Reset ();
		void Init ();

		//@info 動作はタスクリスト側で行う
		void Move ();

		//描画
		void Draw ();
		void DrawVertex ();

		//Z値で降順ソートされた位置に挿入
		//描画Z位置(後:1.f ～ 0.0f:前) "GameGraphicConst.h"に Z_BG などで定数が宣言してある
		void InsertByZ_Main ( P_GrpCr pGrpCr );
		void InsertByZ_Sys ( P_GrpCr pGrpCr );

		//対象タスクを取外
		void Remove_Main ( P_GrpCr p ) { ml_GrpMain->remove ( p ); }
		void Erase_Sys ( P_GrpCr p ) { ml_GrpMain->remove ( p ); }

		//対象タスクリストを取得
		PLP_GrpCr GetpGrpList_Main () { return ml_GrpMain; }
		PLP_GrpCr GetpGrpList_Sys () { return ml_GrpSys; }

		//全消去
		void Clear ();
		void Clear_Main ();
		void Clear_Sys ();

		//一時停止 (Move()は行わないが、Draw()は行う)
//		void Pause ( bool b ) { m_pause = b; }

	private:
		//挿入
		void InsertByZ ( PLP_GrpCr plp_grp, P_GrpCr pGrpCr );
	};

	using GrpLst = GameGraphicList;
	using UP_GrpLst = unique_ptr < GrpLst >;


#define		GRPLST_CREATE	GrpLst::Create

#define		GRPLST_RESET	GrpLst::Inst()->Reset
#define		GRPLST_LOAD		GrpLst::Inst()->Load
#define		GRPLST_RELE		GrpLst::Inst()->Rele
#define		GRPLST_INIT		GrpLst::Inst()->Init
#define		GRPLST_MOVE		GrpLst::Inst()->Move
#define		GRPLST_DRAW		GrpLst::Inst()->Draw
#define		GRPLST_DRAW_VERTEX		GrpLst::Inst()->DrawVertex

#define		GRPLST_INSERT_MAIN	GrpLst::Inst()->InsertByZ_Main
#define		GRPLST_INSERT_SYS	GrpLst::Inst()->InsertByZ_Sys

#define		GRPLST_REMOVE_MAIN	GrpLst::Inst()->Remove_Main
#define		GRPLST_REMOVE_SYS	GrpLst::Inst()->Remove_Sys

#define		GRPLST_CLEAR	GrpLst::Inst()->Clear
#define		GRPLST_CLEAR_MAIN	GrpLst::Inst()->Clear
#define		GRPLST_CLEAR_SUB	GrpLst::Inst()->Clear

#define		GRPLST_PAUSE	GrpLst::Inst()->Pause

}	//namespace GAME



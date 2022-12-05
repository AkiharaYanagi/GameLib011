//=================================================================================================
//
// アプリケーション設定ファイル
//
//		・フルスクリーン / ウィンドウ
//		・画面サイズ
//		・画面開始位置
//		・ディスプレイ番号指定
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
	//ウィンドウスタート位置
	enum WINDOW_START_POS
	{
		START_POS_CURSOR,
		START_POS_DISPLAY,
	};

	//定数
	//デフォルトウィンドウサイズ
	enum DEFAULT_WINDOW_SIZE
	{
		DFL_WND_W = 1280,
		DFL_WND_H = 960,
	};


	class AppSettingFile
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using _StgFl = AppSettingFile;
		using _UP_StgFl = unique_ptr < _StgFl >;
		static _UP_StgFl	m_inst;		//シングルトンインスタンス
		AppSettingFile ();		//private コンストラクタで通常の実体化は禁止
	public:
		~AppSettingFile ();	//デストラクタはunique_ptrのためpublic
		static void Create () { if ( ! m_inst ) { m_inst = _UP_StgFl ( new _StgFl () ); } }
		static _UP_StgFl & Inst () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------
	//@info GameSystem でDx3Dにパラメータを渡すためシングルトンで定義する


	private:
		//------------------------------------------------
		//値
		bool	m_bFullscreen;	//フルスクリーン
		int		m_window_w;		//ウィンドウ幅W
		int		m_window_h;		//ウィンドウ高H

		WINDOW_START_POS	m_startPos;		//ウィンドウ開始位置
		int		m_displayNum;	//出力ディスプレイ番号
		//------------------------------------------------

		//基本値
		void	SetDefault ();

	public:

		void Load ();

		//値の取得
		bool GetbFullscreen () const { return m_bFullscreen; }
		UINT GetWindowW () const { return m_window_w; }
		UINT GetWindowH () const { return m_window_h; }

		WINDOW_START_POS GetWindowStartPos () const { return m_startPos; }
		int GetDisplayNum () const { return m_displayNum; }

#if 0
		bool GetbInput1pPlayer () const { return m_input1pPlayer; }
		bool GetbInput2pPlayer () const { return m_input2pPlayer; }
#endif // 0
	};

	using P_SettingFile = unique_ptr < AppSettingFile >;

//シングルトンアクセス用
#define APP_STG	AppSettingFile::Inst()

}	//namespace GAME


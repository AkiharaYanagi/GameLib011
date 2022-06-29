//=================================================================================================
//
// アプリケーション設定ファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
//#include <windows.h>
#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
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
		bool	m_bFullscreen;
		UINT	m_window_w;
		UINT	m_window_h;

		bool	m_input1pPlayer;
		bool	m_input2pPlayer;

		void	SetDefault ();

	public:

		//値の取得
		bool GetbFullscreen () const { return m_bFullscreen; }
		UINT GetWindowW () const { return m_window_w; }
		UINT GetWindowH () const { return m_window_h; }
		bool GetbInput1pPlayer () const { return m_input1pPlayer; }
		bool GetbInput2pPlayer () const { return m_input2pPlayer; }
	};

	using P_SettingFile = unique_ptr < AppSettingFile >;

//シングルトンアクセス用
#define APP_STG	AppSettingFile::Inst()

}	//namespace GAME


//=================================================================================================
//
// 設定ファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	class SettingFile
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using _StgFl = SettingFile;
		using _UP_StgFl = unique_ptr < _StgFl >;
		static _UP_StgFl	m_inst;		//シングルトンインスタンス
		SettingFile ();		//private コンストラクタで通常の実体化は禁止
	public:
		~SettingFile ();	//デストラクタはunique_ptrのためpublic
		static void Create () { if ( ! m_inst ) { m_inst = _UP_StgFl ( new _StgFl () ); } }
		static _UP_StgFl & instance () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------
		bool	m_bFullscreen;
		UINT	m_window_x;
		UINT	m_window_y;

		void	SetDefault ();

	public:

		//値の取得
		bool GetbFullscreen () { return m_bFullscreen; }
		UINT GetWindowX () const { return m_window_x; }
		UINT GetWindowY () const { return m_window_y; }
	};

	using P_SettingFile = unique_ptr < SettingFile >;

}	//namespace GAME


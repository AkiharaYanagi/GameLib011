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
		using P_SettingFile = unique_ptr < SettingFile >;
		static P_SettingFile		m_inst;		//シングルトンインスタンス
		SettingFile ();		//private コンストラクタで通常の実体化は禁止
	public:
		~SettingFile ();		//デストラクタはunique_ptrのためpublic
		static void Create () { if ( ! m_inst ) { m_inst = P_SettingFile ( new SettingFile () ); } }
		static unique_ptr < SettingFile >& instance () { return m_inst; }	//インスタンス取得
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

}	//namespace GAME


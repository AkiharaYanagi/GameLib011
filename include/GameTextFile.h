//=================================================================================================
//
// ゲームテキストファイル　ヘッダ
//
//	テキストファイルからの文字列のロードと管理
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include <fstream>
#include <locale>


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	
	//テキストファイル読込
	class TextFile 
	{
		std::ifstream			m_ifstrm;		//入力ファイルストリーム
		tstring*				m_strArray;		//テキスト保存配列
		UINT			m_nLine;		//テキスト保存行数
		UINT			m_index;		//現在位置

	public:
		TextFile ();
		TextFile ( const TextFile& rhs ) = delete;
		~TextFile ();

		void Load ();
		
		tstring GetStr ( UINT index ) { assert ( index < m_nLine ); return m_strArray[index]; }
		LPCTSTR GetLPCTSTR ( UINT index ) { assert ( index < m_nLine ); return m_strArray[index].c_str(); }
		UINT GetMaxLine () { return m_nLine; }
	};



}	//namespace GAME


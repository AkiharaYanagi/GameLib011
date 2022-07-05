//=================================================================================================
//
// ゲーム画面へのデバッグテキスト表示
//		ゲーム画面への頂点を用いたテキスト表示
//		DebugTextNum = 15までのインデックスを指定
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Dx3D.h"
#include "DxVertex.h"
#include "GameText.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	class DebugOutGameWindow
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_DBG_WND = unique_ptr < DebugOutGameWindow >;
		static P_DBG_WND	m_inst;
		DebugOutGameWindow ();
		DebugOutGameWindow ( const DebugOutGameWindow & rhs ) = delete;
	public:
		~DebugOutGameWindow ();
		static void Create();
		static P_DBG_WND & instance() { return m_inst; }
	//--------------------------------------------------

	private:

	public:
		enum Const_DebugOutGameWindow
		{
			DebugTextNum = 15,
		};
	private:
		TX				m_texture[DebugTextNum];		//テクスチャ
		DxVertex4		m_vertex[DebugTextNum];			//頂点処理オブジェクト
		tstring			m_tstr[DebugTextNum];			//文字列

		//デバッグ用固定表示
		//FPS
		//TIme

		TX				m_testTx;
		DxVertex4		m_testVx;

	public:
		void Load ();
		void Rele ();
		void Reset ( LPDIRECT3DDEVICE9 d3dDevice );	//再設定
		void Move ();

		//頂点による描画
		void DrawVertex ();

		//文字列指定
		void SetStr ( UINT index, LPCTSTR lpctstr );
		void SetStr ( UINT index, tstring& tstr );

		//位置指定
		void SetPos ( UINT index, float x, float y ) { m_vertex[index].SetPos ( x, y ); }

		//画面にテキスト描画する文字列フォーマットを設定
		void DebugOutf ( UINT index, LPCTSTR format, ... );

		//非表示
		void Off ();

	};

	using DBGO_WND = DebugOutGameWindow;

//シングルトンアクセス用
#define DBGOUT_WND		DebugOutGameWindow::instance()
#define DBGOUT_WND_F	DebugOutGameWindow::instance()->DebugOutf
//#define TRACEW_CHF	DebugOutGameWindow::instance()->DebugOutchf

}	//namespace GAME



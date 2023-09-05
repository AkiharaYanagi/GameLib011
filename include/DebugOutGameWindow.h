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
#include "DebugLibrary.h"
#include "Dx3D.h"
#include "DxVertex.h"
#include "GameTextLibrary.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
	using UP_CTSTR = unique_ptr < TCHAR >;

	//=====================================================
	//固定表示
	class ConstDebugOut
	{
		bool		m_valid;
		TX			m_tx;		//テクスチャ
		Vx_Rect		m_vx;		//頂点集合(矩形)

	public:
		ConstDebugOut ();
		ConstDebugOut ( const ConstDebugOut & rhs ) = delete;
		~ConstDebugOut ();

		void Load ();
		void Rele ();
		void Reset ();
		void Move ();
		void Draw ();

		void SetPos ( VEC2 v );
		void SetStr ( UP_TSTR upctstr );
		void SetValid ( bool b ) { m_valid = b; }
	};
	//=====================================================



	// ゲーム画面へのデバッグテキスト表示
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
		static P_DBG_WND & Inst() { return m_inst; }
	//--------------------------------------------------

	private:

	public:
		//定数
		enum Const_DebugOutGameWindow
		{
			DebugTextNum = 15,
			DebugVertexNum = 32,
		};
	private:
		//デバッグ表示配列
		TX			m_texture[DebugTextNum];	//テクスチャ
		Vx_Rect		m_vertex[DebugTextNum];		//頂点処理オブジェクト
		tstring		m_tstr[DebugTextNum];		//文字列

		//デバッグ用固定表示
		ConstDebugOut		m_frame;
		ConstDebugOut		m_FPS;
		ConstDebugOut		m_time;

	public:
		void Load ();
		void Rele ();
		void Reset ( D3DDEV d3dDevice );	//再設定
		void Move ();
		void DrawVertex ();		//頂点による描画


		//-----------------------------------------------------

		//表示文字列指定
		void SetStr ( UINT index, LPCTSTR lpctstr );
		void SetStr ( UINT index, tstring& tstr );
		void SetStr ( UINT index, UP_TSTR pstr );

		//位置指定
		void SetPos ( UINT index, float x, float y ) { m_vertex[index].SetPos ( x, y ); }

		//画面にテキスト描画する文字列フォーマットを設定
		void DebugOutf ( UINT index, LPCTSTR format, ... );


		//-----------------------------------------------------
		//固定表示 : 稼働時間[F]
		void DebugOutWnd_Time ( LPCTSTR format, ... );
		void SetbDisp_Time ( bool b ) { m_frame.SetValid ( b ); }
		//固定表示 : FPS
		void DebugOutWnd_FPS ( LPCTSTR format, ... );
		void SetbDisp_FPS ( bool b ) { m_FPS.SetValid ( b ); }
		//固定表示 : 動作時間[ms], 描画時間[ms]
		void DebugOutWnd_Move_Draw ( LPCTSTR format, ... );
		void SetbDisp_Move_Draw ( bool b ) { m_time.SetValid ( b ); }


		//-----------------------------------------------------
		//非表示
		void Off ();

	private:
		void DebugOutWnd ( UP_TSTR up_tstr, VP_VxRct& vpVpRct );

	};

	using DBGO_WND = DebugOutGameWindow;


//シングルトンアクセス用
#define DBGOUT_WND		DBGO_WND::Inst()
#define DBGOUT_WND_F	DBGO_WND::Inst()->DebugOutf



}	//namespace GAME



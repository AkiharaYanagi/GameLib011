//=================================================================================================
//
// フェード
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "DxDefine.h"			//DirectX内外共通

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//フェードオブジェクト
	//	グラフィックが保有するタスク
	//	時間と色を指定し、フレーム毎に遷移する(現在色を返す)
	//------------------------------------------------------------
	class Fade
	{
		UINT	m_timer;	//現在時間
		UINT	m_time;		//移行時間

		_CLR	m_color_present;//現在色

		_CLR	m_color_start;	//初期色
		_CLR	m_color_end;	//目標色

	public:
		Fade ();
		Fade ( const Fade & rhs );	//コピー可能
		~Fade ();

		//毎フレーム動作(Move()内先頭で呼ぶ)
		void PreMove ();

		//色保存
		void SetColor ( _CLR clr) { m_color_present = clr; }

		//色取得
		_CLR GetColor () const { return m_color_present; }

		//フェード時間設定
		void SetTime ( UINT time );

		//現在時間（稼働状態）を取得
		UINT GetTimer () const { return m_timer; }

		//色設定
		void SetFadeColor ( _CLR clr_start, _CLR clr_end )
		{
			m_color_start = clr_start; 
			m_color_end = clr_end; 
		}

		//フェード設定
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			SetTime ( time );
			SetFadeColor ( clr_start, clr_end );
			m_color_present = clr_start;
		}

		//終了
		void End ( _CLR clr );

	private:

		//実処理
		void _Fade_Do ();
	};


}	//namespace GAME



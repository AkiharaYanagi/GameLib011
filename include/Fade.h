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
#include "GameTask.h"
//#include "GameGraphicLibrary.h"

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
	class _Fade
	{
		UINT	m_timer;	//現在時間
		UINT	m_time;		//移行時間

		_CLR	m_color_present;//現在色

		_CLR	m_color_start;	//初期色
		_CLR	m_color_end;	//目標色

	public:
		_Fade ();
		_Fade ( const _Fade & rhs ) = delete;
		~_Fade ();

		//毎フレーム動作(Move()内先頭で呼ぶ)
		void PreMove ();

		//色取得
		_CLR GetColor () const { return m_color_present; }

		//フェード時間設定
		void SetTime ( UINT time );

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


//=================================================================================================
//=================================================================================================

#if 0

	class Fade : public GrpAcv
	{
		UINT	m_timer;	//現在時間
		UINT	m_time;		//移行時間

//		_CLR	m_color;	//現在色

		_CLR	m_color_start;	//初期色
		_CLR	m_color_end;	//目標色

		bool	m_active;	//稼働フラグ


	public:
		Fade ();
		Fade ( const Fade & rhs ) = delete;
		~Fade ();

		//毎フレーム動作(Move()内先頭で呼ぶ)
		void PreMove ();
		void Move ();

		//色取得
		_CLR GetColor () const { return m_color; }


		//フェード時間設定
		void SetTime ( UINT time );


		//色設定
		void SetColor ( _CLR clr_start, _CLR clr_end ) { m_color_start = clr_start; m_color_end = clr_end; }

		bool IsActive () const { return m_active; }

		//-----------------------------------
		//具体設定
		//@info 0x00000000 を指定するときD3DXCOLORの初期化のため整数リテラル UL を付ける

		//ホワイトアウト( 0x00ffffff → 0xffffffff )
		void SetWhiteOut ( UINT time ) { SetColor ( 0x00ffffff, 0xffffffff ); SetTime ( time ); }

		//ブラックイン ( 0xff000000 → 0x00000000 )
		void SetDarkIn ( UINT time ) { SetColor ( 0xff000000, 0x00000000UL ); SetTime ( time ); }

		//ブラックアウト( 0x00000000 → 0xff000000 )
		void SetDarkOut ( UINT time ) { SetColor ( 0x00000000UL, 0xff000000 ); SetTime ( time ); }

	private:

		//実処理
		void _Fade ();
	};

	using P_FADE = shared_ptr < Fade >;

#endif // 0


}	//namespace GAME



//=================================================================================================
//
// フェード
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphicLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
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

		//毎フレーム動作
		void PreMove ();
		void Move ();

		//色取得
		_CLR GetColor () const { return m_color; }


		//フェード時間設定
		void SetTime ( UINT time );

		void _Fade ();

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

	};

	using P_FADE = shared_ptr < Fade >;


}	//namespace GAME



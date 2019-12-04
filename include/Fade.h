//=================================================================================================
//
// Fade ヘッダファイル
//		最前面に配置した画面サイズの半透明グラフィックで、フェードイン・アウトを行う
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphicLibrary.h"
#include "Timer.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Fade : public PrmRect
	{
		P_Timer	m_timer;

		_CLR	m_color0;	//初期色
		_CLR	m_color1;	//目標色
		UINT	m_targetTime;		//移行時間

		UINT	m_whiteOutTime;
		UINT	m_darkInTime;
		UINT	m_darkOutTime;

	public:
		Fade ();
		Fade ( const Fade & rhs ) = delete;
		~Fade ();

		void Move ();

		//色設定
		void SetColor ( _CLR clr0, _CLR clr1 ) { m_color0 = clr0; m_color1 = clr1; }
		void SetTime ( UINT t ) { m_targetTime = t; }

		void Start ( UINT time )
		{
			m_targetTime = time;
			PrmRect::SetValid ( true );
			m_timer->Start ();
		}

		//-----------------------------------
		//具体設定
		//@info 0x00指定のときD3DXCOLORの初期化のため整数リテラルULを付ける
		
		//ホワイトアウト( 0x00ffffff → 0xffffffff )
		void SetWhiteOut ( UINT time ) { SetColor ( 0x00ffffff, 0xffffffff ); Start ( time ); }

		//ダークイン ( 0xff000000 → 0x00000000 )
		void SetDarkIn ( UINT time ) { SetColor ( 0xff000000, 0x00000000UL ); Start ( time ); }

		//ダークアウト( 0x00000000 → 0xff000000 )
		void SetDarkOut ( UINT time ) { SetColor ( 0x00000000UL, 0xff000000 ); Start ( time ); }

#if 0
//		bool IsActive () { return m_timer->IsActive (); }
		//ホワイトアウト( 0x00ffffff → 0xffffffff )
		void SetWhiteOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_whiteOutTime = time;
			m_timer->Start (); 
		}

		//ダークイン ( 0xff000000 → 0x00000000 )
		void SetDarkIn ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkInTime = time;
			m_timer->Start ();
		}

		//ダークアウト( 0x00000000 → 0xff000000 )
		void SetDarkOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkOutTime = time;
			m_timer->Start ();
		}
#endif // 0
	};

	using P_Fade = shared_ptr < Fade >;


}	//namespace GAME



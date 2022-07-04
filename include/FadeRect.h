//=================================================================================================
//
// FadeRect ヘッダファイル
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
	class FadeRect : public PrmRect
	{
		P_Timer	m_timer;
		_CLR	m_color0;	//初期色
		_CLR	m_color1;	//目標色

	public:
		FadeRect ();
		FadeRect ( const FadeRect & rhs ) = delete;
		~FadeRect ();

		void Move ();

		//色設定
		void SetColor ( _CLR clr0, _CLR clr1 ) { m_color0 = clr0; m_color1 = clr1; }
		void SetTime ( UINT t )
		{ 
			m_timer->SetTargetTime ( t ); 
		}

		void Start ( UINT time )
		{
			m_timer->SetTargetTime ( time );
			m_timer->Start ();
			PrmRect::SetValid ( true );
		}

		bool IsActive () { return m_timer->IsActive (); }

		//-----------------------------------
		//具体設定
		//@info 0x00000000 を指定するときD3DXCOLORの初期化のため整数リテラル UL を付ける
		
		//ホワイトアウト( 0x00ffffff → 0xffffffff )
		void SetWhiteOut ( UINT time ) { SetColor ( 0x00ffffff, 0xffffffff ); Start ( time ); }

		//ブラックイン ( 0xff000000 → 0x00000000 )
		void SetDarkIn ( UINT time ) { SetColor ( 0xff000000, 0x00000000UL ); Start ( time ); }

		//ブラックアウト( 0x00000000 → 0xff000000 )
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

		//ブラックイン ( 0xff000000 → 0x00000000 )
		void SetDarkIn ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkInTime = time;
			m_timer->Start ();
		}

		//ブラックアウト( 0x00000000 → 0xff000000 )
		void SetDarkOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkOutTime = time;
			m_timer->Start ();
		}
#endif // 0
	};

	using P_Fade = shared_ptr < FadeRect >;


}	//namespace GAME



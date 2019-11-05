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

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Fade : public PrmRect
	{
		UINT	m_timer;
		UINT	m_fadeOutTime;
		UINT	m_darkInTime;
		UINT	m_darkOutTime;

	public:
		Fade ();
		Fade ( const Fade & rhs ) = delete;
		~Fade ();

		void Move ();
		bool IsActive () { return ( 0 != m_timer ); }

		//フェード(ホワイト)アウト( 0x00ffffff → 0xffffffff )
		void SetWhiteOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_fadeOutTime = time;
			m_timer = 1; 
		}

		//ダークイン ( 0xff000000 → 0x00000000 )
		void SetDarkIn ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkInTime = time;
			m_timer = 1; 
		}

		//ダークアウト( 0x00000000 → 0xff000000 )
		void SetDarkOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkOutTime = time;
			m_timer = 1; 
		}
	};

	using P_Fade = shared_ptr < Fade >;


}	//namespace GAME



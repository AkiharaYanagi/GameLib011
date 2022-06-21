//=================================================================================================
//
//	テスト
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class TestFade	: public GameTaskVector
	{
		P_FADE		m_grp;

	public:
		TestFade ();
		TestFade ( const TestFade & rhs ) = delete;
		~TestFade ();

		void Move ();
		void Draw ();
	};


}	//namespace GAME


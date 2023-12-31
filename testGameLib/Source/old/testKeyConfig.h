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

	class TestKeyConfig	: public GameTaskVector
	{

	public:
		TestKeyConfig ();
		TestKeyConfig ( const TestKeyConfig & rhs ) = delete;
		~TestKeyConfig ();

		void Move ();
	};


}	//namespace GAME


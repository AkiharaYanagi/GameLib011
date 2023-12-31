//=================================================================================================
//
// ゲームメイン　ヘッダ
//			ゲーム内容における主となる挙動を記述する。ヘッダのみ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameMainBase.h"

//ゲーム内容ヘッダファイルのインクルード
//#include "TestFade.h"
//#include "DispInput.h"
//#include "TestOutLineFont0.h"
//#include "TestStretch.h"
//#include "testMultiple.h"
//#include "testEnumFile.h"
//#include "testInput.h"
#include "TestRelease.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//ゲームメインクラス
	class GameMain	: public GameMainBase
	{
#define GAME_MAIN_ONLY_TEST		0
#if GAME_MAIN_ONLY_TEST
		//ゲームメインのみのテスト
		std::shared_ptr < GameMainTest > m_pTask;
#else
		//ゲームに用いるオブジェクトクラス
		std::shared_ptr < Test >		m_pTask;
#endif	//GAME_MAIN_TEST

	public:
		GameMain()
		{
			Make ();				//タスク生成
			AddpTask ( m_pTask );	//タスクの追加
		}
		GameMain(const GameMain& rhs) = delete;
		~GameMain () {}

		//タスク生成
		void Make ()
		{
#if GAME_MAIN_ONLY_TEST
			m_pTask = std::make_shared < GameMainTest > ();
#else
			m_pTask = std::make_shared < Test > ();
#endif	//GAME_MAIN_TEST
		}
	};


}	//namespace GAME


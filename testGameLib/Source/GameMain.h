//=================================================================================================
//
// ゲームメイン　ヘッダ
//			ゲーム内容における主となる挙動を記述する。
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameMainBase.h"

//ゲーム内容ヘッダファイルのインクルード
//#include "Scene.h"
//#include "MyServer.h"
//#include "MyClient.h"
//#include "test.h"
//#include "testKeyConfig.h"
#include "testStretch.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//ゲームメインクラス
	class GameMain	: public GameMainBase
	{
#define GAME_MAIN_TEST		0
#if GAME_MAIN_TEST
		//ゲームメインのみのテスト
		shared_ptr < GameMainTest > m_pTask;
#else
		//ゲームに用いるオブジェクトクラス
//		shared_ptr < SceneManager >		m_pTask;
		shared_ptr < TestStretch >		m_pTask;
#endif	//GAME_MAIN_TEST

	public:
		GameMain();
		GameMain(const GameMain& rhs) = delete;
		~GameMain();

		//タスク生成
		void Make ()
		{
#if GAME_MAIN_TEST
			m_pTask = make_shared < GameMainTest > ();
#else
//			m_pTask = make_shared < SceneManager > ();
			m_pTask = make_shared < TestStretch > ();
#endif	//GAME_MAIN_TEST
		}

		void Init ();			//初期化
		void Rele ();			//解放
		void Load ();			//読み込み
		void Move ();			//フレーム毎動作
		void Draw ();			//フレーム毎描画(スプライト)
		
		void DrawVertex ();		//フレーム毎描画(頂点)
		void Reset ();			//画面切り替え時にフォントなどを再設定する
	};


}	//namespace GAME


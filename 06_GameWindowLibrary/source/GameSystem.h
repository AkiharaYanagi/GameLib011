//=================================================================================================
//
// ゲームシステム　ヘッダ
//
//					ゲーム内容の前に必要になるアプリケーションやライブラリとの連動を記述する。
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "DirectX_Library.h"
#include "GameTextLibrary.h"
#include "KeyInput.h"
#include "Archiver.h"
#include "SoundArchiver.h"
#include "GameMainBase.h"
#include "KeyConfig.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------------------------------------------------------------------
	//	ゲーム内のライブラリ使用など
	//-------------------------------------------------------------------------------------------------
	class GameSystem
	{
		UP_GameMainBase		m_pGameMain;	//ゲームのメインオブジェクトポインタ

		//@info グラフィックは特にMove()をゲームメインの後で行うため、個別で保持する
		P_Task	m_grpList;	//共通グラフィックリストのタスクポインタ

	public:
		GameSystem () : m_pGameMain ( nullptr ) {}
		GameSystem ( const GameSystem& rhs ) = delete;
		~GameSystem () { Rele(); }

		void SystemLoad ();		//シングルトンのクリエイトなど初期化

		void Load ();	//読込
		void Rele ();	//解放
		void Reset();	//再設定
		void Init ();	//初期化
		void Move ();	//フレーム毎動作
		void Draw ();	//描画

		//メインオブジェクトの設定
		void SetGameMain ( UP_GameMainBase pGameMain );


	private:
		static bool m_bDispTimer;
		static bool m_bMakeArchive;

	public:
		//-----------------------------
		//	static 環境設定
		//-----------------------------
		
		//デバッグ表示をすべてON
		static void FullDebugMode () { m_bDispTimer = T; }

		//デバッグ表示をすべてON
		static void NoDebugMode () { m_bDispTimer = F; }
		
		//アーカイブを作成して読み込み
		static void SetFlag_MakeArchive ( bool b ) { m_bMakeArchive = b; }
	};


}	//namespace GAME


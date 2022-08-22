//=================================================================================================
//
// フレーム制御ヘッダ
//	アプリケーションにおけるフレーム制御の管理
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//ライブラリのリンク
//-------------------------------------------------------------------------------------------------
//ウィンドウズマルチメディアライブラリ(timeGetTimeなど)のリンク
#pragma comment(lib, "winmm.lib")

//-------------------------------------------------------------------------------------------------
//インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
//#include "process.h"
#include "GameMainBase.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------------------------------------------------------------------
	//ライブラリ内クラス宣言
	//-------------------------------------------------------------------------------------------------
	class GameSystem;

	//-------------------------------------------------------------------------------------------------
	//	フレーム制御クラス
	//-------------------------------------------------------------------------------------------------
	class FrameControl
	{
//		bool				m_bPermi;		//スレッド許可フラグ
//		bool				m_bActive;		//スレッド稼動フラグ
	
		DWORD				m_beforeTime;	//計測開始時間
		DWORD				m_frames;		//現在フレーム数
		unique_ptr < GameSystem >		m_gameSystem;	//ゲームシステム

		DWORD				m_averageSleep;		//差分の平均

		//定数
		static const DWORD	dwFps;					//FPS
		static const DWORD	waitOneFrameTime;		//1フレームに待つミリ秒 = 1000 * 0x10000 / dwFps;	//上位16ビットに整数部、下位16ビットに小数部を保存

	public:
		FrameControl ();
		FrameControl ( const FrameControl& obj ) = delete;
		~FrameControl ();

		void SystemLoad ();	//ゲームシステム初期化

		void Load ();		//読込
		void Rele ();		//解放
		void Reset ();		//再設定
		void Init ();		//初期化

		//スレッド稼動フラグ取得
//		bool IsActive() { return m_bActive; }

		void Frame ();	//描画処理

		//ゲームメインオブジェクトの設定
		//実体をソースコード内でのみ用いるため、includeを遅延しヘッダには記述しない
		void SetGameMain ( UP_GameMainBase pGameMain );


	private:
		static bool m_bDispFPS;

	public:
		//デバッグ表示をすべてON
		static void FullDebugMode ();

		//デバッグ表示をすべてON
		static void NoDebugMode ();

	};


}	//namespace GAME


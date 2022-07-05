//=================================================================================================
//
// アプリケーションヘッダ
//
//　windowsアプリケーションにおける初期化とメッセージの処理
//	描画スレッド処理
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"		//デバッグ表示
#include "DirectX_Library.h"	//DirectX利用
#include "HWnd.h"				//ウィンドウハンドルオブジェクトの利用
#include "GameMainBase.h"		//ゲームメイン基底
#include "AppSettingFile.h"		//設定ファイル

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//ライブラリ内クラス宣言
	//		ライブラリ内だけで用いるクラス
	//		ヘッダファイルにインクルードしないためにクラス宣言だけ行う
	//-------------------------------------------------------------------------------------------------
	class FrameControl;

	//リソース名
	struct ResourceName
	{
		LPCTSTR windowClassName;	//ウィンドウクラス名
		LPCTSTR mutexText;			//ミューテックス文字列
		LPCTSTR TitleBar;			//タイトルバー文字列
		LPCTSTR ICON_ID;			//アイコンID
	};

	//-------------------------------------------------------------------------------------------------
	//アプリケーション管理クラス
	//-------------------------------------------------------------------------------------------------
	class Application : public enable_shared_from_this < Application >
	{
		//ウィンドウ初期化
		ResourceName		m_rcName;		//リソース名
		HWND				m_hWnd;			//ウィンドウハンドル
		static shared_ptr < Application >	m_pThis;		//静的thisポインタ
		static bool			m_init;			//初期化フラグ(HWNDとアクティブウィンドウメッセージの関係で必要)

		bool _WinInit ( HINSTANCE hInst );	// ウィンドウの初期化
		static LRESULT CALLBACK WinProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );		//ウィンドウプロシージャ

		//ライブラリ内だけで用いるクラス
		//		ヘッダではポインタだけで宣言し、ソースファイルで対象ヘッダをインクルードする
		unique_ptr < FrameControl > m_pFrameControl;
		
		//多重起動防止のためのミューテックスハンドル
		HANDLE				m_hMutex;
#if 0
		//描画スレッド
		static UINT WINAPI DrawThread ( void* vdParam );
		bool				m_bPermi;		//スレッド許可フラグ
		bool				m_bActive;		//スレッド稼動フラグ
#endif // 0

		//------------------------------------------------------------------------
		//設定ファイル
//		AppSettingFile	m_settingFile;

//		bool		m_InitFromCursorPos;


	public:
		Application ( ResourceName rcName );
		Application ( const Application & rhs ) = delete;
		~Application ();

		//Windowsアプリケーションの初期化
		bool AppInit ( HINSTANCE hInst );

		//タスクの一括操作
		void Load ();		//読込
		void Rele ();		//解放
		void Init ();		//初期化

		//主にDirectX関連の再設定 プロシージャから呼び出すためstatic宣言をする
		static void Reset ();

		//windowsメインループ
		void MainLoop ( MSG* pMsg );

		//ゲームメインオブジェクトの設定
		//FrameControlの記述があるため、ヘッダには記述しない
		//(includeを遅延し実体をソースコード内でのみ用いる)
		void SetGameMain ( UP_GameMainBase pGameMain );

		//スレッド稼動フラグ取得
//		bool IsActive() { return m_bActive; }

		//デバッグ表示をすべてON
		static void FullDebugMode ();

	private:
		POINT GetWindowInitPos ();
		POINT GetWindowInitSize ();
	};


}	//namespace GAME


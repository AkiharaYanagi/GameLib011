//=================================================================================================
//
// アプリケーションヘッダ
//
//　windowsアプリケーションにおける初期化とメッセージの処理
//	(描画スレッド処理)
//	※ static なウィンドウプロシージャのため、thisポインタがstaticで保存の必要がある
//	shared_from_this()のため std::shared_ptr <> で確保する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"		//デバッグ表示
#include "Rect.h"				//Rectユーザ定義利用
#include "DirectX_Library.h"	//DirectX利用
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
		static std::shared_ptr < Application >	m_pThis;		//静的thisポインタ
		static bool			m_init;			//初期化フラグ(HWNDとアクティブウィンドウメッセージの関係で必要)

		bool _WinInit ( HINSTANCE hInst );	// ウィンドウの初期化
		static LRESULT CALLBACK WinProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );		//ウィンドウプロシージャ

		//ライブラリ内だけで用いるクラス
		//		ヘッダではポインタだけで宣言し、ソースファイルで対象ヘッダをインクルードする
		std::unique_ptr < FrameControl > m_pFrameControl;
		
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
		bool AppLoad ( HINSTANCE hInst );

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

		//モニタ列挙プロシージャ
		static BOOL CALLBACK MonitorEnumProc ( HMONITOR hMnt, HDC hdc, LPRECT lpRect, LPARAM dwParam );
		static int m_monitor_count;

		//-----------------------------
		//	static 環境設定
		//-----------------------------

		//デバッグ表示をすべてON
		static void FullDebugMode ();

		//デバッグ表示をすべてOFF
		static void NoDebugMode ();

		//アーカイブ作成
		static void SetFlag_MakeArchive ( bool b );

	private:
		POINT GetWindowInitPos ();
		POINT GetWindowInitSize ();

		//対象RECTの中心に指定ウィンドウを置いたときの位置
		POINT CenterWndOfRect ( const RECT & rect, int wx, int wy ) const;
	};


}	//namespace GAME


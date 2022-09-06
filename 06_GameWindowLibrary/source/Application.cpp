//=================================================================================================
//
// Application管理クラス　ソースコード
//
//=================================================================================================

//------------------------------------------------
//	windowsアプリケーションの管理
//		・アプリケーションの初期化　メモリリーク検出、多重起動防止など
//		・ウィンドウの初期化
//		・ウィンドウプロシージャ
//		・画面フォーカス外れによる再設定
//------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Application.h"

// ライブラリ内部のみで参照するヘッダファイル
#include "FrameControl.h"		//フレーム制御とゲームメイン

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//静的変数
	//------------------------------------------
	//静的thisポインタ
	shared_ptr < Application > Application::m_pThis = nullptr;
	//初期化フラグ
	bool Application::m_init = false;

	//-------------------------------------------------------------------------------------------------
	// コンストラクタ
	//-------------------------------------------------------------------------------------------------
	Application::Application ( ResourceName rcName )
		: m_rcName ( rcName )	//, m_InitFromCursorPos ( false )
	{
		//メモリリーク検出
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

		//多重起動チェック
#define MULTI_ACT 0
#if	MULTI_ACT
		try 
		{
			//ミューテックスによる多重起動の防止
			m_hMutex = CreateMutex ( nullptr, false, rcName.mutexText );
			if ( ::GetLastError () == ERROR_ALREADY_EXISTS )
			{
				throw _T("ミューテックスによる多重起動の防止\n");
			}
		}
		catch ( LPCTSTR str )
		{
			TRACE_F ( str );
			MessageBox ( nullptr, TEXT("同時に2つ以上実行することはできません。"), TEXT("多重起動の防止"), MB_OK );
			Rele ();
			PostQuitMessage(0);
		}
#endif	//MULTI_ACT

		//----------------------------------
		//フレーム制御オブジェクトの生成
		m_pFrameControl = make_unique < FrameControl > ();

		//設定ファイルの初期化と読込
		AppSettingFile::Create ();
		AppSettingFile::Inst()->Load ();
	}


	//-------------------------------------------------------------------------------------------------
	// デストラクタ
	//-------------------------------------------------------------------------------------------------
	Application::~Application ()
	{
		Rele ();

#if MULTI_ACT
		//多重起動防止のミューテックスを解放
		ReleaseMutex ( m_hMutex );
		CloseHandle ( m_hMutex );
#endif	//MULTI_ACT
	}


	//-------------------------------------------------------------------------------------------------
	// アプリケーションの初期化
	// 引数：hInst		インスタンスハンドル
	// 戻値：成功 = true, 失敗 = false
	//-------------------------------------------------------------------------------------------------
	bool Application::AppInit ( HINSTANCE hInst )
	{
		//----------------------------------
		//thisポインタの保存	
		m_pThis = shared_from_this ();
	
		//----------------------------------
		//ウィンドウの初期化
		if ( ! _WinInit ( hInst ) )
		{
			TRACE_F ( _T("ウィンドウの初期化に失敗\n") );
			return false;
		}

		//----------------------------------
		//ゲームシステム初期化
		m_pFrameControl->SystemLoad ();

		//----------------------------------
		//スレッド関連
#define APP_THREAD 0
#if APP_THREAD
		m_bPermi = true;		//スレッド許可フラグ
		m_bActive = true;		//スレッド稼動フラグ

		//描画スレッドの開始
		UINT threadID;		//スレッドID
		_beginthreadex ( nullptr, 0, DrawThread, (LPVOID)this, 0, &threadID );
#endif // APP_THREAD
		//----------------------------------

		return true;
	}

	//読込
	void Application::Load ()
	{
		m_pFrameControl->Load ();	//読込
	}

	//初期化
	void Application::Init ()
	{
		m_pFrameControl->Init ();	//初期化
		m_init = true;		//初期化フラグ
	}


	//-------------------------------------------------------------------------------------------------
	// アプリケーションの解放
	//-------------------------------------------------------------------------------------------------
	void Application::Rele ()
	{
#if APP_THREAD
		//スレッド解放
		//////TRACE_F ( TEXT("フレーム制御スレッド：解放\n") );
		m_bActive = false;	//スレッド終了をフラグに設定
#endif // APP_THREAD

		m_pFrameControl->Rele ();	//解放
		m_init = false;		//初期化フラグ
	}


	//-------------------------------------------------------------------------------------------------
	// アプリケーションの再設定
	//-------------------------------------------------------------------------------------------------
	void Application::Reset ()
	{
		//一度も初期化していない場合リセットしない
		if ( ! m_init ) { return; }

		//オブジェクトの再設定
		//プロシージャはCreateWindow()後のthisポインタの保存が使えないので
		//staticなm_pThisを用いる
		m_pThis->m_pFrameControl->Reset ();
	}


	//-------------------------------------------------------------------------------------------------
	// (内部利用) ウィンドウの初期化
	// 引数：hInstance		インスタンスハンドル
	// 戻値：成功するとtrue、失敗するとfalse
	//-------------------------------------------------------------------------------------------------
	bool Application::_WinInit ( HINSTANCE hInst )
	{
		//ウィンドウクラスの登録
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof ( WNDCLASSEX );
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)Application::WinProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = LoadIcon ( hInst, m_rcName.ICON_ID );
		wcex.hIconSm = LoadIcon ( hInst, m_rcName.ICON_ID );
		wcex.hCursor = LoadCursor ( nullptr, IDC_ARROW );
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = m_rcName.windowClassName;

		ATOM atom = RegisterClassExW ( & wcex );
		//LPCTSTR windowsClassName = (LPCTSTR)atom;

		//設定からウィンドウサイズの指定
		int window_w = (int)AppSettingFile::Inst()->GetWindowW ();
		int window_h = (int)AppSettingFile::Inst()->GetWindowH ();

		//ウィンドウの作成
		m_hWnd = CreateWindowW ( 
			m_rcName.windowClassName, m_rcName.TitleBar,
			WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
			0, 0, window_w, window_h,
			nullptr, nullptr, hInst, nullptr );
		if ( ! m_hWnd ) { return false; }

		//ウィンドウハンドルの保存
		HWnd::Set ( m_hWnd );

		//ウィンドウサイズ指定
		POINT pos = GetWindowInitPos ();
		POINT size = GetWindowInitSize ();
		::SetWindowPos ( m_hWnd, HWND_TOP, pos.x, pos.y, size.x, size.y, SWP_SHOWWINDOW );
//		::ShowWindow ( m_hWnd, SW_SHOW );
		
		TRACE_F ( _T("ApplicationManager:: hWnd = %d\n"), m_hWnd );

		return true;
	}


	//-------------------------------------------------------------------------------------------------
	// ウィンドウ プロシージャ
	//-------------------------------------------------------------------------------------------------
	LRESULT CALLBACK Application::WinProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		switch ( uMsg )
		{
		case WM_DESTROY:	//ウィンドウ終了メッセージ
			//////TRACE_F(TEXT("WM_DESTROY\n"));
//			pThis->m_bPermi = false;	//スレッド許可フラグをfalseにする
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
			//////TRACE_F(TEXT("WM_PAINT\n"));
			break;

		case WM_ACTIVATE:		//ウィンドウのアクティブ状態が変化
			//////TRACE_F(TEXT("WM_ACTIVATE : "));
			switch ( LOWORD ( wParam ) )
			{
			case WA_INACTIVE:		//非アクティブになった
				//////TRACE_F(TEXT("WA_INACTIVE\n"));
				break;

			case WA_ACTIVE:		//マウス以外でアクティブになった
				//////TRACE_F(TEXT("WA_ACTIVE\n"));
				Reset ();	//再設定
				break;

			case WA_CLICKACTIVE:	//マウスクリックでアクティブになった
				//////TRACE_F(TEXT("WA_CLICKACTIVE\n"));
				Reset ();	//再設定
				break;
			}
			break;

#if	0
		case WM_ACTIVATEAPP:	//アクティブウィンドウではないアプリケーションに属するウィンドウがアクティブになった
			//////TRACE_F(TEXT("WM_ACTIVATEAPP\n"));
			break;
#endif	//0

#if	0
		case WM_MOUSEMOVE:
			DebugOutGameWindow::instance()->DebugOutf ( TEXT("%d,%d"), LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
#endif	//0

		}
		return DefWindowProc( hWnd, (unsigned int)uMsg, wParam, lParam );
	}


	//-------------------------------------------------------------------------------------------------
	// ウィンドウ メッセージのメインループ
	// 引数：メッセージのポインタ
	//-------------------------------------------------------------------------------------------------
	void Application::MainLoop ( MSG * pMsg )
	{
		while ( true )
		{
			if ( PeekMessage( pMsg, nullptr, 0, 0, PM_REMOVE ) )	//Windowメッセージがあるときの処理
			{
				if ( pMsg->message == WM_QUIT )
				{
					break;
				}
				TranslateMessage ( pMsg );
				DispatchMessage ( pMsg );
			}
			else	//メッセージ以外の処理
			{
				m_pFrameControl->Frame ();	//フレーム制御とゲームメイン
			}
		}
	}


#if	APP_THREAD
	//------------------------------------------
	//フレーム制御スレッド (static)
	//------------------------------------------
	UINT WINAPI ApplicationManager::DrawThread ( void* vdParam )
	{
		//thisポインタの取得
		Application* pThis = reinterpret_cast<Application*>( vdParam );

		pThis->Frame();	//フレーム制御とゲームメイン

		return 0;
	}
#endif	//APP_THREAD


	//------------------------------------------------------------------------
	void Application::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_pFrameControl->SetGameMain ( ::move ( pGameMain ) );
		
		//@todo Load()の位置を調整
		Load ();	//読込
		Init ();	//初期化
	}

	//------------------------------------------------------------------------
	POINT Application::GetWindowInitPos ()
	{
		//-------------------------------------------------
		//カーソル位置から初期位置を設定する
		if ( START_POS_CURSOR == AppSettingFile::Inst()->GetWindowStartPos () )
		{
			//カーソル位置の取得
			POINT cursorPos;
			::GetCursorPos ( & cursorPos );
			cursorPos.x -= 300;
			cursorPos.y -= 10;
			return cursorPos;
		}

		//-------------------------------------------------
		//画面中央配置
		POINT pos = { 0, 0 };

		//設定からウィンドウサイズの指定 (サイズ差を計算するためintにキャスト)
		int window_w = (int)AppSettingFile::Inst ()->GetWindowW ();
		int window_h = (int)AppSettingFile::Inst ()->GetWindowH ();

		//複数モニタの取得
		int targetDisp = (int)AppSettingFile::Inst ()->GetDisplayNum ();	//０から
		int n = ::GetSystemMetrics ( SM_CMONITORS );	//1から

		m_count = 0;
		V_RECT vecRect ( n );

		::EnumDisplayMonitors ( NULL, NULL, MonitorEnumProc, (LPARAM)&vecRect );

		if ( targetDisp + 1 <= n )
		{
			vecRect [ targetDisp ];
			pos = CenterWndOfRect ( vecRect [ targetDisp ], window_w, window_h );
		}
		else
		{
			//プライマリモニタの作業領域サイズを取得
			RECT workRect;
			::SystemParametersInfo ( SPI_GETWORKAREA, 0, &workRect, 0 );
	#if 0
			int wWidth = workRect.right - workRect.left;
			int wHeight = workRect.bottom - workRect.top;
			int wPos_x = ( wWidth / 2 ) - ( window_w / 2 );
			int wPos_y = ( wHeight / 2 ) - ( window_h / 2 );

			pos.x = wPos_x;
			pos.y = wPos_y;
	#endif // 0
			pos = CenterWndOfRect ( workRect, window_w, window_h );
		}

		return pos;
	}

	POINT Application::CenterWndOfRect ( const RECT & rect, int wx, int wy ) const
	{
		int rW = rect.right - rect.left;
		int rH = rect.bottom - rect.top;
		int wPos_x = ( rW / 2 ) - ( wx / 2 );
		int wPos_y = ( rH / 2 ) - ( wy / 2 );
		return POINT { rect.left + wPos_x, rect.top + wPos_y };
	}

	int Application::m_count;


	BOOL CALLBACK Application::MonitorEnumProc ( HMONITOR hMnt, HDC hdc, LPRECT lpRect, LPARAM dwParam )
	{
		V_RECT* pr = (V_RECT*)dwParam;
		
		MONITORINFOEX mntInfo;
		mntInfo.cbSize = sizeof ( mntInfo );
		GetMonitorInfo ( hMnt, & mntInfo );

		::CopyRect ( &(*pr)[ m_count ], & mntInfo.rcMonitor );
		++ m_count;

		return TRUE;
	}

	POINT Application::GetWindowInitSize ()
	{
		//ウィンドウモード時のサイズ補正
		RECT windowRect, clientRect;

		//ウィンドウ幅、高さ
		::GetWindowRect ( m_hWnd, & windowRect );
		TRACE_F ( _T ( "windowRect = ( %d, %d, %d, %d ) \n" ), windowRect.left, windowRect.top, windowRect.right, windowRect.bottom );
		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		//クライアント幅、高さ
		::GetClientRect ( m_hWnd, & clientRect );
		TRACE_F ( _T ( "clientRect = ( %d, %d, %d, %d ) \n" ), clientRect.left, clientRect.top, clientRect.right, clientRect.bottom );
		int clientWidth = clientRect.right - clientRect.left;
		int clientHeight = clientRect.bottom - clientRect.top;

		//タイトルバー補正サイズ
		POINT size;
		size.x = windowWidth + ( windowWidth - clientWidth );
		size.y = windowHeight + ( windowHeight - clientHeight );

		return size;
	}

	void Application::FullDebugMode ()
	{
		FrameControl::FullDebugMode ();
	}

	void Application::NoDebugMode ()
	{
		FrameControl::NoDebugMode ();
	}

}	//namespace GAME


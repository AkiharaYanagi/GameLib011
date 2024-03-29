//=================================================================================================
//
// ウィンドウメイン ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "stdafx.h"
#include "WinMain.h"

//-------------------------------------------------------------------------------------------------
//ネームスペースの利用
//-------------------------------------------------------------------------------------------------
using namespace GAME;

//------------------------------------------
// windows　エントリポイント
//------------------------------------------
int APIENTRY wWinMain ( HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow )
{
	//------------------------------------------------------------------------
	//デバッグ出力
//	DebugOutTrace::Create();	//IDE出力にデバッグメッセージを表示
	TRACE_F ( _T("\n---------------------------------------\n") );
	TRACE_F ( _T("wWinMain : アプリケーション開始 hInst = %d\n"), hInst );
	DebugOutFile::Create();		//ファイルにデバッグメッセージを書出
	DBGOUT_FL_F ( _T("ファイル書出開始\n") );
	
	//------------------------------------------------------------------------
	//アプリケーション処理のオブジェクト
	//ウィンドウクラス名, ミューテックス文字列, タイトルバー, アイコン
	LPCTSTR wndclss = _T ( "GameLibWnd" );
	LPCTSTR mutex = _T ( "2018-2024 AkiharaSoft." );
	LPCTSTR title = _T ( "Test Lib011" );
	LPCTSTR icon = MAKEINTRESOURCE ( IDI_ICON1 );
	ResourceName rcName = { wndclss, mutex, title, icon };

	std::shared_ptr < Application > app = std::make_shared < Application > ( rcName );
	
	//デバッグ表示を切替
	app->FullDebugMode ();
//	app->NoDebugMode ();
	app->SetFlag_MakeArchive ( T );	//アーカイブ作成フラグ

	app->AppLoad( hInst );		//アプリケーションの初期化

	//------------------------------------------------------------------------
	//ゲームメインテスト (何もしないテスト)
//	std::unique_ptr < GameMainTest > gameMain = std::make_unique < GameMainTest > ();
	//ゲームメインオブジェクト
	std::unique_ptr < GameMain >	gameMain = std::make_unique < GameMain > ();
	TRACE_F ( _T("ゲームメインの生成 sizeof(gameMain) = %d\n"), sizeof(gameMain) );
	app->SetGameMain ( ::move ( gameMain ) );	//ゲームメインの設置
	app->Load ();	//タスクの読込
	app->Init ();	//タスクの初期化

	//------------------------------------------------------------------------
	//Windowsメッセージのメインループ
	MSG msg = { 0 };		//メッセージ
	TRACE_F ( _T("メッセージループの開始\n") );
	app->MainLoop ( & msg );
	TRACE_F ( _T("メッセージループの終了\n") );

	//------------------------------------------------------------------------
	TRACE_F ( _T("wWinMain : 終了\n") );
	TRACE_F ( _T("---------------------------------------\n\n") );
	return (int) msg.wParam;
}



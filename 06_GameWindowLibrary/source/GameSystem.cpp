//=================================================================================================
//
// ゲームシステム　クラス定義
//
//		ゲーム内容の前に初期化が必要になるアプリケーションやライブラリとの連動を記述する。
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameSystem.h"
#include "DebugOutGameWindow.h"
#include "AppSettingFile.h"
#include "GameGraphicList.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//static実体
	bool GameSystem::m_bDispTimer = true;
	bool GameSystem::m_bMakeArchive = true;


	//各種シングルトンのクリエイトなど1回のみの初期化
	void GameSystem::SystemLoad ()
	{
		//設定からウィンドウ状態の取得
		UINT window_w = AppSettingFile::Inst ()->GetWindowW ();
		UINT window_h = AppSettingFile::Inst ()->GetWindowH ();
		bool bFullScreen = AppSettingFile::Inst ()->GetbFullscreen ();
		int displayNum = AppSettingFile::Inst ()->GetDisplayNum ();

		// Direct3Dの初期化
		Dx3D::Create ();
		Dx3D::instance()->SetWindowSize ( window_w, window_h );
		Dx3D::instance()->SetFullscreen ( bFullScreen );
		Dx3D::instance ()->SetDisplayNum ( displayNum );
		Dx3D::instance()->Load ();

		//Graphic配列の初期化
		GRPLST_CREATE ();
		m_grpList = GRPLST_MAKE ();		//共通グラフィックリスト

		//ゲームテキスト初期化
		GameText::Create();
		GameText::Inst()->Load ( Dx3D::instance()->GetDevice() );

		OutlineFont::Create ();
		OutlineFont::Inst ()->Load ( Dx3D::instance ()->GetDevice () );

#if	0
		//ゲームテキストファイル初期化
		TextFile::Create ();
		TextFile::instance()->Load();
#endif	//0
	
		//ゲーム画面デバッグ表示の初期化
		DebugOutGameWindow::Create ();
		DebugOutGameWindow::Inst()->Load ();

		//サウンドの生成
		DxSound::Create ();
		DxSound::instance()->Load();

		//キー入力の初期化
		DxInput::Create ();		//DirectInput(キーボード、ジョイスティックの利用)
		KeyInput::Create();
		KeyConfig::Create ();

		//グラフィックファイルアーカイバの初期化
		Archiver::Create ();
#if	_DEBUG
		//デバッグ時 かつ フラグON のみアーカイブファイルを生成する
		if ( m_bMakeArchive )
		{
			Archiver::instance()->Make ();
		}
#endif	//_DEBUG
		Archiver::instance()->Open ();		//アーカイブファイルの読込


		//サウンドアーカイバの初期化
		SoundArchiver::Create ();
#if	_DEBUG
		//デバッグ時 かつ フラグON のみアーカイブファイルを生成する
		if ( m_bMakeArchive )
		{
			SoundArchiver::instance ()->Make ();
		}
#endif	//_DEBUG
		SoundArchiver::instance()->Open ();		//アーカイブファイルの読込
	}


	//読込
	void GameSystem::Load ()
	{
		//ゲームメインの読込
		assert ( m_pGameMain );
		m_pGameMain->Load ();
		m_grpList->Load ();
		KeyConfig::instance ()->Load ();
	}


	//解放
	void GameSystem::Rele ()
	{
//　※　デストラクタで派生クラスの仮想関数を呼ぶと、基底クラスの仮想関数が呼ばれる
//　　　このことより、純粋仮想関数のときはPurecallとなる可能性があるので注意。
//		→　デストラクタで仮想関数を呼ばない
//ex.		if ( m_pGameMain ) m_pGameMain->Rele ();		//ゲームオブジェクトの解放
//		→　持っているポインタの仮想関数を呼ぶのではなく、
//			自分のデストラクタで自分の終了処理関数を呼ぶ
	}


	//再設定
	void GameSystem::Reset()
	{
		//DirectX関連の再設定
		Dx3D::instance()->Reset();
		D3DDEV dev = Dx3D::instance ()->GetDevice ();
		GameText::Inst()->Reset ( dev );
		OutlineFont::Inst ()->Reset ( dev );
		DebugOutGameWindow::Inst()->Reset( dev );
		DxInput::instance ()->Reset ();
		GRPLST_RESET ();

		if ( m_pGameMain ) { m_pGameMain->Reset(); }
		if ( m_grpList ) { m_grpList->Reset (); }
	}


	//初期化
	void GameSystem::Init ()
	{
		//ゲームメインの初期化
		assert ( m_pGameMain );
		m_pGameMain->Init ();
		m_grpList->Init ();
	}

	
	//フレーム毎動作
	void GameSystem::Move ()
	{
		//test		Move()とDraw()の時間計測
		static DWORD count = 0;
		DWORD startTime = ::timeGetTime ();
		DWORD moveTime = 0;


		DxSound::instance ()->Move ();	//サウンドの更新
		DxInput::instance ()->Update ();	//入力の更新

#ifdef	_DEBUG
		//----------------------------------------------
		// 'F5'キーで稼働フレーム数表示切替
		static int time = 0;
		if( ::GetAsyncKeyState( VK_F5 ) & 0x0001 )
		{
			m_bDispTimer ^= true;
			DBGOUT_WND->SetbDisp_Time ( m_bDispTimer );
		}
		if( m_bDispTimer )
		{
			//ゲーム画面固定表示
			DBGOUT_WND->DebugOutWnd_Time ( _T ( "Frame:%d" ), time );
		}
		else
		{
			DBGOUT_WND->SetbDisp_Time ( false );
			DBGOUT_WND->DebugOutWnd_Time ( _T ( "" ) );
		}

		//----------------------------------------------
		// 'W'キーでスタート/ストップのトグル切替
		static bool bStop = false;
		if( ::GetAsyncKeyState('W') & 0x0001 )
		{
			bStop ^= true; 
		}
		//----------------------------------------------
		// ストップ時、'Q'キーで 1 フレームずつ進ませる
		if( ! bStop || ::GetAsyncKeyState('Q') & 0x0001 )
		{
			assert ( m_pGameMain );
			
			//フレーム毎の動作	
			m_pGameMain->Move ();

			//@info デバッグ用'W'ストップでグラフィックリストのMove()も止める
			//グラフィックリスト
			m_grpList->Move ();


			//ゲーム画面におけるデバッグ表示の動作
			DebugOutGameWindow::Inst()->Move ();
#if	0
			TextFile::instance()->Move ();
#endif	//0

			
			++ time;
		}
		//----------------------------------------------
#endif	// _DEBUG

		//test: 動作時間の計測
		moveTime = ::timeGetTime ();


		//test
		DWORD DrawTime = ::timeGetTime ();


		// 'F7'キーでMove, Draw 処理時間 表示切替
		static bool bMoveDrawTimer = true;
		if ( ::GetAsyncKeyState ( VK_F7 ) & 0x0001 )
		{
			bMoveDrawTimer ^= true;
			DBGOUT_WND->SetbDisp_Move_Draw ( bMoveDrawTimer );
		}
		if ( bMoveDrawTimer )
		{
			//60[F]の平均
			if ( ++ count > 60 )
			{
				DBGOUT_WND->DebugOutWnd_Move_Draw ( _T ( "MoveTime = %d, DrawTime = %d" ), moveTime - startTime, DrawTime - startTime );
			}
			else
			{
				DBGOUT_WND->DebugOutWnd_Move_Draw ( _T ( "MoveTime = -, DrawTime = -" ) );
			}
		}
		else
		{
			DBGOUT_WND->SetbDisp_Move_Draw ( false );
			DBGOUT_WND->DebugOutWnd_Move_Draw ( _T ( "" ) );
		}
	}


	//描画
	void GameSystem::Draw()
	{
		assert ( m_pGameMain );

		Dx3D::instance()->BeginScene ();	//描画開始
		{
			//スプライト描画
			Dx3D::instance()->BeginSprite ();	//スプライト描画開始
			{
				m_pGameMain->Draw ();	//ゲームメイン描画
				m_grpList->Draw ();
			}
			Dx3D::instance()->EndSprite ();		//スプライト描画終了

			//頂点描画
			m_pGameMain->DrawVertex ();			//ゲームメイン以下のタスクによる頂点描画
			m_grpList->DrawVertex ();

			DebugOutGameWindow::Inst()->DrawVertex ();	//ゲーム画面上のデバッグ表示
		}
		Dx3D::instance()->EndScene ();		//描画終了
	}


	//メインオブジェクトの設定
	void GameSystem::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = ::move ( pGameMain ); 
	}


}	//namespace GAME


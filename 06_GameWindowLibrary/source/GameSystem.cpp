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
//	bool GameSystem::m_bDispTimer = true;
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


		//サウンドの生成
		DxSound::Create ();
		DxSound::instance()->Load();

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
		GRPLST_LOAD ();
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

		//共通グラフィックリスト
//		GRPLST_RELE ();

		if ( m_pGameMain ) { m_pGameMain->Rele (); }
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
	}


	//初期化
	void GameSystem::Init ()
	{
		//ゲームメインの初期化
		assert ( m_pGameMain );
		m_pGameMain->Init ();
//		GRPLST_INIT ();
	}

	
	//フレーム毎動作
	void GameSystem::Move ()
	{
		DxSound::instance ()->Move ();	//サウンドの更新
		DxInput::instance ()->Update ();	//入力の更新

		//----------------------------------------------
		//稼働フレーム数
		static UINT frame_time = 0;
		DBGOUT_WND->DebugOutWnd_Frame ( frame_time );

		//----------------------------------------------
		// 'W'キーでスタート/ストップのトグル切替
		static bool bStop = false;
		if( WND_UTL::AscKey ( 'W' ) )
		{
			bStop ^= true; 
		}
		//----------------------------------------------
		// ストップ時、'Q'キーで 1 フレームずつ進ませる
		if( ! bStop || WND_UTL::AscKey ( 'Q' ) )
		{
			//フレーム毎の動作	
			m_pGameMain->Move ();

			//ゲーム画面におけるデバッグ表示の動作
			DBGOUT_WND->Move ();
#if	0
			TextFile::instance()->Move ();
#endif	//0
			
			++ frame_time;
		}
		//----------------------------------------------
#ifdef	_DEBUG
#else	// _DEBUG
		
		//フレーム毎の動作	
		m_pGameMain->Move ();

#endif	// _DEBUG

	}


	//描画
	void GameSystem::Draw()
	{
		assert ( m_pGameMain );

		Dx3D::instance()->BeginScene ();	//描画開始
		{

			//@todo スプライトと頂点を合わせて、Z大順で描画する

#if 0
			//スプライト描画
			Dx3D::instance()->BeginSprite ();	//スプライト描画開始
			{
//				m_pGameMain->Draw ();	//ゲームメイン描画
				GRPLST_DRAW ();
			}
			Dx3D::instance()->EndSprite ();		//スプライト描画終了


			//@info スプライトと頂点の描画順番に注意

			//頂点描画
//			m_pGameMain->DrawVertex ();			//ゲームメイン以下のタスクによる頂点描画
			GRPLST_DRAW_VERTEX ();
#endif // 0
			GRPLST_DRAW ();


			DBGOUT_WND->DrawVertex ();	//ゲーム画面上のデバッグ表示
		}
		Dx3D::instance()->EndScene ();		//描画終了
	}


	//メインオブジェクトの設定
	void GameSystem::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = ::move ( pGameMain ); 
	}


}	//namespace GAME


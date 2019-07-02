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
#include "SettingFile.h"
#include "GameGraphicArray.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//シングルトンのクリエイトなど1回のみの初期化
	void GameSystem::SystemLoad ()
	{
		//設定からウィンドウサイズの取得
		UINT window_x = SettingFile::instance ()->GetWindowX ();
		UINT window_y = SettingFile::instance ()->GetWindowY ();

		// Direct3Dの初期化
		Dx3D::Create ();
		Dx3D::instance()->SetWindowSize ( window_x, window_y );
		Dx3D::instance()->Load ();

		//Graphic配列の初期化
		GameGraphicArray::Create ();
		
		//ゲームテキスト初期化
		GameText::Create();
		GameText::instance()->Load ( Dx3D::instance()->GetDevice() );
#if	0
		//ゲームテキストファイル初期化
		TextFile::Create ();
		TextFile::instance()->Load();
#endif	//0
	
		//ゲーム画面デバッグ表示の初期化
		DebugOutGameWindow::Create ();
		DebugOutGameWindow::instance()->Load ();

		//サウンドの生成
		DxSound::Create ();
		DxSound::instance()->Load();

		//キー入力の初期化
		KeyInput::Create();

		//アーカイバの初期化
		Archiver::Create ();
#if	_DEBUG
		Archiver::instance()->Make ();		//デバッグ時のみアーカイブファイルを生成する
#endif	//_DEBUG
		Archiver::instance()->Open ();		//アーカイブファイルの読込

		//サウンドアーカイバの初期化
		SoundArchiver::Create ();
#if	_DEBUG
		SoundArchiver::instance()->Make ();		//デバッグ時のみアーカイブファイルを生成する
#endif	//_DEBUG
		SoundArchiver::instance()->Open ();		//アーカイブファイルの読込
	}


	//読込
	void GameSystem::Load ()
	{
		//ゲームメインの読込
		assert ( m_pGameMain );
		m_pGameMain->Load ();
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
		//DirectXの再設定
		Dx3D::instance()->Reset();
		GameText::instance()->Reset ( Dx3D::instance()->GetDevice() );
		DebugOutGameWindow::instance()->Reset( Dx3D::instance()->GetDevice() );
		KeyInput::instance()->Reset ();

		if ( m_pGameMain ) { m_pGameMain->Reset(); }
	}


	//初期化
	void GameSystem::Init ()
	{
		//ゲームメインの初期化
		assert ( m_pGameMain );
		m_pGameMain->Init ();
	}

	
	//フレーム毎動作
	void GameSystem::Move ()
	{
		DxSound::instance ()->Move ();	//サウンドの更新
		KeyInput::instance()->Update ();	//入力の更新

		assert ( m_pGameMain );
		m_pGameMain->Move ();		//フレーム毎の動作

		//ゲーム画面におけるデバッグ表示の動作
		DebugOutGameWindow::instance()->Move ();
#if	0
		TextFile::instance()->Move ();
#endif	//0
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
			}
			Dx3D::instance()->EndSprite ();		//スプライト描画終了

			//頂点描画
			m_pGameMain->DrawVertex ();			//ゲームメイン以下のタスクによる頂点描画

			DebugOutGameWindow::instance()->DrawVertex ();	//ゲーム画面上のデバッグ表示
		}
		Dx3D::instance()->EndScene ();		//描画終了
	}


	//メインオブジェクトの設定
	void GameSystem::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = ::move ( pGameMain ); 

		//Graphic配列をゲームメインに設定
		P_TASK_VEC pGrpAry = GrpAry::instance()->GetpInstance ();
		m_pGameMain->AddpTask ( pGrpAry );
	}


}	//namespace GAME


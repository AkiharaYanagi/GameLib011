//=================================================================================================
//
// ゲームメイン　実装
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "stdafx.h"
#include "GameMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	GameMain::GameMain()
	{
		//DirectX関連はHWND初期化順序のためにコンストラクタではなくInit()で行う必要がある
		//->GameSystemで行う

		Make ();				//タスク生成
		GameTaskVector::AddpTask ( m_pTask );	//タスクの追加

		//乱数の種
		::srand ( timeGetTime () );
	}

	GameMain::~GameMain()
	{
		Rele();
	}


	//読込
	void GameMain::Load ()
	{
		GameTaskVector::Load();
	}

	//解放
	void GameMain::Rele ()
	{
		GameTaskVector::Rele();
	}

	//再設定
	void GameMain::Reset()
	{
		GameTaskVector::Reset();
	}


	//初期化
	void GameMain::Init ()
	{
		GameTaskVector::Init();
	}

	//フレーム毎の動作
	void GameMain::Move ()
	{
#if 0
		//ESCでアプリケーションを終了
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 ) 
		{ 
			::PostQuitMessage( 0 );
		}
#endif // 0

#ifdef	_DEBUG
#endif	// _DEBUG
		static bool b = true;
		// W キーでスタート/ストップの切り替え
		if( ::GetAsyncKeyState('W') & 0x0001 )
		{
			b ^= 1; 
		}
		// Q キーで 1 フレームずつ進ませる
		if( b || ::GetAsyncKeyState('Q') & 0x0001 )
		{

		//@todo GrpAryの０フレーム目の非表示問題

//			static int time = 0;
//			DebugOutGameWindow::instance()->DebugOutf ( _T("time = %d"), time++ );
			GameTaskVector::Move();
		}
	}


	//フレーム毎のスプライト描画
	void GameMain::Draw ()
	{
		GameTaskVector::Draw();
	}


	//フレーム毎の頂点描画
	void GameMain::DrawVertex ()
	{
		GameTaskVector::DrawVertex();
	}


}	//namespace GAME


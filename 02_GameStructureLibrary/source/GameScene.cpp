//=================================================================================================
//
// ゲームシーン ソースファイル
//		遷移時にデータの破棄をする状態遷移
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameScene.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//------------------------------------------------------------------
	//	ゲームシーン
	//------------------------------------------------------------------
	//ヘッダのみ


	//------------------------------------------------------------------
	//	ゲームシーンマネージャ
	//------------------------------------------------------------------
	GameSceneManager::GameSceneManager ()
		: m_pScene ( nullptr )
	{
	}

	GameSceneManager::~GameSceneManager ()
	{
	}

	void GameSceneManager::Load ()
	{
		if ( m_pScene ) { m_pScene->Load (); }
		GameTaskVector::Load ();
	}

	void GameSceneManager::Rele ()
	{
		if ( m_pScene ) { m_pScene->Rele (); }
		GameTaskVector::Rele ();
	}

	void GameSceneManager::Reset ()
	{
		if ( m_pScene ) { m_pScene->Reset (); }
		GameTaskVector::Reset ();
	}

	void GameSceneManager::Init ()
	{
		if ( m_pScene ) { m_pScene->Init (); }
		GameTaskVector::Init ();
	}

	void GameSceneManager::Move ()
	{
		Transit ();	//遷移条件確認

		if ( m_pScene ) { m_pScene->Move (); }
		GameTaskVector::Move ();
	}

	void GameSceneManager::Draw ()
	{
		if ( m_pScene ) { m_pScene->Draw (); }
		GameTaskVector::Draw ();
	}

	void GameSceneManager::DrawVertex ()
	{
		if ( m_pScene ) { m_pScene->DrawVertex (); }
		GameTaskVector::DrawVertex ();
	}

	void GameSceneManager::Transit ()
	{
		if ( ! m_pScene ) { return; }

		shared_ptr < GameScene > next = m_pScene->Transit ();		//Transit()内で指定した遷移先、またはthisが返る
		if ( next != m_pScene )	//以前と異なる場合
		{
			//パラメータの移譲
			next->SetpParam ( m_pScene->GetpParam () );

			//新規シーンを設定
			m_pScene = next;
			m_pScene->ParamInit ();
			m_pScene->Load ();
			m_pScene->Init ();
		}
	}


}	//namespace GAME


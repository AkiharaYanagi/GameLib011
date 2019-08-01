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

	//フレーム毎動作と遷移チェック
	void GameSceneManager::Move ()
	{
		Transit ();	//遷移条件確認

		assert ( m_pScene );
//		if ( m_pScene ) { m_pScene->Move (); }
		GameTaskVector::Move ();
	}

	void GameSceneManager::Transit ()
	{
//		if ( ! m_pScene ) { return; }
		assert ( m_pScene );

		shared_ptr < GameScene > next = m_pScene->Transit ();		//Transit()内で指定した遷移先、またはthisが返る
		if ( next != m_pScene )	//以前と異なる場合
		{
			//パラメータの移譲
			next->SetpParam ( m_pScene->GetpParam () );

			//タスクの除外
//			TASK_VEC::EraseTask ( m_pScene );

			//明示的解放
			m_pScene.reset ();

			//新規シーンを設定
			m_pScene = next;
			m_pScene->ParamInit ();
			m_pScene->Load ();
			m_pScene->Init ();
		}
	}


}	//namespace GAME


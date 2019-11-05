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
		GameTaskVector::Move ();
	}

	void GameSceneManager::Transit ()
	{
		assert ( m_pScene );

		//Transit()内で指定した遷移先、またはthisが返る
		shared_ptr < GameScene > next = m_pScene->Transit ();	

		if ( next != m_pScene )	//以前と異なる場合
		{
			TRACE_F ( _T ( "■ GameSceneManager : next.use_count = %d\n" ), next.use_count() );
			//パラメータの移譲
			next->SetpParam ( m_pScene->GetpParam () );

			//明示的解放
			TRACE_F ( _T ( "■ GameSceneManager : m_pScene.use_count = %d" ), m_pScene.use_count() );
			EraseTask ( m_pScene );
			TRACE_F ( _T ( "-> %d " ), m_pScene.use_count() );
			m_pScene.reset ();
			TRACE_F ( _T ( "-> %d\n" ), m_pScene.use_count() );

			//新規シーンを設定
			m_pScene = next;
			TRACE_F ( _T ( "■ GameSceneManager : m_pScene.use_count = %d\n" ), m_pScene.use_count () );
			TRACE_F ( _T ( "■ GameSceneManager : next.use_count = %d\n" ), next.use_count () );
			next.reset ();
			TRACE_F ( _T ( "next.reset (); \n" ), m_pScene.use_count () );
			TRACE_F ( _T ( "■ GameSceneManager : m_pScene.use_count = %d\n" ), m_pScene.use_count () );
			TRACE_F ( _T ( "■ GameSceneManager : next.use_count = %d\n" ), next.use_count () );
			m_pScene->ParamInit ();
			m_pScene->Load ();
			m_pScene->Init ();
		}
	}


}	//namespace GAME


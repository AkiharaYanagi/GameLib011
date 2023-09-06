//=================================================================================================
//
// ゲームステート
//		状態遷移
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameState.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	GameState::GameState () : m_next(nullptr), m_change(false)
	{
	}

	GameState::~GameState ()
	{
	}

//-------------------------------------------------------------------------------
	GameStateManager::GameStateManager() : m_state(nullptr)
	{
	}

	GameStateManager::~GameStateManager()
	{
//		if ( m_state ) delete m_state;		//最後のオブジェクトの解放
		m_state = nullptr;
	}

	void GameStateManager::Init()
	{
		if ( m_state ) m_state->Init();
		GameTaskVector::Init ();
	}

	void GameStateManager::Rele()
	{
		if ( m_state ) m_state->Rele();
		GameTaskVector::Rele ();
	}

	void GameStateManager::Load()
	{
		if ( m_state ) m_state->Load();
		GameTaskVector::Load ();
	}

	void GameStateManager::Reset()
	{
		if ( m_state ) m_state->Reset();
		GameTaskVector::Reset ();
	}

	void GameStateManager::Move()
	{
		if ( m_state ) m_state->Move();
		GameTaskVector::Move ();
	}

#if 0
	void GameStateManager::Draw()
	{
		if ( m_state ) m_state->Draw();
		GameTaskVector::Draw ();
	}

	void GameStateManager::DrawVertex()
	{
		if ( m_state ) { m_state->DrawVertex(); }
		GameTaskVector::DrawVertex ();
	}
#endif // 0

	void GameStateManager::Transit()
	{
		if ( ! m_state ) return;

		//遷移状態のチェック
		GameState* next = m_state->Transit();		//Transit()内でnewしたオブジェクトまたはthisが返る
		if ( next != m_state )	//以前と異なる場合
		{
			m_state->Rele();
//			if ( m_state ) delete m_state;	//前のオブジェクトを破棄
			m_state = next;		//新規オブジェクトを設定
			m_state->Load();
			m_state->Init();
		}
	}


//======================================================================================

	void _GameStateManager::Transit ()
	{
		if ( m_state )
		{
			_GameState* next = m_state->Transit ();		//Transit()内で指定した遷移先、またはthisが返る
			if ( next != m_state )	//以前と異なる場合
			{
				m_state = next;		//新規ステートを設定
			}
		}
	}


}	//namespace GAME


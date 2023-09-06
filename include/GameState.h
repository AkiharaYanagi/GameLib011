//=================================================================================================
//
// ゲームステート　ヘッダ
//		状態遷移
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "GameTask.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//ゲームステート
	//-------------------------------------------------------------------------------------------------
	//	ゲームの状態を示す
	//	Transit()で任意の遷移条件を調べ、次の状態もしくはthisを返す
	//-------------------------------------------------------------------------------------------------
	class GameState	: public GameTaskVector
	{
		GameState*			m_next;			//次の状態
		bool				m_change;		//一度遷移したらthisを返すように戻す

	public:
		GameState ();
		GameState ( const GameState& rhs ) = delete;
		~GameState ();

		//遷移先を指定
		void SetNext ( GameState* p ) 
		{
			m_change = true; 
			m_next = p; 
		}

		//遷移判定
		virtual GameState* Transit () 
		{
			if ( m_change )
			{
				m_change = false;
				return m_next;
			}
			return this; 
		}
	};

	//ゲーム状態遷移管理
	//-------------------------------------------------------------------------------------------------
	//	ゲームタスクを一つだけ実体化して実行する
	//	Move()中でTransit()を実行
	//	Transit()で遷移するときに以前のタスクを破棄
	//-------------------------------------------------------------------------------------------------
	class GameStateManager : public GameTaskVector
	{
		GameState*		m_state;	//現在のステート

	public:
		GameStateManager ();
		GameStateManager ( const GameStateManager& rhs ) = delete;
		virtual ~GameStateManager ();

		void Init ();
		void Rele ();
		void Load ();
		void Reset ();
		void Move ();
#if 0
		void Draw ();
		void DrawVertex ();
#endif // 0

		void SetState ( GameState* p ) { m_state = p; }
		GameState* GetState () { return m_state; }

		void Transit ();
	};


//======================================================================================


	//ゲームステート
	class _GameState	// : public GameTask
	{
		_GameState*			m_next;
		bool				m_change;		//一度遷移したらthisを返すように戻す

	public:
		_GameState () : m_next(nullptr), m_change(false) {}
		_GameState ( const _GameState& rhs ) = delete;
		~_GameState () {}

		//遷移先を指定
		void SetNext ( _GameState* p ) 
		{
			m_change = true; 
			m_next = p; 
		}

		//毎回の遷移チェック
		virtual _GameState* Transit () 
		{
			_GameState* ret = this;
			
			if ( m_change )		//遷移先が指定されていた場合
			{
				ret = m_next;
				m_next = this;		//thisを返すように戻す
				m_change = false;
			}
			return ret; 
		}
	};

	//ゲームステートマネージャ
	//-------------------------------------------------------------------------------------------------
	//	すでに実体化しているゲームタスクに遷移する
	//	Move()中でTransit()を実行
	//	Transit()で遷移するときに以前のタスクを破棄しない
	//-------------------------------------------------------------------------------------------------
	class _GameStateManager : public GameTask
	{
		_GameState*		m_state;

	public:
		_GameStateManager () : m_state (nullptr) {}
		_GameStateManager ( const _GameStateManager& rhs ) = delete;
		~_GameStateManager () {}

		void SetState ( _GameState* p ) { m_state = p; }
		_GameState* GetState () { return m_state; }

		void Transit ();
	};


	//ゲームステート(オート)
	//自動で次の状態の遷移条件と遷移先を指定する
	class _GameStateTransit : public _GameState
	{
	public:
		virtual _GameStateTransit* Transit() = 0;
	};

	//ゲームステートマネージャ(トランジット)
	class _GameStateTransitManager : public _GameStateManager
	{
	public:
	};


}	//namespace GAME


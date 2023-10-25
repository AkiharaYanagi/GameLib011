//=================================================================================================
//
// ゲームタスク　クラス　
//		ゲームで用いるオブジェクト(処理の単位)を定義する。
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//=========================================================================
	// ゲームタスク
	//=========================================================================
	//	ヘッダのみに記述

	//=========================================================================
	// ゲームタスクベクタ
	//=========================================================================
	GameTaskVector::GameTaskVector ()
	{
		m_pvpTask = make_shared < VP_Task > ();
	}

	GameTaskVector::~GameTaskVector ()
	{
		Clear ();
	}

	//初期化
	void GameTaskVector::Clear ()
	{
		if ( m_pvpTask ) { m_pvpTask->clear (); }
	}

	//タスクの追加（サイズの変更も自動的に行う）
	void GameTaskVector::AddpTask ( P_Task pTask )
	{
		m_pvpTask->push_back ( pTask );
	}

	//タスクの取得
	P_Task GameTaskVector::GetpTask ( UINT index )
	{
		return m_pvpTask->at ( index );
	}

	//アクセサ
	P_Task GameTaskVector::operator [] ( UINT index )
	{
		return m_pvpTask->at ( index );
	}

	//タスクの挿入
	void GameTaskVector::InsertTask ( P_Task pTask, UINT index )
	{
		VP_Task::iterator it = begin ( *m_pvpTask );
		it += index;
		m_pvpTask->insert ( it, pTask );
	}

	//タスクの取外
	void GameTaskVector::EraseTask ( P_Task pTask )
	{
		VP_Task::iterator it = begin ( *m_pvpTask );
		for ( ; it != end ( *m_pvpTask ); ++it )
		{
			if ( (*it) == pTask )
			{
				m_pvpTask->erase ( it );
			}
			break;
		}
	}
	void GameTaskVector::EraseTask ( const VP_Task::iterator it )
	{
		m_pvpTask->erase ( it );
	}

	//----------------------------------------------------------------------------------------
	//	各種インターフェースの実行
	//----------------------------------------------------------------------------------------
	void GameTaskVector::Init () { for ( auto p : (*m_pvpTask) ) { p->Init (); } }
	void GameTaskVector::Rele () { for ( auto p : (*m_pvpTask) ) { p->Rele (); } }
	void GameTaskVector::Load () { for ( auto p : (*m_pvpTask) ) { p->Load (); } }
	void GameTaskVector::Reset () { for ( auto p : (*m_pvpTask) ) { p->Reset (); } }
	void GameTaskVector::Move () { for ( auto p : (*m_pvpTask) ) { p->Move (); } }

#if 0
	void GameTaskVector::Draw () { for ( auto p : (*m_pvpTask) ) { p->Draw (); } }
	void GameTaskVector::DrawVertex () { for ( auto p : (*m_pvpTask) ) { p->DrawVertex (); } }
#endif // 0


	//指定オブジェクトを最前列描画(末尾)にする
	//	指定したオブジェクトが無い場合なにもしない
	void GameTaskVector::Top ( P_Task pTask )
	{
		for ( auto p : (*m_pvpTask) )
		{
			if ( p == pTask )
			{
				//該当オブジェクトポインタと末尾を入れ替える
				p.swap ( *end ( *m_pvpTask ) );
				break;
			}
		}
	}

	//指定オブジェクトを先頭にする
	//	指定したオブジェクトが無い場合なにもしない
	void GameTaskVector::End ( P_Task pTask )
	{
		for ( auto p : (*m_pvpTask) )
		{
			if ( p == pTask )
			{
				//該当オブジェクトポインタと先頭を入れ替える
				p.swap ( *begin ( *m_pvpTask ) );
				break;
			}
		}
	}


	//=========================================================================
	// ゲームタスクリスト
	//=========================================================================
	GameTaskList::GameTaskList ()
	{
		m_plpTask = make_shared < LP_Task > ();
	}

	GameTaskList::~GameTaskList ()
	{
//		TRACE_F (_T("TaskList:~\n"));
		Clear ();
	}

	//初期化
	void GameTaskList::Clear ()
	{
		if ( m_plpTask ) { m_plpTask->clear (); }
	}

	//タスクを末尾に追加
	void GameTaskList::AddpTask ( P_Task pTask )
	{
		m_plpTask->push_back ( pTask );
	}

	//タスクの挿入
	void GameTaskList::InsertTask ( LP_Task::iterator it, P_Task pTask )
	{
		m_plpTask->insert ( it, pTask );
	}

	bool Pred ( P_Task p )
	{

		return false;
	}

	//タスクの取外
	void GameTaskList::EraseTask ( P_Task pTask )
	{

		//削除にはforeachは使わない
		LP_Task::iterator it = begin ( * m_plpTask );
		while ( it != end ( * m_plpTask ) )
		{
			if ( (*it) == pTask )
			{
				it = m_plpTask->erase ( it );
				break;
			}
			++ it;
		}
#if 0

		remove_if ( begin ( *m_plpTask ), end ( *m_plpTask ), Pred );
#endif // 0
	}

	void GameTaskList::EraseTask ( const LP_Task::iterator it )
	{
		m_plpTask->erase ( it );
	}

	//----------------------------------------------------------------------------------------
	//	各種インターフェースの実行
	//----------------------------------------------------------------------------------------
	void GameTaskList::Init ()	{ for ( auto p : (*m_plpTask) ) { p->Init (); } }
	void GameTaskList::Rele ()	{ for ( auto p : (*m_plpTask) ) { p->Rele (); } }
	void GameTaskList::Load ()	{ for ( auto p : (*m_plpTask) ) { p->Load (); } }
	void GameTaskList::Reset ()	{ for ( auto p : (*m_plpTask) ) { p->Reset (); } }
	void GameTaskList::Move ()	{ for ( auto p : (*m_plpTask) ) { p->Move (); } }

#if 0
	void GameTaskList::Draw ()	{ for ( auto p : (*m_plpTask) ) { p->Draw (); } }
	void GameTaskList::DrawVertex () { for ( auto p : (*m_plpTask) ) { p->DrawVertex (); } }
#endif // 0


	//指定オブジェクトを最前列描画(末尾)にする
	//	指定したオブジェクトが無い場合なにもしない
	void GameTaskList::Top ( P_Task pTask )
	{
		for ( auto p : (*m_plpTask) )
		{
			if ( p == pTask )
			{
				//該当オブジェクトポインタと末尾を入れ替える
				p.swap ( *end ( *m_plpTask ) );
				break;
			}
		}
	}

	//指定オブジェクトを最背列描画(先頭)にする
	//	指定したオブジェクトが無い場合なにもしない
	void GameTaskList::End ( P_Task pTask )
	{
		for ( auto p : (*m_plpTask) )
		{
			if ( p == pTask )
			{
				//該当オブジェクトポインタと先頭を入れ替える
				p.swap ( *begin ( *m_plpTask ) );
				break;
			}
		}
	}


#if 0
	//-------------------------------------------------------------------------------------------------
	// ゲームタスクアサイン
	//	特定の一つにゲームタスクの基本インターフェースを実行する配列
	//-------------------------------------------------------------------------------------------------
	
	GameTaskAssign::GameTaskAssign() : m_index(0)
	{
	}

	GameTaskAssign::~GameTaskAssign()
	{
	}

	void GameTaskAssign::Move()
	{
		if ( GetSize() != 0 )
		{
			GetTask()->Move ();
		}
	}

	void GameTaskAssign::Draw()
	{
		if ( GetSize() != 0 )
		{
			GetTask()->Draw ();
		}
	}

	void GameTaskAssign::SetIndex ( shared_ptr < GameTask > p )
	{
		UINT index = 0;
		UINT size = GetSize();

		//先頭から走査
		while ( index++ < size )
		{
			if ( GameTaskVector::GetTask( index ) == p )
			{
				SetIndex ( index );
				break;
			}
		}
		//なかったら何もしない
	}

#endif // 0

}	//namespace GAME


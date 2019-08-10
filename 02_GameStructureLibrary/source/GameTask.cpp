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
	//	ゲームタスクの基本インターフェースを一括して行う配列
	//=========================================================================
	GameTaskVector::GameTaskVector ()
	{
		m_pvpTask = make_shared < VP_Task > ();
	}

	GameTaskVector::~GameTaskVector ()
	{
		Clear();
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
			{ m_pvpTask->erase ( it ); }
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
	void GameTaskVector::Draw () { for ( auto p : (*m_pvpTask) ) { p->Draw (); } }
	void GameTaskVector::DrawVertex () { for ( auto p : (*m_pvpTask) ) { p->DrawVertex (); } }
	

	//指定オブジェクトを最前列描画(末尾)にする
	//	指定したオブジェクトが無い場合なにもしない
	void GameTaskVector::Top ( P_Task pTask )
	{
		for ( auto p : (*m_pvpTask) )
		{
			if ( p == pTask )
			{
				//該当オブジェクトポインタと末尾を入れ替える
				p.swap ( * end ( *m_pvpTask ) );
				break;
			}
		}
	}
	
	//指定オブジェクトを最背列描画(先頭)にする
	//	指定したオブジェクトが無い場合なにもしない
	void GameTaskVector::End ( P_Task pTask )
	{
		for ( auto p : (*m_pvpTask) )
		{
			if ( p == pTask )
			{
				//該当オブジェクトポインタと先頭を入れ替える
				p.swap ( * begin ( *m_pvpTask ) );
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


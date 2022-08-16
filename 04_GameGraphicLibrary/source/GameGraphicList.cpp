//=================================================================================================
//
// GameGraphicList ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphicList.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	UP_GrpLst	GrpLst::m_inst;

	//コンストラクタ
	GameGraphicList::GameGraphicList ()
		: m_pTaskList ( nullptr )
	{
	}

	//新規リストを作成
	P_TASK_LST GameGraphicList::NewTaskList ()
	{
		m_pTaskList = make_shared < GameTaskList > ();
		return m_pTaskList;
	}

	//Z値で降順ソートされた位置に挿入
	void GameGraphicList::InsertByZ ( P_GrpCr pTask )
	{
		//一つも無いとき通常の追加
		if ( 0 == m_pTaskList->GetSize () ) { m_pTaskList->AddpTask ( pTask ); return; }

		//Z値をチェックして指定位置に挿入
		float z = pTask->GetZ ();

		//リストのループ
		PLP_Task plpTask = m_pTaskList->GetplpTask ();
		LP_Task::iterator it = begin ( * plpTask );
		for ( ; end ( * plpTask ) != it; ++ it )
		{
			//グラフィックタスクの取得
			P_GrpCr pg = dynamic_pointer_cast < GrpCr > ( * it );

			//Z値の取得
			float gz = pg->GetZ ();

			//Z値が対象より大きいとき、その前に挿入して終了
			if ( z > gz )
			{
				m_pTaskList->InsertTask ( it, pTask );
				return;
			}
		}

		//すべての値より小さい場合、末尾に追加
		m_pTaskList->AddpTask ( pTask );
	}

	void GameGraphicList::Reset ()
	{
		if ( nullptr == m_pTaskList ) { return; }

		for ( auto p : *(m_pTaskList->GetplpTask ()) )
		{
			p->Reset ();
		}
	}

	void GameGraphicList::Clear ()
	{
		m_pTaskList->Clear ();
		//明示的解放
		m_pTaskList.reset ();
	}


}	//namespace GAME


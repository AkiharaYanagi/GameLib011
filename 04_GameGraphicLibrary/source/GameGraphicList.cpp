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
		: m_pGrpTaskList ( nullptr )
	{
	}

	//新規リストを作成
	P_TASK_LST GameGraphicList::NewTaskList ()
	{
		m_pGrpTaskList = make_shared < GameTaskList > ();
		return m_pGrpTaskList;
	}

	//Z値で降順ソートされた位置に挿入
	void GameGraphicList::InsertByZ ( P_GrpCr pTask )
	{
		//一つも無いとき通常の追加
		if ( 0 == m_pGrpTaskList->GetSize () ) { m_pGrpTaskList->AddpTask ( pTask ); return; }

		//Z値をチェックして指定位置に挿入
		float z = pTask->GetZ ();

		//リストのループ
		PLP_Task plpTask = m_pGrpTaskList->GetplpTask ();
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
				m_pGrpTaskList->InsertTask ( it, pTask );
				return;
			}
		}

		//すべての値より小さい場合、末尾に追加
		m_pGrpTaskList->AddpTask ( pTask );
	}

	void GameGraphicList::Reset ()
	{
		if ( nullptr == m_pGrpTaskList ) { return; }

		for ( auto p : *(m_pGrpTaskList->GetplpTask ()) )
		{
			p->Reset ();
		}
	}

	void GameGraphicList::Clear ()
	{
		m_pGrpTaskList->Clear ();
		//明示的解放
//		m_pGrpTaskList.reset ();
	}

	void GameGraphicList::Load ()
	{
		m_pGrpTaskList->Load ();
	}

	void GameGraphicList::Init ()
	{
		m_pGrpTaskList->Init ();
	}


}	//namespace GAME


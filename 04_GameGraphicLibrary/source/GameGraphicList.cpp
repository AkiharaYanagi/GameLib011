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
	//----------------------------------------------------------------------------------------
	//@info
	//		SetSpritePostion ( VEC3 ) での設定で
	//		スプライトが順番によってアルファ値を完全に透明にしてしまうことの、
	//		原因追究と解決
	// ->
	//		DirectX の仕様
	//		透過情報(α値)のあるオブジェクトをレンダリングするときには、
	//		背面(Z値の大きい)のオブジェクトをすべてレンダリングしなければならない
	//->
	//		グラフィックを一元管理するオブジェクトの作成
	//----------------------------------------------------------------------------------------

	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	UP_GrpLst	GrpLst::m_inst;

	//コンストラクタ
	GameGraphicList::GameGraphicList ()
//		: m_pGrpTaskList ( nullptr ), m_pause ( F )
	{
	}

	//新規リストを作成して取得
	P_TASK_LST GameGraphicList::NewTaskList ()
	{
//		m_pGrpTaskList = make_shared < GameTaskList > ();
//		return m_pGrpTaskList;
		return make_shared < GameTaskList > ();
	}

	//新規リストを作成
	void GameGraphicList::MakeList ()
	{
//		m_pGrpTaskList = make_shared < GameTaskList > ();
	}

	//Z値で降順ソートされた位置に挿入
	void GameGraphicList::InsertByZ ( P_GrpCr pGrpCr )
	{
		//一つも無いとき通常の追加
//		if ( 0 == m_pGrpTaskList->GetSize () ) { m_pGrpTaskList->AddpTask ( pTask ); return; }
		if ( 0 == m_GrpLst.size () ) { m_GrpLst.push_back ( pGrpCr ); return; }


		//Z値をチェックして指定位置に挿入
		float z = pGrpCr->GetZ ();

#if 0
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
			//(同値の場合は後に追加される)
			if ( z > gz )
			{
				m_pGrpTaskList->InsertTask ( it, pGrpCr );
				return;
			}
		}
#endif // 0

		list < P_GrpCr > ::iterator it = m_GrpLst.begin ();
		for ( ; m_GrpLst.end () != it; ++ it )
		{
			float pz = (*it)->GetZ ();
			if ( z > pz )
			{
				m_GrpLst.insert ( it, pGrpCr );
				return;
			}
		}

		//すべての値より小さい場合、末尾に追加
//		m_pGrpTaskList->AddpTask ( pGrpCr );
		m_GrpLst.push_back ( pGrpCr );
	}

	void GameGraphicList::Reset ()
	{
#if 0
		if ( nullptr == m_pGrpTaskList ) { return; }

		for ( auto p : *(m_pGrpTaskList->GetplpTask ()) )
		{
			p->Reset ();
		}
#endif // 0
	}

	void GameGraphicList::Clear ()
	{
//		m_pGrpTaskList->Clear ();

		//明示的解放
//		m_pGrpTaskList.reset ();
	}

	void GameGraphicList::Load ()
	{
//		m_pGrpTaskList->Load ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->Load (); }
	}

	void GameGraphicList::Init ()
	{
//		m_pGrpTaskList->Init ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->Init (); }
	}

	void GameGraphicList::Move ()
	{
		//一時停止中はMove処理を飛ばす
		if ( m_pause ) { return; }

//		m_pGrpTaskList->Move ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->Move (); }
	}

	void GameGraphicList::Draw ()
	{
//		m_pGrpTaskList->Draw ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->Draw (); }
	}

	void GameGraphicList::DrawVertex ()
	{
//		m_pGrpTaskList->DrawVertex ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->DrawVertex (); }
	}


}	//namespace GAME


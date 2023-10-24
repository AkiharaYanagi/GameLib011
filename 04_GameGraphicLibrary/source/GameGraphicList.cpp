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
	{
		ml_GrpMain = make_shared < LP_GrpCr > ();
		ml_GrpSys = make_shared < LP_GrpCr > ();
	}

	GameGraphicList::~GameGraphicList ()
	{
		TxRele ();
		ml_GrpMain.reset ();
		ml_GrpSys.reset ();
	}

	//Z値で降順ソートされた位置に挿入
	void GameGraphicList::InsertByZ_Main ( P_GrpCr pGrpCr )
	{
		InsertByZ ( ml_GrpMain, pGrpCr );
	}

	void GameGraphicList::InsertByZ_Sys ( P_GrpCr pGrpCr )
	{
		InsertByZ ( ml_GrpSys, pGrpCr );
	}

	void GameGraphicList::InsertByZ ( PLP_GrpCr plp_grp, P_GrpCr pGrpCr )
	{
		//既存が１つも無いとき、通常の追加
		if ( 0 == plp_grp->size () ) { plp_grp->push_back ( pGrpCr ); return; }

		//Z値をチェックして指定位置に挿入
		float z = pGrpCr->GetZ ();
		for ( LP_GrpCr::iterator it = plp_grp->begin (); plp_grp->end () != it; ++ it )
		{
			float pz = ( *it )->GetZ ();
//			TRACE_F ( _T ( "pz = %lf, z = %lf\n" ), pz, z );
			if ( z > pz )
			{
				plp_grp->insert ( it, pGrpCr );
				return;
			}
		}

		//すべての値より小さい場合、末尾に追加
		plp_grp->push_back ( pGrpCr );
	}


	void GameGraphicList::TestZList ( PLP_GrpCr plp_grp )
	{
		float pre_z = 20;

		//テスト
		TRACE_F ( _T( "//-------------------\n" ) );
		for ( LP_GrpCr::iterator it = plp_grp->begin (); plp_grp->end () != it; ++ it )
		{
			float pz = ( *it )->GetZ ();
			TRACE_F ( _T( "%lf\n" ), pz );

			if ( pre_z < pz )
			{
				int i = 0;
			}

			pre_z = pz;
		}
		TRACE_F ( _T ( "//-------------------\n\n" ) );
	}


	void GameGraphicList::TxLoad ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->TxLoad (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->TxLoad (); }
	}

	void GameGraphicList::TxRele ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->TxRele (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->TxRele (); }
	}

	void GameGraphicList::TxReset ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->TxReset (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->TxReset (); }
	}

#if 0
	void GameGraphicList::Init ()
	{
#if 0
		for ( P_GrpCr p : *ml_GrpMain ) { p->Init (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->Init (); }
#endif // 0
	}

	void GameGraphicList::Move ()
	{
#if 0
		//一時停止中はMove処理を飛ばす
		if ( m_pause ) { return; }

		for ( P_GrpCr p : *ml_GrpMain ) { p->Move (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->Move (); }
#endif // 0
	}
#endif // 0

	void GameGraphicList::Draw ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->Draw (); }
//		for ( P_GrpCr p : *ml_GrpSys ) { p->Draw (); }
	}

	void GameGraphicList::DrawVertex ()
	{
//		for ( P_GrpCr p : *ml_GrpMain ) { p->DrawVertex (); }
		//for ( P_GrpCr p : *ml_GrpSys ) { p->DrawVertex (); }

#if 0

		//MainとSysでZの大きい方(後ろ側)から描画する
		float z = 1.f;	//最背面
		UINT index_main = 0;
		UINT index_sys = 0;
		LP_GrpCr::iterator it_main = ml_GrpMain->begin ();
		LP_GrpCr::iterator it_sys = ml_GrpSys->begin ();

		while ( it_main != ml_GrpMain->end () || it_sys != ml_GrpSys->end () )
		{
			//片方しかない場合
			if ( it_main == ml_GrpMain->end () )
			{
				( *it_sys )->DrawVertex ();
				++ it_sys;
				continue;
			}

			if ( it_sys == ml_GrpSys->end () )
			{
				( *it_main )->DrawVertex ();
				++ it_main;
				continue;
			}


			//両方残っているとき比較して大きい方を先に処理して進める
			float f_main = ( *it_main )->GetZ ();
			float f_sys = ( *it_sys )->GetZ ();

			if ( f_main >= f_sys )
			{
				( *it_main )->DrawVertex ();
				++ it_main;
				continue;
			}
			else
			{
				( *it_sys )->DrawVertex ();
				++ it_sys;
			}
		}

#endif // 0
	}

	void GameGraphicList::Clear ()
	{
		ml_GrpMain->clear ();
		ml_GrpSys->clear ();
	}

	void GameGraphicList::Clear_Main ()
	{
		ml_GrpMain->clear ();
	}

	void GameGraphicList::Clear_Sys ()
	{
		ml_GrpSys->clear ();
	}


}	//namespace GAME


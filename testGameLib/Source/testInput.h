//=================================================================================================
//
//	テスト
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using VP_PrmRect = vector < P_PrmRect >;

	class Test	: public TASK_VEC
	{
		VP_PrmRect		m_vp_rect;

#if 0
		P_GrpStr		m_grpStr;
		P_GrpApTx		m_grpApTx;

		P_GrpApTx		m_ascii;
		P_TxBs			m_tx;

#endif // 0
		P_GrpAcv		m_grpAcv;

		P_PrmRect		m_rect0;
		P_PrmRect		m_rect1;
		P_PrmRect		m_rect2;

	public:
		Test ();
		Test ( const Test & rhs ) = delete;
		~Test ();

		void Load () { TASK_VEC::Load (); }
		void Move ();

		void Check ( GAME_USE_KEY key );
	};


}	//namespace GAME


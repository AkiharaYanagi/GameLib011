//=================================================================================================
//
// GrpDemo ヘッダファイル
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

	class GrpDemo : public GrpAcv
	{
		UINT		m_timer;
		VEC2		m_startScaling;		//開始
		VEC2		m_targetScaling;	//目標
		VEC2		m_vec;
		VEC2		m_vel;
		VEC2		m_acc;

		VEC2		m_secondVel;	//第2速度

	public:
		GrpDemo ();
		GrpDemo ( const GrpDemo& rhs ) = delete;
		~GrpDemo ();

		void Init ();
		void Move ();

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetAcc ( VEC2 vec ) { m_acc = vec; }
		void SetSecondVel ( VEC2 vec ) { m_secondVel = vec; }
	};


}	//namespace GAME



//=================================================================================================
//
// GrpDemo ヘッダファイル
//	キャラ位置によらず一定の位置で表示
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
		UINT		m_timer;	//内部タイマ
		VEC2		m_startScaling;		//開始
		VEC2		m_targetScaling;	//目標
		VEC2		m_mag;		//倍率
		VEC2		m_vel;		//倍率変化速度
		VEC2		m_acc;		//倍率変化加速度

		VEC2		m_secondVel;	//第2速度

		bool		m_end;	//終了フラグ
		UINT		m_endTime;

	public:
		GrpDemo ();
		GrpDemo ( const GrpDemo& rhs ) = delete;
		~GrpDemo ();

		void Init ();
		void Move ();

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }
		void SetSecondVel ( VEC2 vec ) { m_secondVel = vec; }

		void SetEnd ( UINT n ) { m_end = false; m_endTime = n; }
		void ResetEnd () { m_end = false; }
	};

	using P_GrpDemo = shared_ptr < GrpDemo >;


}	//namespace GAME



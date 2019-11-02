//=================================================================================================
//
// GrpEf ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Const.h"
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GrpEf : public GrpAcv
	{
		P_VEC2	m_pDispGameBase;	//外部からの画面補正量

		UINT	m_timer;
		VEC2	m_base;
		VEC2	m_pos;
		VEC2	m_startScaling;		//開始
		VEC2	m_targetScaling;	//目標
		VEC2	m_vec;
		VEC2	m_vel;
		VEC2	m_acc;
		V_VEC2	m_vPosMatrix;		//複数マトリックス使用時の補正位置

	public:
		//引数：外部からの画面補正量
		GrpEf ( P_VEC2 pDispGameBase );
		GrpEf ( const GrpEf & rhs ) = delete;
		~GrpEf ();

		void Load ();
		void Move ();

		void On ();

		//キャラ位置による画面補正
		void SetpDispGameBase ( P_VEC2 pVec ) { m_pDispGameBase = pVec; }

		void SetBase ( VEC2 vec ) { m_base = vec; }
		void SetPos ( VEC2 vec ) { m_pos = vec; }

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }

		//複数オブジェクト
		void AddObject () 
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
			GrpAcv::AddObject ();
		}
		
		void SetPosMatrix ( UINT i, VEC2 pos )
		{
			m_vPosMatrix[i] = pos;
		}

		//計算後の最終位置を取得
		VEC2 GetCalcPos ( UINT i )
		{
			//基準位置 + 補正位置 + 外部補正位置 + 個別位置
			return m_base + m_pos + *m_pDispGameBase + m_vPosMatrix[i];

		}

		//インデックスで指定したテクスチャで中心を設定する
		void SetCenterOfTexture ( UINT index );
	};

	using P_GrpEf = shared_ptr < GrpEf >;


}	//namespace GAME



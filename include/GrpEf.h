//=================================================================================================
//
// GrpEf ヘッダファイル
//	キャラ同士による位置補正を用いる
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
		VEC2	m_base;				//基準位置
		VEC2	m_revised;			//補正位置	//GrpAcvとの混同に注意
		V_VEC2	m_vPosMatrix;		//複数マトリックス使用時の補正位置
		VEC2	m_dispBase;			//外部補正位置

		UINT	m_timer;
		VEC2	m_startScaling;		//開始
		VEC2	m_targetScaling;	//目標
		VEC2	m_vec;
		VEC2	m_vel;
		VEC2	m_acc;


	public:
		GrpEf ();
		GrpEf ( const GrpEf & rhs ) = delete;
		~GrpEf ();

		void TxLoad ();
		void Move ();

		void On ();

		//キャラ位置による画面補正
		void SetDispBase ( VEC2 v ) { m_dispBase = v; }

		void SetBase ( VEC2 vec ) { m_base = vec; }
		VEC2 GetRevised () const { return m_revised; }
		void SetRevised ( VEC2 vec ) { m_revised = vec; }

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }

		//複数オブジェクトの初期設定
		void ResetObjectNUm ( UINT n ) {}

		void AddObject () 
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
			GrpAcv::AddObject ();
		}

		void AddObject ( UINT n )
		{
			for ( UINT i = 0; i < n; ++i ) { AddObject (); }
		}
		
		void AddpObject ( P_Object p )
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
			GrpAcv::AddpObject ( p );
		}
		
		void SetPosMatrix ( UINT i, VEC2 pos )
		{
			m_vPosMatrix[i] = pos;
		}

		//計算後の最終位置を取得
		VEC2 GetCalcPos ( UINT i )
		{
			//基準位置 + 補正位置 + 外部補正位置 + 個別位置
			return m_base + m_revised + m_dispBase + m_vPosMatrix[i];

		}

		//インデックスで指定したテクスチャで中心を設定する
		void SetCenterOfTexture ( UINT index );
	};

	using P_GrpEf = std::shared_ptr < GrpEf >;


}	//namespace GAME



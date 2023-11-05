//=================================================================================================
//
// ゲームマトリクス
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameMatrix.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GameMatrix::GameMatrix ()
	{
		m_vecPos			= VEC2 ( 0.0f, 0.0f );	//自オブジェクト位置
//		m_vecDisp			= VEC2 ( 0.0f, 0.0f );	//スクリーン表示位置
		m_scalingCenter		= VEC2 ( 0.0f, 0.0f );	//回転時の中心座標
		m_scaling			= VEC2 ( 1.0f, 1.0f );	//スケーリング
		m_scalingRotation	= 0.0f;					//拡大回転の要素
		m_rotationCenter	= VEC2 ( 0.0f, 0.0f );	//回転時の中心座標
//		m_nDegree			= 0;					//角度
		m_radian			= 0;					//角度[rad]
	}

	GameMatrix::GameMatrix ( const GameMatrix& rhs )
	{
		m_vecPos			= rhs.m_vecPos;
//		m_vecDisp			= rhs.m_vecDisp;
		m_scalingCenter		= rhs.m_scalingCenter;
		m_scaling			= rhs.m_scaling;
		m_scalingRotation	= rhs.m_scalingRotation;
		m_rotationCenter	= rhs.m_rotationCenter;
//		m_nDegree			= rhs.m_nDegree;
		m_radian			= rhs.m_radian;
	}

	//変換行列の作成
	void GameMatrix::Move()
	{
//		m_vecDisp = m_vecPos;

//		D3DXMatrixTransformation2D ( &m_matrix, &m_scalingCenter, m_scalingRotation, 
//			&m_scaling, &m_rotationCenter, D3DXToRadian(m_nDegree), &m_vecDisp );
		D3DXMatrixTransformation2D ( &m_matrix, &m_scalingCenter, m_scalingRotation, 
			&m_scaling, &m_rotationCenter, m_radian, &m_vecPos );
	}

}	//namespace GAME



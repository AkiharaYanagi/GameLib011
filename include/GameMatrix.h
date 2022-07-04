//=================================================================================================
//
//	ゲームマトリクス　ヘッダ
//		１つの変換行列とそのパラメータを持つ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "Dx3D.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameMatrix
	{
		D3DXMATRIX		m_matrix;				//変換行列の一時保存

		VEC2			m_vecPos;				//自オブジェクト位置
//		VEC2			m_vecDisp;				//スクリーン表示位置
		VEC2			m_scalingCenter;		//スケーリングの中心座標
		VEC2			m_scaling;				//スケーリング
		float			m_scalingRotation;		//拡大回転の要素
		VEC2			m_rotationCenter;		//回転時の中心座標
//		INT				m_nDegree;				//角度
		float			m_radian;				//角度[rad]

	public:
		GameMatrix();
		GameMatrix ( const GameMatrix& rhs );	//複製可能
		~GameMatrix(){}

		//変換行列の作成
		void Move();

		//変換行列の取得
		D3DXMATRIX* GetpMatrix() { return & m_matrix; }
		const D3DXMATRIX* GetcpMatrix() const { return & m_matrix; }

		//値の設定
		VEC2 GetPos() const			{ return m_vecPos; }
		void SetPos ( VEC2 vecPos )	{ m_vecPos = vecPos; }
		void SetPos ( float x, float y )	{ m_vecPos.x = x; m_vecPos.y = y; }
		void SetPosX ( float x )			{ m_vecPos.x = x; }
		void SetPosY ( float y )			{ m_vecPos.y = y; }
		void AddPos ( VEC2 vecPos )	{ m_vecPos += vecPos; }
		void AddPos ( float x, float y )	{ m_vecPos.x += x; m_vecPos.y += y; }
		void AddPosX ( float x )			{ m_vecPos.x += x; }
		void AddPosY ( float y )			{ m_vecPos.y += y; }

		VEC2 GetScaling() const			{ return m_scaling; }
		void SetScaling ( VEC2 vec )		{ m_scaling = vec; }
		void SetScaling ( float x, float y )	{ m_scaling.x = x; m_scaling.y = y; }

		void SetScalingRotation ( float f )			{ m_scalingRotation = f; }
		void SetScalingCenter ( VEC2 vec )	{ m_scalingCenter = vec; }
		void SetRotationCenter ( VEC2 vec )	{ m_rotationCenter = vec; }
//		void SetDegree ( int n )					{ m_nDegree = n; }
		void SetRadian ( float f )					{ m_radian = f; }
	};


}	//namespace GAME


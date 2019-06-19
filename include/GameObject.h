//=================================================================================================
//
// GameObject ヘッダファイル
//		テクスチャ以外のグラフィックの実体
//		マトリックス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Const.h"
#include "GameMatrix.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GameObject
	{
		GameMatrix		m_matrix;			//座標
		bool			m_valid;			//表示 ON/OFF
		UINT			m_indexTexture;		//テクスチャ指定添字
		D3DXCOLOR		m_color;			//色

	public:
		GameObject ();
		GameObject ( const GameObject& rhs );	//コピー可能
		~GameObject ();

		virtual void Move ();

		void SetMatrix ( GameMatrix m ) { m_matrix = m; }	//GameMatrixは複製可能
		GameMatrix GetMatrix () const { return m_matrix; }
		GameMatrix * GetpMatrix () { return & m_matrix; }
		const D3DXMATRIX * GetcpMatrix () const { return m_matrix.GetcpMatrix (); }
		
		//マトリックスパラメータ
		VEC2 GetPos () const { return m_matrix.GetPos (); }
		void SetPos ( VEC2 v ) { m_matrix.SetPos ( v ); }
		void SetPos ( float x, float y ) { m_matrix.SetPos ( x, y ); }
		void SetPosX ( float x ) { m_matrix.SetPosX ( x ); }
		void SetPosY ( float y ) { m_matrix.SetPosY ( y ); }
		void AddPos ( VEC2 v ) { m_matrix.AddPos ( v ); }
		void AddPos ( float x, float y ) { m_matrix.AddPos ( x, y ); }
		void AddPosX ( float x ) { m_matrix.AddPosX ( x ); }
		void AddPosY ( float y ) { m_matrix.AddPosY ( y ); }

		VEC2 GetScaling () const { return m_matrix.GetScaling (); }
		void SetScaling ( VEC2 v ) { m_matrix.SetScaling ( v ); }
		void SetScaling ( float x, float y ) { m_matrix.SetScaling ( x, y ); }

		void SetScalingRotation ( float f ) { m_matrix.SetScalingRotation ( f ); }
		void SetScalingCenter ( VEC2 v ) { m_matrix.SetScalingCenter ( v ); }
		void SetRotationCenter ( VEC2 v ) { m_matrix.SetRotationCenter ( v ); }
		void SetRadian ( float f ) { m_matrix.SetRadian ( f ); }

		//有効・無効
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () const { return m_valid; }

		//テクスチャインデックス
		void SetIndexTexture ( UINT i ) { m_indexTexture = i; }
		UINT GetIndexTexture () const { return m_indexTexture; }

		//色
		void SetColor ( _CLR c ) { m_color = c; }
		_CLR GetColor () const { return m_color; }
	};

	//型定義
	typedef shared_ptr < GameObject > P_Object;
	typedef vector < P_Object > VP_Object;
	typedef shared_ptr < VP_Object > PVP_Object;


}	//namespace GAME


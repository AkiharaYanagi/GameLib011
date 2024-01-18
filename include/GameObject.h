//=================================================================================================
//
// GameObject ヘッダファイル
//		テクスチャ以外のグラフィックの実体
//		マトリックスを持つ
//		タスクではないのでグラフィック内で手動操作する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Const.h"
#include "GameMatrix.h"
#include "Fade.h"

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
		Fade			m_fade;				//フェード (単色指定もフェードに統合)

	public:
		GameObject ();
		GameObject ( const GameObject& rhs );	//コピー可能
		~GameObject ();

		void PreMove ();
		void Move ();

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
		void SetColor ( _CLR c ) { m_fade.SetColor ( c ); }
		_CLR GetColor () const { return m_fade.GetColor (); }

		//フェード
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			m_valid = true;
			m_fade.SetFade ( time, clr_start, clr_end ); 
		}
		void SetFadeIn  ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0x00ffffff, 0xffffffff );
		}
		void SetFadeOut ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0xffffffff, 0x00ffffff );
		}
		void EndFade ( _CLR clr ) { m_fade.End ( clr ); }
	};

	//型定義
	typedef std::shared_ptr < GameObject > P_Object;
	typedef std::vector < P_Object > VP_Object;
	typedef std::shared_ptr < VP_Object > PVP_Object;


}	//namespace GAME


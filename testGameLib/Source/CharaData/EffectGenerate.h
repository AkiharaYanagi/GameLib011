//=================================================================================================
//
// EffectGenerate ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
//#include "../Const.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class EffectGenerate
	{
		//--------------------------------------------------
		UINT	m_id;		//エフェクト生成のID

		//--------------------------------------------------
		UINT	m_index;	//指定Efインデックス
		VEC2	m_pos;		//生成位置
		float	m_z;		//z位置
		bool	m_gnrt;		//生成
		bool	m_loop;		//繰返
		bool	m_sync;		//同期

	public:
		EffectGenerate ();
		EffectGenerate ( const EffectGenerate& rhs ) = delete;		//コピー禁止
		~EffectGenerate ();

		void SetID ( UINT i ) { m_id = i; }
		UINT GetID () const { return m_id; }

		void SetIndex ( UINT i ) { m_index = i; }
		UINT GetIndex () const { return m_index; }

		void SetPos ( VEC2 v ) { m_pos = v; }
		VEC2 GetPos () const { return m_pos; }

		void SetZ ( float f ) { m_z = f; }
		float GetZ () const { return m_z; }

		void SetGnrt ( bool b ) { m_gnrt = b; }
		bool GetGnrt () const { return m_gnrt; }

		void SetLoop ( bool b ) { m_loop = b; }
		bool GetLoop () const { return m_loop; }

		void SetSync ( bool b ) { m_sync = b; }
		bool GetSync () const { return m_sync; }

	};
	

	using P_EfGnrt = shared_ptr < EffectGenerate >;
	using VP_EfGnrt = vector < P_EfGnrt >;
	using PVP_EfGnrt = shared_ptr < VP_EfGnrt >;


}	//namespace GAME



//=================================================================================================
//
//	Sequence ヘッダファイル
//		スクリプトの一連、アクションとエフェクトに派生
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Script.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Sequence
	{
		PVP_Script		m_pvpScript;	//スクリプト配列
		UINT			m_next;			//次シークエンスID

	public:
		Sequence ();
		Sequence ( const Sequence & rhs ) = delete;
		virtual ~Sequence ();

		void Rele ();

		//-----------------------------------------------------------------
		//スクリプトの追加
		void AddpScript ( P_Script pScript ) { m_pvpScript->push_back ( pScript ); }

		//スクリプト配列サイズの取得
		UINT SizeScript () const { return m_pvpScript->size(); }

		//スクリプト配列ポインタを取得
		PVP_Script GetpvpScript () { return m_pvpScript; }

		//スクリプトの取得
		P_Script GetpScript ( UINT index ) { return m_pvpScript->at ( index ); }

		//次スクリプトが存在するかどうか
		bool IsNextScript ( UINT index ) const { return ( index < m_pvpScript->size() - 1 ); }

		//最終スクリプトかどうか
		bool IsEndScript ( UINT index ) const { return ( index == m_pvpScript->size() - 1 ); }

		//次シークエンスID
		UINT GetNextID () const { return m_next; }
		void SetNextID ( UINT id ) { m_next = id; }
	};

	using WP_Sqc = weak_ptr < Sequence >;
	using P_Sqc = shared_ptr < Sequence >;
	using VP_Sqc = vector < P_Sqc >;
	using PVP_Sqc = shared_ptr < VP_Sqc >;


}	//namespace GAME



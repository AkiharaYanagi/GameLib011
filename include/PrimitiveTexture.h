//=================================================================================================
//
//	プリミティブ テクスチャ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "GamePrimitive.h"
#include "GameTexture.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class PrimitiveTexture : public GamePrimitiveRect
	{
		P_TxAcv			m_tx;
		bool			m_multiple;

	public:
		PrimitiveTexture ();
		PrimitiveTexture ( const PrimitiveTexture & rhs ) = delete;
		~PrimitiveTexture ();

		void Load ();
		void Rele ();
		void Reset ();
		void DrawVertex ();

		void SetFileName ( LPCTSTR filename ) { m_tx->SetFileName ( filename ); }
		void SetFileName ( tstring filename ) { m_tx->SetFileName ( filename ); }

		void SetMultiple ( bool b ) { m_multiple = b; }
	};

	using PrmTx = PrimitiveTexture;
	using P_PrmTx = shared_ptr < PrmTx >;


}	//namespace GAME


//=================================================================================================
//
// GrpBlink ヘッダファイル
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
	class GrpBlink : public GrpAcv
	{
		bool	m_blink;
		UINT	m_timer;
		UINT	m_blinkTime;
		bool	m_active;

		void Blink ();

	public:
		GrpBlink ();
		GrpBlink ( const GrpBlink & rhs ) = delete;
		~GrpBlink ();

		void Move ();

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetBlinkTime ( UINT n ) { m_blinkTime = n; }
		void Stop ();
		void Start ();
	};

	using P_GrpBlink = shared_ptr < GrpBlink >;


}	//namespace GAME



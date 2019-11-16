//=================================================================================================
//
// GrpBlink �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// �錾
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



//=================================================================================================
//
// Fade �w�b�_�t�@�C��
//		�őO�ʂɔz�u������ʃT�C�Y�̔������O���t�B�b�N�ŁA�t�F�[�h�C���E�A�E�g���s��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameGraphicLibrary.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Fade : public PrmRect
	{
		UINT	m_timer;
		UINT	m_fadeOutTime;
		UINT	m_darkInTime;
		UINT	m_darkOutTime;

	public:
		Fade ();
		Fade ( const Fade & rhs ) = delete;
		~Fade ();

		void Move ();
		bool IsActive () { return ( 0 != m_timer ); }

		void SetWhiteOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_fadeOutTime = time;
			m_timer = 1; 
		}

		void SetDarkIn ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkInTime = time;
			m_timer = 1; 
		}

		void SetDarkOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkOutTime = time;
			m_timer = 1; 
		}
	};

	using P_Fade = shared_ptr < Fade >;


}	//namespace GAME



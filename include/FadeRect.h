//=================================================================================================
//
// FadeRect �w�b�_�t�@�C��
//		�őO�ʂɔz�u������ʃT�C�Y�̔������O���t�B�b�N�ŁA�t�F�[�h�C���E�A�E�g���s��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameGraphicLibrary.h"
#include "Timer.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class FadeRect : public PrmRect
	{
		P_Timer	m_timer;
		_CLR	m_color0;	//�����F
		_CLR	m_color1;	//�ڕW�F

	public:
		FadeRect ();
		FadeRect ( const FadeRect & rhs ) = delete;
		~FadeRect ();

		void Move ();

		//�F�ݒ�
		void SetColor ( _CLR clr0, _CLR clr1 ) { m_color0 = clr0; m_color1 = clr1; }
		void SetTime ( UINT t )
		{ 
			m_timer->SetTargetTime ( t ); 
		}

		void Start ( UINT time )
		{
			m_timer->SetTargetTime ( time );
			m_timer->Start ();
			PrmRect::SetValid ( true );
		}

		bool IsActive () { return m_timer->IsActive (); }

		//-----------------------------------
		//��̐ݒ�
		//@info 0x00000000 ���w�肷��Ƃ�D3DXCOLOR�̏������̂��ߐ������e���� UL ��t����
		
		//�z���C�g�A�E�g( 0x00ffffff �� 0xffffffff )
		void SetWhiteOut ( UINT time ) { SetColor ( 0x00ffffff, 0xffffffff ); Start ( time ); }

		//�u���b�N�C�� ( 0xff000000 �� 0x00000000 )
		void SetDarkIn ( UINT time ) { SetColor ( 0xff000000, 0x00000000UL ); Start ( time ); }

		//�u���b�N�A�E�g( 0x00000000 �� 0xff000000 )
		void SetDarkOut ( UINT time ) { SetColor ( 0x00000000UL, 0xff000000 ); Start ( time ); }

#if 0
//		bool IsActive () { return m_timer->IsActive (); }
		//�z���C�g�A�E�g( 0x00ffffff �� 0xffffffff )
		void SetWhiteOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_whiteOutTime = time;
			m_timer->Start (); 
		}

		//�u���b�N�C�� ( 0xff000000 �� 0x00000000 )
		void SetDarkIn ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkInTime = time;
			m_timer->Start ();
		}

		//�u���b�N�A�E�g( 0x00000000 �� 0xff000000 )
		void SetDarkOut ( UINT time )
		{
			PrmRect::SetValid ( true );
			m_darkOutTime = time;
			m_timer->Start ();
		}
#endif // 0
	};

	using P_Fade = shared_ptr < FadeRect >;


}	//namespace GAME



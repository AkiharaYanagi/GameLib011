//=================================================================================================
//
// FadeRect �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "FadeRect.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FadeRect::FadeRect ()
	: m_color0 ( 0x00000000UL ), m_color1 ( 0xff000000UL )
	{
		PrmRect::SetValid ( false );
		PrmRect::SetRect ( 0, 0, 1.f * WINDOW_WIDTH, 1.f * WINDOW_HEIGHT );
		PrmRect::SetAllZ ( Z_FADE );
		m_timer = make_shared < Timer > ();
	}

	FadeRect::~FadeRect ()
	{
	}

	void FadeRect::Move ()
	{
		UINT t = m_timer->GetTime ();

		//�����F->�ڕW�F( m_color0 �� m_color1 )
//		if ( 0 != m_targetTime )
		if ( m_timer->IsActive () )
		{
			if ( m_timer->IsLast () )
			{
				m_timer->Reset ();
				PrmRect::SetAllColor ( m_color1 );
				PrmRect::SetValid ( false );
			}
			else
			{
				float alpha = (1.f / m_timer->GetTargetTime () ) * t;	//���l���Z�o
				if ( m_color0.a > m_color1.a )	//�����̏ꍇ��1.f����
				{
					alpha = 1.f - alpha;
				};
				DWORD c = _CLR ( m_color1.r, m_color1.g, m_color1.b, alpha );
				PrmRect::SetAllColor ( c );
			}
		}

#if 0
		//�z���C�g�A�E�g( 0x00ffffff �� 0xffffffff )
		if ( 0 != m_whiteOutTime )
		{
			if ( t == m_whiteOutTime )
			{
				m_timer->Reset ();
				m_whiteOutTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0xffffffff ) );
				PrmRect::SetValid ( false );
			}
			else
			{
//				UINT alpha = (0xff / m_whiteOutTime) * t;		//���l���Z�o
				UCHAR alpha = (UCHAR)((255.f / m_whiteOutTime) * t);		//���l���Z�o
				UINT alpha_s = alpha << 24;
				UINT U_color = alpha_s ^ 0x00ffffff;
				//				_CLR color = _CLR ( alpha_s ^ 0x00ffffff );
				_CLR color = _CLR ( U_color );
				TRACE_F ( _T ( "alpha = %x, alpha_s = %x, color = %x\n" ), alpha, alpha_s, U_color );
				PrmRect::SetAllColor ( color );
			}
		}

		//�u���b�N�C�� ( 0xff000000 �� 0x00000000 )
		if ( 0 != m_darkInTime ) 
		{
			if ( t == m_darkInTime )
			{
				m_timer->Reset ();
				m_darkInTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0x00ffffff ) );
				PrmRect::SetValid ( false );
			}
			else
			{
				UINT alpha = 0xff - ( 0xff / m_darkInTime ) * t;			//���l���Z�o
				_CLR color = _CLR ( alpha << 24 ^ 0x00000000 );
				PrmRect::SetAllColor ( color );
			}
		}

		//�u���b�N�A�E�g( 0x00000000 �� 0xff000000 )
		if ( 0 != m_darkOutTime )
		{
			if ( t == m_darkOutTime )
			{
				m_timer->Reset ();
				m_darkOutTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0xff000000 ) );
			}
			else
			{
				UINT alpha = ( 0xff / m_darkOutTime ) * t;			//���l���Z�o
				_CLR color = _CLR ( alpha << 24 ^ 0x00000000 );
				PrmRect::SetAllColor ( color );
			}
		}
#endif // 0


		m_timer->Move ();
		PrmRect::Move ();
	}


}	//namespace GAME


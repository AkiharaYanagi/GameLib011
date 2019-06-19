//=================================================================================================
//
// Fade �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Fade.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Fade::Fade () : 
		m_timer ( 0 ), m_fadeOutTime ( 0 ), m_darkInTime ( 0 ), m_darkOutTime ( 0 )
	{
		PrmRect::SetValid ( false );
		PrmRect::SetRect ( 0, 0, 1.f * WINDOW_WIDTH, 1.f * WINDOW_HEIGHT );
		PrmRect::SetAllColor ( _CLR ( 0xff000000 ) );
	}

	Fade::~Fade ()
	{
	}

	void Fade::Move ()
	{
		//�t�F�[�h(�z���C�g)�A�E�g( 0x00ffffff �� 0xffffffff )
		if ( m_fadeOutTime == 0 )
		{
		}
		else 
		{
			if ( m_timer == m_fadeOutTime )
			{
				m_timer = 0;
				m_fadeOutTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0xffffffff ) );
				PrmRect::SetValid ( false );
			}
			else
			{
				UINT alpha = ( 0xff / m_fadeOutTime ) * m_timer;				//���l���Z�o
				_CLR color = _CLR ( alpha << 24 ^ 0x00000000 );
				PrmRect::SetAllColor ( color );

				++m_timer;
			}
		}

		//�_�[�N�C�� ( 0xff000000 �� 0x00000000 )
		if ( m_darkInTime == 0 ) 
		{
		}
		else
		{
			if ( m_timer == m_darkInTime )
			{
				m_timer = 0;
				m_darkInTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0x00ffffff ) );
				PrmRect::SetValid ( false );
			}
			else
			{
				UINT alpha = 0xff - ( 0xff / m_darkInTime ) * m_timer;			//���l���Z�o
				_CLR color = _CLR ( alpha << 24 ^ 0x00000000 );
				PrmRect::SetAllColor ( color );

				++m_timer;
			}
		}

		//�_�[�N�A�E�g( 0x00000000 �� 0xff000000 )
		if ( 0 != m_darkOutTime )
		{
			if ( m_timer == m_darkOutTime )
			{
				m_timer = 0;
				m_darkOutTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0xff000000 ) );
			}
			else
			{
				UINT alpha = ( 0xff / m_darkOutTime ) * m_timer;			//���l���Z�o
				_CLR color = _CLR ( alpha << 24 ^ 0x00000000 );
				PrmRect::SetAllColor ( color );
				++m_timer;
			}
		}

		PrmRect::Move ();
	}


}	//namespace GAME


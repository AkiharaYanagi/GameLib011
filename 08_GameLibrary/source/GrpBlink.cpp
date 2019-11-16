//=================================================================================================
//
// GrpEf �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GrpBlink.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GrpBlink::GrpBlink ()
	 :	m_blink ( true ), m_timer ( 0 ), m_blinkTime ( 30 )
	{
	}

	GrpBlink::~GrpBlink ()
	{
	}

	void GrpBlink::Move ()
	{
		if ( m_active )
		{
			//�_��
			Blink ();
		}
		GrpAcv::Move ();
	}

	void GrpBlink::Blink ()
	{
		//�_��
		if ( m_blink )
		{
			if ( m_timer == m_blinkTime )
			{
				m_blink = false;
			}
			else
			{
				++m_timer;
			}
		}
		else
		{
			if ( m_timer == 0 )
			{
				m_blink = true;
			}
			else
			{
				--m_timer;
			}
		}

		//���l���Z�o���Đݒ�
		UINT alpha = 0x80 + (0xff / m_blinkTime) / 2 * m_timer;
		_CLR color = _CLR ( alpha << 24 ^ 0x00ffffff );
		SetAllColor ( color );
	}

	void GrpBlink::Stop ()
	{
		m_active = false;
		SetAllColor ( 0xffffffff );
	}

	void GrpBlink::Start ()
	{
		m_active = true;
	}



}	//namespace GAME


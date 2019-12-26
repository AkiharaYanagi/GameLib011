//=================================================================================================
//
// GrpEf �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "stdafx.h"
#include "GrpEf.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GrpEf::GrpEf () :
		m_timer ( 0 ), 
		m_base ( VEC2 ( 0.f, 0.f ) ), 
		m_pos ( VEC2 ( 0.f, 0.f ) ), 
		m_startScaling ( VEC2 ( 1.8f, 1.8f ) ), 
		m_targetScaling ( VEC2 ( 1.2f, 1.2f ) ),
		m_vec ( VEC2 ( 0.f, 0.f ) ), 
		m_vel ( VEC2 ( 0.f, 0.f ) ),
		m_acc ( VEC2 ( 0.01f, 0.01f ) )
	{
		SetValid ( false );
		m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
	}

	GrpEf::~GrpEf ()
	{
	}

	void GrpEf::Load ()
	{
		GrpAcv::Load ();

		//�ǂݍ��񂾃e�N�X�`���̃T�C�Y�ɂ��̂� Load() ��
		SetCenterOfTexture ( 0 );
	}

	void GrpEf::Move ()
	{
		//-----------------------------------------------
		//�ʒu
//		GetpMatrix()->SetPos ( m_pos + m_base );
//		SetAllPos ( m_pos + m_base + *m_pDispGameBase );

		PVP_Object pvpObj = GrpAcv::GetpvpObject ();
		UINT size = pvpObj->size ();
		for ( UINT i = 0; i < size; ++ i )
		{
			//��ʒu + �␳�ʒu + �O���␳�ʒu + �ʈʒu
			(*pvpObj)[i]->SetPos (  m_base + m_pos + m_dispBase + m_vPosMatrix[i] );
		}
		
		//-----------------------------------------------
		//�g�k
		for ( UINT i = 0; i < size; ++i )
		{
			if ( ! (*pvpObj)[i]->GetValid () ) { continue; }

			//�ڕW�l�ɒB������I��
			if ( m_targetScaling.x < 0 )
			{
				if ( m_vec.x > m_targetScaling.x || m_vec.y > m_targetScaling.y )
				{
					m_vel += m_acc;
					m_vec += m_vel;
				}
			}
			else
			{
				if ( m_vec.x < m_targetScaling.x || m_vec.y < m_targetScaling.y )
				{
					m_vel += m_acc;
					m_vec += m_vel;
				}
			}

			(*pvpObj)[i]->SetScaling ( m_vec );
		}

		GrpAcv::Move ();
	}

	void GrpEf::On ()
	{
		m_vec = m_startScaling;
		m_vel = VEC2 ( 0.f, 0.f );
//		SetIndexTexture ( 0 );
	}

	void GrpEf::SetCenterOfTexture ( UINT index )
	{
		//�f�t�H���g��ScalingCenter��RotationCenter���e�N�X�`���̒��S�ɂ���
		VEC2 vec = GetCenterOfTexture ( index );
		PVP_Object pvpObj = GrpAcv::GetpvpObject ();
		UINT size = pvpObj->size ();
		for ( UINT i = 0; i < size; ++i )
		{
			(*pvpObj)[i]->SetScalingCenter ( vec );
			(*pvpObj)[i]->SetRotationCenter ( vec );
		}
		m_base = -1.f * vec;		//�\���ʒu���e�N�X�`���̒��S�ɂ���
	}



}	//namespace GAME


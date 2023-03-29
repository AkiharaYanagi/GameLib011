//=================================================================================================
//
// Rect �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Rect.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�[���ŏ���������
	void ZeroRect ( RECT & rect )
	{
		rect.top = 0;
		rect.left = 0;
		rect.right = 0;
		rect.bottom = 0;
	}

	//��g(���ׂ�0)���ǂ���
	bool IsZeroRect ( const RECT & rect )
	{
		return ( rect.top == 0 ) && ( rect.bottom == 0 ) && ( rect.left == 0 ) && ( rect.right == 0 );
	}

	//��`�̒l��ݒ肷��
	void SetRect ( RECT & rect, LONG left, LONG top, LONG right, LONG bottom )
	{
		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;
	}

	//��`��rhs����lhs�ɃR�s�[����
	void CopyRect ( RECT & lhs, const RECT & rhs )
	{
		lhs.left	= rhs.left;
		lhs.top		= rhs.top;
		lhs.right	= rhs.right;	
		lhs.bottom	= rhs.bottom;
	}

	//�g�z����[������������
	void ZeroVecRect ( PV_RECT pvRect )
	{
		for ( RECT & rect : * pvRect ) { ZeroRect ( rect ); }
	}


	//-------------------------------------
	//�d�Ȃ蔻��
	//�_�Ƌ�`�̏d�Ȃ蔻��
	bool OverlapPoint ( const VEC2 & pt, const RECT & rect )
	{
		if ( rect.left <= pt.x && pt.x <= rect.right )
		{
			if ( rect.top <= pt.y && pt.y <= rect.bottom )
			{
				return T;
			}
		}
		return F;
	}


	//��`�Q�ŏd�Ȃ蔻��
	bool OverlapRect ( const RECT & rect1, const RECT & rect2 )
	{
		LONG t1 = rect1.top;
		LONG l1 = rect1.left;
		LONG b1 = rect1.bottom;
		LONG r1 = rect1.right;
		LONG t2 = rect2.top;
		LONG l2 = rect2.left;
		LONG b2 = rect2.bottom;
		LONG r2 = rect2.right;

		//�����ꂩ�̑傫�����O�������画�肵�Ȃ�
		if ( ( b1 - t1 ) == 0 || ( r1 - l1 ) == 0 || ( b2 - t2 ) == 0 || ( r2 - l2 ) == 0 ) { return false; }
		
		//�㉺�ƍ��E�ŏd�Ȃ���������ׂĖ������Ă�����true
		return ( (t1 <= b2) && (b1 >= t2) && (l1 <= r2) && (r1 >= l2) );
	}

	//�g�z��ɍs���d�Ȃ蔻��
	bool OverlapAryRect ( PV_RECT pvRect1, PV_RECT pvRect2 )
	{
		UINT i1 = 0;
		for ( RECT r1 : * pvRect1 )
		{
			if ( IsZeroRect ( r1 ) ) { continue; }
			UINT i2 = 0;
			for ( RECT r2 : * pvRect2 )
			{
				if ( IsZeroRect ( r2 ) ) { continue; }
				if ( OverlapRect ( r1, r2 ) ) { return true; }
			}
			++ i1;
		}
		return false;
	}


	//�g�d�Ȃ蕔���̒��S�ʒu���擾
	VEC2 GetOverlayCenterRects ( const RECT & rect1, const RECT & rect2 )
	{
		//�ߒl
		VEC2 ret = VEC2 ( 0, 0 );
		
		//====================================================
		//������(x)

		//-------------------------------------------------------
		//				:     (l1 < l2)		:	(l2 < l1)		:
		//-------------------------------------------------------
		// (r1 < r2)	: [A] l1,l2,r1,r2	: [C] l2,l1,r1,r2	:
		//-------------------------------------------------------
		// (r2 < r1)	: [B] l1,l2,r2,r1	: [D] l2,l1,r2,r1	:
		//-------------------------------------------------------

		//[A] �y1�k2 �z�l	//[C] �k2�y1 �z�l
		//[B] �y1�k2 �l�z	//[D] �k2�y1 �l�z


		//�d�Ȃ�O��
		//[-] �y1�z�k2�l
		//[-] �k2�l�y1�z

		if ( rect1.left < rect2.left )
		{
			if ( rect1.right < rect2.right )
			{
				ret.x = rect2.left + ( rect1.right - rect2.left ) * 0.5f;	//[A]
			}
			else
			{
				ret.x = rect2.left + ( rect2.right - rect2.left ) * 0.5f;	//[B]
			}
		}
		else
		{
			if ( rect1.right < rect2.right )
			{
				ret.x = rect1.left + ( rect1.right - rect1.left ) * 0.5f;	//[D]
			}
			else
			{
				ret.x = rect1.left + ( rect2.right - rect1.left ) * 0.5f;	//[C]
			}
		}

		//====================================================
		//�c����(y)
		if ( rect1.top < rect2.top )
		{
			if ( rect1.bottom < rect2.bottom )
			{
				ret.y = rect2.top + ( rect1.bottom - rect2.top ) * 0.5f;	//[A]
			}
			else
			{
				ret.y = rect2.top + ( rect2.bottom - rect2.top ) * 0.5f;	//[B]
			}
		}
		else
		{
			if ( rect1.bottom < rect2.bottom )
			{
				ret.y = rect1.top + ( rect1.bottom - rect1.top ) * 0.5f;	//[D]
			}
			else
			{
				ret.y = rect1.top + ( rect2.bottom - rect1.top ) * 0.5f;	//[C]
			}
		}

		return ret;
	}

	//�g�z��ɍs���d�Ȃ蔻��(�d�Ȃ�̒��S�t��)
	bool OverlapAryRect_Center ( PV_RECT pvRect1, PV_RECT pvRect2, VEC2 & center )
	{
		UINT i1 = 0;
		for ( RECT r1 : * pvRect1 )
		{
			if ( IsZeroRect ( r1 ) ) { continue; }
			UINT i2 = 0;
			for ( RECT r2 : * pvRect2 )
			{
				if ( IsZeroRect ( r2 ) ) { continue; }
				if ( OverlapRect ( r1, r2 ) )
				{
					center = GetOverlayCenterRects ( r1, r2 );
					return true; 
				}
			}
		}
		return false;
	}


}	//namespace GAME


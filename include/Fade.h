//=================================================================================================
//
// �t�F�[�h
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "DxDefine.h"			//DirectX���O����
#include "GameTask.h"
//#include "GameGraphicLibrary.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//�t�F�[�h�I�u�W�F�N�g
	//	�O���t�B�b�N���ۗL����^�X�N
	//	���ԂƐF���w�肵�A�t���[�����ɑJ�ڂ���(���ݐF��Ԃ�)
	//------------------------------------------------------------
	class _Fade
	{
		UINT	m_timer;	//���ݎ���
		UINT	m_time;		//�ڍs����

		_CLR	m_color_present;//���ݐF

		_CLR	m_color_start;	//�����F
		_CLR	m_color_end;	//�ڕW�F

	public:
		_Fade ();
		_Fade ( const _Fade & rhs ) = delete;
		~_Fade ();

		//���t���[������(Move()���擪�ŌĂ�)
		void PreMove ();

		//�F�擾
		_CLR GetColor () const { return m_color_present; }

		//�t�F�[�h���Ԑݒ�
		void SetTime ( UINT time );

		//�F�ݒ�
		void SetFadeColor ( _CLR clr_start, _CLR clr_end )
		{
			m_color_start = clr_start; 
			m_color_end = clr_end; 
		}

		//�t�F�[�h�ݒ�
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			SetTime ( time );
			SetFadeColor ( clr_start, clr_end );
			m_color_present = clr_start;
		}

		//�I��
		void End ( _CLR clr );

	private:

		//������
		void _Fade_Do ();
	};


//=================================================================================================
//=================================================================================================

#if 0

	class Fade : public GrpAcv
	{
		UINT	m_timer;	//���ݎ���
		UINT	m_time;		//�ڍs����

//		_CLR	m_color;	//���ݐF

		_CLR	m_color_start;	//�����F
		_CLR	m_color_end;	//�ڕW�F

		bool	m_active;	//�ғ��t���O


	public:
		Fade ();
		Fade ( const Fade & rhs ) = delete;
		~Fade ();

		//���t���[������(Move()���擪�ŌĂ�)
		void PreMove ();
		void Move ();

		//�F�擾
		_CLR GetColor () const { return m_color; }


		//�t�F�[�h���Ԑݒ�
		void SetTime ( UINT time );


		//�F�ݒ�
		void SetColor ( _CLR clr_start, _CLR clr_end ) { m_color_start = clr_start; m_color_end = clr_end; }

		bool IsActive () const { return m_active; }

		//-----------------------------------
		//��̐ݒ�
		//@info 0x00000000 ���w�肷��Ƃ�D3DXCOLOR�̏������̂��ߐ������e���� UL ��t����

		//�z���C�g�A�E�g( 0x00ffffff �� 0xffffffff )
		void SetWhiteOut ( UINT time ) { SetColor ( 0x00ffffff, 0xffffffff ); SetTime ( time ); }

		//�u���b�N�C�� ( 0xff000000 �� 0x00000000 )
		void SetDarkIn ( UINT time ) { SetColor ( 0xff000000, 0x00000000UL ); SetTime ( time ); }

		//�u���b�N�A�E�g( 0x00000000 �� 0xff000000 )
		void SetDarkOut ( UINT time ) { SetColor ( 0x00000000UL, 0xff000000 ); SetTime ( time ); }

	private:

		//������
		void _Fade ();
	};

	using P_FADE = shared_ptr < Fade >;

#endif // 0


}	//namespace GAME



//=================================================================================================
//
// �t�F�[�h
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

		//���t���[������
		void PreMove ();
		void Move ();

		//�F�擾
		_CLR GetColor () const { return m_color; }


		//�t�F�[�h���Ԑݒ�
		void SetTime ( UINT time );

		void _Fade ();

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

	};

	using P_FADE = shared_ptr < Fade >;


}	//namespace GAME



//=================================================================================================
//
// �Q�[����ʂւ̃f�o�b�O�e�L�X�g�\��
//		�Q�[����ʂւ̒��_��p�����e�L�X�g�\��
//		DebugTextNum = 15�܂ł̃C���f�b�N�X���w��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Dx3D.h"
#include "DxVertex.h"
#include "GameText.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	class DebugOutGameWindow
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using P_DBG_WND = unique_ptr < DebugOutGameWindow >;
		static P_DBG_WND	m_inst;
		DebugOutGameWindow ();
		DebugOutGameWindow ( const DebugOutGameWindow & rhs ) = delete;
	public:
		~DebugOutGameWindow ();
		static void Create();
		static P_DBG_WND & instance() { return m_inst; }
	//--------------------------------------------------

	private:

	public:
		enum Const_DebugOutGameWindow
		{
			DebugTextNum = 15,
		};
	private:
		TX				m_texture[DebugTextNum];		//�e�N�X�`��
		DxVertex4		m_vertex[DebugTextNum];			//���_�����I�u�W�F�N�g
		tstring			m_tstr[DebugTextNum];			//������

		//�f�o�b�O�p�Œ�\��
		//FPS
		//TIme

		TX				m_testTx;
		DxVertex4		m_testVx;

	public:
		void Load ();
		void Rele ();
		void Reset ( LPDIRECT3DDEVICE9 d3dDevice );	//�Đݒ�
		void Move ();

		//���_�ɂ��`��
		void DrawVertex ();

		//������w��
		void SetStr ( UINT index, LPCTSTR lpctstr );
		void SetStr ( UINT index, tstring& tstr );

		//�ʒu�w��
		void SetPos ( UINT index, float x, float y ) { m_vertex[index].SetPos ( x, y ); }

		//��ʂɃe�L�X�g�`�悷�镶����t�H�[�}�b�g��ݒ�
		void DebugOutf ( UINT index, LPCTSTR format, ... );

		//��\��
		void Off ();

	};

	using DBGO_WND = DebugOutGameWindow;

//�V���O���g���A�N�Z�X�p
#define DBGOUT_WND		DebugOutGameWindow::instance()
#define DBGOUT_WND_F	DebugOutGameWindow::instance()->DebugOutf
//#define TRACEW_CHF	DebugOutGameWindow::instance()->DebugOutchf

}	//namespace GAME



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
#include "DebugLibrary.h"
#include "Dx3D.h"
#include "DxVertex.h"
#include "GameTextLibrary.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	using UP_CTSTR = unique_ptr < TCHAR >;


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
		static P_DBG_WND & Inst() { return m_inst; }
	//--------------------------------------------------

	private:

	public:
		enum Const_DebugOutGameWindow
		{
			DebugTextNum = 15,
			DebugVertexNum = 64,
		};
	private:
		TX			m_texture[DebugTextNum];	//�e�N�X�`��
		Vx_Rect		m_vertex[DebugTextNum];		//���_�����I�u�W�F�N�g
		tstring		m_tstr[DebugTextNum];		//������

		//�f�o�b�O�p�Œ�\��
		//FPS
		//TIme

		TX			m_testTx;
		Vx_Rect		m_testVx;

		bool		m_bTime;
		vector < P_VxRct >		m_vpVx;

	public:
		void Load ();
		void Rele ();
		void Reset ( D3DDEV d3dDevice );	//�Đݒ�
		void Move ();

		//���_�ɂ��`��
		void DrawVertex ();

		//������w��
		void SetStr ( UINT index, LPCTSTR lpctstr );
		void SetStr ( UINT index, tstring& tstr );
		void SetStr ( UINT index, UP_TSTR pstr );

		//�ʒu�w��
		void SetPos ( UINT index, float x, float y ) { m_vertex[index].SetPos ( x, y ); }

		//��ʂɃe�L�X�g�`�悷�镶����t�H�[�}�b�g��ݒ�
		void DebugOutf ( UINT index, LPCTSTR format, ... );

		//�Œ�\�� : �ғ�����[F]
		void DebugOutWnd_Time ( LPCTSTR format, ... );
		void SetbDispTime ( bool b ) { m_bTime = b; }

		//��\��
		void Off ();

	private:
		UINT Size ( LPCTSTR lpctstr ) const;
	};

	using DBGO_WND = DebugOutGameWindow;


//�V���O���g���A�N�Z�X�p
#define DBGOUT_WND		DBGO_WND::Inst()
#define DBGOUT_WND_F	DBGO_WND::Inst()->DebugOutf


}	//namespace GAME



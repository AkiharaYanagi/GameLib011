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

	//=====================================================
	//�Œ�\��
	class ConstDebugOut
	{
		bool		m_valid;
		TX			m_tx;		//�e�N�X�`��
		Vx_Rect		m_vx;		//���_�W��(��`)

	public:
		ConstDebugOut ();
		ConstDebugOut ( const ConstDebugOut & rhs ) = delete;
		~ConstDebugOut ();

		void Load ();
		void Rele ();
		void Reset ();
		void Move ();
		void Draw ();

		void SetPos ( VEC2 v );
		void SetStr ( UP_TSTR upctstr );
		void SetValid ( bool b ) { m_valid = b; }
	};
	//=====================================================



	// �Q�[����ʂւ̃f�o�b�O�e�L�X�g�\��
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
		//�萔
		enum Const_DebugOutGameWindow
		{
			DebugTextNum = 15,
			DebugVertexNum = 32,
		};
	private:
		//�f�o�b�O�\���z��
		TX			m_texture[DebugTextNum];	//�e�N�X�`��
		Vx_Rect		m_vertex[DebugTextNum];		//���_�����I�u�W�F�N�g
		tstring		m_tstr[DebugTextNum];		//������

		//�f�o�b�O�p�Œ�\��
		ConstDebugOut		m_frame;
		ConstDebugOut		m_FPS;
		ConstDebugOut		m_time;

	public:
		void Load ();
		void Rele ();
		void Reset ( D3DDEV d3dDevice );	//�Đݒ�
		void Move ();
		void DrawVertex ();		//���_�ɂ��`��


		//-----------------------------------------------------

		//�\��������w��
		void SetStr ( UINT index, LPCTSTR lpctstr );
		void SetStr ( UINT index, tstring& tstr );
		void SetStr ( UINT index, UP_TSTR pstr );

		//�ʒu�w��
		void SetPos ( UINT index, float x, float y ) { m_vertex[index].SetPos ( x, y ); }

		//��ʂɃe�L�X�g�`�悷�镶����t�H�[�}�b�g��ݒ�
		void DebugOutf ( UINT index, LPCTSTR format, ... );


		//-----------------------------------------------------
		//�Œ�\�� : �ғ�����[F]
		void DebugOutWnd_Time ( LPCTSTR format, ... );
		void SetbDisp_Time ( bool b ) { m_frame.SetValid ( b ); }
		//�Œ�\�� : FPS
		void DebugOutWnd_FPS ( LPCTSTR format, ... );
		void SetbDisp_FPS ( bool b ) { m_FPS.SetValid ( b ); }
		//�Œ�\�� : ���쎞��[ms], �`�掞��[ms]
		void DebugOutWnd_Move_Draw ( LPCTSTR format, ... );
		void SetbDisp_Move_Draw ( bool b ) { m_time.SetValid ( b ); }


		//-----------------------------------------------------
		//��\��
		void Off ();

	private:
		void DebugOutWnd ( UP_TSTR up_tstr, VP_VxRct& vpVpRct );

	};

	using DBGO_WND = DebugOutGameWindow;


//�V���O���g���A�N�Z�X�p
#define DBGOUT_WND		DBGO_WND::Inst()
#define DBGOUT_WND_F	DBGO_WND::Inst()->DebugOutf



}	//namespace GAME



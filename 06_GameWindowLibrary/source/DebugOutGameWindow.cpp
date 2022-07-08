//=================================================================================================
//
// �Q�[����ʂւ̃f�o�b�O�e�L�X�g�\��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugOutGameWindow.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//--------------------------------------------------
	//�V���O���g���p�^�[��
	//static����
	DBGO_WND::P_DBG_WND		DBGO_WND::m_inst = nullptr;

	//�R���X�g���N�^
	DebugOutGameWindow::DebugOutGameWindow ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_texture[i] = nullptr;
			m_tstr[i] = _T("");
		}
	}
 
	//�f�X�g���N�^
	DebugOutGameWindow::~DebugOutGameWindow ()
	{
		Rele ();
	}
	
	//�C���X�^���X����
	void DebugOutGameWindow::Create ()
	{
		assert ( ! m_inst );		//���ɑ��݂��Ă�����assert
		m_inst = DBGO_WND::P_DBG_WND ( new DBGO_WND () );
	}
	//--------------------------------------------------


	//�Ǎ�
	void DebugOutGameWindow::Load ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_vertex[i].Load ();		//���_�o�b�t�@�̍쐬
			m_vertex[i].SetPos ( 0, 20.f * i );
		}
//		m_tstr.assign ( TEXT("DebugOutGameWindow::Init _  ()") );
//		GameText::instance()->MakeStrTexture ( m_tstr, m_texture, m_vertex );


//		tstring testStr = _T ( "Test String" );
//		m_testVx.Load ();
//		m_testVx.SetPos ( 100, 100 );
//		GameText::instance ()->MakeStrTexture ( testStr, m_testTx, m_testVx );
	}

	void DebugOutGameWindow::Rele ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}


//		m_testVx.Rele ();
	}

	void DebugOutGameWindow::Reset ( LPDIRECT3DDEVICE9 d3dDevice )
	{
		Rele ();
		Load ();
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			GameText::Inst()->MakeStrTexture ( m_tstr[i], m_texture[i], m_vertex[i] );
		}
	}

	void DebugOutGameWindow::Move ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_vertex[i].ApplyPos ();
			m_vertex[i].SetVertexBuffer ();
		}


//		m_testVx.Move ();
	}

	void DebugOutGameWindow::DrawVertex ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			//�����񂪋�Ȃ牽�����Ȃ��ŕԂ�
			if ( ! m_tstr[i].compare ( TEXT("") ) ) { continue; }

			//�S���_�Ƀe�N�X�`���`��
			m_vertex[i].DrawVertex ( m_texture[i] );
		}


//		m_testVx.DrawVertex ( nullptr );
	}


	//������ݒ�
	void DebugOutGameWindow::SetStr ( UINT index, LPCTSTR lpctstr )
	{
		//���݂̕�����Ɣ�r���ĈقȂ�ꍇ�V���Ƀe�N�X�`�����쐬
		if ( m_tstr[index].compare ( lpctstr ) )
		{
			m_tstr[index].assign ( lpctstr );
//			GameText::instance()->MakeStrTexture ( m_tstr[index], m_texture[index], m_vertex[index] );

			OutlineFont::Inst ()->SetParam ( 40, 1, 1 );
//			OutlineFont::Inst ()->SetFontFace ( _T ( "���C���I" ) );

			m_texture[index] = OutlineFont::Inst ()->Make ( m_tstr [ index ].c_str (), 0xffffffff, 0xffffffff );
			POINT size = OutlineFont::Inst ()->GetSize ();

			m_vertex [ index ].SetSize ( 1.f * size.x, 1.f * size.y );
			m_vertex [ index ].ApplyPos ();
		}
	}

	void DebugOutGameWindow::SetStr ( UINT index, tstring& tstr )
	{
		SetStr ( index, tstr.c_str () );
	}


	void DebugOutGameWindow::DebugOutf ( UINT index, LPCTSTR format, ... )
	{
		va_list args;	//�ϒ����X�g
		va_start ( args, format );	//������̐擪�|�C���^���Z�b�g

		//Unicode�i���C�h�����j�Ή��@_vsc w printf() / �}���`�o�C�g�����Ή� _vscprintf()
		int size = _vsctprintf ( format, args ) + 1;		//'\0'���Ō�ɂ����T�C�Y�𓾂�
		TCHAR* buf = new TCHAR[size];		//�o�b�t�@���m��
		//Unicode�i���C�h�����j�Ή��@vs w printf_s() / �}���`�o�C�g�����Ή� vswprintf_s()
		_vstprintf_s ( buf, size, format, args );	//�o�b�t�@�ɏ�������

		//�e�L�X�g�̐ݒ�
		SetStr ( index, buf );

		va_end ( args );
		delete[] buf;
	}

	void DebugOutGameWindow::Off ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}
	}


}	//namespace GAME


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

		for ( UINT i = 0; i < DebugVertexNum; ++ i )
		{
			m_vpVx.push_back ( make_shared < Vx_Rect > () );
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
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			GameText::Inst()->MakeStrTexture ( m_tstr[i], m_texture[i], m_vertex[i] );
		}
//		m_tstr.assign ( TEXT("DebugOutGameWindow::Init _  ()") );
//		GameText::instance()->MakeStrTexture ( m_tstr, m_texture, m_vertex );


		tstring testStr = _T ( "Test String" );
		m_testVx.Load ();
		m_testVx.SetPos ( 100, 400 );
		m_testVx.SetAllColor ( 0xffff0000 );
		GameText::Inst ()->MakeStrTexture ( testStr, m_testTx, m_testVx );


		UINT index = 0;
		float pos_x = 50;
		for ( P_VxRct pVx : m_vpVx )
		{
			pVx->Load ();
			pVx->SetPos ( pos_x, 130 );
			pos_x += 12;
			pVx->SetAllColor ( 0xffff00ffL | ++ index * 255 / DebugVertexNum );
		}
	}

	void DebugOutGameWindow::Rele ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}


		m_testVx.Rele ();
		for ( P_VxRct pVx : m_vpVx ) { pVx->Rele (); }
	}

	void DebugOutGameWindow::Reset ( D3DDEV d3dDevice )
	{
		Rele ();
		Load ();
	}

	void DebugOutGameWindow::Move ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_vertex[i].ApplyPos ();
			m_vertex[i].SetVertexBuffer ();
		}

//		m_testVx.SetPos ( VEC2 ( 500, 300 ) );
//		m_testVx.ApplyPos ();

		m_testVx.Move ();

		char ch = 32;
		for ( P_VxRct pVx : m_vpVx )
		{
#if 0
			VEC2 pos = GameText::Inst ()->GetChToPos ( ch ++ );
			USIZE ch = GameText::Inst ()->GetCharTxSize ();
			USIZE all = GameText::Inst ()->GetAsciiTxSize ();
			float x = pos.x / (float)all.w;
			float y = pos.y / (float)all.h;
			float u = ch.w  / (float)all.w;
			float v = ch.h  / (float)all.h;
			pVx->SetTxUVWH ( x, y, u, v );
			pVx->SetSize ( 1.f * ch.w, 1.f * ch.h );
#endif // 0
			pVx->Move (); 
		}
	}

	void DebugOutGameWindow::DrawVertex ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			//�����񂪋�Ȃ牽�����Ȃ��ŕԂ�
			if ( ! m_tstr[i].compare ( _T("") ) ) { continue; }

			//�S���_�Ƀe�N�X�`���`��
			m_vertex[i].DrawVertex ( m_texture[i] );
		}


//		m_testVx.DrawVertex ( m_testTx );

		for ( P_VxRct pVx : m_vpVx )
		{
			pVx->DrawVertex ( GameText::Inst()->GetAsciiTx () );
		}
	}


	//������ݒ�
	void DebugOutGameWindow::SetStr ( UINT index, LPCTSTR lpctstr )
	{
		//���݂̕�����Ɣ�r���ē����ꍇ�������Ȃ�
		if ( ! m_tstr [ index ].compare ( lpctstr ) ) { return; }

		//�V���Ƀe�N�X�`�����쐬
		m_tstr[index].assign ( lpctstr );
		GameText::Inst()->MakeStrTexture ( m_tstr[index], m_texture[index], m_vertex[index] );

#if 0
		OutlineFont::Inst ()->SetParam ( 40, 1, 1 );
//			OutlineFont::Inst ()->SetFontFace ( _T ( "���C���I" ) );

		m_texture[index] = OutlineFont::Inst ()->Make ( m_tstr [ index ].c_str (), 0xffffffff, 0xffffffff );
		POINT size = OutlineFont::Inst ()->GetSize ();

		m_vertex [ index ].SetSize ( 1.f * size.x, 1.f * size.y );
		m_vertex [ index ].ApplyPos ();
#endif // 0
	}

	void DebugOutGameWindow::SetStr ( UINT index, tstring& tstr )
	{
		SetStr ( index, tstr.c_str () );
	}
	void DebugOutGameWindow::SetStr ( UINT index, UP_TSTR pstr )
	{
		SetStr ( index, pstr.get () );
	}


	void DebugOutGameWindow::DebugOutf ( UINT index, LPCTSTR format, ... )
	{
		//������t�H�[�}�b�g
		va_list args;	//�ϒ����X�g
		va_start ( args, format );	//������̐擪�|�C���^���Z�b�g
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		//�e�L�X�g�̐ݒ�
		SetStr ( index, p.get () );
	}

	void DebugOutGameWindow::DebugOutWnd_Time ( LPCTSTR format, ... )
	{
		va_list args;
		va_start ( args, format );	//������̐擪�|�C���^���Z�b�g
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		UINT index = 0;
		LPTCH tch = p.get ();

		TCHAR t = *tch;
		UINT size = 0;
		while ( t != '\0' )
		{
			t = *(tch + (index++));
			++ size;
		}


		USIZE ch = GameText::Inst ()->GetCharTxSize ();
		USIZE all = GameText::Inst ()->GetAsciiTxSize ();
		float u = ch.w / (float)all.w;
		float v = ch.h / (float)all.h;

		index = 0;
		t = *tch;
		while ( t != '\0' && index < size )
		{
			UINT code = GameText::Inst()->GetCode ( tch + index );

			VEC2 pos = GameText::Inst ()->GetChToPos ( code );
			float x = pos.x / (float)all.w;
			float y = pos.y / (float)all.h;
			
			P_VxRct pVx = m_vpVx [ index ];
			pVx->SetTxUVWH ( x, y, u, v );
			pVx->SetSize ( 1.f * ch.w, 1.f * ch.h );
			
			++ index;
		}
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


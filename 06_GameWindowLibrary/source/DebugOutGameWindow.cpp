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
		: m_bTime ( true ), m_bFPS ( true )
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			m_texture[i] = nullptr;
			m_tstr[i] = _T("");
		}

		for ( UINT i = 0; i < DebugVertexNum; ++ i )
		{
			m_vpVxTime.push_back ( make_shared < Vx_Rect > () );
		}
		for ( UINT i = 0; i < DebugVertexNum; ++ i )
		{
			m_vpVxFPS.push_back ( make_shared < Vx_Rect > () );
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

		LoadVVx ( m_vpVxTime, VEC2 ( 0, 0 ) );
		LoadVVx ( m_vpVxFPS, VEC2 ( 300, 0 ) );
	}

	void DebugOutGameWindow::LoadVVx ( VP_VxRct& vpVxRct, VEC2 pos )
	{
		for ( P_VxRct pVx : vpVxRct )
		{
			pVx->Load ();
			pVx->SetPos ( pos.x, 0 );
			pos.x += 12;
			pVx->SetAllColor ( 0xffffffffL );
		}
	}

	void DebugOutGameWindow::Rele ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}

		for ( P_VxRct pVx : m_vpVxTime ) { pVx->Rele (); }
		for ( P_VxRct pVx : m_vpVxFPS ) { pVx->Rele (); }
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

		for ( P_VxRct pVx : m_vpVxTime ) { pVx->Move (); }
		for ( P_VxRct pVx : m_vpVxFPS ) { pVx->Move (); }
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


		//�Œ�\�� : �ғ�����[F]
		if ( m_bTime )
		{
			for ( P_VxRct pVx : m_vpVxTime )
			{
				pVx->DrawVertex ( GameText::Inst ()->GetAsciiTx () );
			}
		}
		//�Œ�\�� : FPS
		if ( m_bFPS )
		{
			for ( P_VxRct pVx : m_vpVxFPS )
			{
				pVx->DrawVertex ( GameText::Inst ()->GetAsciiTx () );
			}
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

	//-------------------------------------------------------------------------
	//�Œ�\�� : �ғ�����[F]
	void DebugOutGameWindow::DebugOutWnd_Time ( LPCTSTR format, ... )
	{
		va_list args;
		va_start ( args, format );	//������̐擪�|�C���^���Z�b�g
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		DebugOutWnd ( std::move ( p ), m_vpVxTime );
	}

	//�Œ�\�� : FPS
	void DebugOutGameWindow::DebugOutWnd_FPS ( LPCTSTR format, ... )
	{
		va_list args;
		va_start ( args, format );	//������̐擪�|�C���^���Z�b�g
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		DebugOutWnd ( std::move ( p ), m_vpVxFPS );
	}

	void DebugOutGameWindow::Off ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}
	}

	//������T�C�Y�̎擾
	UINT DebugOutGameWindow::Size ( LPCTSTR lpctstr ) const
	{
		UINT ret = 0;
		TCHAR t = *lpctstr;

		try
		{
			while ( t != '\0' )
			{
				t = *( lpctstr + ( ret ++ ) );
			}
		}
		catch ( ... )
		{
			return 0;
		}

		return ret;
	}


	void DebugOutGameWindow::DebugOutWnd ( UP_TSTR up_tstr, VP_VxRct& vpVpRct )
	{
		//�擪����̕�����̂Ƃ��������Ȃ�
		LPTCH tch = up_tstr.get ();
		if ( up_tstr [ 0 ] == '\0' ) { return; }

		//������T�C�Y�̎擾
		UINT old_size = vpVpRct.size ();
		UINT size = Size ( up_tstr.get () );
		if ( size < old_size )
		{
			vpVpRct.resize ( size );
		}
		else if ( old_size < size )
		{
			vpVpRct.resize ( size );
			for ( UINT i = size - old_size; i < size; ++ i )
			{
				vpVpRct [ i ] = make_shared < Vx_Rect > ();
				vpVpRct [ i ]->Load ();
			}

			float pos_x = 0.f;
			for ( P_VxRct pVx : vpVpRct )
			{
				pVx->SetPos ( pos_x, 0 );
				pos_x += 12;
				pVx->SetAllColor ( 0xffffffffL );
			}
		}

		//�e�N�X�`���T�C�Y�ƈʒu�̎擾
		USIZE ch = GameText::Inst ()->GetCharTxSize ();
		USIZE all = GameText::Inst ()->GetAsciiTxSize ();
		float u = ch.w / (float)all.w;
		float v = ch.h / (float)all.h;

		for ( UINT i = 0; i < size; ++ i )
		{
			UINT code = GameText::Inst ()->GetCode ( tch + i );
			VEC2 pos = GameText::Inst ()->GetChToPos ( code );
			float x = pos.x / (float)all.w;
			float y = pos.y / (float)all.h;

			P_VxRct pVx = vpVpRct [ i ];
			pVx->SetTxUVWH ( x, y, u, v );
			pVx->SetSize ( 1.f * ch.w, 1.f * ch.h );
		}
	}


}	//namespace GAME


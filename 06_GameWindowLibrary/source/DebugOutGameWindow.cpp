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

		m_frame.SetPos ( VEC2 ( 0, 0 ) );
		m_FPS.SetPos ( VEC2 ( 200, 0 ) );
		m_time.SetPos ( VEC2 ( 500, 0 ) );
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

		m_frame.Load ();
		m_FPS.Load ();
		m_time.Load ();
	}

	void DebugOutGameWindow::Rele ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}
		m_frame.Rele ();
		m_FPS.Rele ();
		m_time.Rele ();
	}

	void DebugOutGameWindow::Reset ( D3DDEV d3dDevice )
	{
		Rele ();
		Load ();
	}

	void DebugOutGameWindow::Move ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i ) { m_vertex [ i ].Move (); }
		m_frame.Move ();
		m_FPS.Move ();
		m_time.Move ();
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

		m_frame.Draw ();
		m_FPS.Draw ();
		m_time.Draw ();
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

		m_frame.SetStr ( std::move ( p ) );
	}

	//�Œ�\�� : FPS
	void DebugOutGameWindow::DebugOutWnd_FPS ( LPCTSTR format, ... )
	{
		va_list args;
		va_start ( args, format );	//������̐擪�|�C���^���Z�b�g
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		m_FPS.SetStr ( std::move ( p ) );
	}

	//�Œ�\�� : MoveTime[ms], DrawTime[ms]
	void DebugOutGameWindow::DebugOutWnd_Move_Draw ( LPCTSTR format, ... )
	{
		//�ϒ������ɂ�镶����t�H�[�}�b�g
		va_list args;
		va_start ( args, format );	//������̐擪�|�C���^���Z�b�g
		UP_TSTR p = Format::Printf_Args ( format, args );
		va_end ( args );

		m_time.SetStr ( std::move ( p ) );
	}

	//-------------------------------------------------------------------------
	void DebugOutGameWindow::Off ()
	{
		for ( UINT i = 0; i < DebugTextNum; ++i )
		{
			RELEASE ( m_texture[i] );
			m_vertex[i].Rele ();
		}
	}

	void DebugOutGameWindow::DebugOutWnd ( UP_TSTR up_tstr, VP_VxRct& vpVpRct )
	{
		//�擪����̕�����̂Ƃ��������Ȃ�
		LPTCH tch = up_tstr.get ();
		if ( up_tstr [ 0 ] == '\0' ) { return; }

		//������T�C�Y�̎擾
		UINT old_size = vpVpRct.size ();
		UINT size = STR_UTL::Size ( up_tstr.get () );
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



	//=====================================================
	//�Œ�\��
	ConstDebugOut::ConstDebugOut ()
		: m_valid ( T )
	{
		m_vx.SetAllZ ( 0 );
		m_vx.SetPos ( 600, 0 );
		m_vx.SetSize ( 200, 16 );
		m_vx.SetAllColor ( 0xff00ffffL );
	}

	ConstDebugOut::~ConstDebugOut ()
	{
		Rele ();
	}

	void ConstDebugOut::Load ()
	{
		m_vx.Load ();
	}

	void ConstDebugOut::Rele ()
	{
		m_vx.Rele ();
		m_tx->Release ();
	}

	void ConstDebugOut::Reset ()
	{
		Rele ();
		Load ();
	}

	void ConstDebugOut::Move ()
	{
		m_vx.Move ();
	}

	void ConstDebugOut::Draw ()
	{
		if ( ! m_valid ) { return; }

		m_vx.DrawVertex ( m_tx );
	}

	void ConstDebugOut::SetStr ( UP_TSTR upctstr )
	{
		tstring str ( upctstr.get () );
		GameText::Inst ()->MakeStrTexture ( str, m_tx, m_vx );
	}

	void ConstDebugOut::SetPos ( VEC2 v )
	{
		m_vx.SetPos ( v );
	}


}	//namespace GAME


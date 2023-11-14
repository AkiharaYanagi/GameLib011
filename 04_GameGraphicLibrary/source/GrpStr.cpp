//=================================================================================================
//
// GrpEf �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GrpStr.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------
	GrpStr::GrpStr ()
	{
		m_tx = std::make_shared < TxStr > ();
	}

	GrpStr::~GrpStr ()
	{
	}

	void GrpStr::Load ()
	{
		m_tx->Load ();

#if 0
		D3DSURFACE_DESC dc;
		m_tx->GetTexture ()->GetLevelDesc ( 0, & dc );

		P_PrmRect rect = std::make_shared < PrmRect > ();
		rect->SetSize ( 1.f * dc.Width, 1.f * dc.Height );
		rect->SetPos ( GetPos () );
		rect->SetZ ( Z_BG );
		rect->SetAllColor ( 0x80ff8080 );
		rect->Load ();
		GRPLST_INSERT ( rect );
#endif // 0
	}

	void GrpStr::Rele ()
	{
		m_tx->Rele ();
	}

	void GrpStr::Reset ()
	{
		m_tx->Reset ();
	}

	void GrpStr::SetStr ( LPCTSTR str )
	{
		//�����񂩂�e�N�X�`�����쐬
		m_tx->SetStr ( str );

		//�O���t�B�b�N�Ɏw��
		GrpApTx::SetpTexture ( m_tx );
	}

	void GrpStr::SetStrF ( LPCTSTR str, ... )
	{
		va_list args;	//�ϒ����X�g
		va_start ( args, str );	//������̐擪�|�C���^���Z�b�g
		UP_TSTR buf = Format::Printf_Args ( str, args );
		va_end ( args );	//�ϒ����X�g�I��

		//�����񂩂�e�N�X�`�����쐬
		m_tx->SetStr ( buf.get() );

		//�O���t�B�b�N�Ɏw��
		GrpApTx::SetpTexture ( m_tx );
	}

	void GrpStr::SetFontParam ( int fontSize, int penSize, int quolity )
	{
		m_tx->SetParam ( fontSize, penSize, quolity );
	}

	void GrpStr::SetFontFace ( LPCTSTR fontname )
	{
		m_tx->SetFontFace ( fontname );
	}

	void GrpStr::SetFontColor ( DWORD fill, DWORD edge )
	{
		m_tx->SetColor ( fill, edge );
	}



}	//namespace GAME


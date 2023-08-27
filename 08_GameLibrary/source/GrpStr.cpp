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
	TxStr::GameTextureFromString ()
	{
	}

	TxStr::~GameTextureFromString ()
	{
	}

	void TxStr::Load ()
	{
		//�����񂩂�e�N�X�`�����쐬
		TX tx = OutlineFont::Inst ()->Make ( m_str.c_str (), 0x00ffffff, 0xffffffff );
		TxBs::SetTexture ( tx );
	}

	void TxStr::Rele ()
	{
	}

	void TxStr::Reset ()
	{
		Rele ();
		Load ();
	}

	void TxStr::SetStr ( LPCTSTR str )
	{
		m_str.assign ( str );
		Load ();
	}


	//-------------------------------------
	GrpStr::GrpStr ()
	{
	}

	GrpStr::~GrpStr ()
	{
	}

	void GrpStr::SetStr ( LPCTSTR str )
	{
		//�����񂩂�e�N�X�`�����쐬
		P_TxStr txstr = make_shared < TxStr > ();
		txstr->SetStr ( str );

		//�O���t�B�b�N�Ɏw��
		GrpApTx::SetpTexture ( txstr );
	}

}	//namespace GAME


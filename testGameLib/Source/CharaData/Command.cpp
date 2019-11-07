//=================================================================================================
//
// Command �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Command::Command () :
		m_name (_T("command name")), m_limitTime ( 0 )
	{
	}

	Command::~Command ()
	{
		m_vecGameKey.clear ();
	}

	bool Command::Compare ( const V_GAME_KEY & vecGameKey, bool dirRight )
	{
		//�L�[�z�񒷂����A�R�}���h��t���Ԃ̒Z�����Ō���
		UINT len = vecGameKey.size ();
		UINT frame = ( m_limitTime < len ) ? m_limitTime : len;
		
		//�������͐��i�J�E���g�_�E���j(�����-1�܂ŗp����)
		int comp = m_vecGameKey.size() - 1;

		//�t���[����k���Č���
		for ( UINT i = 0; i < frame; ++i )
		{
			if ( vecGameKey[i].Compare( m_vecGameKey[comp], dirRight ) )
			{
				--comp;
			}
			if ( 0 > comp ) { return true; }
		}
		return false;
	}


}	//namespace GAME

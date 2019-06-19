//=================================================================================================
//
// �ݒ�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "SettingFile.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	SettingFile::P_SettingFile	SettingFile::m_inst;

	SettingFile::SettingFile ()
	{
		try
		{
			TCHAR path [ MAX_PATH ];
			::GetCurrentDirectory ( MAX_PATH, path );
			TRACE_F ( path );

			//���̓X�g���[���𐶐�
			ifstream ifstrm( _T("Setting.dat"), ios::in );
			
			//������Ȃ��Ƃ��f�t�H���g�̒l��ݒ肵�ďI��
			if ( ! ifstrm )
			{
				SetDefault ();
			}
			
			//�Ǎ�
			ifstrm.read ( (char*)& m_bFullscreen, sizeof(bool) );
			UINT size = sizeof ( UINT );
			ifstrm.read ( (char*)& m_window_x, sizeof ( UINT ) );
			ifstrm.read ( (char*)& m_window_y, sizeof ( UINT ) );

			//�I��
			ifstrm.close ();
		}
		catch (...)
		{
		}
	}

	SettingFile::~SettingFile ()
	{
	}
	
	void SettingFile::SetDefault ()
	{
		m_bFullscreen = false;
		m_window_x = 640;
		m_window_x = 480;
	}


}	//namespace GAME


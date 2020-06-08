//=================================================================================================
//
// �A�v���P�[�V�����ݒ�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "AppSettingFile.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	AppSettingFile::_UP_StgFl	AppSettingFile::m_inst;

	AppSettingFile::AppSettingFile ()
	{
		try
		{
			TCHAR path [ MAX_PATH ];
			::GetCurrentDirectory ( MAX_PATH, path );
			TRACE_F ( path );
			TRACE_F ( _T("\n") );

			//���̓X�g���[���𐶐�
			ifstream ifstrm( _T("AppSetting.dat"), ios::in );
			
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
			ifstrm.read ( (char*)& m_input1pPlayer, sizeof(bool) );
			ifstrm.read ( (char*)& m_input2pPlayer, sizeof(bool) );

			//�I��
			ifstrm.close ();
		}
		catch (...)
		{
		}
	}

	AppSettingFile::~AppSettingFile ()
	{
	}
	
	void AppSettingFile::SetDefault ()
	{
		m_bFullscreen = false;
		m_window_x = 1280;
		m_window_y = 960;
		m_input1pPlayer = true;
		m_input2pPlayer = true;
	}


}	//namespace GAME


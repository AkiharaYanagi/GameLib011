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
	}

	AppSettingFile::~AppSettingFile ()
	{
	}
	
	void AppSettingFile::Load ()
	{
		try
		{
			TCHAR path [ MAX_PATH ];
			::GetCurrentDirectory ( MAX_PATH, path );
			TRACE_F ( path );
			TRACE_F ( _T("\n") );

			//���̓X�g���[���𐶐�
			ifstream ifstrm( _T("AppSettings.dat"), ios::in );
			
			//������Ȃ��Ƃ��f�t�H���g�̒l��ݒ肵�ďI��
			if ( ! ifstrm )
			{
				SetDefault ();
				return;
			}
			
			//�Ǎ�
			ifstrm.read ( (char*)& m_bFullscreen, sizeof(bool) );
			ifstrm.read ( (char*)& m_window_w, sizeof ( int ) );
			ifstrm.read ( (char*)& m_window_h, sizeof ( int ) );

			int temp = 0;
			ifstrm.read ( (char*)& temp, sizeof ( int ) );
			m_startPos = ( WINDOW_START_POS )temp;
			ifstrm.read ( (char*)& m_displayNum, sizeof ( int ) );

#if 0
			ifstrm.read ( (char*)& m_input1pPlayer, sizeof(bool) );
			ifstrm.read ( (char*)& m_input2pPlayer, sizeof(bool) );
#endif // 0

			//�I��
			ifstrm.close ();
		}
		catch (...)
		{
			TRACE_F ( _T( "catch(...)\n" ) );
			SetDefault ();
		}
	}

	void AppSettingFile::SetDefault ()
	{
		m_bFullscreen = false;
		m_window_w = DFL_WND_W;
		m_window_h = DFL_WND_H;
		m_startPos = START_POS_CURSOR;
		m_displayNum = 0;
#if 0
		m_input1pPlayer = true;
		m_input2pPlayer = true;
#endif // 0
	}


}	//namespace GAME


//=================================================================================================
//
// SoundArchiver �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "SoundArchiver.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//@info �ǂݍ��ރf�B���N�g����SE��BGM�ɕ����ASE�̓o�b�t�@�𕡐��ABGM�̓o�b�t�@��P��Ŏ���
	//ID��SE�CBGM���ʂŊė�, �Ăяo�������ID�w��͕�enum�ōs��

	//------------------------------------------
	//	�萔
	//------------------------------------------
	//�쐬����T�E���h�A�[�J�C�u�t�@�C����
	LPCTSTR SoundArchiver::m_archiveFileName = _T("sound.dat");


	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
	LPCTSTR SoundArchiver::m_archiveDirName = _T ( "Sound/" );

	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������
	LPCTSTR SoundArchiver::m_searchCondition = _T ( "Sound/*.*" );


	//SE �A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
	LPCTSTR SoundArchiver::m_archiveDirName_SE = _T ( "SE/" );

	//SE �A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������
	LPCTSTR SoundArchiver::m_searchCondition_SE = _T ( "SE/*.*" );

	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	SoundArchiver::P_SoundArchiver		SoundArchiver::m_inst;

	//------------------------------------------
	//�R���X�g���N�^
	SoundArchiver::SoundArchiver ()
//		: m_hFile ( nullptr ) //, m_count ( 0 )
		: m_nBGM ( 0 ), m_nSE ( 0 )
	{
	}

	//�f�X�g���N�^
	SoundArchiver::~SoundArchiver ()
	{
	}

	//�쐬
	void SoundArchiver::Make ()
	{
		//DBGOUT_FL_F ( _T ("SoundArchiver::Make()\n") );

		//�J�����g�f�B���N�g���̎擾
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//�o�C�i���ŏ��o�p�t�@�C�����J��
		HANDLE hWriteFile = CreateFile ( m_archiveFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );


		//�t�@�C�������
		m_nBGM = CountFileNum ( m_searchCondition );
		m_nSE = CountFileNum ( m_searchCondition_SE );

		//�e�t�@�C���������o
		::WriteFile ( hWriteFile, & m_nBGM, sizeof ( DWORD ), nullptr, nullptr );
		::WriteFile ( hWriteFile, & m_nSE, sizeof ( DWORD ), nullptr, nullptr );



#if 0
		//�t�@�C����
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( m_searchCondition, &fileData );	//�f�B���N�g���w��("sound/*.*")

		//���𐔂��グ
		while ( T )
		{
			//���t�@�C�����擾
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//�f�B���N�g���͔�΂�
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͔�΂�
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				++ m_count;
			}
			//���t�@�C�����擾�ł��Ȃ������Ƃ�
			else
			{
				break;
			}
		}
		FindClose ( hFileList );
#endif // 0

#if 0
		//�t�@�C����
//		m_count = CountFileNum ( m_searchCondition );
		UINT count = CountFileNum ( m_searchCondition );

		//�t�@�C�������L�^
		::WriteFile ( hWriteFile, & count, sizeof ( DWORD ), nullptr, nullptr );


		//�ė�
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( m_searchCondition, &fileData );	//�f�B���N�g���w��("sound/*.*")

		//���o
		while ( T )
		{
			//���t�@�C�����擾
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//�f�B���N�g���͔�΂�
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͔�΂�
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				//DBGOUT_FL_F ( _T ( "Filename=\"%s\"\n" ), fileData.cFileName );

				//�t�@�C���T�C�Y
				DWORD fileSize = fileData.nFileSizeLow;	//4Gbyte�����̂�
				DWORD numberOfBytesWritten = 0;

				::WriteFile ( hWriteFile, &fileSize, sizeof ( DWORD ), &numberOfBytesWritten, nullptr );

				//�f�B���N�g���w��
				tstring filename ( m_archiveDirName );
				filename.append ( fileData.cFileName );

				//�t�@�C���Ǎ�
				HANDLE hReadFile = CreateFile ( filename.c_str(), GENERIC_READ, 0, nullptr, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
				
				std::unique_ptr < BYTE[] > buf = std::make_unique < BYTE[] > ( fileSize );
				DWORD numberOfByteRead = 0;
				::ReadFile ( hReadFile, buf.get(), fileSize, &numberOfByteRead, nullptr );

				::CloseHandle ( hReadFile );

				//�A�[�J�C�u�ɃT�C�Y�����o
				::WriteFile ( hWriteFile, buf.get(), fileSize, &numberOfBytesWritten, nullptr );
				
//				++m_count;
			}
			//���t�@�C�����擾�ł��Ȃ������Ƃ�
			else 
			{
				break;
			}
		}
#endif // 0

		///BGM
		_Make ( hWriteFile, m_archiveDirName, m_searchCondition );

		//SE
		_Make ( hWriteFile, m_archiveDirName_SE, m_searchCondition_SE );


		//�I��
		CloseHandle ( hWriteFile );
	}

	void SoundArchiver::_Make ( HANDLE hWriteFile, LPCTSTR dirname, LPCTSTR condition )
	{
		//�ė�
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( condition, &fileData );	//�f�B���N�g���w��("sound/*.*")

		//���o
		while ( T )
		{
			//���t�@�C�����擾
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//�f�B���N�g���͔�΂�
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͔�΂�
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				//DBGOUT_FL_F ( _T ( "Filename=\"%s\"\n" ), fileData.cFileName );

				//�t�@�C���T�C�Y����
				DWORD fileSize = fileData.nFileSizeLow;	//4Gbyte�����̂�
				DWORD numberOfBytesWritten = 0;
				::WriteFile ( hWriteFile, &fileSize, sizeof ( DWORD ), &numberOfBytesWritten, nullptr );

				//�o�b�t�@�Ƀt�@�C���f�[�^�Ǎ�
				tstring filename ( dirname );			
				filename.append ( fileData.cFileName );	//�t�@�C���p�X�쐬
				HANDLE hReadFile = CreateFile ( filename.c_str(), GENERIC_READ, 0, nullptr, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
				
				std::unique_ptr < BYTE[] > buf = std::make_unique < BYTE[] > ( fileSize );
				DWORD numberOfByteRead = 0;
				::ReadFile ( hReadFile, buf.get(), fileSize, &numberOfByteRead, nullptr );

				::CloseHandle ( hReadFile );

				//�A�[�J�C�u�ɃT�C�Y�����o
				::WriteFile ( hWriteFile, buf.get(), fileSize, &numberOfBytesWritten, nullptr );
			}
			//���t�@�C�����擾�ł��Ȃ������Ƃ�
			else 
			{
				break;
			}
		}
		//�I��
		FindClose ( hFileList );
	}


	//�����̃t�@�C�������グ
	UINT SoundArchiver::CountFileNum ( LPCTSTR condition )
	{
		UINT ret = 0;

		//�t�@�C����( OpenHandle )
		WIN32_FIND_DATA		fileData;
		//�f�B���N�g���w��("sound/*.*")
		HANDLE hFileList = ::FindFirstFile ( condition, & fileData );

		//���𐔂��グ
		while ( T )
		{
			//���t�@�C�����擾
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//�f�B���N�g���͔�΂�
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͔�΂�
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				++ ret;
			}
			//���t�@�C�����擾�ł��Ȃ������Ƃ�
			else
			{
				break;
			}
		}
		::FindClose ( hFileList );

		return ret;
	}


	//�J
	void SoundArchiver::Open ()
	{
		//DBGOUT_FL_F ( _T ( "�T�E���h�A�[�J�C�o�Ǎ��J�n\n" ) );
		//�t�@�C���Ǎ�
		HANDLE hFile = CreateFile ( m_archiveFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, nullptr );

//		TCHAR cur [ 255 ] = _T("filepath");
//		::GetCurrentDirectory ( 255, cur );

		//�t�@�C�������v��Ǎ�
		::ReadFile ( hFile, & m_nBGM, sizeof ( DWORD ), nullptr, nullptr );
		::ReadFile ( hFile, & m_nSE, sizeof ( DWORD ), nullptr, nullptr );
		UINT count = m_nBGM + m_nSE;

		//�e�t�@�C���Ǎ�
		//DBGOUT_FL_F ( _T ( "count = %d\n" ), m_count );
		for ( UINT i = 0; i < count; ++i )
		{
			DWORD numberOfByteRead = 0;
			DWORD fileSize = 0;
			::ReadFile ( hFile, &fileSize, sizeof ( DWORD ), &numberOfByteRead, nullptr );
			std::unique_ptr < BYTE [] > buf = std::make_unique < BYTE [] > ( fileSize );
			::ReadFile ( hFile, buf.get(), fileSize, &numberOfByteRead, nullptr );
			
			//�T�E���h�o�b�t�@���쐬 (SE�͕����Đ��̂��߃o�b�t�@�����w��)
			//BGM
			if ( i < m_nBGM )
			{
				DxSound::instance ()->LoadWaveFromMemEx ( 1, (HPSTR)buf.get(), fileSize, m_volume );
			}
			//SE
			else
			{
				DxSound::instance ()->LoadWaveFromMemEx ( 8, (HPSTR)buf.get(), fileSize, m_volume );
			}
		}

		//����
		CloseHandle ( hFile );
	}

	//------------------------------------------------------------------
	//�Đ�
	void SoundArchiver::Play_BGM ( UINT BGM_ID )
	{
		DxSound::instance()->Play ( BGM_ID );
	}

	//���[�v�Đ�
	void SoundArchiver::Play_Loop_BGM ( UINT BGM_ID )
	{
		DxSound::instance()->PlayLoop ( BGM_ID );
	}

	//��~
	void SoundArchiver::Stop_BGM ( UINT BGM_ID )
	{
		DxSound::instance()->Stop ( BGM_ID );
	}

	//�Đ�
	void SoundArchiver::Play_SE ( UINT SE_ID )
	{
		//@info �����[�X���[�h����Make()��ʂ�Ȃ����߁Am_nBGM�̓t�@�C������ǂݍ���
		//BGM�̐������I�t�Z�b�g���Ďw��
		DxSound::instance()->Play ( m_nBGM + SE_ID );
	}



}	//namespace GAME


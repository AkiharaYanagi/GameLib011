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

	//------------------------------------------
	//	�萔
	//------------------------------------------
	//�A�[�J�C�u�t�@�C����
	const TCHAR SoundArchiver::m_archiveFileName[] = TEXT("sound.dat");

	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
	const TCHAR SoundArchiver::m_archiveDirName[] = TEXT("sound/");

	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������
	const TCHAR SoundArchiver::m_searchCondition[] = TEXT("sound/*.*");

	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	SoundArchiver::P_SoundArchiver		SoundArchiver::m_inst;

	//------------------------------------------
	//�R���X�g���N�^
	SoundArchiver::SoundArchiver () : m_hFile ( nullptr ), m_count ( 0 )
	{
	}

	//�f�X�g���N�^
	SoundArchiver::~SoundArchiver ()
	{
	}

	//�쐬
	void SoundArchiver::Make ()
	{
		//�J�����g�f�B���N�g���̎擾
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//�o�C�i���ŏ��o�p�t�@�C�����J��
		HANDLE hWriteFile = CreateFile ( m_archiveFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );

		//�t�@�C����
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( m_searchCondition, &fileData );	//�f�B���N�g���w��("sound/*.*")

		while ( 1 )
		{
			//���t�@�C�����擾
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//�f�B���N�g���͔�΂�
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͔�΂�
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				//�t�@�C���T�C�Y
				DWORD fileSize = fileData.nFileSizeLow;	//4Gbyte�����̂�
				DWORD numberOfBytesWritten = 0;

				::WriteFile ( hWriteFile, &fileSize, sizeof ( DWORD ), &numberOfBytesWritten, nullptr );

				//�f�B���N�g���w��
				LPTSTR filename = new TCHAR [ sizeof ( m_archiveDirName ) + sizeof ( fileData.cFileName ) ];
				::lstrcpy ( filename, m_archiveDirName );
				::lstrcat ( filename, fileData.cFileName );

				//�t�@�C���Ǎ�
				HANDLE hReadFile = CreateFile ( filename, GENERIC_READ, 0, nullptr, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
				
				BYTE* buf = new BYTE [ fileSize ];
				DWORD numberOfByteRead = 0;
				::ReadFile ( hReadFile, buf, fileSize, &numberOfByteRead, nullptr );

				::CloseHandle ( hReadFile );

				//�t�@�C���ɃT�C�Y�����o
				::WriteFile ( hWriteFile, buf, fileSize, &numberOfBytesWritten, nullptr );
				
				delete[] buf;
				delete[] filename;
				
				++m_count;
			}
			//���t�@�C�����擾�ł��Ȃ������Ƃ�
			else 
			{
				break;
			}
		}

		//�I��
		FindClose ( hFileList );
		CloseHandle ( hWriteFile );
	}

	//�J
	void SoundArchiver::Open ()
	{
		//�t�@�C���Ǎ�
		m_hFile = CreateFile ( m_archiveFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, nullptr );

		for ( UINT i = 0; i < m_count; ++i )
		{
			DWORD numberOfByteRead = 0;
			DWORD fileSize = 0;
			::ReadFile ( m_hFile, &fileSize, sizeof ( DWORD ), &numberOfByteRead, nullptr );
			BYTE* buf = new BYTE [ fileSize ];
			::ReadFile ( m_hFile, buf, fileSize, &numberOfByteRead, nullptr );

			DxSound::instance ()->LoadWaveFromMem_Renew ( (HPSTR)buf, fileSize );

			delete[] buf;
		}
	}

	//��
	void SoundArchiver::Close ()
	{
		if ( m_hFile ) { CloseHandle ( m_hFile ); m_hFile = nullptr; }
	}

	//�Đ�
	void SoundArchiver::Play ( UINT id )
	{
		DxSound::instance()->Play_Renew ( id );
	}

	//���[�v�Đ�
	void SoundArchiver::PlayLoop ( UINT id )
	{
		DxSound::instance()->PlayLoop ( id );
	}

	//��~
	void SoundArchiver::Stop ( UINT id )
	{
		DxSound::instance()->Stop ( id );
	}



}	//namespace GAME


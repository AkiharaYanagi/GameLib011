//=================================================================================================
//
// �t�@�C���A�[�J�C�o
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���@�C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Archiver.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//------------------------------------------
	//	�萔
	//------------------------------------------
	//�A�[�J�C�u�t�@�C����
	const TCHAR Archiver::m_archiveFileName[] = TEXT("archive.dat");

	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
	const TCHAR Archiver::m_archiveDirName[] = TEXT("archive/");

	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������
	const TCHAR Archiver::m_searchCondition[] = TEXT("archive/*.*");

	//�t�@�C���}�b�s���O�̖��O
	const TCHAR Archiver::m_mapName[] = TEXT("mapName");

	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	Archiver::P_Archiver	Archiver::m_inst;

	//------------------------------------------

	//�R���X�g���N�^
	Archiver::Archiver ()
		: m_hFile ( nullptr ), m_archiveHeader ( nullptr ), m_hMap ( nullptr )
		, m_pFile ( nullptr ), m_fileNum ( 0 )
	{
	}

	//�f�X�g���N�^
	Archiver::~Archiver ()
	{
		Close ();
		if ( m_archiveHeader ) { delete[] m_archiveHeader; m_archiveHeader = nullptr; }
	}

	//�A�[�J�C�u�t�@�C���쐬
	void Archiver::Make ()
	{
		WIN32_FIND_DATA fileData;

		DWORD fileNum = 0;	//�t�@�C����
		DWORD fileSize = 0;		//�e�t�@�C���T�C�Y
		DWORD fileTotalSize = 0;	//���t�@�C���T�C�Y

		//�J�����g�f�B���N�g���̎擾
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//�o�C�i���ŏ��o�p�t�@�C�����J��
		HANDLE hWriteFile = CreateFile ( m_archiveFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );

		//-------------------------------------------------------------------------
		//�w�b�_�̍쐬
		//-------------------------------------------------------------------------
		//���̎擾
		HANDLE hFile = ::FindFirstFile ( m_searchCondition, &fileData );
		while ( true )
		{
			//���̃t�@�C�����擾
			if ( FindNextFile ( hFile, &fileData ) )
			{
				//�f�B���N�g���͂Ƃ΂�(../���̃f�B���N�g���Ȃ�)�_�����Z�Ń`�F�b�N����
//				if ( fileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͂Ƃ΂�
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }
				
				TCHAR fileName[MAX_PATH];		//�t�@�C����
				_tcscpy_s ( fileName, TEXT("archive/") );
				_tcscat_s ( fileName, fileData.cFileName );
				fileSize = fileData.nFileSizeLow;	//4Gbyte�T�C�Y�ȏ�͈���Ȃ�
				
#if	1
				tostringstream toss;
				toss << fileName << TEXT(", �I�t�Z�b�g: ") << fileTotalSize << TEXT(", �t�@�C���T�C�Y: ") << fileSize << std::endl;
//				OutputDebugString ( toss.str().c_str () );
#endif	//0
				//���̃J�E���g
				++fileNum;
			}
			else	//���̃t�@�C�����擾�ł��Ȃ������Ƃ�
			{
				if ( GetLastError () == ERROR_NO_MORE_FILES ) {}	//�񋓏I��
				else {}		//�G���[�I��
				break;
			}
		}
		FindClose ( hFile );

		DWORD numberOfBytesWritten = 0;
		WriteFile ( hWriteFile, &fileNum, sizeof(DWORD), &numberOfBytesWritten, nullptr );

		tostringstream tossDebug;
		tossDebug << TEXT("�A�[�J�C�u�@�t�@�C���� = ") << fileNum << std::endl;
//		OutputDebugString ( tossDebug.str().c_str () );


		//�t�@�C�����A�I�t�Z�b�g�A�t�@�C���T�C�Y���擾
		hFile = FindFirstFile ( m_searchCondition, &fileData );
		while ( 1 )
		{
			//���̃t�@�C�����擾
			if ( FindNextFile ( hFile, &fileData ) )
			{
				//�f�B���N�g���͂Ƃ΂�
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
					tstring str ( fileData.cFileName );
					tostringstream toss;
					toss << TEXT("�f�B���N�g��: ") << str << TEXT(", �t�@�C���T�C�Y: ") << fileData.nFileSizeLow << std::endl;
//					OutputDebugString ( toss.str().c_str () );
					continue; 
				}

				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͂Ƃ΂�
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM )
				{
					tstring str ( fileData.cFileName );
					tostringstream toss;
					toss << TEXT("�V�X�e���t�@�C��: ") << str << TEXT(", �t�@�C���T�C�Y: ") << fileData.nFileSizeLow << std::endl;
//					OutputDebugString ( toss.str().c_str () );
					continue; 
				}

				TCHAR fileName[MAX_PATH];		//�t�@�C����
				_tcscpy_s ( fileName, TEXT("archive/") );
				_tcscat_s ( fileName, fileData.cFileName );
				fileSize = fileData.nFileSizeLow;	//4Gbyte�T�C�Y�ȏ�͈���Ȃ�
				
#if	1
				tostringstream toss;
				toss << fileName << TEXT(", �I�t�Z�b�g: ") << fileTotalSize << TEXT(", �t�@�C���T�C�Y: ") << fileSize << std::endl;
//				OutputDebugString ( toss.str().c_str () );
#endif	//0

				DWORD numberOfBytesWritten = 0;
				WriteFile ( hWriteFile, fileName, sizeof(fileName), &numberOfBytesWritten, nullptr );
				WriteFile ( hWriteFile, &fileTotalSize, sizeof(DWORD), &numberOfBytesWritten, nullptr );
				WriteFile ( hWriteFile, &fileSize, sizeof(DWORD), &numberOfBytesWritten, nullptr );

				//���̃I�t�Z�b�g�ʒu
				fileTotalSize += fileSize;
			}
			else	//���̃t�@�C�����擾�ł��Ȃ������Ƃ�
			{
				if ( GetLastError () == ERROR_NO_MORE_FILES ) {}	//�񋓏I��
				else {}		//�G���[�I��
				break;
			}
		}
		FindClose ( hFile );


		//-------------------------------------------------------------------------
		//���f�[�^���o
		//-------------------------------------------------------------------------
		hFile = FindFirstFile ( m_searchCondition, &fileData );
		while ( 1 )
		{
			//���̃t�@�C�����擾
			if ( FindNextFile ( hFile, &fileData ) )
			{
				//�f�B���N�g���͂Ƃ΂�
//				if ( fileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͂Ƃ΂�
				if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }

				fileSize = fileData.nFileSizeLow;	//4Gbyte�T�C�Y�ȏ�͈���Ȃ�
				
#if	0
				TCHAR fileName[MAX_PATH];		//�t�@�C����
				_tcscpy_s ( fileName, TEXT("archive/") );
				_tcscat_s ( fileName, fileData.cFileName );
				HANDLE hReadFile = CreateFile ( fileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
#endif	//0
				tstring fileName ( m_archiveDirName );
				fileName.append ( fileData.cFileName );

				HANDLE hReadFile = CreateFile ( fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );

				//�t�@�C���n���h������T�C�Y���Ǎ�
				BYTE* buf = new BYTE [ fileSize ];
				DWORD numberOfBytesRead = 0;
				ReadFile ( hReadFile, buf, fileSize, &numberOfBytesRead, nullptr );

				//�t�@�C���ɃT�C�Y�����o
				DWORD numberOfBytesWritten = 0;
				WriteFile ( hWriteFile, buf, fileSize, &numberOfBytesWritten, nullptr );
				delete[] buf;

				CloseHandle ( hReadFile );

#if	0
				tostringstream toss0;
				toss0 << "read = " << numberOfBytesRead << ", write = " << numberOfBytesWritten << std::endl;
				OutputDebugString ( toss0.str().c_str () );
#endif	//0
			}
			else	//���̃t�@�C�����擾�ł��Ȃ������Ƃ�
			{
				if ( GetLastError () == ERROR_NO_MORE_FILES ) {}	//�񋓏I��
				else {}		//�G���[�I��
				break;
			}
		}
		FindClose ( hFile );

		CloseHandle ( hWriteFile );
	}


	//�A�[�J�C�u�t�@�C���Ǎ�
	void Archiver::Open ()
	{
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		m_hFile = ::CreateFile ( m_archiveFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD erorr = GetLastError();

		//�t�@�C�����𓾂�
		DWORD dwFileNum = 0;
		DWORD numberOfBytesRead = 0;
		bool bRet = ::ReadFile ( m_hFile, &dwFileNum, sizeof ( DWORD ), &numberOfBytesRead, nullptr );

		//�w�b�_����������
		if ( m_archiveHeader ) { return; }
		m_archiveHeader = new ARCHIVE_HEADER_SEARCH [ dwFileNum ];

		for ( DWORD i = 0; i < dwFileNum; ++i )
		{
			ARCHIVE_HEADER temp;
			ReadFile ( m_hFile, &temp, sizeof ( ARCHIVE_HEADER ), &numberOfBytesRead, nullptr );
			m_archiveHeader[i].fileName.assign ( temp.fileName );
			m_archiveHeader[i].align.offset = temp.align.offset;
			m_archiveHeader[i].align.fileSize = temp.align.fileSize;

			m_map.insert ( ARCHIVE_MAP::value_type ( m_archiveHeader[i].fileName, &m_archiveHeader[i].align ) );
		}

		m_fileNum = dwFileNum;

		//�t�@�C���}�b�s���O
		//
		// �� ���O��t����ƕ����N�����ɓ����̃}�b�s���O�ŃA�N�Z�X�ᔽ�ɂȂ�̂Ŗ����ɂ���
		//
//		m_hMap = CreateFileMapping ( m_hFile, nullptr, PAGE_READONLY, 0, 0, m_mapName );
		m_hMap = CreateFileMapping ( m_hFile, nullptr, PAGE_READONLY, 0, 0, nullptr );
		if ( m_hMap == nullptr )
		{
			////DebugOutTrace::instance()->DebugOutf( TEXT("�t�@�C���}�b�s���O�Ɏ��s") );
			return;
		}
		m_pFile = MapViewOfFile ( m_hMap, FILE_MAP_READ, 0, 0, 0 );
	}


	//�A�[�J�C�u�t�@�C����
	void Archiver::Close ()
	{
		if ( m_hMap ) { CloseHandle ( m_hMap ); m_hMap = nullptr; }
		if ( m_hFile ) { CloseHandle ( m_hFile ); m_hFile = nullptr; }
	}



	//���̃t�@�C��������A�[�J�C�u���̃t�@�C���|�C���^�𓾂�
	ARCHIVE_FILE_USE Archiver::GetFilePointer ( LPCTSTR fileName ) 
	{
		ARCHIVE_FILE_USE ret = { nullptr, 0 };
//		if ( m_fileBuf ) { return ret; }
		
		//����
		tstring str ( m_archiveDirName );
		str.append ( fileName );
		if ( m_map.find ( str ) == m_map.end() ) 
		{
			////DebugOutTrace::instance()->DebugOutf ( TEXT("%s, �A�[�J�C�u�̒��ɑΏۂ̃t�@�C����������܂���ł���\n"), fileName );
			return ret; 
		}

		//map����|�C���^�z�u�����擾
		ARCHIVE_ALIGN* align = m_map [ str ];

		//�f�[�^�J�n�ʒu
		DWORD startData = sizeof ( DWORD ) + sizeof ( ARCHIVE_HEADER ) * m_fileNum;

		ret.filePointer = (LPBYTE)m_pFile + startData + align->offset;
		ret.fileSize = align->fileSize;

		return ret;

#if	0
		m_fileBuf = new BYTE [ align->fileSize ];

		SetFilePointer ( m_hFile, startData + align->offset, nullptr, FILE_BEGIN );
		DWORD numberOfBytesRead = 0;
		ReadFile ( m_hFile, m_fileBuf, align->fileSize, &numberOfBytesRead, nullptr );

		ret.filePointer = m_fileBuf;
		ret.fileSize = align->fileSize;
		return ret;
#endif	//0
	}


}	//namespace GAME


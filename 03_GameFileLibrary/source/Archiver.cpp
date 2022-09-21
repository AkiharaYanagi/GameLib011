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
	const TCHAR Archiver::ARCHIVE_FILE_NAME[] = _T("archive.dat");

	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
	const TCHAR Archiver::ARCHIVE_DIR_NAME[] = _T("archive\\");

	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������
	const TCHAR Archiver::SEARCH_CONDITION[] = _T("archive\\*.*");

	//�t�@�C���}�b�s���O�̖��O
	const TCHAR Archiver::MAP_NAME[] = _T("mapName");

	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	Archiver::P_Archiver	Archiver::m_inst;

	//------------------------------------------

	//�R���X�g���N�^
	Archiver::Archiver ()
		: m_hMap ( nullptr ), m_pFile ( nullptr ), m_fileNum ( 0 )
	{
	}

	//�f�X�g���N�^
	Archiver::~Archiver ()
	{
		Close ();
	}

	//�A�[�J�C�u�t�@�C����
	void Archiver::Close ()
	{
		if ( m_hMap ) { CloseHandle ( m_hMap ); m_hMap = nullptr; }
	}




	//@todo �ċN�ɂ��T�u�f�B���N�g���̌�����ǉ�����




	//�A�[�J�C�u�t�@�C���쐬
	void Archiver::Make ()
	{
		//�J�����g�f�B���N�g���̎擾
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//�o�C�i���ŏ��o�p�t�@�C�����J��
		HANDLE hWriteFile = CreateFile ( ARCHIVE_FILE_NAME, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD numberOfBytesWritten = 0;

		//-------------------------------------------------------------------------
		//	�w�b�_�̍쐬
		//-------------------------------------------------------------------------

		//�T�u�f�B���N�g�����܂ތ����Ńt�@�C�����X�g���쐬����
		Find ( SEARCH_CONDITION );

		//�t�@�C���������o
		DWORD nFile = m_vFilename.size();
		::WriteFile ( hWriteFile, & nFile, sizeof ( DWORD ), & numberOfBytesWritten, nullptr );

		//-------------------------------------------------------------------------
		//	�t�@�C�����A�t�@�C���T�C�Y(�I�t�Z�b�g)���擾
		//-------------------------------------------------------------------------
#if 0
		WIN32_FIND_DATA findData;
		HANDLE hFind = FindFirstFile ( SEARCH_CONDITION, & findData );
		while ( T )
		{
			//���̃t�@�C�����擾
			if ( FindNextFile ( hFind, &findData ) )
			{
				//�f�B���N�g���͂Ƃ΂�
				if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
					tstring str ( findData.cFileName );
					tostringstream toss;
					toss << _T("�f�B���N�g��: ") << str << _T(", �t�@�C���T�C�Y: ") << findData.nFileSizeLow << std::endl;
//					OutputDebugString ( toss.str().c_str () );
					continue; 
				}

				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͂Ƃ΂�
				if ( findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM )
				{
					tstring str ( findData.cFileName );
					tostringstream toss;
					toss << _T("�V�X�e���t�@�C��: ") << str << _T(", �t�@�C���T�C�Y: ") << findData.nFileSizeLow << std::endl;
//					OutputDebugString ( toss.str().c_str () );
					continue; 
				}

				TCHAR fileName[MAX_PATH];		//�t�@�C����
				_tcscpy_s ( fileName, _T("archive/") );
				_tcscat_s ( fileName, findData.cFileName );
				fileSize = findData.nFileSizeLow;	//4Gbyte�T�C�Y�ȏ�͈���Ȃ�
				
#if	1
				tostringstream toss;
				toss << fileName << _T(", �I�t�Z�b�g: ") << fileTotalSize << _T(", �t�@�C���T�C�Y: ") << fileSize << std::endl;
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
		FindClose ( hFind );
#endif // 0


		//@todo �w�b�_�̏������݂ƓǍ��̌^�̈Ⴂ���C��



		//�Ώۃt�@�C�����ׂĂɑ΂��ă��[�v
		for ( ACV_H_SRC acvSrc : m_vFilename )
		{
			//�A�[�J�C�u�t�@�C��(.dat)�ɏ��o
			DWORD nWrtn = 0;
			TCHAR fn [ MAX_PATH ];
			_tcscpy_s ( fn, MAX_PATH, acvSrc.fileName.c_str () );
			::WriteFile ( hWriteFile, fn, sizeof ( fn ), &nWrtn, nullptr );
			::WriteFile ( hWriteFile, & acvSrc.align.offset, sizeof ( DWORD ), &nWrtn, nullptr );
			::WriteFile ( hWriteFile, & acvSrc.align.fileSize, sizeof ( DWORD ), &nWrtn, nullptr );
		}



		//-------------------------------------------------------------------------
		//�t�@�C�����f�[�^���o
		//-------------------------------------------------------------------------
#if 0
		hFind = FindFirstFile ( SEARCH_CONDITION, &findData );
		while ( T )
		{
			//���̃t�@�C�����擾
			if ( FindNextFile ( hFind, &findData ) )
			{
				//�f�B���N�g���͂Ƃ΂�
				if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) { continue; }
				//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͂Ƃ΂�
				if ( findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }

				fileSize = findData.nFileSizeLow;	//4Gbyte�T�C�Y�ȏ�͈���Ȃ�

				//�t�@�C���Ǎ�
#if	0
				TCHAR fileName[MAX_PATH];		//�t�@�C����
				_tcscpy_s ( fileName, _T("archive/") );
				_tcscat_s ( fileName, fileData.cFileName );
				HANDLE hReadFile = CreateFile ( fileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
#endif	//0
				tstring fileName ( ARCHIVE_DIR_NAME );
				fileName.append ( findData.cFileName );
				HANDLE hReadFile = ::CreateFile ( fileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );

				//�t�@�C���n���h������T�C�Y���Ǎ�
//				BYTE* buf = new BYTE [ fileSize ];
				unique_ptr < BYTE[] > buf = make_unique < BYTE[] > ( fileSize );
				DWORD numberOfBytesRead = 0;
				ReadFile ( hReadFile, buf.get (), fileSize, &numberOfBytesRead, nullptr );

				//�t�@�C���ɃT�C�Y�����o
				DWORD numberOfBytesWritten = 0;
				WriteFile ( hWriteFile, buf.get (), fileSize, &numberOfBytesWritten, nullptr );
//				delete[] buf;

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
		FindClose ( hFind );
#endif // 0

		//�Ώۃt�@�C�����ׂĂɑ΂��ă��[�v
		for ( ACV_H_SRC acvSrc : m_vFilename )
		{
			//�ꎞ�Ǎ�
			HANDLE hReadFile = ::CreateFile ( acvSrc.fileName.c_str (), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
			unique_ptr < BYTE[] > buf = make_unique < BYTE[] > ( acvSrc.align.fileSize );
			DWORD nRead = 0;
			::ReadFile ( hReadFile, buf.get (), acvSrc.align.fileSize, & nRead, nullptr );

			//�A�[�J�C�u�t�@�C��(.dat)�ɏ��o
			DWORD nWrtn = 0;
			::WriteFile ( hWriteFile, buf.get (), acvSrc.align.fileSize, & nWrtn, nullptr );
		}

		CloseHandle ( hWriteFile );
	}


	//�A�[�J�C�u�t�@�C���Ǎ�
	void Archiver::Open ()
	{
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

//		m_hFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		HANDLE hFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD erorr = GetLastError();

		//�t�@�C�����𓾂�
		DWORD dwFileNum = 0;
		DWORD numberOfBytesRead = 0;
		bool bRet = ::ReadFile ( hFile, & dwFileNum, sizeof ( DWORD ), & numberOfBytesRead, nullptr );

		//�w�b�_����������
#if 0
		if ( m_archiveHeader ) { return; }
		m_archiveHeader = new ARCHIVE_HEADER_SEARCH [ dwFileNum ];
#endif // 0
		unique_ptr < ACV_H_SRC [] > hAcv ( new ACV_H_SRC [ dwFileNum ] );

		for ( DWORD i = 0; i < dwFileNum; ++ i )
		{
			ARCHIVE_HEADER tempAcvHd;
			::ReadFile ( hFile, & tempAcvHd, sizeof ( ARCHIVE_HEADER ), & numberOfBytesRead, nullptr );
			hAcv [i].fileName.assign ( tempAcvHd.fileName );
			hAcv [i].align.offset = tempAcvHd.align.offset;
			hAcv [i].align.fileSize = tempAcvHd.align.fileSize;

			m_map.insert ( ARCHIVE_MAP::value_type ( hAcv [i].fileName, & (hAcv [i].align ) ) );
		}

		m_fileNum = dwFileNum;

		//�t�@�C���}�b�s���O
		//@info ���O��t����ƕ����N�����ɓ����̃}�b�s���O�ŃA�N�Z�X�ᔽ�ɂȂ�̂Ŗ����ɂ���
//		m_hMap = CreateFileMapping ( m_hFile, nullptr, PAGE_READONLY, 0, 0, m_mapName );
		m_hMap = CreateFileMapping ( hFile, nullptr, PAGE_READONLY, 0, 0, nullptr );
		if ( m_hMap == nullptr )
		{
			////TRACE_F( _T("�t�@�C���}�b�s���O�Ɏ��s") );
			return;
		}
		m_pFile = ::MapViewOfFile ( m_hMap, FILE_MAP_READ, 0, 0, 0 );
	}




	//���̃t�@�C��������A�[�J�C�u���̃t�@�C���|�C���^�𓾂�
	ACV_FL_USE Archiver::GetFilePointer ( LPCTSTR fileName )
	{
		ACV_FL_USE ret = { nullptr, 0 };
		
		//����
		tstring str ( ARCHIVE_DIR_NAME );
		str.append ( fileName );
		if ( m_map.find ( str ) == m_map.end() ) 
		{
			TRACE_F ( _T("%s, �A�[�J�C�u�̒��ɑΏۂ̃t�@�C����������܂���ł���\n"), fileName );
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



	void Archiver::Find ( LPCTSTR path )
	{
		//�t�@�C�����
		WIN32_FIND_DATA findData;

		//�����̃p�X����ŏ��̃t�@�C��������
		HANDLE hFind = ::FindFirstFile ( path, & findData );

		DWORD fileNum = 0;	//�t�@�C����
		DWORD fileTotalSize = 0;	//���t�@�C���T�C�Y

		//�񋓌�A����("*.*")�������f�B���N�g��������ɂ���
		TRACE_F ( _T ( "Find( %s )\n" ), path );
		tstring tstr_path ( path );
		tstring tstr_cond ( _T ( "*.*" ) );
		size_t nSize = tstr_path.find_last_of ( _T ( "\\" ) ) + 1;
		tstring tstr_dir = tstr_path.substr ( 0, tstr_path.length () - tstr_cond.length () );
		TRACE_F ( _T ( "dir = %s \n" ), tstr_dir );

		//�ȍ~�̃t�@�C��
		do
		{
			//�V�X�e���t�@�C��(Thumbs.db�Ȃ�)�͂Ƃ΂�
			if ( findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) { continue; }

			//�f�B���N�g���͍ċA����
			if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) 
			{
				if ( _tcscmp ( _T ( "." ), findData.cFileName ) == 0 ) { continue; }
				if ( _tcscmp ( _T ( ".." ), findData.cFileName ) == 0 ) { continue; }

				tstring bsbs ( _T ( "\\" ) );
				tstring a = tstr_dir.substr ( 0, tstr_dir.length () - bsbs.length () );
				size_t i_dir = a.find_last_of ( _T ( "\\" ) ) + 1;
				tstring name = a.substr ( i_dir, a.length() - i_dir );
				if ( _tcscmp ( name.c_str (), findData.cFileName ) == 0 ){ continue; }
				TRACE_F ( _T ( "�f�B���N�g��\n" ), path );

				TCHAR subpath [ MAX_PATH ];
				_stprintf_s ( subpath, MAX_PATH, _T ( "%s%s\\*.*" ), tstr_dir.c_str (), findData.cFileName );
				Find ( subpath );
			}
			else
			{
				TCHAR filename [ MAX_PATH ];		//�t�@�C����
				_stprintf_s ( filename, MAX_PATH, _T("%s%s"), tstr_dir.c_str (), findData.cFileName );

				TRACE_F ( _T ( "filename = %s\n" ), filename );

				ACV_H_SRC acv;
				acv.fileName = filename;
				acv.align.fileSize = findData.nFileSizeLow;
				acv.align.offset = fileTotalSize;
				
				//�ۑ�
				m_vFilename.push_back ( acv );

				//�t�@�C���̃I�t�Z�b�g�v�Z
				fileTotalSize += findData.nFileSizeLow;
			}
		} while ( FindNextFile ( hFind, & findData ) );

		::FindClose ( hFind );
	}


}	//namespace GAME


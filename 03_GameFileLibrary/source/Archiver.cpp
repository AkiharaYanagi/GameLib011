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
		: m_hMap ( nullptr ), m_pFile ( nullptr )
		, m_current_offset ( 0 )
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
		if ( m_hMap ) { ::UnmapViewOfFile ( m_hMap ); m_hMap = nullptr; }
	}


	//�A�[�J�C�u�t�@�C���쐬
	void Archiver::Make ()
	{
		//�J�����g�f�B���N�g���̎擾
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );
//		TRACE_F ( _T ( "Make(): %s\n" ), path );

		//�o�C�i���ŏ��o�p�t�@�C�����J��
		HANDLE hWriteFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD numberOfBytesWritten = 0;
		
		//-------------------------------------------------------------------------
		//	�Ώۃt�@�C�����X�g�ƌ�
		//-------------------------------------------------------------------------
		//�T�u�f�B���N�g�����܂ތ����Ńt�@�C�����X�g���쐬����
		//@info ! �ċA�̂��߁A���݃I�t�Z�b�g�ʒu�͊O���ɒu��
		m_current_offset = 0;
		Find ( SEARCH_CONDITION );

		//�t�@�C���������o
		DWORD nFile = m_vFilename.size();
		::WriteFile ( hWriteFile, & nFile, sizeof ( DWORD ), & numberOfBytesWritten, nullptr );

		//-------------------------------------------------------------------------
		//	�w�b�_�̍쐬
		//-------------------------------------------------------------------------
		//	�t�@�C�����A�t�@�C���T�C�Y(�I�t�Z�b�g)���擾

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

//			TRACE_F ( _T ( "%s: offset = %d, size = %d\n" ), fn, acvSrc.align.offset, acvSrc.align.fileSize );
		}

		//-------------------------------------------------------------------------
		//�t�@�C�����f�[�^���o
		//-------------------------------------------------------------------------

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

			::CloseHandle ( hReadFile );
		}

		::CloseHandle ( hWriteFile );
	}


	//�A�[�J�C�u�t�@�C���Ǎ�
	void Archiver::Open ()
	{
		//�J�����g�f�B���N�g���̎擾
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );
//		TRACE_F ( _T ( "Open(): %s\n" ), path );

		HANDLE hFile = ::CreateFile ( ARCHIVE_FILE_NAME, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
		DWORD error = ::GetLastError();
		if ( ERROR_SUCCESS != error )
		{
			TRACE_F ( _T ( "Error : %d\n" ), error );
			return;
		}

		//�t�@�C�����𓾂�
		DWORD dwFileNum = 0;
		DWORD numberOfBytesRead = 0;
		bool bRet = ::ReadFile ( hFile, & dwFileNum, sizeof ( DWORD ), & numberOfBytesRead, nullptr );

		//�w�b�_����������
		unique_ptr < ACV_H_SRC [] > hAcv ( new ACV_H_SRC [ dwFileNum ] );

		for ( DWORD i = 0; i < dwFileNum; ++ i )
		{
			ARCHIVE_HEADER tempAcvHd;
			::ReadFile ( hFile, & tempAcvHd, sizeof ( ARCHIVE_HEADER ), & numberOfBytesRead, nullptr );
			hAcv [i].fileName.assign ( tempAcvHd.fileName );
			hAcv [i].align.offset = tempAcvHd.align.offset;
			hAcv [i].align.fileSize = tempAcvHd.align.fileSize;

//			TRACE_F ( _T ( "%s: offset = %d, size = %d\n" ), hAcv [ i ].fileName, hAcv [ i ].align.offset, hAcv[i].align.fileSize );
			m_map.insert ( ARCHIVE_MAP::value_type ( hAcv [i].fileName, hAcv [i].align ) );
		}

		//�t�@�C���}�b�s���O
		//@info ���O��t����ƕ����N�����ɓ����̃}�b�s���O�ŃA�N�Z�X�ᔽ�ɂȂ�̂Ŗ����ɂ���
		//	�t�@�C���}�b�s���O�͕ʃv���Z�X�ŋ��ʃ������ɃA�N�Z�X�����@
//		m_hMap = CreateFileMapping ( m_hFile, nullptr, PAGE_READONLY, 0, 0, m_mapName );
		m_hMap = ::CreateFileMapping ( hFile, nullptr, PAGE_READONLY, 0, 0, nullptr );
		if ( m_hMap == nullptr )
		{
			////TRACE_F( _T("�t�@�C���}�b�s���O�Ɏ��s") );
			return;
		}
		m_pFile = ::MapViewOfFile ( m_hMap, FILE_MAP_READ, 0, 0, 0 );

		::CloseHandle ( hFile );
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
		ARCHIVE_ALIGN align = m_map [ str ];


		//�f�[�^�J�n�ʒu
//		size_t nFile = m_vFilename.size ();
		//--------------------------------------------------------------------------------
		//@info ! Release���[�h�ł�Make()��ʂ�Ȃ����߁Am_vFileName.size()�Ɍ����L�^����Ȃ�
		//--------------------------------------------------------------------------------
		size_t nFile = m_map.size ();
		DWORD startData = sizeof ( DWORD ) + sizeof ( ARCHIVE_HEADER ) * nFile;

		//(LPVOID)�ł͈ʒu�v�Z���ł��Ȃ��̂�(LPBYTE)�ɂ���
//		ret.filePointer = (LPVOID)m_pFile + startData + align.offset;
		ret.filePointer = (LPBYTE)m_pFile + startData + align.offset;
		ret.fileSize = align.fileSize;

		return ret;
	}


	void Archiver::Find ( LPCTSTR path )
	{
		//�t�@�C�����
		WIN32_FIND_DATA findData;

		//�����̃p�X����ŏ��̃t�@�C��������
		HANDLE hFind = ::FindFirstFile ( path, & findData );

		//�񋓌�A����("*.*")�������f�B���N�g��������ɂ���
//		TRACE_F ( _T ( "Find( %s )\n" ), path );
		tstring tstr_path ( path );
		tstring tstr_cond ( _T ( "*.*" ) );
		size_t nSize = tstr_path.find_last_of ( _T ( "\\" ) ) + 1;
		tstring tstr_dir = tstr_path.substr ( 0, tstr_path.length () - tstr_cond.length () );
//		TRACE_F ( _T ( "dir = %s \n" ), tstr_dir );

		//@info ���݃I�t�Z�b�g�ʒu�͊֐��̊O���ɒu��
//		DWORD	all_offset = 0;

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
//				TRACE_F ( _T ( "�f�B���N�g��\n" ), path );

				TCHAR subpath [ MAX_PATH ];
				_stprintf_s ( subpath, MAX_PATH, _T ( "%s%s\\*.*" ), tstr_dir.c_str (), findData.cFileName );
				Find ( subpath );
			}
			else
			{
				TCHAR filename [ MAX_PATH ];		//�t�@�C����
				_stprintf_s ( filename, MAX_PATH, _T("%s%s"), tstr_dir.c_str (), findData.cFileName );

//				TRACE_F ( _T ( "filename = %s\n" ), filename );

				ACV_H_SRC acv;
				acv.fileName = filename;
				acv.align.fileSize = findData.nFileSizeLow;
//				acv.align.offset = all_offset;
				acv.align.offset = m_current_offset;

				//�ۑ�
				m_vFilename.push_back ( acv );

				//�t�@�C���̃I�t�Z�b�g�v�Z
				m_current_offset += findData.nFileSizeLow;
			}
		} while ( FindNextFile ( hFind, & findData ) );

		::FindClose ( hFind );
	}


}	//namespace GAME


//=================================================================================================
//
// �t�@�C���A�[�J�C�o
//		Debug���[�h����Archive�f�B���N�g���ɂ���t�@�C����archive.dat�ɏ����o���A
//		Debug���[�h, Release���[�h����archive.dat����t�@�C���|�C���^��ǂݍ���
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <iostream>
#include <map>
#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	//========================================================
	//	���A�[�J�C�u�f�[�^�@�w�b�_�t�H�[�}�b�g
	//	DWORD			fileNum		//�t�@�C���̌�
	//	ARCHIVE_HEADER	...			//fileNum��������
	//	BYTE			...			//�o�C�i���f�[�^
	//========================================================

	//�t�@�C�����z�u
	struct ARCHIVE_ALIGN
	{
		DWORD		offset;			//(�w�b�_������)�f�[�^�J�n�ʒu����̃|�C���^�ʒu�I�t�Z�b�g
		DWORD		fileSize;		//�t�@�C���T�C�Y
	};

	//�����p
	struct ARCHIVE_HEADER
	{
		TCHAR			fileName[ MAX_PATH ];	//�t�@�C����
		ARCHIVE_ALIGN	align;					//�z�u
	};

	//�����p
	struct ARCHIVE_HEADER_SEARCH
	{
		tstring			fileName;		//�t�@�C����
		ARCHIVE_ALIGN	align;			//�z�u
	};

	//�ߒl�p
	struct ARCHIVE_FILE_USE
	{
		LPCVOID		filePointer;		//�t�@�C���|�C���^
		DWORD		fileSize;			//�t�@�C���T�C�Y
	};

	//map�^�錾
	using ARCHIVE_MAP = std::map < tstring, ARCHIVE_ALIGN* >;


	//�A�[�J�C�o�N���X
	class Archiver
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using P_Archiver = unique_ptr < Archiver >;
		static P_Archiver	m_inst;
		Archiver ();
		Archiver ( const Archiver & rhs ) = delete;
	public:
		~Archiver ();
		static void Create () { if ( ! m_inst ) { m_inst = P_Archiver ( new Archiver () ); } }
		static P_Archiver & instance() { return m_inst; }	//�C���X�^���X�擾
	//--------------------------------------------------

	private:
		HANDLE						m_hFile;
		HANDLE						m_hMap;		//�t�@�C���}�b�s���O

		DWORD						m_fileNum;
		ARCHIVE_HEADER_SEARCH*		m_archiveHeader;
		ARCHIVE_MAP					m_map;
		LPVOID						m_pFile;
		
		static const TCHAR			m_archiveFileName[];
		static const TCHAR			m_archiveDirName[];
		static const TCHAR			m_searchCondition[];
		static const TCHAR			m_mapName[];

	public:
		//�A�[�J�C�u�t�@�C���쐬
		void Make ();

		//�A�[�J�C�u�t�@�C���Ǎ�
		void Open ();

		//�A�[�J�C�u�t�@�C����
		void Close ();

		//���̃t�@�C��������A�[�J�C�u���̃t�@�C���|�C���^�𓾂�
		ARCHIVE_FILE_USE GetFilePointer ( LPCTSTR fileName );
	};




}	//namespace GAME


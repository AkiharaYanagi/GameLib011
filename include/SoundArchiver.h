//=================================================================================================
//
// SoundArchiver �w�b�_�t�@�C��
//
//		Debug���[�h����Sound�f�B���N�g���ɂ���wave�t�@�C����sound.dat�ɏ����o���A
//		Debug���[�h, Release���[�h����sound.dat����wave��ǂݍ���
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>

#include "DebugLibrary.h"
#include "DxSound.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//========================================================
	//	�� �T�E���h�A�[�J�C�u �t�H�[�}�b�g
	//	----
	//	UINT	4byte	//�T�C�Y
	//	BYTE	...		//�o�C�i���f�[�^
	//	----
	//	n�̗�
	//	��������Ƃ��͒萔�Y��
	//========================================================

	class SoundArchiver
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using P_SoundArchiver = unique_ptr < SoundArchiver >;
		static P_SoundArchiver		m_inst;
		SoundArchiver ();
		SoundArchiver ( const SoundArchiver& rhs ) = delete;
	public:
		~SoundArchiver ();
		static void Create () { if ( ! m_inst ) { m_inst = P_SoundArchiver ( new SoundArchiver () ); } }
		static P_SoundArchiver & instance () { return m_inst; }
	//--------------------------------------------------

	private:
		static LPCTSTR	m_archiveFileName;	//�쐬����T�E���h�A�[�J�C�u�t�@�C����

		static LPCTSTR	m_archiveDirName;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
		static LPCTSTR	m_searchCondition;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������

		static LPCTSTR	m_archiveDirName_SE;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
		static LPCTSTR	m_searchCondition_SE;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������

//		HANDLE		m_hFile;	//�Ǎ��t�@�C���n���h��
//		UINT		m_count;	//�Ǎ���

		DWORD		m_nBGM;
		DWORD		m_nSE;

	public:
		void Make ();
		void Open ();

		//------------------------------------------------------------------
#if 0
		void Play ( UINT id );
		void PlayLoop ( UINT id );
		void Stop ( UINT id );
#endif // 0
		void Play_BGM ( UINT BGM_ID );
		void Play_Loop_BGM ( UINT BGM_ID );
		void Stop_BGM ( UINT BGM_ID );

		void Play_SE ( UINT SE_ID );

	private:

		//�����̃t�@�C�������グ
		UINT CountFileNum ( LPCTSTR condition );

		//�쐬
		void _Make ( HANDLE hWriteFile, LPCTSTR dirname, LPCTSTR condition );
	};

	//�O�����p��`
	#define		SOUND	SoundArchiver::instance()


}	//namespace GAME


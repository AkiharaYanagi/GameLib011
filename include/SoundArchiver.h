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
		static const TCHAR			m_archiveFileName[];
		static const TCHAR			m_archiveDirName[];
		static const TCHAR			m_searchCondition[];

		HANDLE						m_hFile;

		UINT	m_count;		//�Ǎ���

	public:
		void Make ();

		void Open ();
		void Close ();

		void Play ( UINT id );
		void PlayLoop ( UINT id );
		void Stop ( UINT id );
	};

	//�O�����p��`
	#define		SOUND	SoundArchiver::instance()


}	//namespace GAME


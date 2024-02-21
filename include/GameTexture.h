//=================================================================================================
//
// �Q�[���e�N�X�`���@�w�b�_
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���@�C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "Dx3D.h"
#include "Archiver.h"
#include "OutlineFont.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------------------------
	//�Q�[���e�N�X�`���@�x�[�X
	//--------------------------------------------------------
	class GameTextureBase
	{
		TX		m_lpTexture;		//�e�N�X�`��(�m�ہE����͌p����ōs��)
		UINT	m_textureIndex;		//�e�N�X�`���C���f�b�N�X
	
	public:
		GameTextureBase ();
		GameTextureBase ( const GameTextureBase& obj ) = delete;		//�R�s�[�֎~
		virtual ~GameTextureBase ();

		virtual void Load () {};		//�e�N�X�`���ǂݍ���
		virtual void Rele () {};		//���
		virtual void Reset () {};		//�Đݒ�

		//�C���f�b�N�X���w��
		void SetTextureIndex( UINT i )	{ m_textureIndex = i; }
		UINT GetTextureIndex() const	{ return m_textureIndex; }

		//�e�N�X�`���̐ݒ�
		void SetTexture ( TX lpTexture ) { m_lpTexture = lpTexture; }
		
		//�擾
		TX&	GetTexture () { return m_lpTexture; }
		USIZE GetSize () const;	//�e�N�X�`�������݂��Ȃ��ꍇ(0,0)��Ԃ�
	};

	using TxBs = GameTextureBase;
	using P_TxBs = std::shared_ptr < TxBs >;
	using VP_TxBs = std::vector < P_TxBs >;
	using PVP_TxBs = std::shared_ptr < VP_TxBs >;


	//--------------------------------------------------------
	//�Q�[���e�N�X�`���@�t�����t�@�C��
	//		���ڃt�@�C�����疼�O���w�肵�ăe�N�X�`�����쐬���Ǘ�����
	//--------------------------------------------------------
	class GameTextureFromFile : public TxBs
	{
		TX			m_lpTexture;		//�e�N�X�`��
		tstring		m_strFilename;		//�Ǎ��t�@�C����
	
	public:
		GameTextureFromFile ();
		GameTextureFromFile ( tstring filename ) : m_lpTexture(nullptr) { m_strFilename = filename; }
		GameTextureFromFile ( const GameTextureFromFile& obj ) = delete;		//�R�s�[�֎~
		virtual ~GameTextureFromFile ();

		virtual void Load ();	//�e�N�X�`���ǂݍ���
		virtual void Rele ();	//���
		virtual void Reset ();	//�Đݒ�

		//�Ǎ��t�@�C�������w��
		void SetFileName ( LPCTSTR filename ) { m_strFilename.assign ( filename ); }
		void SetFileName ( tstring filename ) { m_strFilename = filename; }
	};
	
	using TxFl = GameTextureFromFile;
	using P_TxFl = std::shared_ptr < TxFl >;
	using VP_TxFl = std::vector < P_TxFl >;
	using PVP_TxFl = std::shared_ptr < VP_TxFl >;


	//--------------------------------------------------------
	//�Q�[���e�N�X�`���@�t�����A�[�J�C�u
	//		archive.dat���̃t�@�C�������w�肵�ăe�N�X�`�����쐬���Ǘ�����
	//		�Ǎ���Load���ɍs��
	//		Debug���[�h���ɂ�archive�f�B���N�g�����̃t�@�C�����w�肷��
	//--------------------------------------------------------
	class GameTextureFromArchive : public TxBs
	{
		TX			m_lpTexture;		//�e�N�X�`��
		tstring		m_strFileName;		//�Ǎ��t�@�C����
	
	public:
		GameTextureFromArchive ();
		GameTextureFromArchive ( const GameTextureFromArchive& obj ) = delete;		//�R�s�[�֎~
		virtual ~GameTextureFromArchive ();

		virtual void Load ();	//�e�N�X�`���ǂݍ���
		virtual void Rele ();	//���
		virtual void Reset ();	//�Đݒ�

		//�Ǎ��t�@�C�������w��
		void SetFileName ( LPCTSTR fileName ) { m_strFileName.assign ( fileName ); }
		void SetFileName ( tstring fileName ) { m_strFileName = fileName; }
	};

	using TxAcv= GameTextureFromArchive;
	using P_TxAcv= std::shared_ptr < TxAcv >;
	using VP_TxAcv= std::vector < P_TxAcv >;
	using PVP_TxAcv= std::shared_ptr < VP_TxAcv >;


	//--------------------------------------------------------
	//�Q�[���e�N�X�`���@�t����������
	//		�A�[�J�C�u���̃������ォ��e�N�X�`�����쐬���Ǘ�����
	//		�Ǎ��͎��̉����đ����ɍs��
	//		�A�[�J�C�u�Ǎ����̂ݐV�K�쐬����A�Đݒ�̓A�[�J�C�u���ōs��
	//--------------------------------------------------------
	class GameTextureFromMemory : public TxBs
	{
		TX		m_lpTexture;		//�e�N�X�`��

	public:
		GameTextureFromMemory ( LPCVOID pSrcData, UINT SrcDataSize );
		GameTextureFromMemory ( const GameTextureFromMemory& obj ) = delete;		//�R�s�[�֎~
		virtual ~GameTextureFromMemory ();

		virtual void Load ();	//�e�N�X�`���ǂݍ���
		virtual void Rele ();	//���
		virtual void Reset ();	//�Đݒ�
	};

	using TxMem = GameTextureFromMemory;
	using P_TxMem = std::shared_ptr < TxMem >;
	using VP_TxMem = std::vector < P_TxMem >;
	using PVP_TxMem = std::shared_ptr < VP_TxMem >;


	//--------------------------------------------------------
	//�Q�[���e�N�X�`���@�t�����X�g�����O
	//		�����񂩂琶�������Q�[���e�N�X�`��
	//--------------------------------------------------------
	class GameTextureFromString : public TxBs
	{
		tstring		m_str;

		int			m_fontSize;
		int			m_penSize;
		int			m_quality;
		DWORD		m_fillColor;
		DWORD		m_edgeColor;
		TCHAR		m_fontName [ LF_FACESIZE ];	//�t�H���g��(FaceName)

	public:
		GameTextureFromString ();
		GameTextureFromString ( const GameTextureFromString& rhs ) = delete;
		~GameTextureFromString ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR lpctstr );
		tstring& GetStr () { return m_str; }

		void SetParam ( int fontSize, int penSize, int quolity );
		void SetFontFace ( LPCTSTR fontname );
		void SetColor ( DWORD fill, DWORD edge );
	};

	using TxStr = GameTextureFromString;
	using P_TxStr = std::shared_ptr < TxStr >;


}	//namespace GAME


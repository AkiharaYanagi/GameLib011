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
#include "GameTask.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//--------------------------------------------------------
	//�Q�[���e�N�X�`���@�x�[�X
	//		�e�N�X�`���̊�{
	//		�E�������z�֐������̂Ŏ��̉��͕s��
	//--------------------------------------------------------
	class GameTextureBase
	{
		TX		m_lpTexture;		//�e�N�X�`��(�m�ہE����͌p����ōs��)
//		_CLR	m_color;			//�J���[
		UINT	m_textureIndex;		//�e�N�X�`���C���f�b�N�X
	
	public:
		GameTextureBase ();
		GameTextureBase ( const GameTextureBase& obj ) = delete;		//�R�s�[�֎~
		virtual ~GameTextureBase ();

		virtual void Load () = 0;		//�e�N�X�`���ǂݍ���
		virtual void Rele () = 0;		//���
		virtual void Reset () = 0;		//�Đݒ�

		//�C���f�b�N�X���w��
		void SetTextureIndex( UINT i )	{ m_textureIndex = i; }
		UINT GetTextureIndex() const	{ return m_textureIndex; }

		//�e�N�X�`���̐ݒ�
		void SetTexture ( TX lpTexture ) { m_lpTexture = lpTexture; }
		TX	GetTexture() const { return m_lpTexture; }

		//�J���[���O���t�B�b�N�I�u�W�F�N�g�Ɉڐ�
#if 0
		//�J���[�̐ݒ�
		void SetColor ( D3DXCOLOR color ) { m_color = color; }
		D3DXCOLOR	GetColor () const { return m_color; }
		
		//���l�݂̂̐ݒ�
		void SetAlpha ( float alpha ) 
		{ 
			m_color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, alpha ); 
		}		
#endif // 0
	};

	typedef GameTextureBase			TxBs;
	typedef shared_ptr < TxBs >		P_TxBs;
	typedef vector < P_TxBs >		VP_TxBs;
	typedef shared_ptr < VP_TxBs >	PVP_TxBs;


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
		GameTextureFromFile ( tstring filename ) { m_strFilename = filename; }
		GameTextureFromFile ( const GameTextureFromFile& obj ) = delete;		//�R�s�[�֎~
		virtual ~GameTextureFromFile ();

		virtual void Load ();	//�e�N�X�`���ǂݍ���
		virtual void Rele ();	//���
		virtual void Reset ();	//�Đݒ�

		//�Ǎ��t�@�C�������w��
		void SetFileName ( LPCTSTR filename ) { m_strFilename.assign ( filename ); }
		void SetFileName ( tstring filename ) { m_strFilename = filename; }
	};
	
	typedef GameTextureFromFile		TxFl;
	typedef shared_ptr < TxFl >		P_TxFl;
	typedef vector < P_TxFl >		VP_TxFl;
	typedef shared_ptr < VP_TxFl >	PVP_TxFl;


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

	typedef GameTextureFromArchive	TxAcv;
	typedef shared_ptr < TxAcv >	P_TxAcv;
	typedef vector < P_TxAcv >		VP_TxAcv;
	typedef shared_ptr < VP_TxAcv >	PVP_TxAcv;


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

	typedef GameTextureFromMemory	TxMem;
	typedef shared_ptr < TxMem >	P_TxMem;
	typedef vector < P_TxMem >		VP_TxMem;
	typedef shared_ptr < VP_TxMem >	PVP_TxMem;


}	//namespace GAME


//=================================================================================================
//
// �Q�[���O���t�B�b�N�@�N���X�@�w�b�_
//		�O���t�B�b�N�������I�u�W�F�N�g���`����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���@�C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "GameTask.h"
#include "GameTexture.h"
#include "GameObject.h"
#include <vector>
#include "GameGraphicCore.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
using namespace std;

namespace GAME
{
	//��=======================================================================
	// �Q�[���O���t�B�b�N�@�x�[�X
	//		�E�����e�N�X�`���ƕ����I�u�W�F�N�g�����O���t�B�b�N
	//		�E�e�N�X�`�����w�肳��Ă��Ȃ��Ƃ��͉������Ȃ�
	//		�E�������z�֐������̂Ŏ��̉��͕s��
	//		�E�p����
	//			GameGraphicFromFile
	//			GameGraphicFromArchive
	//			GameGraphicApprovedTexture
	//		�@�̂����ꂩ��p����
	//��=======================================================================
	class GameGraphicBase	: public GameGraphicCore
	{
		//�I�u�W�F�N�g�ʒu
		P_VEC3		m_pCenter;		//�X�v���C�g���S�ʒu
		P_VEC3		m_pPosition;	//�X�v���C�g�\���ʒu

		//�I�u�W�F�N�g�z��
		PVP_Object	m_pvpObject;
		UINT		m_indexObject;

		//�e�N�X�`���z��(�C���f�b�N�X�̓I�u�W�F�N�g������)
		PVP_TxBs	m_pvpTexture;

	public:
		GameGraphicBase ();
		GameGraphicBase ( const GameGraphicBase & rhs ) = delete;
		virtual ~GameGraphicBase ();

		//�������z�֐�
		virtual void Load () = 0;	//�Ǎ�
		virtual void Rele () = 0;	//���
		virtual void Reset () = 0;	//�Đݒ�

		virtual void Move();	//�t���[��������
		virtual void Draw();	//�t���[�����`��

		//---------------------------------------------------------------------
		//�X�v���C�g���S�ʒu
		void SetSpriteCenter ( VEC3 center ) { (* m_pCenter) = center; }
		VEC3 GetSpriteCenter () { return (* m_pCenter); }
		//�X�v���C�g�\���ʒu /* Z: 1.f == �Ŕw��, 0.f == �őO�� */
		void SetSpritePosition ( VEC3 position ) { (* m_pPosition) = position; }
		VEC3 GetSpritePosition () { return (* m_pPosition); }
		void SetZ ( float z ) { m_pPosition->z = z; }
		float GetZ () const { return m_pPosition->z; }

		//---------------------------------------------------------------------
		//�I�u�W�F�N�gvector�̃|�C���^
		PVP_Object GetpvpObject () { return m_pvpObject; }

		//�N���A
		void ClearObject ();

		//�Đݒ�(�ŏ��̂P���N���A���Ă������ǉ�)
		virtual void ResetObjectNum ( UINT n ) { ClearObject (); AddObject ( n ); }

		//�ǉ�
		virtual void AddObject () { m_pvpObject->push_back ( make_shared < GameObject > () ); }
		virtual void AddObject ( UINT n ) { for ( UINT i = 0; i < n; ++i ) { AddObject (); } }
		virtual void AddpObject ( P_Object p ) { m_pvpObject->push_back ( p ); }

		void SetAllValid ( bool b );		//���ׂĉ��ؑ�
		void SetAllPos ( VEC2 vec );		//���ׂĈʒu�w��
		void SetAllColor ( D3DXCOLOR color );		//���ׂĂ̐F���w��

		//---------------------------------------------------------------------
		//�I�u�W�F�N�g���ڐ擪����
		void SetPos ( VEC2 v ) { m_pvpObject->at ( 0 )->SetPos ( v ); }
		void SetPos ( float x, float y ) { m_pvpObject->at ( 0 )->SetPos ( x, y ); }
		VEC2 GetPos () const { return m_pvpObject->at ( 0 )->GetPos (); }

		void SetScaling ( VEC2 v ) { m_pvpObject->at ( 0 )->SetScaling ( v ); }
		void SetScaling ( float x, float y ) { m_pvpObject->at ( 0 )->SetScaling ( x, y ); }
		void SetScalingCenter ( VEC2 v ) { m_pvpObject->at ( 0 )->SetScalingCenter ( v ); }

		void SetRotationCenter ( VEC2 v ) { m_pvpObject->at ( 0 )->SetRotationCenter ( v ); }
		void SetRadian ( float f ) { m_pvpObject->at ( 0 )->SetRadian ( f ); }

		//�I�u�W�F�N�g�w��
		void SetiPos ( UINT i, VEC2 v ) { m_pvpObject->at ( i )->SetPos ( v ); }

		//---------------------------------------------------------------------
		//�e�N�X�`���̐ݒ�

		//�e�N�X�`���|�C���^��ǉ�
		void AddpTexture ( P_TxBs pTexture );

		//�e�N�X�`����ݒ�
		void SetpTexture ( P_TxBs pTexture );

		//Clear
		void ClearTexture () { m_pvpTexture->clear (); }

		//�e�N�X�`���̐擪��Ԃ�
		P_TxBs GetpTexture () { return m_pvpTexture->at ( 0 ); }

		//�e�N�X�`���z��|�C���^��Ԃ�
		PVP_TxBs GetpvpTexture () { return m_pvpTexture; }

		//�擪�̂ݎw��
		void SetIndexTexture ( UINT i )
		{
			m_pvpObject->at ( 0 )->SetIndexTexture ( i );
		}

		//�e�N�X�`���̒��S�ʒu (Load()��̂�)
		VEC2 GetCenterOfTexture ( UINT index ) const ;

		//---------------------------------------------------------------------

		//�I�u�W�F�N�g��p�����t�F�[�h


		//@todo
		//�I�u�W�F�N�g���Q�ȏ�̂Ƃ��t�F�[�h�œ���
		void FadeChangeOb ( UINT i0, UINT i1 );


	};

	//�^�w��
	typedef		GameGraphicBase			GrpBs;
	typedef		shared_ptr < GrpBs >	P_GrpBs;


	//��=======================================================================
	// �Q�[���O���t�B�b�N �t�����t�@�C��
	// (�摜�t�@�C���w��)
	//		GameTextureFromFile��p���Ė��O���w�肵�Ē��ډ摜�t�@�C������Ǎ�
	//		�P�̃e�N�X�`����ێ����A�Ǘ�����
	//��=======================================================================
	class GameGraphicFromFile : public GrpBs
	{
		VP_TxBs	m_vpTexture;

	public:
		GameGraphicFromFile ();
		GameGraphicFromFile ( const GameGraphicFromFile& rhs ) = delete;	//�R�s�[�֎~
		virtual ~GameGraphicFromFile ();

		virtual void Load();	//�Ǎ�
		virtual void Rele();	//���
		virtual void Reset();	//�Đݒ�

		//�e�N�X�`���̓Ǎ��t�@�C�������w��
//		void SetFileName ( LPCTSTR fileName ) { m_pTextureFromFile->SetFileName ( fileName ); }

		//�e�N�X�`����ǉ�
		void AddTexture ( LPCTSTR fileName );
	};

	typedef		GameGraphicFromFile		GrpFl;
	typedef		shared_ptr < GrpFl >	P_GrpFl;


	//��=======================================================================
	// �Q�[���O���t�B�b�N �t�����A�[�J�C�u
	// (�A�[�J�C�u���p)
	//		GameTextureFromArchive��p���Ė��O���w�肵�ăA�[�J�C�u����Ǎ�
	//		GameGraphicBase���e�N�X�`���ƃ}�g���N�X��vector������
	//��=======================================================================
	class GameGraphicFromArchive : public GrpBs
	{
		VP_TxBs	m_vpTexture;

	public:
		GameGraphicFromArchive ();
		GameGraphicFromArchive ( const GameGraphicFromArchive& rhs ) = delete;	//�R�s�[�֎~
		virtual ~GameGraphicFromArchive ();

		virtual void Load();	//�Ǎ�
		virtual void Rele();	//���
		virtual void Reset();	//�Đݒ�

		//�e�N�X�`����ǉ�
		void AddTexture ( LPCTSTR fileName );
	};

	typedef		GameGraphicFromArchive	GrpAcv;
	typedef		shared_ptr < GrpAcv >	P_GrpAcv;


	//��=======================================================================
	// �Q�[���O���t�B�b�N�@�A�v���u�h�e�N�X�`��
	//		���ɓǂݍ���ł���e�N�X�`�����w�肷��
	//		GameGraphicBase���e�N�X�`���ƃ}�g���N�X��vector������
	//��=======================================================================
	class GameGraphicApprovedTexture	: public GrpBs
	{
		P_TxBs	m_pTexture;		//�Ǎ��ς݃e�N�X�`��(����E�Đݒ�͐ݒ茳�ōs��)

	public:
		GameGraphicApprovedTexture ();
		GameGraphicApprovedTexture ( const GameGraphicApprovedTexture& rhs ) = delete;	//�R�s�[�֎~
		virtual ~GameGraphicApprovedTexture ();

		//�Ǎ��E����E�Đݒ�̓e�N�X�`�����ōs��
		//�e�N�X�`����������Ȃ����z�֐�

		//GraphicBase��Clear()�̂ݍs��
		virtual void Load();	//�Ǎ�
		virtual void Rele();	//���
		virtual void Reset();	//�Đݒ�

		//�e�N�X�`��
		void SetpTexture ( P_TxBs pTexture )
		{
			GrpBs::SetpTexture ( pTexture );
		}
	};

	typedef		GameGraphicApprovedTexture	GrpApTx;
	typedef		shared_ptr < GrpApTx >	P_GrpApTx;


}	//namespace GAME


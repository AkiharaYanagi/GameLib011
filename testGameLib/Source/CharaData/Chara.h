//=================================================================================================
//
//	Chara �w�b�_�t�@�C��
//		�L�����N�^�̃f�[�^���Ǘ�����
//		�C���[�W�A�X�N���v�g�A�R�}���h
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
#include "Action.h"
#include "Effect.h"
#include "Behavior.h"
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	�L���� ���s��f�[�^ ver105
	//	
	//	�L����	
	//		��[]�C���[�W
	//		��[]Ef�C���[�W
	//		��
	//		��[]�A�N�V����
	//	new	��	��[]�X�N���v�g
	//		��		��[]�u�����`
	//		��		��[]Ef�W�F�l���[�g
	//		��
	//		��[]Ef
	//		��	��[]�X�N���v�g new
	//		��		��[]�u�����`
	//		��		��[]Ef�W�F�l���[�g
	//		��
	//		��[]�R�}���h
	//		����{��ԃA�N�V����ID
	//		��	������, �\��, �ō�, ����, ��낯, �_���[�W, �_�E��, ����
	//		��
	//
	//==================================================================================


	class Chara
	{
//		Behavior		m_bhvMain;		//���C�� �X�N���v�g
		PVP_TxBs		m_pvpTxMain;	//���C���C���[�W �e�N�X�`���z��
		PVP_Action		m_pvpAction;	//�A�N�V�����z��

//		Behavior		m_bhvEf;		//EF �X�N���v�g
		PVP_TxBs		m_pvpTxEf;		//EF�C���[�W �e�N�X�`���z��
		PVP_Effect		m_pvpEf;		//�G�t�F�N�g�z��

		VP_Command		m_vpCommand;		//�R�}���h�z��

		UINT	m_bsAction [ BASIC_ACTION_NUM ];		//��{�A�N�V����

	public:
		Chara ();
		Chara ( const Chara & rhs ) = delete;
		~Chara ();

		void Make ();
		void Rele ();
		void Reset ();

		//-----------------------------------------------------------------
		//���C���C���[�W �e�N�X�`���z��|�C���^
		PVP_TxBs GetpvpMainTexture () const { return m_pvpTxMain; }

		//���C���C���[�W �e�N�X�`���z��ɒǉ�
		void AddpMainTexture ( P_TxBs pTexture ) { m_pvpTxMain->push_back ( pTexture ); }

		//���C���C���[�W �e�N�X�`���|�C���^�̎擾
		P_TxBs GetpMainTexture ( UINT index ) { return m_pvpTxMain->at ( index ); }

		//-----------------------------------------------------------------
		//Ef�C���[�W �e�N�X�`���z��|�C���^
		PVP_TxBs GetpvpEfTexture () const { return m_pvpTxEf; }

		//Ef�C���[�W �e�N�X�`���z��ɒǉ�
		void AddpEfTexture ( P_TxBs pTexture ) { m_pvpTxEf->push_back ( pTexture ); }

		//Ef�C���[�W �e�N�X�`���|�C���^�̎擾
		P_TxBs GetpEfTexture ( UINT index ) { return m_pvpTxEf->at ( index ); }

		//-----------------------------------------------------------------
		//�A�N�V�����z��|�C���^���擾
		PVP_Action GetpvpAction () { return m_pvpAction; }

		//�A�N�V�����z��ɒǉ�
		void AddpAction ( P_Action pAction ) { m_pvpAction->push_back ( pAction ); }

		//�A�N�V�����|�C���^���擾
		P_Action GetpAction ( UINT index ) { return m_pvpAction->at ( index ); }

		//---------------------------------------------------------------------
		//��{�A�N�V����ID
		UINT GetBsAction ( BASIC_ACTION index ) const { return m_bsAction[ index ]; }
		void SetBsAction ( BASIC_ACTION index, UINT actionID ) { m_bsAction [ index ] = actionID; }

		//-----------------------------------------------------------------
		//�G�t�F�N�g�z��ɒǉ�
		void AddpEffect ( P_Effect pEffect ) { m_pvpEf->push_back ( pEffect ); }

		//�G�t�F�N�g�z��|�C���^���擾
		PVP_Effect GetpvpEffect () { return m_pvpEf; }

		//�G�t�F�N�g�|�C���^���擾
		P_Effect GetpEffect ( UINT index ) { return m_pvpEf->at ( index ); }

		//---------------------------------------------------------------------
		//�X�N���v�g�|�C���^���擾
		P_Script GetpScript ( UINT indexAction, UINT indexScript ) { return m_pvpAction->at ( indexAction )->GetpScript( indexScript ); }

		//���X�N���v�g�����݂��邩�ǂ���
		bool IsNextScript ( UINT indexAction, UINT indexScript )
		{
			return m_pvpAction->at ( indexAction )->IsNextScript( indexScript );
		}

		//---------------------------------------------------------------------
		//�R�}���h�z��ɒǉ�
		void AddpCommand ( P_Command pCommand ) { m_vpCommand.push_back ( pCommand ); }

		//�R�}���h���擾
		P_Command GetpCommand ( UINT indexCommand ) const { return m_vpCommand[indexCommand]; }

	};

	using P_Chara = shared_ptr < Chara >;
	using VP_Chara = vector < P_Chara >;
	using PVP_Chara = shared_ptr < VP_Chara >;


}	//namespace GAME


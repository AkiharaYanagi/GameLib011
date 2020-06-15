//------------------------------------------------------------------
//
// _GameKeyCommand �w�b�_
//	�R�}���h����p�̂P�t���[�����̓��̓f�[�^
//		�Q�[����̋L�^�f�[�^(_GameKey)�ƈقȂ�_�́A
//		���o�[�͂P�ɂ܂Ƃ߁A����p��WILD��ے�̃t���O�Ȃǂ�����
//
//------------------------------------------------------------------
// �������7���
// 
//	[__] �������������
//	[--] �������������		
//	[-_] �������u��		
//	[_-] �������u��		
//	[**] �ǂ̏�Ԃł�	
//	[*_] ���݂̂݉��������
//	[*-] ���݂̂ݗ��������
// 
//------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <map>
using namespace std;
#include "DebugLibrary.h"

#include "_GameKey.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _GameKeyCommand
	{
	public:
		//���͏��
		enum GAME_KEY_STATE
		{
			GAME_KEY_OFF,		// �������������
			GAME_KEY_ON,		// �������������
			GAME_KEY_PUSH,		// �������u��
			GAME_KEY_RELE,		// �������u��
			GAME_KEY_WILD,		// �ǂ̏�Ԃł�
			GAME_KEY_IS,		// ���݂̂݉��������
			GAME_KEY_NIS,		// ���݂̂ݗ��������
		};

		//���o�[���P�ɂ܂Ƃ߂�
		enum GAME_KEY_LVR_CMD
		{
			LVR_CMD_N = 0,	//���͂Ȃ�

			LVR_CMD_1 = 1,
			LVR_CMD_2 = 2,
			LVR_CMD_3 = 3,
			LVR_CMD_6 = 4,
			LVR_CMD_9 = 5,
			LVR_CMD_8 = 6,
			LVR_CMD_7 = 7,
			LVR_CMD_4 = 8,

			LVR_CMD_2E = 9,		//���v�f
			LVR_CMD_6E = 10,	//�E�v�f
			LVR_CMD_8E = 11,	//��v�f
			LVR_CMD_4E = 12,	//���v�f
		};

	private:
		//���o�[���
		GAME_KEY_STATE m_Lvr [ _GameKey::_LVR_NUM ];

		//���݃��o�[�C���f�b�N�X
		int IdLvr = 0;

		//�{�^�����
		GAME_KEY_STATE m_Btn [ _GameKey::_BTN_NUM ];

		//�ے�
		bool	m_bNot;

	public:
		_GameKeyCommand ();
		_GameKeyCommand ( const _GameKeyCommand & rhs );
		~_GameKeyCommand ();

		//��r
		//this�̏�Ԃ��`�F�b�N����R�}���h�����A�������v���C������
		//�����F�R�}���h���������ƂȂ�Q�[���L�[���, �L�����N�^����(�E��)
		//�ߒl�F�K��������true�A����ȊO��false
		bool CompareTarget ( _GameKey gameKeyData, bool dirRight ) const
		{
			return false;
		}

		bool CompareTarget ( _GameKey gameKeyData ) const;


		//���o�[(�����w��)
		void SetLvr ( UINT index, GAME_KEY_STATE state ) { m_Lvr[index] = state; }
		GAME_KEY_STATE GetLvr ( UINT index ) const { return m_Lvr[index]; }

		//���o�[(1����)
//		GAME_KEY_LVR_CMD GetKeyLvrCmd () const;
		bool IsKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const;
		bool PushKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const;


		//�{�^��
		void SetBtn ( UINT index, GAME_KEY_STATE state ) { m_Btn[index] = state; }
		GAME_KEY_STATE GetButton ( UINT index ) const { return m_Btn[index]; }

		//�ے�̃t���O
		void SetNot ( bool b ) { m_bNot = b; }
		bool GetNot () const { return m_bNot; }

	private:
		//�������p�֐�
		//Is == ( ���݉�����Ă����� ( ON || PUSH ) )
		bool Is ( _GameKey::GAME_KEY_LEVER lvr ) const;
		bool IsNeutral () const;
		bool Is2E () const;
		bool Is6E () const;
		bool Is8E () const;
		bool Is4E () const;
	};

	using V_GAME_KEY_CMD = vector < _GameKeyCommand >;


}	//namespace GAME


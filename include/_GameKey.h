//------------------------------------------------------------------
//	�Q�[�����̓L�[
//------------------------------------------------------------------
// ���Q�[�����C���ɂ�����1�t���[�����̃L�[���͏��(���o�[, �{�^��)
// ��8�������o�[(Lever)�A�{�^���S��(Button)��\��
// �����o�[�ʕ��������������ɑΉ�����
//
//------------------------------------------------------------------
//	�yLever�z
// [7] [8] [9]
//
// [4] [_] [6]
//				�yButton�z
// [1] [2] [3]	,[0], [1], [2], [3]
//------------------------------------------------------------------
//
// ���f�[�^�Ƃ��Č��݃t���[���A�O�t���[����������
// (..., -2, [-1, 0], 2, 3, ...)[F]
//


//------------------------------------------------------------------
//
// ���o�[�A�C�R���\������12369874(�e���L�[�\���łP���甽���v���)
// ���o�[�ɂ��u�Ԃ̏�Ԃ��L�q
//
// �w���͏�Ԃ����N���X�x�Ɓw�R�}���h�̂P�t���[�������̃N���X�x�𕪊�����
// �R�}���h�Ƃ��āu�ے�v�t���O���u�w��̃Q�[���L�[��ԂłȂ��Ȃ����Ƃ��v
//-------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <map>
using namespace std;
#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _GameKey
	{
	public:
		//�����L�[
		enum GAME_KEY_LEVER
		{
			LVR_1 = 0,
			LVR_2 = 1,
			LVR_3 = 2,
			LVR_6 = 3,
			LVR_9 = 4,
			LVR_8 = 5,
			LVR_7 = 6,
			LVR_4 = 7,
		};
		static const int LVR_NUM;
		enum _tagLvr { _LVR_NUM = 8 };

		//�{�^��
		static const int BTN_NUM = 4;
		enum _tagBtn { _BTN_NUM = 4 };

	private:
		bool Lvr [ _LVR_NUM ]	 = { false };	//���o�[���
		bool PreLvr [ _LVR_NUM ] = { false };	//�O���o�[���
		bool Btn [ _BTN_NUM ]	 = { false };	//�{�^�����
		bool PreBtn [ _BTN_NUM ] = { false };	//�O�{�^�����

	public:
		_GameKey ();
		_GameKey ( const _GameKey & rhs );
		~_GameKey ();

		//����̃L�[��O��ɕۑ�����
		void Update ();

		bool GetLvr ( UINT index ) { return Lvr[index]; }
		void SetLvr ( UINT index, bool b ) { Lvr[index] = b; }
		bool GetPreLvr ( UINT index ) { return PreLvr[index]; }
		void SetPreLvr ( UINT index, bool b ) { PreLvr[index] = b; }

		bool GetBtn ( UINT index ) { return Lvr[index]; }
		void SetBtn ( UINT index, bool b ) { Btn[index] = b; }
		bool GetPreBtn ( UINT index ) { return PreLvr[index]; }
		void SetPreBtn ( UINT index, bool b ) { PreBtn[index] = b; }
	};

	using V_GAME_KEY = vector < _GameKey >;


}	//namespace GAME


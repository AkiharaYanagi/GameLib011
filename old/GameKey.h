//=================================================================================================
//
// GameKey �w�b�_�t�@�C��
//
//	�Q�[�����C���ɂ�����1�t���[���̃L�[����
//�@8�����L�[�P�A�{�^���S��
//
//	�����L�[�̃R�}���h�w��ł�12369874���i�����v���j
//
//	7 8 9
//	4   6
//	1 2 3
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <iostream>
#include <map>
using namespace std;

#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GameKey
	{
	public:
		//�����L�[
		enum GAME_KEY_DIRECTION
		{
			NEUTRAL = 0,	//���͖�
			DIR_1 = 1,
			DIR_2 = 2,
			DIR_3 = 3,
			DIR_6 = 4,
			DIR_9 = 5,
			DIR_8 = 6,
			DIR_7 = 7,
			DIR_4 = 8,

			//�����v�f(Element)
			DIR_2E = 9,
			DIR_6E = 10,
			DIR_8E = 11,
			DIR_4E = 12,

			DIR_WILD = 13,		//�����Ƃ��ē��͂�v�����Ȃ�
			DIR_NUM = 14		//��
		};

		//Enum�����p�z��
		static const GAME_KEY_DIRECTION gameKeyDirection [ DIR_NUM ];

		//�{�^��
		static const UINT		GAME_KEY_BUTTON_NUM;	//4
		enum GAME_KEY_BUTTON
		{
			BTN_OFF = 0,		// ���͖�
			BTN_ON = 1,			// ���͗L
			BTN_WILD = 2		// �ǂ���ł�
		};

	private:
		GAME_KEY_DIRECTION		m_dir;
		GAME_KEY_BUTTON			m_button[4];

//#define	STR(var) #var	//�����ɂ����ϐ�����A�ϐ��������������񃊃e�����Ƃ��ĕԂ�((#)�������񉻉��Z�q)
		
		typedef map < tstring, GAME_KEY_DIRECTION > GAME_KEY_DIR_STR;
		typedef map < tstring, GAME_KEY_BUTTON > GAME_KEY_BTN_STR;

		//enum�ƕ������ϊ�����map
		static GAME_KEY_DIR_STR		m_mapDirection;
		static GAME_KEY_BTN_STR		m_mapButton;

		//�ے�̃t���O
		bool		m_not;

	public:
		GameKey ();
		GameKey ( const GameKey & rhs );		//�R�s�[��
		~GameKey ();

		//���
		GameKey & operator = ( const GameKey & rhs );

		//��r
//		bool operator == ( const GameKey& rhs );

		//��r	this	����
		//�����F	rhs		�R�}���h����
		//		bDirRight	����
		bool Compare ( const GameKey & rhs, bool bDirRight ) const;

		//�����L�[
		void SetDir ( GAME_KEY_DIRECTION dir ) { m_dir = dir; }
		GAME_KEY_DIRECTION GetDir () const { return m_dir; }

		//�{�^��
		void SetBtn ( UINT index, GAME_KEY_BUTTON button ) { m_button[index] = button; }
		GAME_KEY_BUTTON GetButton ( UINT index ) const { return m_button[index]; }

		//enum�ƕ�����̕ϊ�
		static GAME_KEY_DIRECTION DirFromStr ( tstring str ) { return m_mapDirection [ str ]; }
		static GAME_KEY_BUTTON BtnFromStr ( tstring str ) { return m_mapButton [ str ]; }

		//�ے�̃t���O
		void SetNot ( bool b ) { m_not = b; }
		bool GetNot () const { return m_not; }
	};


	using SP_GameKey = shared_ptr < GameKey >;
	using V_GAME_KEY = vector < GameKey >;

}	//namespace GAME



//-------------------------------------------------------------------------------------------------
//	�L�[�R���t�B�O�ݒ�t�@�C�����p�N���X
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "DxInput.h"
#include <fstream>

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�v���C�����Ƃ̎g�p�L�[
	enum INPUT
	{
		UP, 
		DOWN, 
		LEFT, 
		RIGHT, 
		BUTTON1, 
		BUTTON2, 
		BUTTON3, 
		BUTTON4,
		INPUT_NUM
	};

	//�Q�[���g�p�L�[
	enum KEY_NAME
	{
		P1_UP, 
		P1_DOWN, 
		P1_LEFT, 
		P1_RIGHT, 
		P1_BUTTON1, 
		P1_BUTTON2, 
		P1_BUTTON3, 
		P1_BUTTON4, 

		P2_UP, 
		P2_DOWN, 
		P2_LEFT, 
		P2_RIGHT, 
		P2_BUTTON1, 
		P2_BUTTON2, 
		P2_BUTTON3, 
		P2_BUTTON4, 

		KEY_NAME_NUM,	//�Q�[���g�p�L�[�̐�
	};

	//�v���C���Ɠ���
	static const KEY_NAME	PL_IP_KEY [ _PLAYER_NUM ][ INPUT_NUM ] = 
	{
		  { P1_UP, P1_DOWN, P1_LEFT, P1_RIGHT, P1_BUTTON1, P1_BUTTON2, P1_BUTTON3, P1_BUTTON4, }
		, { P2_UP, P2_DOWN, P2_LEFT, P2_RIGHT, P2_BUTTON1, P2_BUTTON2, P2_BUTTON3, P2_BUTTON4, }
	};

	//�f�o�C�X�L�[
	enum GAME_DEVICE_TYPE
	{
		KEYBOARD,
		JOYSTICK,
		NODEVICE,
	};

	//�L�[�ݒ�
	struct KEY_CONFIG
	{
		GAME_DEVICE_TYPE	m_type;		//�f�o�C�X�̎��
		int					m_num;		//�f�o�C�X�ԍ�
		int					m_key;		//�L�[�ԍ�
	};

	enum JOYSTICK_KEY
	{
        NUM_JOYSTICK_BUTTON = 128,					 //�W���C�X�e�B�b�N�̃{�^���̐�
        JOYSTICK_UP = NUM_JOYSTICK_BUTTON + 1,       //���o�[��
        JOYSTICK_DOWN = NUM_JOYSTICK_BUTTON + 2,     //���o�[��
        JOYSTICK_LEFT = NUM_JOYSTICK_BUTTON + 3,     //���o�[��
        JOYSTICK_RIGHT = NUM_JOYSTICK_BUTTON + 4,    //���o�[�E
        JOYSTICK_NEUTRAL = NUM_JOYSTICK_BUTTON + 5,    //������
	};


	//�L�[����
	class KeyInput
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using P_KeyInput = unique_ptr < KeyInput >;
		static P_KeyInput		m_inst;
		KeyInput();
		KeyInput( const KeyInput& rhs );
	public:
		~KeyInput();
		static void Create () { if ( ! m_inst ) { m_inst = P_KeyInput ( new KeyInput () ); } }
		static P_KeyInput & instance () { return m_inst; }
	//--------------------------------------------------

	private:
		//�L�[�R���t�B�O�f�[�^
		struct KEY_CONFIG		m_keyconfig[KEY_NAME_NUM];

	public:
		void Reset();	//�Đݒ�
		void Load();	//�f�[�^�̓Ǎ�
		void Update();	//�X�V

		//�Q�[���L�[
		bool IsKey ( KEY_NAME key );		//��������Ԃ��ǂ���(���̃t���[���̂�)
		bool OffKey ( KEY_NAME key )		//��������Ԃ��ǂ���(���̃t���[���̂�)
		{ return ( ! IsKey ( key ) ); }

		bool PushKey ( KEY_NAME key );		//�������u�Ԃ��ǂ���(�O��off ����on)
		bool ReleaseKey ( KEY_NAME key );	//�������u�Ԃ��ǂ���(�O��on ����off)

	};
	
//�V���O���g���A�N�Z�X�p
#define KEY_INPUT KeyInput::instance()
#define IS_KEY KeyInput::instance()->IsKey 
#define OFF_KEY KeyInput::instance()->OffKey 
#define PUSH_KEY KeyInput::instance()->PushKey 
#define RELE_KEY KeyInput::instance()->ReleaseKey 

}


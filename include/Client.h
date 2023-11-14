//=================================================================================================
//
// Client �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <thread>
#include <mutex>
#include "NetBase.h"
#include "NetCommon.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Client : public NetBase
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using P_Client = std::unique_ptr < Client >;
		static P_Client m_inst;
	public:
		Client ();
		Client ( const Client & rhs ) = delete;
		~Client ();
		static void Create () { if ( ! m_inst ) { m_inst = std::make_unique < Client > (); } }
		static P_Client & instance () { return m_inst; }
	//--------------------------------------------------

	//--------------------------------------------------
	//�X���b�h
	public:
		static void ThreadFunc ();		//�X���b�h�֐�
		void Start ( LPCSTR ip, int port );		//�X���b�h���J�n

		//���C������
		static void Wait ();
		static void Act ();

		//--------------------------------------------------

	//--------------------------------------------------
	//�l�b�g���[�N
	private:
		static SOCKET			m_sockConnect;		//�N���C�A���g�p�\�P�b�g
		static string	m_ip;		//IP
		static int		m_port;		//�|�[�g

		//IP�ƃ|�[�g�̐ݒ�
		static void _SetIp ( LPCSTR ip ) { LOCK; m_ip.assign ( ip ); }
		static void _SetPort ( int port ) { LOCK; m_port = port; }

	public:
	//--------------------------------------------------

	//--------------------------------------------------
	//���C��
	private:
		//���L������
	public:

		int Send ( LPCSTR msg );
		int Recv ( char* buf );
	};


//�V���O���g���A�N�Z�X�p
#define		CLIENT		Client::instance()
#define		CLIENT_SEND Client::instance()->Send
#define		CLIENT_RECV Client::instance()->Recv


}	//namespace GAME



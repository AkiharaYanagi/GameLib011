//=================================================================================================
//
// Server �w�b�_�t�@�C��
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

	class Server : public NetBase
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using P_Server = std::unique_ptr < Server >;
		static P_Server m_instance;
		Server ();
		Server ( const Server & rhs ) = delete;
	public:
		~Server ();
		static void Create () { if ( ! m_instance ) { m_instance = P_Server ( new Server () ); } }
		static P_Server & instance () { return m_instance; }
	//--------------------------------------------------

	//--------------------------------------------------
	//�X���b�h
	public:
		void Start ();
		void End ();

		static void ThreadFunc ();		//�X���b�h�֐�
		//���C������
		static void Wait ();	//�ڑ��ҋ@
		static void Act ();

	//---------------------------------------------

	//---------------------------------------------
	//�l�b�g���[�N
	private:

		//�T�[�o���\�P�b�g
		static SOCKET		m_sockListen;
		static SOCKET		m_sockAccept;

		//�t���O
		static bool			m_bLogin;
		static bool			m_bRead;

	public:

		static void SetLogin ( bool b ) { LOCK; m_bLogin = b; }
		static bool IsLogin () { LOCK; return m_bLogin; }

//		static void SetRead ( bool b ) { LOCK; m_bRead = b; }
//		static bool IsRead () { LOCK; return m_bRead; }

		//---------------------------------------------
		//���C��
	private:
		//���L������
		static ostringstream		m_oss;
		static bool			m_bInput;	//���̓t���O
		static NET_GAME_INPUT	m_netInput;	//�Q�[������
		static UINT			m_syncFrame;	//�t���[������

		//���C���X���b�h��������
		static tstring		m_nameMain;	//�N���C�A���g��

	public:

		int Send ( LPCSTR msg );
		int Recv ( char* buf );

		static void WriteName ( char* name );
		tstring & GetName () { return m_nameMain; }

	};


//�V���O���g���A�N�Z�X�p
#define		SERVER		Server::instance()
#define		SERVER_SEND Server::instance()->Send
#define		SERVER_RECV Server::instance()->Recv


}	//namespace GAME


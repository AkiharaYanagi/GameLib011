//=================================================================================================
//
// Network �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <memory>
using namespace std;
#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//����M�T�C�Y
	enum
	{
		SEND_SIZE = 256,
		RECV_SIZE = 256,
	};

	//�l�b�g���[�N
	class Network
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
		using P_Network = std::unique_ptr < Network >;
		static P_Network m_inst;
		Network ();
		Network ( const Network & rhs ) = delete;
	public:
		~Network ();
		static void Create () { if ( ! m_inst ) { m_inst = P_Network ( new Network () ); } }
		static P_Network & instance () { return m_inst; }
	//--------------------------------------------------

	private:
		//�T�[�o
		SOCKET			m_sockListen;
		SOCKET			m_sockAccept;
		sockaddr_in		m_sa_in;
		sockaddr_in		m_sa_inClient;
		//�N���C�A���g
		SOCKET			m_sockConnect;

	public:
		void Release ();

		void StartServer ( LPCSTR ip, int port );
		SOCKET CreateSocket ( LPCSTR ip, int port );
		SOCKET Accept ();


		void StartClient ( LPCSTR ip, int port );
		SOCKET CreateClientSocket ( LPCSTR ip, int port );
		int Connect ();


		int Send ( SOCKET sock, LPCSTR msg ) const;
		int Recv ( SOCKET scok, LPSTR buf );
	};

//�V���O���g���A�N�Z�X
#define NETWORK Network::instance()
#define SEND Network::instance()->Send
#define RECV Network::instance()->Recv

}	//namespace GAME



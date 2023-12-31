//=================================================================================================
//
// Network ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Network.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//Static実体
	//------------------------------------------------
	//シングルトン
	Network::P_Network	 Network::m_inst;

	//------------------------------------------------

	Network::Network ()
	{
		WSADATA wsaData;
		int retStartup = WSAStartup ( MAKEWORD ( 2, 0 ), & wsaData );
	}

	Network::~Network ()
	{
		Release ();
	}

	void Network::Release ()
	{
		closesocket ( m_sockAccept );
		closesocket ( m_sockListen );
		closesocket ( m_sockConnect );
		WSACleanup ();
	}

	int Network::Send ( SOCKET sock, LPCSTR msg ) const 
	{
		return send ( sock, msg, strlen ( msg ), 0 );
	}

	int Network::Recv ( SOCKET sock, LPSTR buf )
	{
		return recv ( sock, buf, RECV_SIZE, 0 );
	}


	//--------------------------------------------------------
	void Network::StartServer ( LPCSTR ip, int port )
	{
		m_sockListen = CreateSocket ( ip, port );
	}

	SOCKET Network::Accept ()
	{
#if 0
		//select用ファイルディスクリプタ
		fd_set	fds, readfds;
		FD_ZERO ( & readfds );
		FD_SET ( m_sockListen, & readfds );
		timeval tv = { 1, 0 };
		int retSelect = 0;

		int len = sizeof ( m_sa_inClient );

		while ( 1 )
		{
			//毎回の初期化
			memcpy ( & fds, & readfds, sizeof ( fd_set ) );

			//Selectでソケットの稼働チェック
			retSelect = ::select ( 0, & fds, NULL, NULL, & tv );
			if ( 0 == retSelect )
			{
				::Sleep ( 1 );
				if ( m_bPermi )
				{
					continue;
				}
				break;
			}

			//受信できるとき
			m_sockAccept = accept ( m_sockListen, (sockaddr*)& m_sa_inClient, & len );
			if ( INVALID_SOCKET == m_sockAccept )
			{
				Release ();
				return INVALID_SOCKET;
			}

		}
#endif // 0

		int len = sizeof ( m_sa_inClient );
		m_sockAccept = accept ( m_sockListen, (sockaddr*)& m_sa_inClient, &len );
		if ( INVALID_SOCKET == m_sockAccept )
		{
//			Release ();
			return INVALID_SOCKET;
		}
		return m_sockAccept;
	}

	SOCKET Network::CreateSocket ( LPCSTR ip, int port )
	{
		//ソケットの作成
		SOCKET retSock = socket ( AF_INET, SOCK_STREAM, 0 );	//受信ソケット
		if ( INVALID_SOCKET == retSock )
		{
			return NULL;
		}

		//ソケットの設定
		m_sa_in.sin_family = AF_INET;
		m_sa_in.sin_port = htons ( port );
		m_sa_in.sin_addr.S_un.S_addr = INADDR_ANY;

		//バインド
		//	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//
		//	Winsockのbindと、
		//	<functional> bind との混同を避けるため
		//	::bindで指定する
		//
		//	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		int nBind = ::bind ( retSock, (sockaddr *)& m_sa_in, sizeof ( m_sa_in ) );
		if ( SOCKET_ERROR == nBind )
		{
			int errBind = WSAGetLastError ();
		}
//		printf ( ("bind : %d = ntohs ( %d )\n"), ntohs ( addri.sin_port ), addri.sin_port );

		//ノンブロッキングモード設定
		int iBlc = 1;
		int retNonBlocking = ioctlsocket ( retSock, FIONBIO, (unsigned long *)& iBlc );
		if ( SOCKET_ERROR == retNonBlocking )
		{
//			printf ( ("ノンブロッキングモード：失敗\n") );
			return NULL;
		}

		//TCPクライアントからの接続要求を待てる状態にする
		int nListen = listen ( retSock, 5 );
		if ( SOCKET_ERROR == nListen )
		{
			int err = WSAGetLastError ();
//			printf ( ("SOCKET_ERROR %d: listen\n"), err);
			return NULL;
		}

		//内部保存
		m_sockListen = retSock;

		return retSock;
	}


	//--------------------------------------------------------
	void Network::StartClient ( LPCSTR ip, int port )
	{
		m_sockConnect = CreateClientSocket ( ip, port );
	}

	SOCKET Network::CreateClientSocket ( LPCSTR ip, int port )
	{
		//ソケットの作成
		SOCKET retSock = socket ( AF_INET, SOCK_STREAM, 0 );
		if ( INVALID_SOCKET == retSock )
		{
			return NULL;
		}

		//ソケットの設定
		m_sa_in.sin_family = AF_INET;
		m_sa_in.sin_port = htons ( port );
//		m_sa_in.sin_addr.S_un.S_addr = inet_addr ( "127.0.0.1" );
//		m_sa_in.sin_addr.S_un.S_addr = inet_addr ( ip );

		//multibyte文字からTCHAR(WCHAR)に変換
		size_t size = 1 + strlen ( ip );
		std::unique_ptr < TCHAR[] > tbuf = std::make_unique < TCHAR[] > ( size );		//バッファを確保
		size_t _PptNumOfCharConverted = 0;
		mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get(), size, ip, _TRUNCATE );
		
		//inet_addr()の代わりにInetPton()を使う
		InetPton ( m_sa_in.sin_family, tbuf.get(), & m_sa_in.sin_addr.S_un.S_addr );
//		InetPton ( m_sa_in.sin_family, _T("127.0.0.1"), & m_sa_in.sin_addr.S_un.S_addr );

		//ノンブロッキングモード設定
#if 0
		int nonBlockingFlag = 1;
		int retNonBlocking = ioctlsocket ( retSock, FIONBIO, (unsigned long *)& nonBlockingFlag );
		if ( SOCKET_ERROR == retNonBlocking )
		{
			return NULL;
		}
#endif // 0

		//内部保存
		m_sockConnect = retSock;

		return retSock;
	}

	int Network::Connect ()
	{
//		TRACE_F ( _T ( "■ Network::Connect\n" ) );
		int ret = ::connect ( m_sockConnect, (sockaddr*)& m_sa_in, sizeof ( m_sa_in ) );
		if ( SOCKET_ERROR == ret )
		{
			TRACE_F ( _T ( "■ SOCKET_ERROR\n" ) );
			int iError = WSAGetLastError ();
			TRACE_CHF ( ("## connect Error: %d\n"), WSAGetLastError () );
//			Release ();
		}
		if ( INVALID_SOCKET == m_sockConnect )
		{
			TRACE_F ( _T ( "■ INVALID_SOCKET\n" ) );
//			Release ();
		}
		return ret;
	}


}	//namespace GAME


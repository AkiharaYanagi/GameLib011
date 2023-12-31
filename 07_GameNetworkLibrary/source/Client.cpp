//=================================================================================================
//
// Client ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Client.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//Static実体
	//------------------------------------------------
	//シングルトン
	Client::P_Client	Client::m_inst;

	//ネットワーク
	SOCKET			Client::m_sockConnect;
	string			Client::m_ip;
	int				Client::m_port;

	//------------------------------------------------
	Client::Client ()
	{
	}

	Client::~Client ()
	{
		End ();
	}

	void Client::Start ( LPCSTR ip, int port )
	{
		_SetIp ( ip );
		_SetPort ( port );

//		NetBase::StartThread ( ThreadFunc );
	}

	int Client::Send ( LPCSTR msg )
	{
		int i = send ( m_sockConnect, msg, sizeof ( msg ), 0 );
//		DebugOutTrace::instance ()->DebugOutf ( _T ( "■ send = %d\n" ), i );
		return i;
	}

	int Client::Recv ( char* buf )
	{
		return recv ( m_sockConnect, buf, sizeof ( buf ), 0 );
	}

	//ネットワークスレッド
	void Client::ThreadFunc ()
	{
		OutputDebugString ( _T ( "■ Client::スレッド開始\n" ) );
		SetActive ( true );

		//許可状態なら繰返
		while ( GetPermi () )
		{
			//接続の状態で分岐
			switch ( GetState () )
			{
			case NS_START:				break;	//開始状態
			case NS_WAIT:	Wait ();	break;	//待機状態
			case NS_CONNECT:			break;
			case NS_ACT:	Act ();		break;
			case NS_DISCONNECT:			break;
			default:	break;
			}
		}

		SetActive ( false );
		OutputDebugString ( _T ( "■ Client::スレッド終了\n" ) );
	}


	void Client::Wait ()
	{
		m_sockConnect = Network::instance ()->CreateClientSocket ( m_ip.c_str(), m_port );
		TRACE_CHF (  ( "## m_sockConnect = %d\n" ), m_sockConnect );

		//接続
		int iConnect = 0;
		while ( GetPermi () )
		{
			iConnect = Network::instance ()->Connect ();
			if ( SOCKET_ERROR != iConnect )
			{
				TRACE_F ( _T ( "■ Connect \n" ) );
				break;
			}
			this_thread::sleep_for ( chrono::milliseconds ( 1 ) );
		}

		//サーバからの返信
		char buf [ RECV_SIZE ] = { 0 };
		int nRecv = Network::instance ()->Recv ( m_sockConnect, buf );
		if ( 0 > nRecv )
		{
			int iError = WSAGetLastError ();
			TRACE_CHF ( ("## Recv Error: %d\n"), iError );
		}
		else
		{
			TRACE_CHF (  ( "## Recv: [%d] %s \n" ), nRecv, buf );
		}

		//名前の転送
		int nSend = Network::instance ()->Send ( m_sockConnect, "name" );
		if ( 0 > nSend )
		{
			int iError = WSAGetLastError ();
			TRACE_CHF ( ("## Send Error: %d\n"), iError );
		}
		else
		{
			TRACE_CHF (  ( "## Send: [%d] \n" ), nSend );
		}

		SetState ( NS_ACT );
	}

	void Client::Act ()
	{
		char buf[RECV_SIZE] = { 0 };
		int iRecv = 0;

		UINT startTime = 0;
		UINT doTime = 0;
		int loop = 0;

		//受信ループ
		while ( GetPermi () )
		{
			startTime = ::timeGetTime ();

			::ZeroMemory ( buf, sizeof ( buf ) );
			iRecv = RECV ( m_sockConnect, buf );

			//受信が１未満
			if ( 1 > iRecv )
			{
				//データそのものがない場合
				if ( WSAEWOULDBLOCK == WSAGetLastError () )
				{
					//続行
				}
				//その他エラー
				else
				{
					SetState ( NS_DISCONNECT );
					break;
				}
			}
			//受信があった場合
			else
			{
				//入力を記録
				SetInput ( true );
				SetNetInput ( buf );
			}

			//sleepしてループ
			this_thread::sleep_for ( chrono::milliseconds ( 1 ) );
			
			if ( 100 < ++loop )
			{
				loop = 0;
				doTime = ::timeGetTime ();
				TRACE_F ( _T("%u[ms]\n"), doTime - startTime );

				NET_GAME_INPUT input = GetNetInput ();
				TRACE_F ( _T("Server : input.frame = %d, input.btIsKey = %d\n"), input.frame, input.btIsKey );
			}
		}
	}


}	//namespace GAME


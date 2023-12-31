//=================================================================================================
//
// Server ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Server.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//Static実体
	//------------------------------------------------
	//シングルトン
	Server::P_Server	Server::m_instance;
	
	//ネットワーク
	SOCKET	Server::m_sockListen;
	SOCKET	Server::m_sockAccept;

	//共有メモリ
	bool	Server::m_bLogin = false;
	bool	Server::m_bRead = false;
	tstring Server::m_nameMain;

	//------------------------------------------------


	//コンストラクタ
	Server::Server ()
	{
	}

	//デストラクタ
	Server::~Server ()
	{
		End ();
	}


	//スレッドをスタートさせる
	void Server::Start ()
	{
//		NetBase::StartThread ( ThreadFunc );
	}

	void Server::End ()
	{
		NetBase::End ();
	}

	int Server::Send ( LPCSTR msg )
	{
		int i = send ( m_sockAccept, msg, sizeof ( msg ), 0 );
//		DebugOutTrace::instance ()->DebugOutf ( _T ( "■ send = %d\n" ), i );
		return i;
	}

	int Server::Recv ( char* buf )
	{
		return recv ( m_sockAccept, buf, sizeof ( buf ), 0 );
	}

	//ネットワークスレッド
	void Server::ThreadFunc ()
	{
		OutputDebugString ( _T ( "■ スレッド開始\n" ) );
//		DBGOUT_FL_F ( _T("ネットワーク　サーバ　スレッド開始\n") );
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

			//1[ms]スリープしてから許可状態を確認
			this_thread::sleep_for ( chrono::milliseconds ( 1 ) );
		}

		SetActive ( false );
		OutputDebugString ( _T ( "■ スレッド終了\n" ) );
	}


	//接続待機開始
	void Server::Wait ()
	{
		m_sockListen = Network::instance ()->CreateSocket ( "", 12345 );	//INADDR_ANY
		
		//待受
		while ( GetPermi () )
		{
			m_sockAccept = Network::instance ()->Accept ();

			//アクセプトがあって、ソケットがINVALIDでないときループ脱出
			if ( INVALID_SOCKET != m_sockAccept )
			{
				//DBGOUT_FL_F ( _T("ネットワーク　accept ok.\n") );
				OutputDebugString ( _T ( "■ accept ok.\n" ) );
				break; 
			}

			this_thread::sleep_for ( chrono::milliseconds ( 1 ) );
		}

		//返信
		int iSend = Network::instance ()->Send ( m_sockAccept, "accept ok." );

		//名前の受信
		char buf [ RECV_SIZE ] = { 0 };
		while ( GetPermi () )
		{
			int iRecv = Network::instance ()->Recv ( m_sockAccept, buf );
			//接続ありのとき
			if ( 0 < iRecv )
			{
				WriteName ( buf );		//共有メモリに書込
				tstring tstr;
				tstr.assign ( SERVER->GetName() );
				//DBGOUT_FL_F ( _T("ネットワーク　%ls\n"), tstr.c_str() );
				SetLogin ( true );
				SetState ( NS_ACT );		//状態遷移
				break;
			}
			else	//接続エラー、切断のとき
			{
				SetState ( NS_DISCONNECT );
			}
			this_thread::sleep_for ( chrono::milliseconds ( 1 ) );
		}

		TRACE_CHF ( "## Recv : %s\n", buf );
	}


	void Server::Act ()
	{
		timeval		m_timeval;
		m_timeval.tv_sec = 1;
		m_timeval.tv_usec = 0;

		char buf[RECV_SIZE] = { 0 };
		int iRecv = 0;

		int loop = 0;	//ループ回数
		int nRecv = 0;	//受信回数

		//受信ループ
		while ( GetPermi () )
		{
			::ZeroMemory ( buf , sizeof ( buf ) );
  			iRecv = RECV ( m_sockAccept, buf );
			
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
				++nRecv;
			}

			//sleepしてループ
			this_thread::sleep_for ( chrono::milliseconds ( 1 ) );

			if ( 0 == ( loop % 1000 ) )
			{
				NET_GAME_INPUT input = GetNetInput ();
				TRACE_F ( _T("Server : loop = %d, nRecv = %d\n"), loop++, nRecv );
				TRACE_F ( _T("Server : input.frame = %d, input.btIsKey = %d\n"), input.frame, input.btIsKey );
			}
		}
	}


	void Server::WriteName ( char* name )
	{
		//charからTCHARに変換
		char str[RECV_SIZE];
		strcpy_s ( str, RECV_SIZE, name );
		std::unique_ptr < TCHAR[] > tstr = std::make_unique < TCHAR [] > ( RECV_SIZE );		//バッファを確保
		size_t size = 0;
		mbstowcs_s ( & size, tstr.get(), RECV_SIZE, str, _TRUNCATE );

		LOCK;
		m_nameMain.assign ( tstr.get() );
	}





}	//namespace GAME


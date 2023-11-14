//=================================================================================================
//
// Client ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <thread>
#include <mutex>
#include "NetBase.h"
#include "NetCommon.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Client : public NetBase
	{
	//--------------------------------------------------
	//シングルトンパターン
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
	//スレッド
	public:
		static void ThreadFunc ();		//スレッド関数
		void Start ( LPCSTR ip, int port );		//スレッドを開始

		//メイン分岐
		static void Wait ();
		static void Act ();

		//--------------------------------------------------

	//--------------------------------------------------
	//ネットワーク
	private:
		static SOCKET			m_sockConnect;		//クライアント用ソケット
		static string	m_ip;		//IP
		static int		m_port;		//ポート

		//IPとポートの設定
		static void _SetIp ( LPCSTR ip ) { LOCK; m_ip.assign ( ip ); }
		static void _SetPort ( int port ) { LOCK; m_port = port; }

	public:
	//--------------------------------------------------

	//--------------------------------------------------
	//メイン
	private:
		//共有メモリ
	public:

		int Send ( LPCSTR msg );
		int Recv ( char* buf );
	};


//シングルトンアクセス用
#define		CLIENT		Client::instance()
#define		CLIENT_SEND Client::instance()->Send
#define		CLIENT_RECV Client::instance()->Recv


}	//namespace GAME



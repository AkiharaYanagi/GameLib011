//=================================================================================================
//
// Server ヘッダファイル
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

	class Server : public NetBase
	{
	//--------------------------------------------------
	//シングルトンパターン
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
	//スレッド
	public:
		void Start ();
		void End ();

		static void ThreadFunc ();		//スレッド関数
		//メイン分岐
		static void Wait ();	//接続待機
		static void Act ();

	//---------------------------------------------

	//---------------------------------------------
	//ネットワーク
	private:

		//サーバ側ソケット
		static SOCKET		m_sockListen;
		static SOCKET		m_sockAccept;

		//フラグ
		static bool			m_bLogin;
		static bool			m_bRead;

	public:

		static void SetLogin ( bool b ) { LOCK; m_bLogin = b; }
		static bool IsLogin () { LOCK; return m_bLogin; }

//		static void SetRead ( bool b ) { LOCK; m_bRead = b; }
//		static bool IsRead () { LOCK; return m_bRead; }

		//---------------------------------------------
		//メイン
	private:
		//共有メモリ
		static ostringstream		m_oss;
		static bool			m_bInput;	//入力フラグ
		static NET_GAME_INPUT	m_netInput;	//ゲーム入力
		static UINT			m_syncFrame;	//フレーム同期

		//メインスレッド側メモリ
		static tstring		m_nameMain;	//クライアント名

	public:

		int Send ( LPCSTR msg );
		int Recv ( char* buf );

		static void WriteName ( char* name );
		tstring & GetName () { return m_nameMain; }

	};


//シングルトンアクセス用
#define		SERVER		Server::instance()
#define		SERVER_SEND Server::instance()->Send
#define		SERVER_RECV Server::instance()->Recv


}	//namespace GAME


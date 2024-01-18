//=================================================================================================
//
// NetBase ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <thread>
#include <mutex>
#include "Network.h"
#include "NetCommon.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//ロック
	static mutex	g_mtx;			//排他制御用ミューテックス
	#define LOCK	std::lock_guard < mutex > lock ( g_mtx )

	//接続状態
	enum NETWORK_STATE
	{
		NS_START,		//開始状態
		NS_WAIT,		//待機状態	
		NS_CONNECT,		//接続時	
		NS_ACT,			//メイン動作
		NS_DISCONNECT,	//切断時
		NS_SEND_ERROR,	//送信エラー
		NS_DRECV_ERROR,	//受信エラー
	};

	enum
	{
		FRAME_PER_SECOND = 60,
	};

	//ネットワーク基本
	class NetBase
	{
	//--------------------------------------------------
	//スレッド
	private:
		static thread		m_thread;		//スレッド
		static bool			m_bPermi;		//スレッド許可
		static bool			m_bActive;		//スレッド稼働状態

	public:
		NetBase ();
		NetBase ( const NetBase & rhs ) = delete;
		~NetBase ();

//		static void ThreadFunc ();		//スレッド関数
#if 0
		virtual void StartThread ( std::function < void () > threadFunc );		//スレッドを開始
#endif // 0
		virtual void End ();		//スレッドを終了

		//許可状態の取得と変更(ロック付)
		static const bool GetPermi () { LOCK; return m_bPermi; }
		static void SetPermi ( bool b ) { LOCK; m_bPermi = b; }

		//稼働状態の取得と変更(ロック付)
		static const bool GetActive () { LOCK; return m_bActive; }
		static void SetActive( bool b ) { LOCK; m_bActive = b; }
		//---------------------------------------------

		//---------------------------------------------
		//ネットワーク
	private:
		//通信状態
		static NETWORK_STATE	m_netwrokState;

	public:
		//状態の取得と変更
		static const NETWORK_STATE GetState () { LOCK; return m_netwrokState; }
		static void SetState ( NETWORK_STATE state ) { LOCK; m_netwrokState = state; }

		//---------------------------------------------
		//メイン
	private:
		//共有メモリ
		static bool			m_bInput;	//入力フラグ
		static NET_GAME_INPUT	m_netInput;	//ゲーム入力
		static UINT			m_myFrame;	//フレーム同期
		static UINT			m_netFrame;	//フレーム同期

		//メインスレッド側メモリ
		static tstring		m_nameMain;	//クライアント名

	public:

		//入力フラグ
		static bool GetInput () { LOCK; return m_bInput; }
		static void SetInput ( bool b ) { LOCK; m_bInput = b; }
		//ゲーム入力
		static NET_GAME_INPUT GetNetInput () { LOCK; return m_netInput; }
		static void SetNetInput ( char buf[] );

		//フレーム同期
		static void FrameAsyncWait ( UINT frame );
	};


}	//namespace GAME



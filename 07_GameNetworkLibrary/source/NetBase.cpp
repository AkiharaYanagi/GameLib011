//=================================================================================================
//
// NetBase ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "NetBase.h"
#include "NetInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//Static実体
	//------------------------------------------------
	//スレッド
	thread	NetBase::m_thread;
	bool	NetBase::m_bPermi = true;
	bool	NetBase::m_bActive = false;
	
	//ネットワーク
	NETWORK_STATE	NetBase::m_netwrokState = NETWORK_STATE::NS_START;

	//共有メモリ
	tstring NetBase::m_nameMain;
	bool	NetBase::m_bInput = false;
	NET_GAME_INPUT	NetBase::m_netInput;
	UINT	NetBase::m_myFrame = 0;

	//------------------------------------------------


	//コンストラクタ
	NetBase::NetBase ()
	{
	}

	//デストラクタ
	NetBase::~NetBase ()
	{
		End ();
	}

#if 0
	//スレッドをスタートさせる
	void NetBase::StartThread ( function < void () > threadFunc )
	{
		End ();

		//既に稼働していなければ
		if ( ! GetActive () )
		{
			SetPermi ( true );

			//待受スレッド開始
			std::thread th ( threadFunc );
			m_thread = ::move ( th );

#define THREAD_DETACH 0
#if THREAD_DETACH
			m_thread.detach ();
#endif // THREAD_DETACH

			//待機状態へ移行
			SetState ( NS_WAIT );
		}
	}
#endif // 0

	void NetBase::End ()
	{
		//スレッドを停止
		SetPermi ( false );

		//初期状態へ移行
		SetState ( NS_START );

#if ! THREAD_DETACH
		if ( m_thread.joinable () )
		{
			//スレッド終了まで待機
			m_thread.join ();
		}
#endif // THREAD_DETACH
	}


	void NetBase::FrameAsyncWait ( UINT frame )
	{
		//自プロセスのフレーム
		m_myFrame = frame;

		//ネットワーク接続先のフレーム
		UINT netFrame = GetNetInput().frame;

		//比較して自身が早いときSleep
		if ( m_myFrame > netFrame )
		{
			UINT sleepFame = m_myFrame - netFrame;
			long sleepMs = ( sleepFame * 1000 ) / FRAME_PER_SECOND;
			TRACE_F ( _T("NetBase::FrameAsyncWait  sleepMs = %d\n"), sleepMs );
			this_thread::sleep_for ( chrono::milliseconds ( sleepMs ) );
		}
	}

	void NetBase::SetNetInput ( char buf[] )
	{
		LOCK;
		m_netInput = NET_INPUT->DecodeNetInput ( buf );
	}

}	//namespace GAME


//=================================================================================================
//
//	ネットワークインプット　ヘッダ
//		ネットワークからの入力
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "StdAfx.h"
#include "NetInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//Static実体
	//------------------------------------------------
	//シングルトン
	NetInput::P_NetInput	NetInput::m_inst;

	//------------------------------------------------

	NetInput::NetInput ()
		: m_frame ( 0 )
	{
		//テスト
		NET_GAME_INPUT input;
		input.frame = 0x12345678;
		input.btIsKey = 0x01;
		input.btPushKey = 0xef;
		input.end = true;

		char buf[256] = { 0 };
		EncodeNetInput ( buf, input );
		NET_GAME_INPUT input2 = DecodeNetInput ( buf );

	}

	NetInput::~NetInput ()
	{
	}

	//------------------------------------------------------------------
	//入力の保存
	void NetInput::_SetInput ( PLAYER_ID playerNum, KEY_NAME keyName, int key )
	{
		//フレーム記録
		m_netInput[playerNum].frame = m_frame;

		//キーを押した状態
		if ( IS_KEY ( keyName ) )
		{ m_netInput[playerNum].btIsKey |= key; }

		//キーを押した瞬間(前フレーム:False, 現フレーム:true)
		if ( PUSH_KEY ( keyName ) )
		{ m_netInput[playerNum].btPushKey|= key; }
	}

	void NetInput::_SetInputCPU ( int percent, PLAYER_ID playerNum, KEY_NAME keyName, int key )
	{
		//フレーム記録
		m_netInput[playerNum].frame = m_frame;

		//キーを押した状態
		if ( 0 == rand () % percent )
		{ m_netInput[playerNum].btIsKey |= key; }

		//キーを押した瞬間(前フレーム:False, 現フレーム:true)
		if ( 0 == rand () % percent )
		{ m_netInput[playerNum].btPushKey|= key; }
	}

	//------------------------------------------------------------------
	//プレイヤ別 入力の保存
	void NetInput::_SetP1Input ()
	{
		_SetInput ( PLAYER_ID_1, P1_UP, 0x01 );
		_SetInput ( PLAYER_ID_1, P1_DOWN, 0x02 );
		_SetInput ( PLAYER_ID_1, P1_LEFT, 0x04 );
		_SetInput ( PLAYER_ID_1, P1_RIGHT, 0x08 );
		_SetInput ( PLAYER_ID_1, P1_BUTTON1, 0x10 );
		_SetInput ( PLAYER_ID_1, P1_BUTTON2, 0x20 );
		_SetInput ( PLAYER_ID_1, P1_BUTTON3, 0x40 );
		_SetInput ( PLAYER_ID_1, P1_BUTTON4, 0x80 );
	}

	void NetInput::_SetP2Input ()
	{
		_SetInput ( PLAYER_ID_2, P2_UP, 0x01 );
		_SetInput ( PLAYER_ID_2, P2_DOWN, 0x02 );
		_SetInput ( PLAYER_ID_2, P2_LEFT, 0x04 );
		_SetInput ( PLAYER_ID_2, P2_RIGHT, 0x08 );
		_SetInput ( PLAYER_ID_2, P2_BUTTON1, 0x10 );
		_SetInput ( PLAYER_ID_2, P2_BUTTON2, 0x20 );
		_SetInput ( PLAYER_ID_2, P2_BUTTON3, 0x40 );
		_SetInput ( PLAYER_ID_2, P2_BUTTON4, 0x80 );
	}


	void NetInput::_SetP1InputCPU ()
	{
		_SetInputCPU ( 90, PLAYER_ID_1, P1_UP, 0x01 );
		_SetInputCPU ( 30, PLAYER_ID_1, P1_DOWN, 0x02 );
		_SetInputCPU ( 60, PLAYER_ID_1, P1_LEFT, 0x04 );
		_SetInputCPU ( 60, PLAYER_ID_1, P1_RIGHT, 0x08 );
		_SetInputCPU ( 30, PLAYER_ID_1, P1_BUTTON1, 0x10 );
		_SetInputCPU ( 30, PLAYER_ID_1, P1_BUTTON2, 0x20 );
		_SetInputCPU ( 30, PLAYER_ID_1, P1_BUTTON3, 0x40 );
		_SetInputCPU ( 30, PLAYER_ID_1, P1_BUTTON4, 0x80 );
	}

	void NetInput::_SetP2InputCPU ()
	{
		_SetInputCPU ( 90, PLAYER_ID_2, P2_UP, 0x01 );
		_SetInputCPU ( 30, PLAYER_ID_2, P2_DOWN, 0x02 );
		_SetInputCPU ( 60, PLAYER_ID_2, P2_LEFT, 0x04 );
		_SetInputCPU ( 60, PLAYER_ID_2, P2_RIGHT, 0x08 );
		_SetInputCPU ( 30, PLAYER_ID_2, P2_BUTTON1, 0x10 );
		_SetInputCPU ( 30, PLAYER_ID_2, P2_BUTTON2, 0x20 );
		_SetInputCPU ( 30, PLAYER_ID_2, P2_BUTTON3, 0x40 );
		_SetInputCPU ( 30, PLAYER_ID_2, P2_BUTTON4, 0x80 );
	}

	//------------------------------------------------------------------
	//モード別入力の保存
	void NetInput::_Set_1P_2P ()
	{
		_SetP1Input ();
		_SetP2Input ();
	}

	void NetInput::_Set_1P_CPU ()
	{
		_SetP1Input ();
		_SetP2InputCPU ();
	}

	void NetInput::_Set_CPU_CPU ()
	{
		_SetP1InputCPU ();
		_SetP2InputCPU ();
	}

	void NetInput::_SetNetInputServer ()
	{
		//1P : 入力を保存
		_SetP1Input ();
		//サーバ(P1)からクライアント(P2)に送信
		SERVER_SEND ( (char *)& m_netInput[PLAYER_ID_1] );
		//->受信は別スレッドが行い、同期して反映する

		//2P : 受信 したデータを設定
		m_netInput[PLAYER_ID_2] = Server::GetNetInput ();
	}

	void NetInput::_SetNetInputClient ()
	{
		//1P : 受信したデータを設定
		m_netInput[PLAYER_ID_1] = Client::GetNetInput ();

		//2P : 入力を保存
		_SetP2Input ();
		//クライアント(P2)からサーバ(P1)に送信
		char buf [ SEND_SIZE ];
		EncodeNetInput ( buf, m_netInput[PLAYER_ID_2] );
		CLIENT_SEND ( buf );
		//->受信は別スレッドが行い、同期して反映する
	}
	//------------------------------------------------------------------


	void NetInput::KeyReset ()
	{
		m_netInput[PLAYER_ID_1].btIsKey = 0;
		m_netInput[PLAYER_ID_1].btPushKey = 0;
		m_netInput[PLAYER_ID_2].btIsKey = 0;
		m_netInput[PLAYER_ID_2].btPushKey = 0;
	}
	
	void NetInput::Store ( UINT frame )
	{
		m_frame = frame;
		KeyReset ();

		switch ( m_mode )
		{
		case SINGLE: _Set_1P_2P (); break;
		case DOUBLE_1P_CPU: _Set_1P_CPU (); break;
		case DOUBLE_1P_2P: _Set_1P_2P (); break;
		case DOUBLE_CPU_CPU: _Set_CPU_CPU (); break;

		case NETWORK_SERVER_1P: _SetNetInputServer (); break;
		case NETWORK_SERVER_2P: break;
		case NETWORK_CLIENT_1P: break;
		case NETWORK_CLIENT_2P: _SetNetInputClient (); break;
		default: break;
		}
	}

	void NetInput::EncodeNetInput ( char buf[SEND_SIZE], NET_GAME_INPUT netGameInput )
	{
		UINT index = 0;
		//(UINT) frame
		UINT tempUi = netGameInput.frame;
		int shift = 0;
		for ( UINT i = 0; i < 4; ++i )
		{
			UINT shift_ui = ( tempUi >> (8 * shift++) );
			UINT mask_ui = 0x000000ff & shift_ui;
			buf[index++] =  (char)mask_ui;
		}
		//(byte) IsKey
		buf[index++] = netGameInput.btIsKey;

		//(byte) pushKey
		buf[index++] = netGameInput.btPushKey;

		//(bool) end
		buf[index++] = (netGameInput.end) ? 1 : 0;
	}

	NET_GAME_INPUT	NetInput::DecodeNetInput ( char pByte[SEND_SIZE] )
	{
		NET_GAME_INPUT netGameInput;
		
		//byte単位でデコード
		UINT index = 0;
		UINT shift = 0;
		
		//(UINT) frame
		UINT ui = 0;
		for ( UINT i = 0; i < 4; ++i )
		{
			UINT mask_ui = 0x000000ff & pByte[index++];
			UINT shift_ui = mask_ui << ( 8 * shift++ );
			ui |= shift_ui;
		}

		netGameInput.frame = ui;
		netGameInput.btIsKey = pByte[index++];
		netGameInput.btPushKey = pByte[index++];
		netGameInput.end = ( 1 == pByte[index++] );

//		memcpy ( & m_netInput, buf, sizeof ( m_netInput ) );
		return netGameInput;
	}


	//------------------------------------------------------------------
	//ゲーム内利用：キーの状態
	bool NetInput::IsKey ( PLAYER_ID playerNum ,byte bt )
	{
		return m_netInput [ playerNum ].btIsKey & bt;
	}

	bool NetInput::IsKey ( KEY_NAME keyName )
	{
		bool bRet = false;
		switch ( keyName )
		{
		case P1_UP:		 bRet = IsKey ( PLAYER_ID_1, 0x01 ); break;
		case P1_DOWN:	 bRet = IsKey ( PLAYER_ID_1, 0x02 ); break;
		case P1_LEFT:	 bRet = IsKey ( PLAYER_ID_1, 0x04 ); break;
		case P1_RIGHT:	 bRet = IsKey ( PLAYER_ID_1, 0x08 ); break;
		case P1_BUTTON1: bRet = IsKey ( PLAYER_ID_1, 0x10 ); break;
		case P1_BUTTON2: bRet = IsKey ( PLAYER_ID_1, 0x20 ); break;
		case P1_BUTTON3: bRet = IsKey ( PLAYER_ID_1, 0x40 ); break;
		case P1_BUTTON4: bRet = IsKey ( PLAYER_ID_1, 0x80 ); break;

		case P2_UP:		 bRet = IsKey ( PLAYER_ID_2, 0x01 ); break;
		case P2_DOWN:	 bRet = IsKey ( PLAYER_ID_2, 0x02 ); break;
		case P2_LEFT:	 bRet = IsKey ( PLAYER_ID_2, 0x04 ); break;
		case P2_RIGHT:	 bRet = IsKey ( PLAYER_ID_2, 0x08 ); break;
		case P2_BUTTON1: bRet = IsKey ( PLAYER_ID_2, 0x10 ); break;
		case P2_BUTTON2: bRet = IsKey ( PLAYER_ID_2, 0x20 ); break;
		case P2_BUTTON3: bRet = IsKey ( PLAYER_ID_2, 0x40 ); break;
		case P2_BUTTON4: bRet = IsKey ( PLAYER_ID_2, 0x80 ); break;

		default: break;
		}
		return bRet;
	}

	bool NetInput::PushKey ( PLAYER_ID playerNum ,byte bt )
	{
		return m_netInput [ playerNum ].btPushKey & bt;
	}

	bool NetInput::PushKey ( KEY_NAME keyName )
	{
		bool bRet = false;
		switch ( keyName )
		{
		case P1_UP:		 bRet = PushKey ( PLAYER_ID_1, 0x01 ); break;
		case P1_DOWN:	 bRet = PushKey ( PLAYER_ID_1, 0x02 ); break;
		case P1_LEFT:	 bRet = PushKey ( PLAYER_ID_1, 0x04 ); break;
		case P1_RIGHT:	 bRet = PushKey ( PLAYER_ID_1, 0x08 ); break;
		case P1_BUTTON1: bRet = PushKey ( PLAYER_ID_1, 0x10 ); break;
		case P1_BUTTON2: bRet = PushKey ( PLAYER_ID_1, 0x20 ); break;
		case P1_BUTTON3: bRet = PushKey ( PLAYER_ID_1, 0x40 ); break;
		case P1_BUTTON4: bRet = PushKey ( PLAYER_ID_1, 0x80 ); break;

		case P2_UP:		 bRet = PushKey ( PLAYER_ID_2, 0x01 ); break;
		case P2_DOWN:	 bRet = PushKey ( PLAYER_ID_2, 0x02 ); break;
		case P2_LEFT:	 bRet = PushKey ( PLAYER_ID_2, 0x04 ); break;
		case P2_RIGHT:	 bRet = PushKey ( PLAYER_ID_2, 0x08 ); break;
		case P2_BUTTON1: bRet = PushKey ( PLAYER_ID_2, 0x10 ); break;
		case P2_BUTTON2: bRet = PushKey ( PLAYER_ID_2, 0x20 ); break;
		case P2_BUTTON3: bRet = PushKey ( PLAYER_ID_2, 0x40 ); break;
		case P2_BUTTON4: bRet = PushKey ( PLAYER_ID_2, 0x80 ); break;

		default: break;
		}
		return bRet;
	}

}	//namespace GAME


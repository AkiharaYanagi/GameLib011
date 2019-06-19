//=================================================================================================
//
//	ネットワークインプット　ヘッダ
//		ネットワークからの入力
//		エンコードとデコード
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "NetCommon.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class NetInput
	{
	//--------------------------------------------------
	//[シングルトンパターン]
	private:
		using P_NetInput = unique_ptr < NetInput >;
		static P_NetInput	m_inst;
		NetInput ();
		NetInput ( const NetInput & rhs ) = delete;
	public:
		~NetInput ();
		static void Create () { if ( ! m_inst ) { m_inst = P_NetInput ( new NetInput () ); } }
		static P_NetInput & instance () { return m_inst; }
	//--------------------------------------------------

	private:
		GAME_MODE	m_mode;
		UINT		m_frame;
		NET_GAME_INPUT	m_netInput [ _PLAYER_NUM ];

		//------------------------------------------------------------------
		//個別 入力の保存
		void _SetInput ( PLAYER_NUM playerNum, KEY_NAME keyName, int key );

		void _SetInputCPU ( int percent, PLAYER_NUM playerNum, KEY_NAME keyName, int key );
		//------------------------------------------------------------------
		//プレイヤ別 入力の保存
		void _SetP1Input ();
		void _SetP2Input ();

		void _SetP1InputCPU ();
		void _SetP2InputCPU ();
		//------------------------------------------------------------------
		//モード別 入力の保存
		void _Set_1P_2P ();
		void _Set_1P_CPU ();
		void _Set_CPU_CPU ();

		void _SetNetInputServer ();
		void _SetNetInputClient ();
		//------------------------------------------------------------------

	public:

		void SetMode ( GAME_MODE mode ) { m_mode = mode; }
		void KeyReset ();

		//入力の保存
		void Store ( UINT frame );

		//入力を送信用バイト列にエンコード
		void EncodeNetInput ( char pByte[ SEND_SIZE ], NET_GAME_INPUT netGameInput );

		//ネットワークから受信したバイト列をゲーム入力にデコード
		NET_GAME_INPUT DecodeNetInput ( char pByte[ SEND_SIZE ] );

		//------------------------------------------------------------------
		//ゲーム内利用：キーの状態
		bool IsKey ( PLAYER_NUM playerNum, byte bt );
		bool IsKey ( KEY_NAME keyName );
		bool PushKey ( PLAYER_NUM playerNum, byte bt );
		bool PushKey ( KEY_NAME keyName );
	};


	//シングルトンアクセス用
#define NET_INPUT NetInput::instance()
#define IS_NET_KEY NetInput::instance()->IsKey 
#define OFF_NET_KEY NetInput::instance()->OffKey 
#define PUSH_NET_KEY NetInput::instance()->PushKey 
#define RELE_NET_KEY NetInput::instance()->ReleaseKey 

//ネットワーク送信用ゲーム入力
using ByteKeyInput = byte;


}	//namespace GAME


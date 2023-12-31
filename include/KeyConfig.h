//=================================================================================================
//
//	キーコンフィグ
//		"ゲーム内で用いるキー" を "外部のデバイス入力" から変換する
//
//		・ジョイスティックにおけるAXISとPOVに対応する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "DxInput.h"
#include <fstream>
#include "KeyDefine.h"
#include "DeviceInput.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class KeyConfig
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_KeyConfig = std::unique_ptr < KeyConfig >;
		static P_KeyConfig		m_inst;
		KeyConfig ();
		KeyConfig ( const KeyConfig & rhs );
	public:
		~KeyConfig ();
		static void Create () { if ( ! m_inst ) { m_inst = P_KeyConfig ( new KeyConfig () ); } }
		static P_KeyConfig & instance () { return m_inst; }
	//--------------------------------------------------

	private:
		//デバイスインプット配列
		DeviceInput		m_deviceInput [ GAME_USE_KEY_NUM ];

	public:

		void Load ();

		bool IsKey ( GAME_USE_KEY key ) const;
		bool OffKey ( GAME_USE_KEY key ) const;
		bool PushKey ( GAME_USE_KEY key ) const;
		bool ReleKey ( GAME_USE_KEY key ) const;

	private:
		void SetInitial ();
		void Save ();

		bool IsJoy ( JoystickInput ji ) const;
		bool Is_Axis_Lvr ( DWORD ID, LEVER lvr ) const;
		bool Is_POV_Lvr ( DWORD ID, LEVER lvr ) const;
		bool Is_Keyboard ( DWORD key ) const;

		bool PushJoy ( JoystickInput ji ) const;
		bool Push_Axis_Lvr ( DWORD ID, LEVER lvr ) const;
		bool Push_POV_Lvr ( DWORD ID, LEVER lvr ) const;
		bool Push_Keyboard ( DWORD key ) const;
	};

//シングルトンアクセス用
#define CFG_IS_KEY KeyConfig::instance()->IsKey 
#define CFG_OFF_KEY KeyConfig::instance()->OffKey 
#define CFG_PUSH_KEY KeyConfig::instance()->PushKey 
#define CFG_RELE_KEY KeyConfig::instance()->ReleaseKey 

}	//namespace GAME


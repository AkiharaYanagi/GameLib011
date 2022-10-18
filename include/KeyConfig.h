//=================================================================================================
//
//	キーコンフィグ
//		"ゲーム内で用いるキー" を "外部のデバイス入力" から変換する
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
		using P_KeyConfig = unique_ptr < KeyConfig >;
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

	private:
		bool IsJoy ( JoystickInput ji ) const;
		bool IsKeyboard ( DWORD key ) const;
	};


}	//namespace GAME


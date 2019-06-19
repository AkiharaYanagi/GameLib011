//=================================================================================================
//
// ウィンドウハンドルの保持と取得
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include "DebugLibrary.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	class HWnd
	{
		static HWND			m_hWnd;		//ウィンドウハンドル

		//HWND取得コールバック関数
		static BOOL CALLBACK EnumWindowsProc ( HWND hWnd, LPARAM lParam );

	public:
		HWnd () = default;
		HWnd ( const HWnd & rhs ) = delete;
		~HWnd () = default;

		//ウィンドウ生成時の値を保存
		static void Set ( HWND hWnd ) { m_hWnd = hWnd; }

		//ウィンドウ生成時の値を取得
		static HWND Get() { return m_hWnd; }

		//WINDOWS_OS上のウィンドウを列挙し、現在プロセスと同一のハンドルを取得する
		static HWND _Get()
		{
			HWND hWnd = nullptr;
			EnumWindows ( EnumWindowsProc, reinterpret_cast<LPARAM>( &hWnd ) );
			return hWnd;
		}
	};

}	//namespace GAME


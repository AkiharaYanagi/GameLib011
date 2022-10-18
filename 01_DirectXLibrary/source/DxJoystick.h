//=================================================================================================
//
// Direct Input によるジョイスティックの管理　クラス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"
#include <dinput.h>		//DirectInput

#include "DebugManager.h"
#include "HWnd.h"

//-------------------------------------------------------------------------------------------------
// ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dinput8.lib")

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//定数宣言
	//------------------------------------------
	const int INPUT_DEVICE_NUM = 16;	//デバイスの最大数(Windowsでジョイスティックの扱える範囲)

	//--------------------------------------------------------
	// Direct Input によるジョイスティックの管理　クラス
	//--------------------------------------------------------
	class DxJoystick
	{
		LPDIRECTINPUT8			m_lpDI;			//DirectInputオブジェクト
		LPDIRECTINPUTDEVICE8	m_lpDIDevice[INPUT_DEVICE_NUM];		//列挙したデバイス
		DIDEVCAPS				m_diDevCaps[INPUT_DEVICE_NUM];		//ジョイスティックの能力

		DIJOYSTATE				m_dijs[INPUT_DEVICE_NUM];			//ジョイスティック状態
		DIJOYSTATE				m_preDijs[INPUT_DEVICE_NUM];		//直前のジョイスティック状態

		//DirectInput変数
		DWORD	m_dwJoyMaxCount;	//扱えるジョイスティックの最大数
		DWORD	m_dwJoyCount;		//ジョイスティックの識別(主にデバイス配列の添え字)

		//DirectInputコールバック関数
		static BOOL CALLBACK EnumJoystickCallback ( const DIDEVICEINSTANCE* lpddi, LPVOID lpContext );
		static BOOL CALLBACK EnumAxisCallback ( LPCDIDEVICEOBJECTINSTANCE lpddi, LPVOID lpvRef );

	public:
		DxJoystick();
		DxJoystick( const DxJoystick& rhs ) = delete;
		~DxJoystick();

		void Init( LPDIRECTINPUT8 lpDI );		//初期化
		void Rele();	//解放

		//指定したボタンが押されている状態か
		bool IsButton( int nDevice, int nButton );
		//指定したボタンが押された瞬間か
		bool PushButton( int nDevice, int nButton );
		//指定したボタンが離された瞬間か
		bool ReleaseButton( int nDevice, int nButton );

		//軸の状態を返す
		LONG GetJoyAxisX( int nDevice ) { return m_dijs[nDevice].lX; }
		LONG GetJoyAxisY( int nDevice ) { return m_dijs[nDevice].lY; }

		//POVの状態を返す( 上から 0, 9000, 18000, 27000 )
		DWORD GetPov ( int nDevice ) { return m_dijs [ nDevice ].rgdwPOV [ 0 ]; }
		bool IsPovUp	( int nDevice ) { return 0		== m_dijs [ nDevice ].rgdwPOV [ 0 ]; }
		bool IsPovRight	( int nDevice ) { return 9000	== m_dijs [ nDevice ].rgdwPOV [ 0 ]; }
		bool IsPovDown	( int nDevice ) { return 18000	== m_dijs [ nDevice ].rgdwPOV [ 0 ]; }
		bool IsPovLeft	( int nDevice ) { return 27000	== m_dijs [ nDevice ].rgdwPOV [ 0 ]; }

		//押した状態の判定
		bool IsJoyUp	( int nDevice ) { return ( m_dijs[nDevice].lY <= -500 ) ? true: false; }
		bool IsJoyDown	( int nDevice ) { return ( m_dijs[nDevice].lY >=  500 ) ? true: false; }
		bool IsJoyLeft	( int nDevice ) { return ( m_dijs[nDevice].lX <= -500 ) ? true: false; }
		bool IsJoyRight ( int nDevice ) { return ( m_dijs[nDevice].lX >=  500 ) ? true: false; }

		//前フレームの状態
		bool IsPreJoyUp		( int nDevice ) { return ( m_preDijs[nDevice].lY <= -500 ) ? true: false; }
		bool IsPreJoyDown	( int nDevice ) { return ( m_preDijs[nDevice].lY >=  500 ) ? true: false; }
		bool IsPreJoyLeft	( int nDevice ) { return ( m_preDijs[nDevice].lX <= -500 ) ? true: false; }
		bool IsPreJoyRight	( int nDevice ) { return ( m_preDijs[nDevice].lX >=  500 ) ? true: false; }

		//押した瞬間の判定(前回off 今回on)
		bool PushJoyUp	 ( int nDevice ) { return ( ! IsPreJoyUp(nDevice)    && IsJoyUp(nDevice)    ) ? true: false; }
		bool PushJoyDown ( int nDevice ) { return ( ! IsPreJoyDown(nDevice)  && IsJoyDown(nDevice)  ) ? true: false; }
		bool PushJoyLeft ( int nDevice ) { return ( ! IsPreJoyLeft(nDevice)  && IsJoyLeft(nDevice)  ) ? true: false; }
		bool PushJoyRight( int nDevice ) { return ( ! IsPreJoyRight(nDevice) && IsJoyRight(nDevice) ) ? true: false; }

		//離した瞬間の判定(前回on 今回off)
		bool ReleaseJoyUp   ( int nDevice ) { return ( IsPreJoyUp(nDevice)    && ! IsJoyUp(nDevice)    ) ? true: false; }
		bool ReleaseJoyDown ( int nDevice ) { return ( IsPreJoyDown(nDevice)  && ! IsJoyDown(nDevice)  ) ? true: false; }
		bool ReleaseJoyLeft ( int nDevice ) { return ( IsPreJoyLeft(nDevice)  && ! IsJoyLeft(nDevice)  ) ? true: false; }
		bool ReleaseJoyRight( int nDevice ) { return ( IsPreJoyRight(nDevice) && ! IsJoyRight(nDevice) ) ? true: false; }

		//	現在ジョイスティック数を返す関数
		DWORD GetJoyCount(void){ return m_dwJoyCount; }

		//ゲーム利用
		//状態の更新
		void Update();
	};


}	//namespace GAME


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
		bool IsButton( int id, int nButton );
		//指定したボタンが押された瞬間か
		bool PushButton( int id, int nButton );
		//指定したボタンが離された瞬間か
		bool ReleaseButton( int id, int nButton );

		//軸の状態を返す
		LONG GetJoyAxisX( int id ) { return m_dijs[id].lX; }
		LONG GetJoyAxisY( int id ) { return m_dijs[id].lY; }

		//POVの状態を返す( 上から 0, 9000, 18000, 27000 )
		//※斜めも単一の値を持つので範囲で指定する
		DWORD GetPov ( int id );
		bool IsPovUp	( int id );
		bool IsPovRight	( int id );
		bool IsPovDown	( int id );
		bool IsPovLeft	( int id );

		//Axis:押した状態の判定
		bool IsAxisUp	( int id ) 
		{ return ( m_dijs[id].lY <= -500 ) ? true: false; }
		bool IsAxisDown	( int id ) { return ( m_dijs[id].lY >=  500 ) ? true: false; }
		bool IsAxisLeft	( int id ) { return ( m_dijs[id].lX <= -500 ) ? true: false; }
		bool IsAxisRight ( int id ) { return ( m_dijs[id].lX >=  500 ) ? true: false; }

		//前フレームの状態
		bool IsPreAxisUp	( int id ) { return ( m_preDijs[id].lY <= -500 ) ? true: false; }
		bool IsPreAxisDown	( int id ) { return ( m_preDijs[id].lY >=  500 ) ? true: false; }
		bool IsPreAxisLeft	( int id ) { return ( m_preDijs[id].lX <= -500 ) ? true: false; }
		bool IsPreAxisRight	( int id ) { return ( m_preDijs[id].lX >=  500 ) ? true: false; }

		//押した瞬間の判定(前回off 今回on)
		bool PushAxisUp		( int id ) { return ( ! IsPreAxisUp(id)    && IsAxisUp(id)    ) ? true: false; }
		bool PushAxisDown	( int id ) { return ( ! IsPreAxisDown(id)  && IsAxisDown(id)  ) ? true: false; }
		bool PushAxisLeft	( int id ) { return ( ! IsPreAxisLeft(id)  && IsAxisLeft(id)  ) ? true: false; }
		bool PushAxisRight	( int id ) { return ( ! IsPreAxisRight(id) && IsAxisRight(id) ) ? true: false; }

		//離した瞬間の判定(前回on 今回off)
		bool ReleAxisUp   ( int id ) { return ( IsPreAxisUp(id)    && ! IsAxisUp(id)    ) ? true: false; }
		bool ReleAxisDown ( int id ) { return ( IsPreAxisDown(id)  && ! IsAxisDown(id)  ) ? true: false; }
		bool ReleAxisLeft ( int id ) { return ( IsPreAxisLeft(id)  && ! IsAxisLeft(id)  ) ? true: false; }
		bool ReleAxisRight( int id ) { return ( IsPreAxisRight(id) && ! IsAxisRight(id) ) ? true: false; }

		//	現在ジョイスティック数を返す関数
		DWORD GetJoyCount(void){ return m_dwJoyCount; }

		//ゲーム利用
		//状態の更新
		void Update();
	};


}	//namespace GAME


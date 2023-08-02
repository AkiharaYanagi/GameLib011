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
		DxJoystick ();
		DxJoystick ( const DxJoystick& rhs ) = delete;
		~DxJoystick ();

		void Init( LPDIRECTINPUT8 lpDI );		//初期化
		void Rele();	//解放


		//--------------------------------------------------------------
		//	現在ジョイスティック数を返す関数
		DWORD GetJoyCount () const { return m_dwJoyCount; }

		//ゲーム利用
		//状態の更新
		void Update ();


		//--------------------------------------------------------------
		//ボタン

		//指定したボタンが押されている状態か
		bool IsButton( int id, int nButton ) const;
		//指定したボタンが押された瞬間か
		bool PushButton( int id, int nButton ) const;
		//指定したボタンが離された瞬間か
		bool ReleaseButton( int id, int nButton ) const;


		//--------------------------------------------------------------
		//軸の状態を返す
		LONG GetJoyAxisX( int id ) const { return m_dijs[id].lX; }
		LONG GetJoyAxisY( int id ) const { return m_dijs[id].lY; }

		//Axis:押した状態の判定
		bool IsAxisUp	( int id ) const { return ( m_dijs[id].lY <= -500 ); }
		bool IsAxisDown	( int id ) const { return ( m_dijs[id].lY >=  500 ); }
		bool IsAxisLeft	( int id ) const { return ( m_dijs[id].lX <= -500 ); }
		bool IsAxisRight( int id ) const { return ( m_dijs[id].lX >=  500 ); }

		//前フレームの状態
		bool IsPreAxisUp	( int id ) const { return ( m_preDijs [ id ].lY <= -500 ); }
		bool IsPreAxisDown	( int id ) const { return ( m_preDijs [ id ].lY >=  500 ); }
		bool IsPreAxisLeft	( int id ) const { return ( m_preDijs [ id ].lX <= -500 ); }
		bool IsPreAxisRight	( int id ) const { return ( m_preDijs [ id ].lX >=  500 ); }

		//押した瞬間の判定(前回off 今回on)
		bool PushAxisUp		( int id ) const { return ( ! IsPreAxisUp(id)    && IsAxisUp(id)    ); }
		bool PushAxisDown	( int id ) const { return ( ! IsPreAxisDown(id)  && IsAxisDown(id)  ); }
		bool PushAxisLeft	( int id ) const { return ( ! IsPreAxisLeft(id)  && IsAxisLeft(id)  ); }
		bool PushAxisRight	( int id ) const { return ( ! IsPreAxisRight(id) && IsAxisRight(id) ); }

		//離した瞬間の判定(前回on 今回off)
		bool ReleAxisUp   ( int id ) const { return ( IsPreAxisUp(id)    && ! IsAxisUp(id)    ); }
		bool ReleAxisDown ( int id ) const { return ( IsPreAxisDown(id)  && ! IsAxisDown(id)  ); }
		bool ReleAxisLeft ( int id ) const { return ( IsPreAxisLeft(id)  && ! IsAxisLeft(id)  ); }
		bool ReleAxisRight( int id ) const { return ( IsPreAxisRight(id) && ! IsAxisRight(id) ); }

		//--------------------------------------------------------------
		//POVの状態を返す( 上から 0, 9000, 18000, 27000 )
		//※斜めも単一の値を持つので範囲で指定する

		DWORD GetPov		( int id ) const;

		//押した状態
		bool IsPovUp		( int id ) const;
		bool IsPovRight		( int id ) const;
		bool IsPovDown		( int id ) const;
		bool IsPovLeft		( int id ) const;

		//前フレームの状態
		bool IsPrePovUp		( int id ) const;
		bool IsPrePovRight	( int id ) const;
		bool IsPrePovDown	( int id ) const;
		bool IsPrePovLeft	( int id ) const;

		//押した瞬間の判定(前回off 今回on)
		bool PushPovUp		( int id ) const { return ( ! IsPrePovUp ( id )		&& IsPovUp ( id ) ); }
		bool PushPovRight	( int id ) const { return ( ! IsPrePovRight ( id )	&& IsPovRight ( id ) ); }
		bool PushPovDown	( int id ) const { return ( ! IsPrePovDown ( id )	&& IsPovDown ( id ) ); }
		bool PushPovLeft	( int id ) const { return ( ! IsPrePovLeft ( id )	&& IsPovLeft ( id ) ); }

		//離した瞬間の判定(前回on 今回off)
		bool RelePovUp		( int id ) const { return ( IsPrePovUp ( id ) && ! IsPovUp ( id ) ); }
		bool RelePovRight	( int id ) const { return ( IsPrePovRight ( id ) && ! IsPovRight ( id ) ); }
		bool RelePovDown	( int id ) const { return ( IsPrePovDown ( id ) && ! IsPovDown ( id ) ); }
		bool RelePovLeft	( int id ) const { return ( IsPrePovLeft ( id )	&& ! IsPovLeft ( id ) ); }

	};


}	//namespace GAME


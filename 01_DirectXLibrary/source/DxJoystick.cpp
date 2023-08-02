//=================================================================================================
//
// DirectInput ジョイスティック の実装
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DxJoystick.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DxJoystick::DxJoystick() : m_lpDI ( nullptr )
	{
	}

	DxJoystick::~DxJoystick()
	{
		Rele();
	}

	void DxJoystick::Init( LPDIRECTINPUT8 lpDI )
	{
		assert( lpDI );

		HRESULT hr;
		m_lpDI = lpDI;	//DirectInputオブジェクトの保存

		//メンバの初期化
		m_dwJoyMaxCount = INPUT_DEVICE_NUM;		//デバイスの最大数を取得
		m_dwJoyCount = 0;						//現在デバイス番号を初期化


		//初期化用
		DIJOYSTATE dijs = {0};

		for ( DWORD dw = 0; dw < INPUT_DEVICE_NUM; dw++ )
		{
			m_lpDIDevice[dw] = nullptr;	//ジョイスティックデバイスの初期化
			memcpy( &m_dijs[dw], &dijs, sizeof(DIJOYSTATE) );
			memcpy( &m_preDijs[dw], &dijs, sizeof(DIJOYSTATE) );
		}


		//デバイスを列挙して作成
		hr = lpDI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoystickCallback, (LPVOID)this, DIEDFL_ATTACHEDONLY );
		if ( FAILED(hr) )
		{
			DXTRACE_ERR( TEXT("DirectInputDevice8オブジェクトの作成に失敗"), hr);
			return;
		}

		//プロパティ初期値を設定（軸とバッファサイズで使用する）
		DIPROPDWORD diprop;
		ZeroMemory( &diprop, sizeof(diprop) );
		diprop.diph.dwSize			= sizeof(diprop);
		diprop.diph.dwHeaderSize	= sizeof(diprop.diph);
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;

		//ジョイスティック個別設定
		//(コールバック関数EnumJoystickCallbackにおいてm_dwJoyCountはデバイスの数になっている)
		for ( DWORD dw = 0; dw < m_dwJoyCount; dw++ )
		{
			//データ形式を設定
			hr = m_lpDIDevice[dw]->SetDataFormat( &c_dfDIJoystick );
			if ( FAILED(hr) )
			{
				DXTRACE_ERR(  TEXT("c_dfDIJoystick2形式の設定に失敗"), hr);
				return;
			}

			//モードを設定（フォアグラウンド＆非排他モード）
			hr = m_lpDIDevice[dw]->SetCooperativeLevel( HWnd::Get(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
			if( FAILED(hr) )
			{
				DXTRACE_ERR(  TEXT("フォアグラウンド＆非排他モードの設定に失敗"), hr);
				return;
			}

			//コールバック関数を使って各軸のモードを設定
			//軸モード初期値
			diprop.dwData = DIPROPAXISMODE_ABS;		//絶対値モード
//			diprop.dwData = DIPROPAXISMODE_REL;		//相対値モード
			hr = m_lpDIDevice[dw]->EnumObjects( EnumAxisCallback, (LPVOID)m_lpDIDevice[dw], DIDFT_AXIS );
			if( FAILED(hr) )
			{
				DXTRACE_ERR(  TEXT("軸モードの設定に失敗"), hr );
				return;
			}

			//プロパティの設定
			hr = m_lpDIDevice[dw]->SetProperty( DIPROP_BUFFERSIZE, &diprop.diph );
			if( FAILED(hr) )
			{
				DXTRACE_ERR(  TEXT("バッファサイズの設定に失敗"), hr );
				return;
			}

//			DXTRACE_MSG( TEXT("DirectInput: ジョイスティック　設定成功") );

			//入力制御開始
			m_lpDIDevice[dw]->Acquire();
		}
	}

	//ジョイスティック　コールバック関数
	//第一引数：デバイスハンドル
	//第二引数：(汎用ポインタ)→元オブジェクトのポインタ
	//戻値：続行……DIENUM_CONTINUE，終了……DIENUM_STOP
	BOOL CALLBACK DxJoystick::EnumJoystickCallback( const DIDEVICEINSTANCE* lpddi, LPVOID lpContext )
	{
		//引数から自身のthisポインタを得る
		DxJoystick* pDxJoystick = (DxJoystick*)lpContext;

		HRESULT hr;	//インターフェース戻値

		//列挙されたジョイスティックへのインターフェースを取得する
		hr = pDxJoystick->m_lpDI->CreateDevice(
				lpddi->guidInstance, 
				&pDxJoystick->m_lpDIDevice[pDxJoystick->m_dwJoyCount], 
				nullptr
		);
		if ( FAILED(hr) )
		{
			DXTRACE_ERR( TEXT("ジョイスティックの列挙に失敗"), hr );
			return DIENUM_CONTINUE;		//失敗したら続行
		}
		
		//ジョイスティック能力を調べる
		DWORD index = pDxJoystick->GetJoyCount();		//現在ジョイスティック数を取得

		pDxJoystick->m_diDevCaps[index].dwSize = sizeof(DIDEVCAPS);
		hr = pDxJoystick->m_lpDIDevice[index]->GetCapabilities( &pDxJoystick->m_diDevCaps[index] );
		if ( FAILED(hr) )
		{
			DXTRACE_ERR( TEXT("ジョイスティックの設定に失敗"), hr);
			RELEASE( pDxJoystick->m_lpDIDevice[index] );
			return DIENUM_CONTINUE;
		}

		//ジョイスティック数をインクリメントし、最大値になっていたらストップする
		if ( ++(pDxJoystick->m_dwJoyCount) == pDxJoystick->m_dwJoyMaxCount )
		{
			return DIENUM_STOP;
		}
		return DIENUM_CONTINUE;		//それ以外は続行
	}


	//ジョイスティックの軸を列挙する関数
	//第一引数：デバイスハンドル
	//第二引数：列挙されたデバイスオブジェクトのポインタ
	//戻値：続行……DIENUM_CONTINUE，終了……DIENUM_STOP
	BOOL CALLBACK DxJoystick::EnumAxisCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpRef )
	{
		//軸の範囲を設定(-1000～+1000)
		DIPROPRANGE diprg;
		ZeroMemory( &diprg, sizeof(diprg) );
		diprg.diph.dwSize		= sizeof(diprg);
		diprg.diph.dwHeaderSize	= sizeof(diprg.diph);
		diprg.diph.dwObj		= lpddoi->dwType;
		diprg.diph.dwHow		= DIPH_BYID;
		diprg.lMin				= -1000;
		diprg.lMax				= +1000;

		//デバイスの設定
		LPDIRECTINPUTDEVICE8 lpDevice = (LPDIRECTINPUTDEVICE8)lpRef;
		HRESULT hr;

		hr = lpDevice->SetProperty( DIPROP_RANGE, &diprg.diph );
		if( FAILED(hr) )
		{
			DXTRACE_ERR( TEXT("ジョイスティックの軸の設定に失敗"), hr);		
			return DIENUM_STOP;
		}

		return DIENUM_CONTINUE;
	}

	//解放
	void DxJoystick::Rele()
	{
		for( DWORD dw = 0; dw < m_dwJoyCount; dw++ )
		{
			if( m_lpDIDevice[dw] ) m_lpDIDevice[dw]->Unacquire();	//要求を解除
			RELEASE( m_lpDIDevice[dw] );	//解放
		}
	}

	//--------------------------------------------------------------------------
	//ゲーム利用
	//--------------------------------------------------------------------------

	//状態の更新
	void DxJoystick::Update()
	{
		//値の保存
		memcpy( &m_preDijs, &m_dijs, sizeof(DIJOYSTATE) * INPUT_DEVICE_NUM );

		for ( DWORD dw = 0; dw < m_dwJoyCount; dw++ )
		{
			if ( m_lpDIDevice[dw] != nullptr )
			{
				HRESULT hr = m_lpDIDevice[dw]->Poll();
				if ( FAILED(hr) )
				{
					if ( hr == DIERR_INPUTLOST )
					{
						m_lpDIDevice[dw]->Acquire();
					}
				}
				hr = m_lpDIDevice[dw]->GetDeviceState( sizeof(DIJOYSTATE), &m_dijs[dw] );
			}
		}
	}

	//--------------------------------------------------------------------------
	//	ボタン
	//--------------------------------------------------------------------------
	//指定したボタンが押されているか
	//引数： nDevice デバイス番号, nButton ボタン番号
	bool DxJoystick::IsButton( int nDevice, int nButton ) const
	{
		//指定デバイスが存在しないときfalseを返す
		if ( ! m_lpDIDevice[nDevice] ) return false;

		return ( m_dijs[nDevice].rgbButtons[ nButton ] & 0x80 ) ? true: false;
	}

	//指定したボタンが押された瞬間か
	//引数： nDevice デバイス番号, nButton ボタン番号
	bool DxJoystick::PushButton( int nDevice, int nButton ) const
	{
		//指定デバイスが存在しないときfalseを返す
		if ( ! m_lpDIDevice[nDevice] ) return false;

		//現在の状態が押されている　かつ　前の状態が押されていない
		return ( (m_dijs[nDevice].rgbButtons[ nButton ] & 0x80) && ! (m_preDijs[nDevice].rgbButtons[ nButton ] & 0x80) ) ? true: false;
	}

	//指定したボタンが離された瞬間か
	//引数： nDevice デバイス番号, nButton ボタン番号
	bool DxJoystick::ReleaseButton( int nDevice, int nButton ) const
	{
		//指定デバイスが存在しないときfalseを返す
		if ( ! m_lpDIDevice[nDevice] ) return false;

		//現在の状態が押されていない　かつ　前の状態が押されている
		return ( ! (m_dijs[nDevice].rgbButtons[ nButton ] & 0x80) && (m_preDijs[nDevice].rgbButtons[ nButton ] & 0x80) ) ? true: false;
	}


	//--------------------------------------------------------------------------
	//POV
	//--------------------------------------------------------------------------
	
	//POVの状態を返す( 上から 0, 9000, 18000, 27000 )
	//※斜めも単一の値を持つので範囲で指定する(0,4500,9000,13500,18000,22500,27000,31500)
	DWORD DxJoystick::GetPov ( int id ) const
	{ 
		return m_dijs [ id ].rgdwPOV [ 0 ]; 
	}

	//-----------------------------------------------
	bool DxJoystick::IsPovUp ( int id ) const
	{
		DWORD th = m_dijs [ id ].rgdwPOV [ 0 ];
		bool ret = ( 0 <= th && th <= 4500 ) || ( 31500 <= th && th <= 35999 );
		return ret;
	}

	bool DxJoystick::IsPovRight ( int id ) const
	{
		DWORD th = m_dijs [ id ].rgdwPOV [ 0 ];
		return ( 4500 <= th && th <= 13500 );
	}

	bool DxJoystick::IsPovDown ( int id ) const
	{
		DWORD th = m_dijs [ id ].rgdwPOV [ 0 ];
		return ( 13500 <= th && th <= 22500 );
	}

	bool DxJoystick::IsPovLeft ( int id )  const
	{
		DWORD th = m_dijs [ id ].rgdwPOV [ 0 ];
		return ( 22500 <= th && th <= 31500 );
	}

	//-----------------------------------------------
	bool DxJoystick::IsPrePovUp ( int id ) const
	{
		DWORD th = m_preDijs [ id ].rgdwPOV [ 0 ];
		bool ret = ( 0 <= th && th <= 4500 ) || ( 31500 <= th && th <= 35999 );
		return ret;
	}

	bool DxJoystick::IsPrePovRight ( int id ) const
	{
		DWORD th = m_preDijs [ id ].rgdwPOV [ 0 ];
		return ( 4500 <= th && th <= 13500 );
	}

	bool DxJoystick::IsPrePovDown ( int id ) const
	{
		DWORD th = m_preDijs [ id ].rgdwPOV [ 0 ];
		return ( 13500 <= th && th <= 22500 );
	}

	bool DxJoystick::IsPrePovLeft ( int id )  const
	{
		DWORD th = m_preDijs [ id ].rgdwPOV [ 0 ];
		return ( 22500 <= th && th <= 31500 );
	}


}	//namespace GAME



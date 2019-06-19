//=================================================================================================
//
// DirectInput	マウス
//
//=================================================================================================


//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DxMouse.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DxMouse::DxMouse() : m_lpDIMouse(nullptr)
	{
	}

	DxMouse::~DxMouse()
	{
		Rele ();
	}

	void DxMouse::Init( LPDIRECTINPUT8 lpDI )
	{
		assert ( lpDI );
		HRESULT hr;

		//デバイスの初期化
		hr = lpDI->CreateDevice ( GUID_SysMouse, &m_lpDIMouse, nullptr );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("マウスデバイスの作成に失敗") );
			return;
		}

		//データ形式を設定
		hr = m_lpDIMouse->SetDataFormat ( &c_dfDIMouse );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("マウス:データ形式の設定に失敗") );
			return;
		}

		//協調レベルを設定
		hr = m_lpDIMouse->SetCooperativeLevel ( HWnd::Get(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("マウス:フォアグラウンド、非排他モードの設定に失敗") );
			return;
		}

		//バッファリングデータの設定
		DIPROPDWORD diprop;
		diprop.diph.dwSize			= sizeof ( diprop );
		diprop.diph.dwHeaderSize	= sizeof ( diprop.diph );
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;
		diprop.dwData				= 100;
		hr = m_lpDIMouse->SetProperty ( DIPROP_BUFFERSIZE, &diprop.diph );
		if ( FAILED ( hr ) )
		{
			DXTRACE( hr, TEXT("バッファリングデータの設定に失敗") );
			return;
		}

//		DXTRACE_MSG ( TEXT("DirectInput: マウス設定成功") );

		//入力制御開始
		m_lpDIMouse->Acquire ();
	}

	void DxMouse::Rele()
	{
		if ( m_lpDIMouse )
		{
			m_lpDIMouse->Unacquire();	//要求を解除
			RELEASE( m_lpDIMouse );		//解放
		}
	}

	//--------------------------------------------------------------------------
	//ゲーム利用
	//--------------------------------------------------------------------------
	void DxMouse::Update()
	{
		if ( m_lpDIMouse == nullptr ) { return; }

		//前データの保存
		m_preMouseState.lX = m_mouseState.lX;
		m_preMouseState.lY = m_mouseState.lY;
		m_preMouseState.lZ = m_mouseState.lZ;
		m_preMouseState.rgbButtons[0] = m_mouseState.rgbButtons[0];
		m_preMouseState.rgbButtons[1] = m_mouseState.rgbButtons[1];
		m_preMouseState.rgbButtons[2] = m_mouseState.rgbButtons[2];
		m_preMouseState.rgbButtons[3] = m_mouseState.rgbButtons[3];

		//マウスの直接データを取得する
		HRESULT hr = m_lpDIMouse->GetDeviceState ( sizeof ( DIMOUSESTATE ), &m_mouseState );
		if ( hr == DIERR_INPUTLOST )	//アクセス権を失った場合
		{
			m_lpDIMouse->Acquire();	//再取得
		}
	}


}	//namespace GAME



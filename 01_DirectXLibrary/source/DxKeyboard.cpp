//=================================================================================================
//
// DirectInput キーボード の実装
//
//=================================================================================================

#include "DxKeyboard.h"


namespace GAME
{

	DxKeyboard::DxKeyboard() : m_lpDIKeyboard(nullptr)
	{
		for ( DWORD dw = 0; dw < DI_KEYBOARD; dw++ )
		{
			m_keyState[dw] = 0x00;
			m_preKeyState[dw] = 0x00;
		}
	}

	DxKeyboard::~DxKeyboard()
	{
		Rele ();
	}

	void DxKeyboard::Init( LPDIRECTINPUT8 lpDI )
	{
		assert ( lpDI );
		HRESULT hr;

		//デバイスの初期化
		hr = lpDI->CreateDevice ( GUID_SysKeyboard, &m_lpDIKeyboard, nullptr );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("キーボードデバイスの作成に失敗") );
			return;
		}

		//データ形式を設定
		hr = m_lpDIKeyboard->SetDataFormat ( &c_dfDIKeyboard );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("キーボード:データ形式の設定に失敗") );
			return;
		}

//		DXTRACE_MSG ( TEXT("DirectInput: キーボード設定成功") );

		//入力制御開始
		m_lpDIKeyboard->Acquire ();
	}

	void DxKeyboard::Rele()
	{
		if ( m_lpDIKeyboard )
		{
			m_lpDIKeyboard->Unacquire();	//要求を解除
			RELEASE( m_lpDIKeyboard );		//解放
		}
	}

	//指定したキーが押されているか
	bool DxKeyboard::IsKey( int nKey )
	{
		if ( m_lpDIKeyboard == nullptr ) return false;	//キーボードのない状態はfalseを返す

		//デバイスの直接データを取得する
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//キーが押されているか調べる
			if ( m_keyState[nKey] & 0x80 )	//key番目のキーが押されているかどうか
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//アクセス権を失った場合
		{
			m_lpDIKeyboard->Acquire ();		//アクセス権の再取得
		}

		return false;	//対象のキーが押された状態でないときはfalseを返す
	}


	//指定したキーが押された瞬間か
	bool DxKeyboard::PushKey( int nKey )
	{
		if ( m_lpDIKeyboard == nullptr ) return false;	//キーボードのない状態はfalseを返す

		//デバイスの直接データを取得する
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//キーが押されているか調べる
			if ( (m_keyState[nKey] & 0x80) && ( ! (m_preKeyState[nKey] & 0x80) ) )	//key番目のキーが押された瞬間かどうか
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//アクセス権を失った場合
		{
			m_lpDIKeyboard->Acquire ();		//アクセス権の再取得
		}

		return false;	//対象のキーが押された状態でないときはfalseを返す
	}

	//指定したキーが離された瞬間か
	bool DxKeyboard::ReleaseKey( int nKey )
	{
		if ( m_lpDIKeyboard == nullptr ) return false;	//キーボードのない状態はfalseを返す

		//デバイスの直接データを取得する
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//キーが押されているか調べる
			if ( ( ! (m_keyState[nKey] & 0x80) ) && (m_preKeyState[nKey] & 0x80) )	//key番目のキーが押された瞬間かどうか
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//アクセス権を失った場合
		{
			m_lpDIKeyboard->Acquire ();		//アクセス権の再取得
		}

		return false;	//対象のキーが押された状態でないときはfalseを返す
	}


	//--------------------------------------------------------------------------
	//ゲーム利用
	//--------------------------------------------------------------------------
	void DxKeyboard::Update()
	{
		if ( m_lpDIKeyboard )
		{
			for ( DWORD dw = 0; dw < DI_KEYBOARD; dw++ )
			{
				m_preKeyState[dw] = m_keyState[dw];	//以前の状態の記録
			}

			HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, m_keyState );
			if ( hr == DIERR_INPUTLOST )	//アクセス権を失った場合
			{
				m_lpDIKeyboard->Acquire();	//再取得
			}
		}
	}


}	//namespace GAME



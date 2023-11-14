//=================================================================================================
//
// DirectInput の実装
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DxInput.h"

//-------------------------------------------------------------------------------------------------
// ライブラリ内部のみで参照するヘッダファイル
//-------------------------------------------------------------------------------------------------
#include "DxJoystick.h"			//ジョイスティック
#include "DxKeyboard.h"			//キーボード
#include "DxMouse.h"			//マウス

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//	シングルトン　インスタンス
	//-------------------------------------------------------------------------------------------------
	DxInput::P_DxInput		DxInput::m_inst = nullptr;

	//-------------------------------------------------------------------------------------------------
	//	シングルトン　インスタンス生成
	//-------------------------------------------------------------------------------------------------
	void DxInput::Create ()
	{
		assert ( ! m_inst );
		if ( ! m_inst ) { m_inst = P_DxInput ( new DxInput () ); }
	}

	//-------------------------------------------------------------------------------------------------
	//	コンストラクタ
	//-------------------------------------------------------------------------------------------------
	DxInput::DxInput ()
		: m_lpDI ( nullptr ), m_joystick ( nullptr ), m_keyboard ( nullptr ), m_mouse ( nullptr )
	{
		m_joystick = std::make_unique < DxJoystick > ();
		m_keyboard = std::make_unique < DxKeyboard > ();
		m_mouse = std::make_unique < DxMouse > ();

		Init ();		//初期化
	}

	//-------------------------------------------------------------------------------------------------
	//	デストラクタ
	//-------------------------------------------------------------------------------------------------
	DxInput::~DxInput ()
	{
		Rele ();	//解放
	}


	//-------------------------------------------------------------------------------------------------
	//	DirectInput 初期化
	//-------------------------------------------------------------------------------------------------
	void DxInput::Init()
	{
		HRESULT hr;
		HINSTANCE hInstance = GetModuleHandle(nullptr);

		//DirectInputオブジェクトの作成
#if	0
		hr = DirectInput8Create (	hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, 
									reinterpret_cast<LPVOID*>(&m_lpDI), nullptr );
		DXTRACE_RETURN_FLASE( hr, TEXT("DirectInputオブジェクトの作成に失敗") );
#else
		::CoInitialize(nullptr);		//COMの初期化
		//COMオブジェクトとして生成するときCoInitialize(nullptr)を呼ぶ必要がある。終了時にはCoUninitialize()。
		hr = ::CoCreateInstance( CLSID_DirectInput8, nullptr, CLSCTX_ALL, IID_IDirectInput8,
									reinterpret_cast<LPVOID*>(&m_lpDI) );
		if ( FAILED(hr) ) DXTRACE( hr, TEXT("COMによるDirectInputオブジェクトの作成に失敗") );

		hr = m_lpDI->Initialize( hInstance, DIRECTINPUT_VERSION );
		if ( FAILED(hr) ) DXTRACE( hr, TEXT("DirectInputオブジェクトの初期化に失敗") );
#endif	//0

		m_joystick->Init ( m_lpDI );	//	ジョイスティック
		m_keyboard->Init ( m_lpDI );	//	キーボード
		m_mouse->Init ( m_lpDI );		//	マウス
	}

	//-------------------------------------------------------------------------------------------------
	//	DirectInput 解放
	//-------------------------------------------------------------------------------------------------
	void DxInput::Rele()
	{
		m_keyboard->Rele ();	//キーボード
		m_joystick->Rele ();	//ジョイスティック
		m_mouse->Rele ();		//マウス
		RELEASE ( m_lpDI );		//DirectInputの解放
		::CoUninitialize ();	//COMの解放
	}

	//-------------------------------------------------------------------------------------------------
	//	DirectInput 再設定
	//-------------------------------------------------------------------------------------------------
	void DxInput::Reset()
	{
		Rele();
		Init();
	}

	//-------------------------------------------------------------------------------------------------
	//	フレーム毎の更新
	//-------------------------------------------------------------------------------------------------
	void DxInput::Update()
	{
		m_keyboard->Update();		//キーボードデバイス
		m_joystick->Update();		//ジョイスティック
		m_mouse->Update();			//マウス
	}


	//---------------------------------------------------------------------------
	//	キーボード
	//---------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//	キーボードで押されている状態かどうかを取得する
	//	引数：key キーボードの配列定数
	//	戻値：対象のキーが押されている状態ならtrue, そうでなければfalse
	//-------------------------------------------------------------------------------------------------
	bool DxInput::IsOneKeyboard ( int key ) const
	{
		return m_keyboard->IsKey( key );
	}

	//-------------------------------------------------------------------------------------------------
	//	キーボードが押された瞬間かどうかを取得する (1フレーム前がfalse かつ 現在フレームがtrue)
	//	引数：key キーボードの配列定数
	//	戻値：対象のキーが押された瞬間ならtrue, そうでなければfalse
	//-------------------------------------------------------------------------------------------------
	bool DxInput::PushOneKeyboard ( int key ) const
	{
		return m_keyboard->PushKey( key );
	}

	//-------------------------------------------------------------------------------------------------
	//	キーボードが離された瞬間かどうかを取得する (1フレーム前がtrue かつ 現在フレームがfalse)
	//	引数：key キーボードの配列定数
	//	戻値：対象のキーが離された瞬間ならtrue, そうでなければfalse
	//-------------------------------------------------------------------------------------------------
	bool DxInput::ReleaseOneKeyboard ( int key ) const
	{
		return m_keyboard->ReleaseKey( key );
	}


	//---------------------------------------------------------------------------
	//	ジョイスティック
	//---------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//	ジョイスティック(キー)で押されている状態かどうかを取得する
	//	引数：num デバイス番号, key キー番号
	//-------------------------------------------------------------------------------------------------
	bool DxInput::IsJoyButton( int num, int btn ) const
	{
		return m_joystick->IsButton( num, btn );
	}
	//ジョイスティック(Axis)で押されている状態かどうかを取得する
	bool DxInput::IsAxisUp( int nDevice ) const { return m_joystick->IsAxisUp(nDevice); }
	bool DxInput::IsAxisDown( int nDevice ) const { return m_joystick->IsAxisDown(nDevice); }
	bool DxInput::IsAxisLeft( int nDevice ) const { return m_joystick->IsAxisLeft(nDevice); }
	bool DxInput::IsAxisRight( int nDevice ) const { return m_joystick->IsAxisRight(nDevice); }

	//ジョイスティック(POV)の状態を返す
	DWORD DxInput::GetPov ( int id ) const { return m_joystick->GetPov ( id ); }
	bool DxInput::IsPovUp ( int nDevice ) const { return m_joystick->IsPovUp ( nDevice ); }
	bool DxInput::IsPovRight ( int nDevice ) const { return m_joystick->IsPovRight ( nDevice ); }
	bool DxInput::IsPovDown ( int nDevice ) const { return m_joystick->IsPovDown ( nDevice ); }
	bool DxInput::IsPovLeft ( int nDevice ) const { return m_joystick->IsPovLeft ( nDevice ); }


	//-------------------------------------------------------------------------------------------------
	//	ジョイスティック(キー)で押された瞬間かどうかを取得する
	//	引数：num デバイス番号, key キー番号
	//-------------------------------------------------------------------------------------------------
	bool DxInput::PushJoyButton( int num, int btn ) const
	{
		return m_joystick->PushButton( num, btn );
	}
	//ジョイスティック(Axis)で押された瞬間かどうかを取得する
	bool DxInput::PushAxisUp( int nDevice ) const { return m_joystick->PushAxisUp(nDevice); }
	bool DxInput::PushAxisDown( int nDevice ) const { return m_joystick->PushAxisDown(nDevice); }
	bool DxInput::PushAxisLeft( int nDevice ) const { return m_joystick->PushAxisLeft(nDevice); }
	bool DxInput::PushAxisRight( int nDevice ) const { return m_joystick->PushAxisRight(nDevice); }

	//ジョイスティック(POV)で押された瞬間かどうかを取得する
	bool DxInput::PushPovUp ( int nDevice ) const { return m_joystick->PushPovUp ( nDevice ); }
	bool DxInput::PushPovRight ( int nDevice ) const { return m_joystick->PushPovRight ( nDevice ); }
	bool DxInput::PushPovDown ( int nDevice ) const { return m_joystick->PushPovDown ( nDevice ); }
	bool DxInput::PushPovLeft ( int nDevice ) const { return m_joystick->PushPovLeft ( nDevice ); }


	//-------------------------------------------------------------------------------------------------
	//	ジョイスティック(キー)で離された瞬間かどうかを取得する
	//	引数：num デバイス番号, key キー番号
	//-------------------------------------------------------------------------------------------------
	bool DxInput::ReleaseJoyButton( int num, int btn ) const
	{
		return m_joystick->ReleaseButton( num, btn );
	}
	//	ジョイスティック(Axis)で離された瞬間かどうかを取得する
	bool DxInput::ReleaseAxisUp( int nDevice ) const { return m_joystick->ReleAxisUp(nDevice); }
	bool DxInput::ReleaseAxisDown( int nDevice ) const { return m_joystick->ReleAxisDown(nDevice); }
	bool DxInput::ReleaseAxisLeft( int nDevice ) const { return m_joystick->ReleAxisLeft(nDevice); }
	bool DxInput::ReleaseAxisRight( int nDevice ) const { return m_joystick->ReleAxisRight(nDevice); }

	//ジョイスティック(POV)で離された瞬間かどうかを取得する
	bool DxInput::RelePovUp ( int nDevice ) const { return m_joystick->RelePovUp ( nDevice ); }
	bool DxInput::RelePovRight ( int nDevice ) const { return m_joystick->RelePovRight ( nDevice ); }
	bool DxInput::RelePovDown ( int nDevice ) const { return m_joystick->RelePovDown ( nDevice ); }
	bool DxInput::RelePovLeft ( int nDevice ) const { return m_joystick->RelePovLeft ( nDevice ); }


	//軸の状態を返す
	LONG DxInput::GetJoyAxisX( int nDevice ) const { return m_joystick->GetJoyAxisX( nDevice ); }
	LONG DxInput::GetJoyAxisY( int nDevice ) const { return m_joystick->GetJoyAxisY( nDevice ); }


	//---------------------------------------------------------------------------
	//	マウス
	//---------------------------------------------------------------------------
	bool DxInput::IsMouseButton ( MOUSE_BUTTON n ) const
	{
		return m_mouse->IsButton ( n ); 
	}

	bool DxInput::UpMouseButton ( MOUSE_BUTTON n ) const
	{
		return m_mouse->UpButton ( n ); 
	}

	POINT DxInput::GetMouseDelta () const
	{
		return m_mouse->GetMouseDelta (); 
	}

	POINT DxInput::GetMousePoint () const
	{
		//マウス位置の取得
		POINT cursorPt;
		::GetCursorPos ( &cursorPt );
		::ScreenToClient ( HWnd::Get(), &cursorPt );
		return cursorPt; 
	}

	bool DxInput::IsMouseInside ( LONG x, LONG y, LONG w, LONG h ) const
	{
		//マウス位置の取得
		POINT cursorPt = GetMousePoint ();
		if (	x <= cursorPt.x 
			&&	cursorPt.x <= x + w
			&&	y <= cursorPt.y 
			&&	cursorPt.y <= y + h )
		{
			return true;
		}
		return false; 
	}


}	//namespace GAME


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
//		m_inst = new DxInput;
//		if ( ! m_inst ) { m_inst = make_unique < DxInput > (); }
		if ( ! m_inst ) { m_inst = P_DxInput ( new DxInput () ); }
	}
#if 0


	//-------------------------------------------------------------------------------------------------
	//	シングルトン　インスタンス破棄
	//-------------------------------------------------------------------------------------------------
	void DxInput::Destroy ()
	{
//		if ( m_inst ) { delete m_inst; }
//		m_inst = nullptr;
		m_inst.reset ();
	}
#endif // 0


	//-------------------------------------------------------------------------------------------------
	//	コンストラクタ
	//-------------------------------------------------------------------------------------------------
	DxInput::DxInput ()
		: m_lpDI ( nullptr ), m_joystick ( nullptr ), m_keyboard ( nullptr ), m_mouse ( nullptr )
	{
		m_joystick = make_unique < DxJoystick > ();
		m_keyboard = make_unique < DxKeyboard > ();
		m_mouse = make_unique < DxMouse > ();

		Init ();		//初期化
	}

	//-------------------------------------------------------------------------------------------------
	//	デストラクタ
	//-------------------------------------------------------------------------------------------------
	DxInput::~DxInput ()
	{
		Rele ();	//解放
#if 0
		if ( m_joystick ) { delete m_joystick; }
		m_joystick = nullptr;
		if ( m_keyboard ) { delete m_keyboard; }
		m_keyboard = nullptr;
		if ( m_mouse ) { delete m_mouse; }
		m_mouse = nullptr;
#endif // 0
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
	bool DxInput::IsOneJoystick( int num, int key ) const
	{
		return m_joystick->IsJoyKey( num, key );
	}
	//	ジョイスティック(XY)で押されている状態かどうかを取得する
	bool DxInput::IsJoyUp( int nDevice ) const { return m_joystick->IsJoyUp(nDevice); }
	bool DxInput::IsJoyDown( int nDevice ) const { return m_joystick->IsJoyDown(nDevice); }
	bool DxInput::IsJoyLeft( int nDevice ) const { return m_joystick->IsJoyLeft(nDevice); }
	bool DxInput::IsJoyRight( int nDevice ) const { return m_joystick->IsJoyRight(nDevice); }


	//-------------------------------------------------------------------------------------------------
	//	ジョイスティック(キー)で押された瞬間かどうかを取得する
	//	引数：num デバイス番号, key キー番号
	//-------------------------------------------------------------------------------------------------
	bool DxInput::PushOneJoystick( int num, int key ) const
	{
		return m_joystick->PushJoyKey( num, key );
	}
	//	ジョイスティック(XY)で押された瞬間かどうかを取得する
	bool DxInput::PushJoyUp( int nDevice ) const { return m_joystick->PushJoyUp(nDevice); }
	bool DxInput::PushJoyDown( int nDevice ) const { return m_joystick->PushJoyDown(nDevice); }
	bool DxInput::PushJoyLeft( int nDevice ) const { return m_joystick->PushJoyLeft(nDevice); }
	bool DxInput::PushJoyRight( int nDevice ) const { return m_joystick->PushJoyRight(nDevice); }


	//-------------------------------------------------------------------------------------------------
	//	ジョイスティック(キー)で離された瞬間かどうかを取得する
	//	引数：num デバイス番号, key キー番号
	//-------------------------------------------------------------------------------------------------
	bool DxInput::ReleaseOneJoystick( int num, int key ) const
	{
		return m_joystick->ReleaseJoyKey( num, key );
	}
	//	ジョイスティック(XY)で離された瞬間かどうかを取得する
	bool DxInput::ReleaseJoyUp( int nDevice ) const { return m_joystick->ReleaseJoyUp(nDevice); }
	bool DxInput::ReleaseJoyDown( int nDevice ) const { return m_joystick->ReleaseJoyDown(nDevice); }
	bool DxInput::ReleaseJoyLeft( int nDevice ) const { return m_joystick->ReleaseJoyLeft(nDevice); }
	bool DxInput::ReleaseJoyRight( int nDevice ) const { return m_joystick->ReleaseJoyRight(nDevice); }


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


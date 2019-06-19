//=================================================================================================
//
// DirectInput の管理クラス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"	//DirectX共通
#include <dinput.h>				//DirectInput


//-------------------------------------------------------------------------------------------------
// ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	//-------------------------------------------------------------------------------------------------
	//ライブラリ内クラス宣言
	//-------------------------------------------------------------------------------------------------
	class DxJoystick;
	class DxKeyboard;
	class DxMouse;


	//------------------------------------------
	//Direct Input の管理クラス
	//------------------------------------------
	class DxInput
	{
		//シングルトン　パターン
		static DxInput*			m_instance;
		DxInput ();
		DxInput ( const DxInput& obj );
		~DxInput ();

		LPDIRECTINPUT8		m_lpDI;			//DirectInputオブジェクト
		DxJoystick*			m_joystick;		//ジョイスティック監理
		DxKeyboard*			m_keyboard;		//キーボード監理
		DxMouse*			m_mouse;		//マウス監理


	public:
		static void Create ();
		static void Destroy ();
		static DxInput* instance () { return m_instance; }

		void Init ();
		void Rele ();
		void Reset ();
		void Update ();		//フレーム毎の更新

		//---------------------------------------------------------------------------
		//	キーボード
		//---------------------------------------------------------------------------
		//	キーボードで押されている状態かどうかを取得する
		//	引数：key キーボードの配列定数
		bool IsOneKeyboard ( int key ) const;

		//	キーボードで押された瞬間かどうかを取得する
		//	引数：key キーボードの配列定数
		bool PushOneKeyboard ( int key ) const;

		//	キーボードで離された瞬間かどうかを取得する
		//	引数：key キーボードの配列定数
		bool ReleaseOneKeyboard ( int key ) const;

		//---------------------------------------------------------------------------
		//	ジョイスティック
		//---------------------------------------------------------------------------
		//	ジョイスティックで押されている状態かどうかを取得する
		//	引数：num デバイス番号, key キー番号
		bool IsOneJoystick ( int num, int key ) const;
		bool IsJoyUp( int nDevice ) const;
		bool IsJoyDown( int nDevice ) const; 
		bool IsJoyLeft( int nDevice ) const;
		bool IsJoyRight( int nDevice ) const;

		//	ジョイスティックで押された瞬間かどうかを取得する
		//	引数：num デバイス番号, key キー番号
		bool PushOneJoystick ( int num, int key ) const;
		bool PushJoyUp( int nDevice ) const;
		bool PushJoyDown( int nDevice ) const;
		bool PushJoyLeft( int nDevice ) const;
		bool PushJoyRight( int nDevice ) const;

		//	ジョイスティックで押された瞬間かどうかを取得する
		//	引数：num デバイス番号, key キー番号
		bool ReleaseOneJoystick ( int num, int key ) const;
		bool ReleaseJoyUp( int nDevice ) const;
		bool ReleaseJoyDown( int nDevice ) const;
		bool ReleaseJoyLeft( int nDevice ) const;
		bool ReleaseJoyRight( int nDevice ) const;

		//軸の状態を返す
		LONG GetJoyAxisX( int nDevice ) const;
		LONG GetJoyAxisY( int nDevice ) const;

		//---------------------------------------------------------------------------
		//	マウス
		//---------------------------------------------------------------------------
		//マウスボタン定数
		enum MOUSE_BUTTON
		{
			MOUSE_LEFT = 0,
			MOUSE_RIGHT = 1,
			MOUSE_CENTER = 2,
		};
		//ボタンを押した状態かどうか
		//	0: LBUTTON, 1: RBUTTON, 2: ホイールクリック
		bool IsMouseButton ( MOUSE_BUTTON n ) const;
		
		//いずれかのキーが押されている状態から離されたかどうか
		//	0: LBUTTON, 1: RBUTTON, 2: ホイールクリック
		bool UpMouseButton ( MOUSE_BUTTON n ) const;

		//マウスの移動量を取得
		POINT GetMouseDelta () const;

		//マウスのクライアントウィンドウ内の位置を取得
		POINT GetMousePoint () const;

		//対象の枠内にマウス位置があるかどうか
		bool IsMouseInside ( LONG x, LONG y, LONG w, LONG h ) const;
	};


}	//namespace GAME


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
#include <dinput.h>			//DirectInput

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
	using P_DxJoystick = std::unique_ptr < DxJoystick >;
	class DxKeyboard;
	using P_DxKeyboard = std::unique_ptr < DxKeyboard >;
	class DxMouse;
	using P_DxMouse = std::unique_ptr < DxMouse >;

	//------------------------------------------
	//Direct Input の管理クラス
	//------------------------------------------
	class DxInput
	{
	//---------------------------------------------------------------------
	//シングルトン　パターン
	private:
		using P_DxInput = std::unique_ptr < DxInput >;	//ポインタ型定義
		static P_DxInput	m_inst;		//シングルトンインスタンス(実体は.cppで定義)
		DxInput ();		//private コンストラクタで通常の実体化は禁止
	public:
		~DxInput ();		//デストラクタはstd::unique_ptrのためpublic
		static void Create ();
		static P_DxInput& instance () { return m_inst; }
	//---------------------------------------------------------------------

	private:
		LPDIRECTINPUT8		m_lpDI;			//DirectInputオブジェクト

		P_DxJoystick		m_joystick;		//ジョイスティック監理
		P_DxKeyboard		m_keyboard;		//キーボード監理
		P_DxMouse			m_mouse;		//マウス監理

	public:

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
		//	引数：num デバイス番号, btn キー番号
		bool IsJoyButton ( int num, int btn ) const;

		bool IsAxisUp( int nDevice ) const;
		bool IsAxisDown( int nDevice ) const; 
		bool IsAxisLeft( int nDevice ) const;
		bool IsAxisRight( int nDevice ) const;

		bool IsPovUp ( int nDevice ) const;
		bool IsPovRight ( int nDevice ) const;
		bool IsPovDown ( int nDevice ) const;
		bool IsPovLeft ( int nDevice ) const;

		//	ジョイスティックで押された瞬間かどうかを取得する
		//	引数：num デバイス番号, btn キー番号
		bool PushJoyButton ( int num, int btn ) const;

		bool PushAxisUp( int nDevice ) const;
		bool PushAxisDown( int nDevice ) const;
		bool PushAxisLeft( int nDevice ) const;
		bool PushAxisRight( int nDevice ) const;

		bool PushPovUp ( int nDevice ) const;
		bool PushPovRight ( int nDevice ) const;
		bool PushPovDown ( int nDevice ) const;
		bool PushPovLeft ( int nDevice ) const;

		//	ジョイスティックで離された瞬間かどうかを取得する
		//	引数：num デバイス番号, btn キー番号
		bool ReleaseJoyButton ( int num, int btn ) const;

		bool ReleaseAxisUp( int nDevice ) const;
		bool ReleaseAxisDown( int nDevice ) const;
		bool ReleaseAxisLeft( int nDevice ) const;
		bool ReleaseAxisRight( int nDevice ) const;

		bool RelePovUp ( int nDevice ) const;
		bool RelePovRight ( int nDevice ) const;
		bool RelePovDown ( int nDevice ) const;
		bool RelePovLeft ( int nDevice ) const;

		//軸の状態を返す
		LONG GetJoyAxisX( int nDevice ) const;
		LONG GetJoyAxisY( int nDevice ) const;

		//POVの状態を返す
		DWORD GetPov ( int id ) const;

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
		bool UpMouseLeft () { return UpMouseButton ( MOUSE_LEFT ); }
		bool UpMouseRight () { return UpMouseButton ( MOUSE_RIGHT ); }
		bool UpMouseCenter () { return UpMouseButton ( MOUSE_CENTER ); }

		//マウスの移動量を取得
		POINT GetMouseDelta () const;

		//マウスのクライアントウィンドウ内の位置を取得
		POINT GetMousePoint () const;

		//対象の枠内にマウス位置があるかどうか
		bool IsMouseInside ( LONG x, LONG y, LONG w, LONG h ) const;
	};


//シングルトンアクセス
#define DXINP DxInput::instance()
#define DXINP_UpMouseLeft DxInput::instance()->UpMouseLeft
#define DXINP_UpMouseRight DxInput::instance()->UpMouseRight
#define DXINP_UpMouseCenter DxInput::instance()->UpMouseCenter

}	//namespace GAME


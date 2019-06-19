//=================================================================================================
//
// Direct Input によるキーボードの管理　クラス
//
//=================================================================================================


#ifndef		__DXKEYBOARD_HEADER_INCLUDE__
#define		__DXKEYBOARD_HEADER_INCLUDE__


//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"
#include <dinput.h>		//DirectInput
#include "DebugManager.h"


//-------------------------------------------------------------------------------------------------
// ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dinput8.lib")


namespace GAME
{
	//------------------------------------------
	//定数宣言
	//------------------------------------------
	const int DI_KEYBOARD = 256;			//キーボード配列数


	class DxKeyboard
	{
		LPDIRECTINPUTDEVICE8	m_lpDIKeyboard;		//キーボードデバイス

		//キーボードの状態保存
		BYTE	m_keyState[DI_KEYBOARD];
		BYTE	m_preKeyState[DI_KEYBOARD];

	public:
		DxKeyboard();
		DxKeyboard( const DxKeyboard& rhs );
		~DxKeyboard();

		void Init( LPDIRECTINPUT8 lpDI );		//初期化
		void Rele();	//解放
		
		//指定したキーが押されているか
		bool IsKey( int nKey );
		//指定したキーが押された瞬間か
		bool PushKey( int nKey );
		//指定したキーが離された瞬間か
		bool ReleaseKey( int nKey );

		//ゲーム利用
		//状態の更新
		void Update();
	};


}	//namespace GAME


#endif	//__DXKEYBOARD_HEADER_INCLUDE__


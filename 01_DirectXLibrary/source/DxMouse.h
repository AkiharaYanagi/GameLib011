//=================================================================================================
//
// Direct Input によるマウスの管理　クラス
//
//=================================================================================================


#ifndef		__DXMOUSE_HEADER_INCLUDE__
#define		__DXMOUSE_HEADER_INCLUDE__


//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
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
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DxMouse
	{
		LPDIRECTINPUTDEVICE8	m_lpDIMouse;		//マウスデバイス

		//直接データ
		DIMOUSESTATE			m_mouseState;
		DIMOUSESTATE			m_preMouseState;	//一つ前のデータ

	public:
		DxMouse();
		DxMouse( const DxMouse& rhs );
		~DxMouse();

		void Init( LPDIRECTINPUT8 lpDI );		//初期化
		void Rele();	//解放

		//いずれかのキーが押されている状態かどうか
		//	0: LBUTTON, 1: RBUTTON, 2: ホイールクリック
		bool IsButton ( UINT n ) const
		{
			assert ( n < 4 );
			return ( m_mouseState.rgbButtons[n] & 0x80 ) ? true: false; 
		}

		//いずれかのキーが押されている状態から離されたかどうか
		//	0: LBUTTON, 1: RBUTTON, 2: ホイールクリック
		bool UpButton ( UINT n ) const
		{
			assert ( n < 4 );
			return (	! (m_mouseState.rgbButtons[n] & 0x80)
					&&	(m_preMouseState.rgbButtons[n] & 0x80) ) ? true: false; 
		}

		//マウスの移動量を取得
		POINT GetMouseDelta () const 
		{
			POINT pt = { m_mouseState.lX, m_mouseState.lY };
			return pt;
		}

		//ゲーム利用
		//状態の更新
		void Update();
	};


}	//namespace GAME


#endif	//__DXMOUSE_HEADER_INCLUDE__


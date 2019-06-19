//=================================================================================================
//
// DirectXを扱うライブラリ内でのみ用いる共通定義ファイル
//
//=================================================================================================
#pragma once

//DirectInputのバージョン定数(DirectInputのヘッダより先に宣言)
#define DIRECTINPUT_VERSION 0x0800

//-------------------------------------------------------------------------------------------------
// ヘッダファイル インクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <assert.h>

//DirectX
#include <DxErr.h>
#include <d3dx9math.h>

//-------------------------------------------------------------------------------------------------
// ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "DxErr.lib")

namespace GAME 
{

//-------------------------------------------------------------------------------------------------
//マクロ
//-------------------------------------------------------------------------------------------------
//DirectX用エラーTRACE
#define		DXTRACE(hr,str)						{ DXTrace(__FILE__, __LINE__, hr, str, false); }
#define		DXTRACE_RETURN_FLASE(hr,str)		{ if( FAILED(hr) ) { DXTrace(__FILE__, __LINE__, hr, str, false); return false; } }
#define		DXTRACE_THROW(hr,str)				{ DXTrace(__FILE__, __LINE__, hr, str, false); throw str; } 
#define		FAILED_THROW(hr)					{ if( FAILED(hr) ) { throw hr; } }
#define		FAILED_DXTRACE_THROW(hr,str)		{ if( FAILED(hr) ) { DXTrace(__FILE__, __LINE__, hr, TEXT("エラーによるthrow"), false); throw str; } } 

//インターフェース解放
#define		RELEASE(x)							if(x){x->Release();x=nullptr;}

//ポインタ解放
#define		SAFE_RELEASE(x)	{ if ( x ) { delete x; x = nullptr; } }
#define		SAFE_RELEASE_ARREY(x)	{ if ( x ) { delete[] x; x = nullptr; } }


}	//namespace GAME


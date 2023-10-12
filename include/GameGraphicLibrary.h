//=================================================================================================
//
// ゲームオブジェクト　利用ヘッダ
//
//		外部からライブラリを用いるときにインクルードするヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphicConst.h"
#include "GameTexture.h"
#include "GameGraphic.h"
#include "GamePrimitive.h"
#include "GameGraphicList.h"
#include "PrimitiveTexture.h"
#include "OutlineFont.h"
#include "Fade.h"
#include "GrpStr.h"

//-------------------------------------------------------------------------------------------------
//	ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#if	_DEBUG
#pragma comment (lib, "04_GameGraphicLibrary_debug.lib")
#else
#pragma comment (lib, "04_GameGraphicLibrary.lib")
#endif	//_DEBUG


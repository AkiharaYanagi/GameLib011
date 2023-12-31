//=================================================================================================
//
// ゲームライブラリ　外部利用ヘッダ
//
//	 外部からライブラリを用いるときにインクルードするヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#if	_DEBUG
#pragma comment (lib, "08_GameLibrary_debug.lib")
#else
#pragma comment (lib, "08_GameLibrary.lib")
#endif	//_DEBUG

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "_GameKey.h"
#include "_GameKeyCommand.h"
#include "GameInput.h"
#include "FadeRect.h"
#include "GrpEf.h"
#include "GrpDemo.h"
#include "GrpBlink.h"
#include "GrpStr.h"
#include "Timer.h"
#include "HoldTimer.h"
#include "CursorUtl.h"
#include "ClrUtl.h"
#include "Menu.h"


﻿//=================================================================================================
//
// デバッグライブラリ　外部利用ヘッダ
//		デバッグテキストファイル(log.txt)出力
//		IDEデバッグ出力
//		シングルトンパターンを用いてグローバルからオブジェクトにアクセスする
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//ライブラリ　リンク
//-------------------------------------------------------------------------------------------------
#if	_DEBUG
#pragma comment (lib, "00_DebugLibrary_debug.lib")
#else
#pragma comment (lib, "00_DebugLibrary.lib")
#endif	//_DEBUG

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "GameLibConst.h"
#include "DebugManager.h"
#include "Format.h"
#include "STR_UTL.h"
#include "WND_UTL.h"


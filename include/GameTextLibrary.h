﻿//=================================================================================================
//
// ゲームテキストライブラリ　外部利用ヘッダ
//		外部からライブラリを用いるときにインクルードするヘッダファイル
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameText.h"
#include "GameTextFile.h"
#include "OutlineFont.h"


//-------------------------------------------------------------------------------------------------
//	ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#if	_DEBUG
#pragma comment (lib, "05_GameTextLibrary_debug.lib")
#else
#pragma comment (lib, "05_GameTextLibrary.lib")
#endif	//_DEBUG


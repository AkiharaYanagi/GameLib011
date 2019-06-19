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
#include "GameKey.h"
#include "Fade.h"
#include "GrpEf.h"
#include "GrpDemo.h"


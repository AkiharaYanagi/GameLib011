﻿//=================================================================================================
//
// DirectXの管理　外部利用のための共通インクルード
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#if	_DEBUG
#pragma comment (lib, "01_DirectxLibrary_debug.lib")
#else
#pragma comment (lib, "01_DirectxLibrary.lib")
#endif	//_DEBUG

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "DxDefine.h"
#include "Dx3D.h"
#include "DxVertex.h"
#include "DxInput.h"
#include "DxSound.h"
#include "Dx_UTL.h"


//----------------------------------
//	プリコンパイル済みヘッダファイル
//----------------------------------

//ライブラリプロジェクトでは用いない
//末端のプロジェクトのみ用いる

//プロジェクトのプロパティ
//"構成プロパティ" -> "C/C++" -> ""プリコンパイル済みヘッダーの作成/使用"
//で指定する

//	ディレクトリ構造に関係なく、
//	#include "stdafx.h"
//	(大文字小文字も関係ない "StdAfx.h"でも通る)

#include <winsock2.h>
#include <windows.h>

//デバッグ情報　メモリリーク検出
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <vector>
#include <list>
#include <map>
#include <set>

#include "Game.h"


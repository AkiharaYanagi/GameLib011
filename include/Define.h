//=================================================================================================
//
// デファインヘッダ
//　		GameLib用共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
#include <WinSock2.h>	//<windows.h>よりも前に宣言する
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <memory>


//=============================================
//
//@info	using namespace std; を止め、	std::宣言を付ける
//	どうしても付けるときは ヘッダ.h ではなく ソース.cppに付ける
//
//=============================================

//using namespace std;


//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	// unsigned int
	//-------------------------------------------------------------------------------------------------
	using UINT = unsigned __int32;
	using UINT64 = unsigned __int64;

	typedef struct USIZE
	{
	public:
		USIZE () { w = 0; h = 0; }
		USIZE ( UINT w0, UINT h0 ) { w = w0; h = h0; }
		UINT w;
		UINT h;
	} USIZE;

	using V_UINT = std::vector < UINT >;

	//-------------------------------------------------------------------------------------------------
	// TCAHR対応
	//-------------------------------------------------------------------------------------------------
	using tstring =			std::basic_string< TCHAR >;
	using tistream =		std::basic_istream< TCHAR >;
	using tostream =		std::basic_ostream< TCHAR >;
	using tfstream =		std::basic_fstream< TCHAR >;
	using tifstream =		std::basic_ifstream< TCHAR >;
	using tofstream =		std::basic_ofstream< TCHAR >;
	using tistringstream =	std::basic_istringstream< TCHAR >;
	using tostringstream =	std::basic_ostringstream< TCHAR >;

	using V_STR = std::vector < tstring >;
	using P_STR = std::shared_ptr < tstring >;
	using VP_STR = std::vector < P_STR >;
	using PVP_STR = std::shared_ptr < tstring >;


	typedef tostringstream TOSS;
	typedef std::shared_ptr < TOSS > P_TOSS;


	using UP_CTSTR = std::unique_ptr < TCHAR >;
	using UP_TSTR = std::unique_ptr < TCHAR[] >;	//配列として < TCHAR[] > で宣言する


	//-------------------------------------------------------------------------------------------------
	// TRUE, FALSE
	//-------------------------------------------------------------------------------------------------
	constexpr bool T = true;
	constexpr bool F = false;

	//-------------------------------------------------------------------------------------------------
	//	引数にした変数から、変数名を示す文字列リテラルとして返す((#)が文字列化演算子)
	//-------------------------------------------------------------------------------------------------
	#define	STR(var) #var


}	//namespace GAME


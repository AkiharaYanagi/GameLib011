//=================================================================================================
//
// �f�t�@�C���w�b�_
//�@		GameLib�p���ʒ�`
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------
#include <WinSock2.h>	//<windows.h>�����O�ɐ錾����
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

using namespace std;

//-------------------------------------------------------------------------------------------------
//	��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	// unsigned int
	//-------------------------------------------------------------------------------------------------
	using UINT = unsigned __int32;

	//-------------------------------------------------------------------------------------------------
	// RECT
	//-------------------------------------------------------------------------------------------------
	using V_RECT = vector < RECT >;
	using PV_RECT = shared_ptr < V_RECT >;
	using SP_RECT = shared_ptr < RECT >;
	using VSP_RECT = vector < SP_RECT >;

	//-------------------------------------------------------------------------------------------------
	// TCAHR�Ή�
	//-------------------------------------------------------------------------------------------------
	using tstring =			std::basic_string< TCHAR >;
	using tistream =		std::basic_istream< TCHAR >;
	using tostream =		std::basic_ostream< TCHAR >;
	using tfstream =		std::basic_fstream< TCHAR >;
	using tifstream =		std::basic_ifstream< TCHAR >;
	using tofstream =		std::basic_ofstream< TCHAR >;
	using tistringstream =	std::basic_istringstream< TCHAR >;
	using tostringstream =	std::basic_ostringstream< TCHAR >;

}	//namespace GAME


//=================================================================================================
//
//	Menu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameTextLibrary.h"
#include "GameGraphicLibrary.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=================================================
	class MenuItem : public TASK_VEC
	{
	public:
		virtual void Do () {}
	};

	using P_MenuItem = shared_ptr < MenuItem >;
	using VP_MenuItem = vector < P_MenuItem >;


	//=================================================
	class MenuString : public GrpStr
	{
	public:
		MenuString ();
		MenuString ( const MenuString & rhs ) = delete;
		~MenuString ();
	};

	using P_MenuString = shared_ptr < MenuString >;


	//=================================================
	class Menu : public TASK_VEC
	{
		bool			m_active;
		P_PrmRect		m_bg;

		VP_MenuItem		mvp_MenuItem;
		VP_MenuItem::iterator		m_itItem;

	public:
		Menu ();
		Menu ( const Menu & rhs ) = delete;
		~Menu ();

		void Init ();

		void SetActive ( bool b ) { m_active = b; }
		bool GetActive () const { return m_active; }

		void SetMenuItem ( P_MenuItem mi );

		void Next ();
		void Prev ();
		void Do ();

		DWORD GetIdItem () const;
	};

	using P_Menu = shared_ptr < Menu >;


}	//namespace GAME


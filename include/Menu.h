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
	//メニュ 項目
	class MenuItem : public TASK_VEC
	{
	public:
		virtual void Do () {}
	};

	using P_MenuItem = shared_ptr < MenuItem >;
	using VP_MenuItem = vector < P_MenuItem >;


	//=================================================
	//メニュ内文字列
	class MenuString : public GrpStr
	{
	public:
		MenuString ();
		MenuString ( const MenuString & rhs ) = delete;
		~MenuString ();
	};

	using P_MenuString = shared_ptr < MenuString >;


	//=================================================
	//メニュ 動作主体
	class Menu : public MenuItem
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

		void SetpMenuItem ( P_MenuItem mi );

		void Next ();
		void Prev ();
		void Do ();

		DWORD GetIdItem () const;
	};

	using P_Menu = shared_ptr < Menu >;


}	//namespace GAME


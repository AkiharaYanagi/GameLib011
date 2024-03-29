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
	class Menu; using WP_Menu = weak_ptr < Menu >;

	//=================================================
	//メニュ 項目
	class MenuItem : public TASK_VEC
	{
	protected:
		WP_Menu		mwp_Parent;	//直接の親メニュ

	public:
		virtual void Do () {}
		virtual void Decide () {}
		virtual void Off () {}
		virtual void On () {}

		void SetwpParent ( WP_Menu wp ) { mwp_Parent = wp; }
	};

	using P_MenuItem = std::shared_ptr < MenuItem >;
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

	using P_MenuString = std::shared_ptr < MenuString >;


	//=================================================
	//メニュ 動作主体
	class Menu : public MenuItem, public enable_shared_from_this < Menu >
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

		//shared_from_this () を含むのでコンストラクタで用いない
		void SetpMenuItem ( P_MenuItem mi );
		P_MenuItem GetpMenuItem () { return *m_itItem; }

		void Next ();
		void Prev ();
		void Do ();
		void Decide ();

		DWORD GetIdItem () const;

		//選択
		void Top ();
		void Last ();
		void Select ( UINT n );	//IDで選択、範囲外は何もしない

		//全体 オン / オフ
		void AllOff ();
		void AllOn ();

		//Itemのみ オン / オフ
		void ItemOff ();
		void ItemOn ();
	};

	using P_Menu = std::shared_ptr < Menu >;


}	//namespace GAME


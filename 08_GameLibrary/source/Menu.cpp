//=================================================================================================
//
//	Menu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Menu.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=================================================
	//MenuItem

	//=================================================
	//MenuString

	MenuString::MenuString ()
	{
		SetFontParam ( 100, 1, 2 );
		SetFontFace ( _T ( "メイリオ" ) );
//		SetFontFace ( _T ( "MSゴシック" ) );
		SetFontColor ( 0xffffffff, 0xff202080 );
		SetZ ( Z_MENU );
	}

	MenuString::~MenuString ()
	{
	}


	//=================================================
	Menu::Menu ()
		: m_active ( F )
	{
		m_itItem = mvp_MenuItem.begin ();
	}

	Menu::~Menu ()
	{
	}

	void Menu::Init ()
	{
		m_itItem = mvp_MenuItem.begin ();
		
		MenuItem::Init ();
	}
	
	void Menu::SetpMenuItem ( P_MenuItem mi )
	{
		mi->SetwpParent ( shared_from_this () );
		mvp_MenuItem.push_back ( mi );
	}

	void Menu::Next ()
	{
//		TRACE_F ( _T ( "Menu::Next()\n" ) );


		//個数が1,または0のとき何もしない
		if ( mvp_MenuItem.size () < 2 ) { return; }

		if ( mvp_MenuItem.end () == m_itItem + 1 )
		{
			m_itItem = mvp_MenuItem.begin ();
		}
		else
		{
			++ m_itItem;
		}
	}

	void Menu::Prev ()
	{
		//個数が1,または0のとき何もしない
		if ( mvp_MenuItem.size () < 2 ) { return; }

		if ( mvp_MenuItem.begin () == m_itItem )
		{
			m_itItem = mvp_MenuItem.end () - 1;
		}
		else
		{
			-- m_itItem;
		}
	}
	
	void Menu::Do ()
	{
		( * m_itItem )->Do ();
	}

	void Menu::Decide ()
	{
		( * m_itItem )->Decide ();
	}

	DWORD Menu::GetIdItem () const
	{
		size_t size = mvp_MenuItem.size ();
		if ( 0 == size ) { return 0; }


		VP_MenuItem::const_iterator	it = mvp_MenuItem.begin ();
		for ( DWORD i = 0; i < size; ++ i )
		{
			if ( it == m_itItem ) { return i; }
			++ it;
		}

		return 0;
	}

	void Menu::Top ()
	{
		if ( mvp_MenuItem.size () == 0 ) { return; }
		m_itItem = mvp_MenuItem.begin ();
	}

	void Menu::Last ()
	{
		if ( mvp_MenuItem.size () == 0 ) { return; }
		m_itItem = mvp_MenuItem.end ();
		-- m_itItem;
	}

	void Menu::Select ( UINT n )
	{
		if ( mvp_MenuItem.size () < n ) { return; }

		m_itItem = mvp_MenuItem.begin ();
		m_itItem += n;
	}

	void Menu::AllOff ()
	{
		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->Off ();
		}
		Off ();	//自身もOff();
	}

	void Menu::AllOn ()
	{
		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->On ();
		}
		On ();	//自身もOn();
	}

	void Menu::ItemOff ()
	{
		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->Off ();
		}
		//		Off ();	//自身はOff();しない
	}

	void Menu::ItemOn ()
	{
		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->On ();
		}
		//		On ();	//自身はOn();しない
	}


}	//namespace GAME


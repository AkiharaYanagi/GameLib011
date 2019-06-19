//=================================================================================================
//
//	文字列フォーマット
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	typedef tostringstream TOSS;
	typedef shared_ptr < TOSS > P_TOSS;


	class Format
	{
		static TOSS		m_toss;

		//再帰末端
		static void _f ( const TCHAR * tstr )
		{
			m_toss << *(tstr++);
			return;
		}

		//再帰用
		template < typename First, typename... Rest >
		static void _f ( const TCHAR * tstr, const First & first, const Rest&... rest )
		{
			while ( *tstr )
			{
				//フォーマット指定子処理
				if ( _T ( '%' ) == (*tstr) && _T ( '%' ) != *(tstr) )
				{
					m_toss << first;

					//存在すれば次を再帰
					_f ( *tstr ? ++tstr : tstr, rest... );
					return;
				}
			}
			return;
		}

	public:
		
		template < typename... Args >
		static void Addf ( const TCHAR * tstr, const Args&... args )
		{
			_f ( tstr, args... );
		}
		static const TOSS & RefToss () { return m_toss; }

		//フォーマットを取得
		template < typename... Args >
		static LPCTSTR f ( const TCHAR * tstr, const Args&... args )
		{
			m_toss.clear ();
			_f ( tstr, args... );
			return m_toss.str().c_str ();
		}

		//va_list
		unique_ptr < TCHAR[] > DebugOutf ( LPCTSTR format, ... );
	};


}	//namespace GAME


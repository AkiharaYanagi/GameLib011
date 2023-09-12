//=================================================================================================
//
//	文字列フォーマット
//		変数を用いないスタティックなクラスでどこからでも扱える
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

	class Format final
	{
	public:
		Format () = delete;	//staticクラスとして実体化禁止
		~Format () = delete;

	private:
		static TOSS		m_toss;

		//再帰末端
		static void _f ( LPCTSTR tstr )
		{
			m_toss << *(tstr++);
			return;
		}

		//再帰用
		template < typename First, typename... Rest >
		static void _f ( LPCTSTR tstr, const First & first, const Rest&... rest )
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
		static void Addf ( LPCTSTR tstr, const Args&... args )
		{
			_f ( tstr, args... );
		}
		static const TOSS & RefToss () { return m_toss; }

		//フォーマットを取得
		template < typename... Args >
		static LPCTSTR f ( LPCTSTR tstr, const Args&... args )
		{
			m_toss.clear ();
			_f ( tstr, args... );
			return m_toss.str().c_str ();
		}

		//---------------------------------------------------------------
		//va_list 可変引数
		static UP_TSTR GetFormatStr ( LPCTSTR format, ... );
		
		static UP_TSTR Printf_Args ( LPCTSTR format, va_list args );
	};


}	//namespace GAME


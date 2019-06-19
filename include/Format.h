//=================================================================================================
//
//	������t�H�[�}�b�g
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���@�C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	typedef tostringstream TOSS;
	typedef shared_ptr < TOSS > P_TOSS;


	class Format
	{
		static TOSS		m_toss;

		//�ċA���[
		static void _f ( const TCHAR * tstr )
		{
			m_toss << *(tstr++);
			return;
		}

		//�ċA�p
		template < typename First, typename... Rest >
		static void _f ( const TCHAR * tstr, const First & first, const Rest&... rest )
		{
			while ( *tstr )
			{
				//�t�H�[�}�b�g�w��q����
				if ( _T ( '%' ) == (*tstr) && _T ( '%' ) != *(tstr) )
				{
					m_toss << first;

					//���݂���Ύ����ċA
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

		//�t�H�[�}�b�g���擾
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


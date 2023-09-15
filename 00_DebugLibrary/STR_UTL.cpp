//=================================================================================================
//
//	文字列ユーティリティ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "STR_UTL.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//文字列サイズの取得
	UINT STR_UTL::Size ( LPCTSTR lpctstr )
	{
		UINT ret = 0;
		TCHAR t = *lpctstr;

		try
		{
			while ( t != '\0' )
			{
				t = *( lpctstr + ( ret ++ ) );
			}
		}
		catch ( ... )
		{
			return 0;
		}

		return ret;
	}


	//文字コード取得
	UINT STR_UTL::GetCode ( PTCHAR ptch )
	{
#if	_UNICODE

		//UNICODEの場合、文字コードは単純にワイド文字のUINT変換
		return (UINT)*ptch;

#else	//_UNICODE

		UINT code;
		//マルチバイト文字の場合、
		//1バイト文字のコードは1バイト目のUINT変換、
		//2バイト文字のコードは[先導コード]*256 + [文字コード]
		if ( IsDBCSeadByte ( *ptch ) ) { code = (BYTE)ptch [ 0 ] << 8 | (BYTE)ptch [ 1 ]; }
		else { code = ptch [ 0 ]; }
		return code;

#endif	//_UNICODE
	}

	UINT STR_UTL::GetCode ( LPCTCH lpctch )
	{
#if	_UNICODE

		//UNICODEの場合、文字コードは単純にワイド文字のUINT変換
		return (UINT)*lpctch;

#else	//_UNICODE

		UINT code;
		//マルチバイト文字の場合、
		//1バイト文字のコードは1バイト目のUINT変換、
		//2バイト文字のコードは[先導コード]*256 + [文字コード]
		if ( IsDBCSeadByte ( *lpctch ) ) { code = (BYTE)lpctch [ 0 ] << 8 | (BYTE)lpctch [ 1 ]; }
		else { code = lpctch [ 0 ]; }
		return code;

#endif	//_UNICODE
	}

	UINT STR_UTL::GetCode ( char ascii )
	{
#if	_UNICODE
		//UNICODEの場合、文字コードは単純にワイド文字のUINT変換
		return (UINT)ascii;

#else	//_UNICODE

		UINT code;
		//マルチバイト文字の場合、
		//1バイト文字のコードは1バイト目のUINT変換、
		//2バイト文字のコードは[先導コード]*256 + [文字コード]
		if ( IsDBCSeadByte ( *lpctch ) ) { code = (BYTE)lpctch [ 0 ] << 8 | (BYTE)lpctch [ 1 ]; }
		else { code = lpctch [ 0 ]; }
		return code;

#endif	//_UNICODE
	}


	//テクスチャ用
	//2のべき乗補完 ( 1 ～ 65536 )
	LONG STR_UTL::PowerNormalize ( LONG ln )
	{
		const long LMT = 65536;
		long pw = 2;
		while ( pw <= LMT )
		{
			if ( ln <= pw ) { return pw; }
			pw *= 2;
		}
		return 1;	//範囲外は１
	}


}	//namespace GAME


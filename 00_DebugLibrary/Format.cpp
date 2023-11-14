//=================================================================================================
//
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Format.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TOSS Format::m_toss;

	UP_TSTR Format::GetFormatStr ( LPCTSTR format, ... )
	{
		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット
		UP_TSTR out = Printf_Args ( format, args );
		va_end ( args );	//可変長リストの解放

		return std::move ( out );
	}

	UP_TSTR Format::Printf_Args ( LPCTSTR format, va_list args )
	{
		//Unicode（ワイド文字）対応　_vsc w printf() / マルチバイト文字対応 _vsc printf()
		int size = _vsctprintf ( format, args ) + 1;		//'\0'を最後につけたサイズを得る
		UP_TSTR buf = std::make_unique < TCHAR[] > ( size );		//バッファを確保
		//Unicode（ワイド文字）対応　vs w printf_s() / マルチバイト文字対応 vs printf_s()
		_vstprintf_s ( buf.get (), size, format, args );	//バッファに書き込み
		return std::move ( buf );
	}

}	//namespace GAME


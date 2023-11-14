//=================================================================================================
//
// デバッグマネージャ　実装
//	・テキストファイル出力
//	・IDEデバッグ出力
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "Format.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	/*===========================================================================*/
	//デバッグファイル出力
	//デバッグ用テキストファイル生成　0:off, 1:on
	#define		DEBUG_OUT_FILE	0

	//------------------------------------------------
	//Static実体
	//------------------------------------------------
	//シングルトン
	DebugOutFile::P_DebugOutFile	DebugOutFile::m_inst;

	//コンストラクタ
	DebugOutFile::DebugOutFile()
	{
#if	DEBUG_OUT_FILE
		m_tofstrm.open ( _T("log.txt"), ios::trunc );
#endif	//	DEBUG_OUT_FILE
	}

	//デストラクタ
	DebugOutFile::~DebugOutFile()
	{
#if	DEBUG_OUT_FILE
		m_tofstrm.close();
#endif	//	DEBUG_OUT_FILE
	}

	//可変長フォーマット出力
	void DebugOutFile::DebugOutf ( LPCTSTR format, ... )
	{
#if	DEBUG_OUT_FILE
//		std::locale::global(std::locale("japanese"));
//		setlocale ( LC_ALL, "japanese" );

		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット

		//ロケールオブジェクト
		_locale_t lc = ::_create_locale(LC_ALL, "jpn");

		//Unicode（ワイド文字）対応　_vsc w printf() / マルチバイト文字対応 _vscprintf()
//		int size = _vsctprintf ( format, args ) + 1;		//'\0'を最後につけたサイズを得る
		int size = _vsctprintf_l ( format, lc, args ) + 1;		//'\0'を最後につけたサイズを得る


		std::unique_ptr < TCHAR[] > tbuf = std::make_unique < TCHAR[] > ( size );		//バッファを確保
	
																			//Unicode（ワイド文字）対応　vs w printf_s() / マルチバイト文字対応 vswprintf_s()
//		_vstprintf_s ( tbuf.get(), size, format, args );	//バッファに書き込み
		_vstprintf_s_l ( tbuf.get(), size, format, lc, args );	//バッファに書き込み


		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// ※ wofstreamはUnicodeで出力する
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		m_tofstrm.imbue ( std::locale("", locale::ctype) );

		tstring tstr ( tbuf.get() );
		m_tofstrm << tstr;	//ファイルに書き出し
//		m_tofstrm << format;	//ファイルに書き出し
		m_tofstrm.flush ();



		va_end ( args );
#endif	//	DEBUG_OUT_FILE
	}


	/*===========================================================================*/
	//	IDEデバッグウィンドウ出力 [ TRACE() ]
	/*===========================================================================*/

	//------------------------------------------------
	//staticの実体
	//------------------------------------------------
//	std::unique_ptr < DebugOutTrace > DebugOutTrace::m_inst = nullptr;

	//文字列フォーマットを表示
	void DebugOutTrace::DebugOutf ( LPCTSTR format, ... )
	{
		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット
		UP_TSTR buf = Format::Printf_Args ( format, args );
		va_end ( args );	//可変長リスト終了

		//デバッグウィンドウに出力
		OutputDebugString ( buf.get () );
//		OutputDebugString ( Format::f ( format, args ) );
	}


	//文字列フォーマットを表示(char*)
	void DebugOutTrace::DebugOutchf ( LPCSTR format, ... )
	{
		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット

		int size = _vscprintf ( format, args ) + 1;		//'\0'を最後につけたサイズを得る
		std::unique_ptr < char[] > buf = std::make_unique < char[] > ( size );		//バッファを確保
		vsprintf_s ( buf.get (), size, format, args );	//バッファに書き込み

		va_end ( args );

		//multibyte文字からTCHAR(WCHAR)に変換
		std::unique_ptr < TCHAR[] > tbuf = std::make_unique < TCHAR[] > ( size );		//バッファを確保
		size_t _PptNumOfCharConverted = 0;
		size_t sizebuf = strlen ( buf.get() ) + 1;
		mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get(), sizebuf, buf.get(), _TRUNCATE );

		//デバッグウィンドウに出力
		OutputDebugString ( tbuf.get () );
	}


	//GetLastError()からのWIN32APIのエラーメッセージ表示
	//引数：呼出側で__FILE__, __LINE__を指定
	void DebugOutTrace::OutputLastError ( LPCSTR file, DWORD line )
	{
		TCHAR filePath [ MAX_PATH ] = _T("");
		size_t _PptNumOfCharConverted = 0;
//		::MultiByteToWideChar ( CP_THREAD_ACP, MB_PRECOMPOSED, file, -1, filePath, 0 );
		setlocale ( LC_ALL, "japanese" );
		size_t sizefile = strlen ( file );
		//multibyte文字からWCHARに変換
		mbstowcs_s ( &_PptNumOfCharConverted, filePath, sizefile, file, _TRUNCATE );
		OutputDebugString( filePath );

		TCHAR lineStr [255];
		size_t size =  sizeof(TEXT(" () : ")) + sizeof ( line );
		_stprintf_s ( lineStr, size, TEXT(" (%d) : "), line );
		OutputDebugString( lineStr );
//		OutputDebugString( TEXT ( __FILE__ ) );
//		OutputDebugString( TEXT ( "(%d)\n" ), __LINE__);

		DWORD error = ::GetLastError();
		LPTSTR lpBuffer = nullptr;
		::FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr, error, LANG_USER_DEFAULT, (LPTSTR)&lpBuffer, 0, nullptr );
		OutputDebugString ( lpBuffer );
		::LocalFree ( lpBuffer );
	}

}	//namespace GAME


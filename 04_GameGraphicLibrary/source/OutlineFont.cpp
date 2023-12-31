//=================================================================================================
//
//	アウトラインフォント
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "OutlineFont.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//static実体
	std::unique_ptr < OutlineFont > OutlineFont::m_inst = nullptr;


	OutlineFont::OutlineFont ()
		: m_quality ( 1 ), m_txW ( 0 ), m_txH ( 0 ), m_gmX ( 0 ), m_gmY ( 0 )
	{
		const TCHAR faceName[] = _T ( "メイリオ" );
		_tcscpy_s ( m_fontName, faceName );
	}

	OutlineFont::~OutlineFont ()
	{
	}

	void OutlineFont::Create ()
	{
		assert ( ! m_inst );	//既に存在していたらassert
		m_inst = std::unique_ptr < OutlineFont > ( new OutlineFont () );
	}

	void OutlineFont::Load ( D3DDEV pDev )
	{
		m_lpD3DDevice = pDev;
	}

	void OutlineFont::Reset ( D3DDEV pDev )
	{
		Load ( pDev );
	}
	
	void OutlineFont::SetParam ( int fontSize, int penSize, int quolity )
	{
		m_fontSize = fontSize;
		m_penSize = penSize;
		m_quality = quolity;
	}
	
	void OutlineFont::SetFontFace ( LPCTSTR fontname )
	{
		_tcscpy_s ( m_fontName, LF_FACESIZE, fontname );
	}

	void OutlineFont::SetColor ( DWORD fill, DWORD edge )
	{
		m_fillColor = fill;
		m_edgeColor = edge;
	}

	TX OutlineFont::Make ( LPCTSTR str, DWORD edgeColor, DWORD fillColor )
	{
		Color cEdge ( edgeColor ), cFill ( fillColor );

		//デバイスコンテキスト
		HDC tempHdc = GetDC ( HWnd::Get () );
		//メモリDC
		m_memDC = CreateCompatibleDC ( tempHdc );

		//フォントの作成
		int q = m_quality;

		LOGFONT logFont = {};
		logFont.lfHeight = m_fontSize * q;
		logFont.lfWeight = 0;
		logFont.lfCharSet = DEFAULT_CHARSET;
		logFont.lfWeight = 0;
		logFont.lfQuality = 0;
//		const TCHAR faceName[] = _T ( "メイリオ" );
		_tcscpy_s ( logFont.lfFaceName, m_fontName );
		HFONT hFont = CreateFontIndirect ( & logFont );
		HFONT oldFont = (HFONT)SelectObject ( m_memDC, hFont );


		//フォントデータ取得
		TEXTMETRIC tm;
		GLYPHMETRICS gm;
		const MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
//		const TCHAR * str0 = _T ( "あ" );
//		UINT code = (UINT)str0[0];
		UINT code = (UINT)*str;
		BOOL b = GetTextMetrics ( m_memDC, & tm );
		DWORD dw = GetGlyphOutline ( m_memDC, code, GGO_METRICS, & gm, 0, 0, & mat );

		m_gmCellIncX = gm.gmCellIncX / q;
		m_gmX = gm.gmptGlyphOrigin.x / q;
		m_gmY = (tm.tmAscent - gm.gmptGlyphOrigin.y) / q;

		int penSize = m_penSize * q;
		LONG rectL = gm.gmptGlyphOrigin.x - penSize / 2;
		LONG rectT = tm.tmAscent - gm.gmptGlyphOrigin.y - penSize / 2;
		LONG rectR = gm.gmptGlyphOrigin.x + gm.gmBlackBoxX + penSize / 2;
		LONG rectB = tm.tmAscent - gm.gmptGlyphOrigin.y + gm.gmBlackBoxY + penSize / 2;
		RECT charRegion = { rectL, rectT, rectR, rectB };

		LONG charW = (gm.gmBlackBoxX + penSize + q - 1) / q * q;
		LONG charH = (gm.gmBlackBoxY + penSize + q - 1) / q * q;
//		RECT charWH = { 0, 0, charW, charH };

		//2のべき乗補完
		RECT charWH = { 0, 0, STR_UTL::PowerNormalize ( charW ), STR_UTL::PowerNormalize ( charH ) };

		//BMP作成
		BITMAPINFO bmpInfo = {};
		bmpInfo.bmiHeader.biSize = sizeof ( BITMAPINFOHEADER );
		bmpInfo.bmiHeader.biWidth = charW;
		bmpInfo.bmiHeader.biHeight = - charH;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 24;
		LPBYTE pBits;
		HBITMAP hBmp = CreateDIBSection ( tempHdc, & bmpInfo, DIB_RGB_COLORS, (LPVOID*)&pBits, 0, 0 );
		HBITMAP oldBmp = (HBITMAP)SelectObject ( m_memDC, hBmp );


		//描画

		//塗り(赤)
		HBRUSH hBrs = (HBRUSH)CreateSolidBrush ( RGB ( 255, 0, 0 ) );
		HBRUSH oldBrs = (HBRUSH)SelectObject ( m_memDC, hBrs );

		//フチ(緑)
		HPEN hPen = (HPEN)CreatePen ( PS_SOLID, penSize, RGB ( 0, 255, 0 ) );
		HPEN oldPen = (HPEN)SelectObject ( m_memDC, hPen );

		//背景(青)
		HBRUSH bgBrs = CreateSolidBrush ( RGB ( 0, 0, 255 ) );
		FillRect ( m_memDC, & charWH, bgBrs );
		DeleteObject ( bgBrs );

		//文字
		SetBkMode ( m_memDC, TRANSPARENT );
		BeginPath ( m_memDC );
		TextOut ( m_memDC, - rectL, - rectT, str, _tcslen ( str ) );
		EndPath ( m_memDC );
		StrokeAndFillPath ( m_memDC );

		//ブラシとペンを戻す
		SelectObject ( m_memDC, oldPen );
		SelectObject ( m_memDC, oldBrs );


		//テクスチャの作成
		TX tx;
		m_txW = charWH.right / q;
		m_txH = charWH.bottom / q;
		m_lpD3DDevice->CreateTexture ( m_txW, m_txH, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, & tx, nullptr );

		//ロックしてビットに書き込む
		int q2 = q * q;
		D3DLOCKED_RECT lockRect;
		bool bLock = SUCCEEDED ( tx->LockRect ( 0, &lockRect, nullptr, 0 ) );
		if ( bLock )
		{
			LPDWORD pBase = (LPDWORD)lockRect.pBits;

			//改行位置
			//ビットマップの3バイト幅[RGB]を4バイト幅[ARGB]に直す
			const int align3 = 3;
			const int align4 = 4;
			const int d = align4 - 1;	//端数(0~3)
			DWORD bmpPitch = (charWH.right * align3 + d) / align4 * align4;

			//ビットマップを走査
			for ( int y = 0; y < m_txH; ++ y )
			{
				for ( int x = 0; x < m_txW; ++ x )
				{
					//テクスチャのピクセル位置
					DWORD & pBitPos = *(pBase + x + y * m_txW);

					unsigned alph = 0;
					unsigned edge = 0;
					unsigned fill = 0;

					//quality倍率分点を平均化
					for ( int i = 0; i < q; ++ i )
					{
						for ( int j = 0; j < q; ++ j )
						{
							//B(背景色)、G(パス色)、R(塗色)
							alph += pBits[(y * q + i) * bmpPitch + (x * q + j) * 3 + 0];
							edge += pBits[(y * q + i) * bmpPitch + (x * q + j) * 3 + 1];
							fill += pBits[(y * q + i) * bmpPitch + (x * q + j) * 3 + 2];
						}
					}
					alph /= q2;
					edge /= q2;
					fill /= q2;


					//透過度がある場合はエッジ色を採用
					//不透明の場合はブレンド色を採用
					unsigned a = 0xff - alph;
					if ( a < 0xff )
					{
						//半透明
						unsigned r = cEdge.R;
						unsigned g = cEdge.G;
						unsigned b = cEdge.B;
						a = (a * cEdge.A) >> 8;
						//					a = 0xff;
						pBitPos = a << 24 | r << 16 | g << 8 | b;
					}
					else
					{
						//不透明
						unsigned r = ((cEdge.R * edge) >> 8) + ((cFill.R * fill) >> 8);
						unsigned g = ((cEdge.G * edge) >> 8) + ((cFill.G * fill) >> 8);
						unsigned b = ((cEdge.B * edge) >> 8) + ((cFill.B * fill) >> 8);
						unsigned c = ((cEdge.A * edge) >> 8) + ((cFill.A * fill) >> 8);
						pBitPos = c << 24 | r << 16 | g << 8 | b;
					}
				}
			}

			tx->UnlockRect ( 0 );
		}

		//終了
		DeleteObject ( hPen );
		DeleteObject ( hBrs );
		DeleteObject ( hBmp );
		DeleteDC ( m_memDC );

		return tx;
	}


	TX OutlineFont::MakeStrTx ( LPCTSTR str, DWORD edgeColor, DWORD fillColor )
	{
		if ( 0 == _tcscmp ( str, _T("") ) ) { return nullptr; }

		Color cEdge ( edgeColor ), cFill ( fillColor );

		//デバイスコンテキスト
		HDC tempHdc = GetDC ( HWnd::Get () );
		//メモリDC
		m_memDC = CreateCompatibleDC ( tempHdc );

		//フォントの作成
		int q = m_quality;	//クォリティ
		LOGFONT logFont = {};
		logFont.lfHeight = m_fontSize * q;
		logFont.lfWeight = 0;
		logFont.lfCharSet = DEFAULT_CHARSET;
		logFont.lfWeight = 0;
		logFont.lfQuality = 0;
		_tcscpy_s ( logFont.lfFaceName, m_fontName );
		HFONT hFont = CreateFontIndirect ( & logFont );
		HFONT oldFont = (HFONT)SelectObject ( m_memDC, hFont );

		//テキストメトリックを取得
		TEXTMETRIC tm;
		BOOL b = GetTextMetrics ( m_memDC, & tm );


		//フォントデータ取得
		const MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
		int penSize = m_penSize * q;
		LONG bmpW = 0;	//合計値
		LONG bmpH = 0;	//最大値

		//各文字から全体サイズを取得
		int length = ::lstrlen ( str );
		for ( int i = 0; i < length; ++ i )
		{
			UINT code = (UINT)str [ i ];	//UNICODE

			GLYPHMETRICS gm;
			DWORD dw = GetGlyphOutline ( m_memDC, code, GGO_METRICS, & gm, 0, 0, & mat );

//			LONG charW = ( gm.gmBlackBoxX + penSize + q - 1 ) / q * q;
			LONG charW = ( gm.gmCellIncX + penSize + q - 1 ) / q * q;
			LONG charH = ( gm.gmBlackBoxY + penSize + q - 1 ) / q * q;

			bmpW += charW;
			bmpH = tm.tmHeight;
		}

		//2のべき乗補完
		bmpW = STR_UTL::PowerNormalize ( bmpW );
		bmpH = STR_UTL::PowerNormalize ( bmpH );


		//一時BMP作成
		BITMAPINFO bmpInfo = {};
		bmpInfo.bmiHeader.biSize = sizeof ( BITMAPINFOHEADER );
		bmpInfo.bmiHeader.biWidth = bmpW;
		bmpInfo.bmiHeader.biHeight = - bmpH;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 24;
		LPBYTE pBits;
		HBITMAP hBmp = CreateDIBSection ( tempHdc, & bmpInfo, DIB_RGB_COLORS, (LPVOID*)&pBits, 0, 0 );
		HBITMAP oldBmp = (HBITMAP)SelectObject ( m_memDC, hBmp );


		//背景(青)塗りつぶし
		RECT rectBmp = { 0, 0, bmpW, bmpH };
		HBRUSH bgBrs = CreateSolidBrush ( RGB ( 0, 0, 255 ) );
		FillRect ( m_memDC, & rectBmp, bgBrs );
		DeleteObject ( bgBrs );

		//文字描画
		//塗り(ブラシ：赤)
		HBRUSH hBrs = (HBRUSH)CreateSolidBrush ( RGB ( 255, 0, 0 ) );
		HBRUSH oldBrs = (HBRUSH)SelectObject ( m_memDC, hBrs );

		//フチ(ペン：緑)
		HPEN hPen = (HPEN)CreatePen ( PS_SOLID, penSize, RGB ( 0, 255, 0 ) );
		HPEN oldPen = (HPEN)SelectObject ( m_memDC, hPen );

		//各文字を描画
		int offset = 0;
		for ( int i = 0; i < length; ++ i )
		{
			//文字コード
//			UINT code = (UINT)str [ i ];
			UINT code = STR_UTL::GetCode ( & str [ i ] );

			//グリフメトリクスを取得
			GLYPHMETRICS gm;
			DWORD dw = GetGlyphOutline ( m_memDC, code, GGO_METRICS, & gm, 0, 0, & mat );

			//サイズを取得
			LONG rectL = gm.gmptGlyphOrigin.x - penSize / 2;
			LONG rectT = tm.tmAscent - gm.gmptGlyphOrigin.y - penSize / 2;
			LONG rectR = gm.gmptGlyphOrigin.x + gm.gmBlackBoxX + penSize / 2;
			LONG rectB = tm.tmAscent - gm.gmptGlyphOrigin.y + gm.gmBlackBoxY + penSize / 2;

//			LONG charW = ( gm.gmBlackBoxX + penSize + q - 1 ) / q * q;
			LONG charW = ( gm.gmCellIncX + penSize + q - 1 ) / q * q;
			LONG charH = ( gm.gmBlackBoxY + penSize + q - 1 ) / q * q;

			SetBkMode ( m_memDC, TRANSPARENT );
			BeginPath ( m_memDC );
			TextOut ( m_memDC, - rectL + offset, 0, str + i, 1 );
//			TextOut ( m_memDC, - rectL + offset, - tm.tmDescent, str + i, 1 );
			EndPath ( m_memDC );
			StrokeAndFillPath ( m_memDC );

			offset += charW;
		}

		//ブラシとペンを戻す
		SelectObject ( m_memDC, oldPen );
		DeleteObject ( hPen );

		SelectObject ( m_memDC, oldBrs );
		DeleteObject ( hBrs );



		//テクスチャの作成
		TX tx;
		m_txW = bmpW / q;
		m_txH = bmpH / q;
		m_lpD3DDevice->CreateTexture ( m_txW, m_txH, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, & tx, nullptr );

		//テクスチャをロックしてピクセル単位で書き込む
		int q2 = q * q;
		D3DLOCKED_RECT lockRect;
		bool bLock = SUCCEEDED ( tx->LockRect ( 0, &lockRect, nullptr, 0 ) );
		if ( bLock )
		{
			LPDWORD pBase = (LPDWORD)lockRect.pBits;

			//改行位置
			//ビットマップの3バイト幅[RGB]を4バイト幅[ARGB]に直す
			const int align3 = 3;
			const int align4 = 4;
			const int d = align4 - 1;	//端数(0~3)
			DWORD bmpPitch = ( rectBmp.right * align3 + d ) / align4 * align4;

			//ビットマップを走査
			for ( int y = 0; y < m_txH; ++ y )
			{
				for ( int x = 0; x < m_txW; ++ x )
				{
					//テクスチャのピクセル位置
					DWORD & pBitPos = *( pBase + x + y * m_txW );

					unsigned alph = 0;
					unsigned edge = 0;
					unsigned fill = 0;

					//quality倍率分点を平均化
					for ( int i = 0; i < q; ++ i )
					{
						for ( int j = 0; j < q; ++ j )
						{
							//B(背景色)、G(パス色)、R(塗色)
							alph += pBits [ ( y * q + i ) * bmpPitch + ( x * q + j ) * 3 + 0 ];
							edge += pBits [ ( y * q + i ) * bmpPitch + ( x * q + j ) * 3 + 1 ];
							fill += pBits [ ( y * q + i ) * bmpPitch + ( x * q + j ) * 3 + 2 ];
						}
					}
					alph /= q2;
					edge /= q2;
					fill /= q2;


					//透過度がある場合はエッジ色を採用
					//不透明の場合はブレンド色を採用
					unsigned a = 0xff - alph;
					if ( a < 0xff )
					{
						//半透明
						unsigned r = cEdge.R;
						unsigned g = cEdge.G;
						unsigned b = cEdge.B;
						a = ( a * cEdge.A ) >> 8;
						//					a = 0xff;
						pBitPos = a << 24 | r << 16 | g << 8 | b;
					}
					else
					{
						//不透明
						unsigned r = ( ( cEdge.R * edge ) >> 8 ) + ( ( cFill.R * fill ) >> 8 );
						unsigned g = ( ( cEdge.G * edge ) >> 8 ) + ( ( cFill.G * fill ) >> 8 );
						unsigned b = ( ( cEdge.B * edge ) >> 8 ) + ( ( cFill.B * fill ) >> 8 );
						unsigned a = ( ( cEdge.A * edge ) >> 8 ) + ( ( cFill.A * fill ) >> 8 );
						pBitPos = a << 24 | r << 16 | g << 8 | b;
					}
				}
			}

			tx->UnlockRect ( 0 );
		}


		//終了
		DeleteObject ( hBmp );
		DeleteDC ( m_memDC );


		//各文字のグリフメトリクスはクリアする
		m_gmCellIncX = 0;
		m_gmX = 0;
		m_gmY = 0;


		return tx;
	}


}	//namespace GAME


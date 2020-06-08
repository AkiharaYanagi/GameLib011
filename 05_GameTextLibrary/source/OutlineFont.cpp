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
	unique_ptr < OutlineFont > OutlineFont::m_inst = nullptr;


	OutlineFont::OutlineFont ()
	{

	}

	OutlineFont::~OutlineFont ()
	{
	}

	void OutlineFont::Create ()
	{
		assert ( ! m_inst );	//既に存在していたらassert
		m_inst = unique_ptr < OutlineFont > ( new OutlineFont () );
	}

	void OutlineFont::Load ( LPDIRECT3DDEVICE9 pDev )
	{
		m_lpD3DDevice = pDev;
	}
	
	void OutlineFont::Init ()
	{
	}

	void OutlineFont::Set ( int fontSize, int penSize, int quolity )
	{
		m_fontSize = fontSize;
		m_penSize = penSize;
		m_quolity = quolity;
	}

	TX OutlineFont::Make ( LPCTSTR str, DWORD edgeColor, DWORD fillColor )
	{
		Color cEdge ( edgeColor ), cFill ( fillColor );

		//デバイスコンテキスト
		HDC tempHdc = GetDC ( HWnd::Get () );
		//メモリDC
		m_memDC = CreateCompatibleDC ( tempHdc );

		//フォントの作成
		int q = m_quolity;

		LOGFONT logFont = {};
		logFont.lfHeight = m_fontSize * q;
		logFont.lfWeight = 0;
		logFont.lfCharSet = DEFAULT_CHARSET;
		logFont.lfWeight = 0;
		logFont.lfQuality = 0;
		const TCHAR faceName[] = _T ( "" );
		_tcscpy_s ( logFont.lfFaceName, faceName );
		HFONT hFont = CreateFontIndirect ( & logFont );
		HFONT oldFont = (HFONT)SelectObject ( m_memDC, hFont );


		//フォントデータ取得
		TEXTMETRIC tm;
		GLYPHMETRICS gm;
		MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
//		const TCHAR * str0 = _T ( "あ" );
//		UINT code = (UINT)str0[0];
		UINT code = (UINT)*str;
		BOOL b = GetTextMetrics ( m_memDC, & tm );
		DWORD dw = GetGlyphOutline ( m_memDC, code, GGO_METRICS, & gm, 0, 0, & mat );

		m_penSize *= q;
		LONG rectL = gm.gmptGlyphOrigin.x - m_penSize / 2;
		LONG rectT = tm.tmAscent - gm.gmptGlyphOrigin.y - m_penSize / 2;
		LONG rectR = gm.gmptGlyphOrigin.x + gm.gmBlackBoxX + m_penSize / 2;
		LONG rectB = tm.tmAscent - gm.gmptGlyphOrigin.y + gm.gmBlackBoxY + m_penSize / 2;
		RECT charRegion = { rectL, rectT, rectR, rectB };

		LONG charW = (gm.gmBlackBoxX + m_penSize + q - 1) / q * q;
		LONG charH = (gm.gmBlackBoxY + m_penSize + q - 1) / q * q;
		RECT charWH = { 0, 0, charW, charH };


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
		HPEN hPen = (HPEN)CreatePen ( PS_SOLID, m_penSize, RGB ( 0, 255, 0 ) );
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


}	//namespace GAME


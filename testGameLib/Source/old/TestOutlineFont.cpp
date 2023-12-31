//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TestOutlineFont.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TestOutlineFont::TestOutlineFont ()
	{
	}

	TestOutlineFont::~TestOutlineFont ()
	{
		Rele ();
	}

	void TestOutlineFont::Load ()
	{
		m_vtx.Load ();
	}

	void TestOutlineFont::Rele ()
	{
		m_tx->Release ();
		if ( m_mmrTx ) m_mmrTx->Rele (); m_mmrTx = nullptr;
		m_vtx.Rele ();
	}

	void TestOutlineFont::Reset ()
	{
		m_vtx.Reset ();
	}

	void TestOutlineFont::Init ()
	{
		m_vtx.SetColor ( 0, 0xFF00FF00 );
		m_vtx.SetColor ( 1, 0xFFFFFF00 );
		m_vtx.SetColor ( 2, 0xFF00FFFF );
		m_vtx.SetColor ( 3, 0xFFFF0000 );
		m_vtx.SetRect ( 10, 20, 200, 100 );

		//フォントのテクスチャを作成
		const TCHAR faceName[] = _T("ＭＳ ゴシック");
		const TCHAR * str = _T("あ");
		unsigned fontH = 450;
		int penSize = 5;
		unsigned edgeColor = 0xffE2B27A;
		unsigned fillColor = 0xff7FDBEB;
		int q = 3;

		//デバイスコンテキスト作成
		HDC hDC = GetDC ( HWnd::Get () );
		HDC memDC = ::CreateCompatibleDC ( hDC );
		ReleaseDC ( HWnd::Get (), hDC );

		//フォント作成
		LOGFONT logFont = {};
		logFont.lfHeight = fontH * q;
		logFont.lfCharSet = SHIFTJIS_CHARSET;
		logFont.lfWeight = 500;
		logFont.lfQuality = ANTIALIASED_QUALITY;
		_tcscpy_s ( logFont.lfFaceName, faceName);
		HFONT hFont = CreateFontIndirect ( & logFont );
		HFONT oldFont = (HFONT)SelectObject ( memDC, hFont );

		//BMP作成
		TEXTMETRIC tm;
		GLYPHMETRICS gm;
		MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
//		int len = IsDBCSLeadByte ( str[0] ) ? 2 : 1;
//		UINT code = (len == 2 ? (UCHAR)str[0] << 8 | (UCHAR)str[1] : (UCHAR)str[0]);
		UINT code = (UINT)str[0];
		penSize *= q;

		BOOL b = GetTextMetrics ( memDC, & tm );
		DWORD dw = GetGlyphOutline ( memDC, code, GGO_METRICS, & gm, 0, 0, & mat );
		size_t s = sizeof ( unsigned );

		RECT charRegion =
		{
			gm.gmptGlyphOrigin.x - penSize / 2,
			tm.tmAscent - gm.gmptGlyphOrigin.y - penSize / 2,
			gm.gmptGlyphOrigin.x + gm.gmBlackBoxX + penSize / 2,
			tm.tmAscent - gm.gmptGlyphOrigin.y + gm.gmBlackBoxY + penSize / 2,
		};
		RECT charWH = 
		{
			0,
			0,
			(gm.gmBlackBoxX + penSize + q - 1) / q * q ,
			(gm.gmBlackBoxY + penSize + q - 1) / q * q
		};

		int bmpW = charWH.right;
		int bmpH = charWH.bottom;
		BITMAPINFO bmpInfo = {};
		bmpInfo.bmiHeader.biSize = sizeof ( BITMAPINFOHEADER );
		bmpInfo.bmiHeader.biWidth = bmpW;
		bmpInfo.bmiHeader.biHeight = -bmpH;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 24;
		LPVOID pBits = 0;
		HBITMAP hBmp = CreateDIBSection ( 0, & bmpInfo, DIB_RGB_COLORS, (LPVOID*)& pBits, 0, 0 );
		HBITMAP oldBmp = (HBITMAP)SelectObject ( memDC, hBmp );

		//背景色を青で塗りつぶし
		HBRUSH hBrBg = (HBRUSH)CreateSolidBrush ( 0x000000FF );
		FillRect ( memDC, & charWH, hBrBg );
		DeleteObject ( hBrBg );

		//パスの塗りつぶし(ブラシ)と線(ペン)
		HPEN hPen = (HPEN)CreatePen ( PS_SOLID, penSize, 0x0000FF00 );
		HBRUSH hBr = (HBRUSH)CreateSolidBrush ( 0x00FF0000 );
		HPEN oldPen = (HPEN)SelectObject ( memDC, hPen );
		HBRUSH oldBr = (HBRUSH)SelectObject ( memDC, hBr );

		SetBkMode ( memDC, TRANSPARENT );
		BeginPath ( memDC );
		TextOut ( memDC, -charRegion.left, -charRegion.top, str, 1 );
		EndPath ( memDC );
		BOOL bRet = StrokeAndFillPath ( memDC );

		//後処理
		SelectObject ( memDC, oldPen );
		SelectObject ( memDC, oldBr );
		SelectObject ( memDC, oldFont );
		SelectObject ( memDC, oldBmp );
		DeleteObject ( hBr );
		DeleteObject ( hPen );
		DeleteObject ( hFont );

		//テクスチャの作成
#if 0


		int txW = charWH.right / q;
		int txH = charWH.bottom / q;
		int q2 = q * q;
		Dx3D::instance()-> GetDevice ()->CreateTexture ( 
			txW,
			txH,
			1,
			0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,
			& m_tx,
			nullptr
		);

		D3DLOCKED_RECT lcRect;
		if ( SUCCEEDED ( m_tx->LockRect ( 0, & lcRect, 0, 0 ) ) )
		{
			void * d = (void *)lcRect.pBits;
			unsigned BMPPitch = (charWH.right * 3 + 3) / 4 * 4;
			for ( int y = 0; y < txH; ++ y )
			{
				for ( int x = 0; x < txW; ++ x )
				{
					unsigned & v = *( (unsigned*)d + x + y * txH );	//テクスチャのピクセル位置
					unsigned alph = 0;
					unsigned edge = 0;
					unsigned fill = 0;

					//quality倍率分点を平均化
					for ( int i = 0; i < q; ++ i )
					{
						for ( int j = 0; j < q; ++ j )
						{
							alph += pBits[(y * q + i) * BMPPitch + (x * 1 + j) * 3 + 0];
							edge += pBits[(y * q + i) * BMPPitch + (x * 1 + j) * 3 + 1];
							fill += pBits[(y * q + i) * BMPPitch + (x * 1 + j) * 3 + 2];
						}
					}
					alph /= q2;
					edge /= q2;
					fill /= q2;
#if 0


					//透過度がある場合はエッジ色を採用
					//不透明の場合はブレンド色を採用
					unsigned a = 0xff - alph;
					if ( a < 0xff )
					{
						//半透明
						unsigned r = 0x80;
						unsigned g = 0x80;
						unsigned b = 0x80;
						a = (a * 0xff) >> 8;
//						v = a << 24 | r << 16 | g << 8 | b;
						v = 0xffffffff;
					}
					else
					{
						//不透明
						unsigned r = 0x80;
						unsigned g = 0x80;
						unsigned b = 0x80;
						a = (a * 0xff) >> 8;
//						v = a << 24 | r << 16 | g << 8 | b;
						v = 0xffffffff;
					}
#endif // 0
				}
			}

			m_tx->UnlockRect ( 0 );
		}
#endif // 0

		m_mmrTx = new GameTextureFromMemory ( pBits, bmpInfo.bmiHeader.biSize );


		DeleteObject ( hBmp );
		ReleaseDC ( HWnd::Get (), memDC );

#if 0
		//テクスチャのテスト
		tstring tstr = _T( "テスト" );
		GameText::instance ()->MakeStrTexture ( tstr, m_tx, m_vtx );
#endif // 0
	}

	void TestOutlineFont::Move ()
	{
		m_vtx.ApplyPos ();
		m_vtx.SetVertexBuffer ();
	}

	void TestOutlineFont::Draw ()
	{
	}

	void TestOutlineFont::DrawVertex ()
	{
		m_vtx.DrawVertex ( m_tx );
	//	m_vtx.DrawVertex ( nullptr );
	}


}	//namespace GAME


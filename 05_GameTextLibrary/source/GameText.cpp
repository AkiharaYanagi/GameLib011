﻿//=================================================================================================
//
// ゲームテキスト　ヘッダ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameText.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//======================================================================================
	//◆フォント

	//フォントに関連付けたデバイスコンテキストハンドル
	HDC_Font::HDC_Font ()
		: m_font ( nullptr ), m_oldFont ( nullptr ), m_hdc ( nullptr )
	{
	}

	HDC_Font::~HDC_Font ()
	{
	}

	void HDC_Font::MakeFont ( UINT fontSize )
	{
		//すでに生成されているとき何もしない
		if ( m_font != nullptr || m_oldFont != nullptr || m_hdc ) { return; }

		//フォントの生成
		LOGFONT logfont = { (LONG)fontSize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
			CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("ＭＳ ゴシック") };
		if ( ! ( m_font = CreateFontIndirect ( &logfont ) ) ) { return; }

		//デバイスコンテキスト取得
		//デバイスにフォントを持たせなければ、GetGlyphOutline関数はエラーとなる
		m_hdc = GetDC ( nullptr );
		m_oldFont = ( HFONT ) SelectObject ( m_hdc, m_font );
	}

	void HDC_Font::Rele ()
	{
		if ( m_font != nullptr && m_oldFont != nullptr && m_hdc )
		{
			//デバイスコンテキストとフォントハンドルの解放
			SelectObject ( m_hdc, m_oldFont );
			DeleteObject ( m_font );
			ReleaseDC ( nullptr, m_hdc );
			m_font = nullptr;
			m_oldFont = nullptr;
			m_hdc = nullptr;
		}
	}

	HDC HDC_Font::GetHDC () const
	{
//		SelectObject ( m_hdc, m_font );
		return m_hdc; 
	}


	//======================================================================================
	//◆GameText

	//-------------------------------------------------------------------------------
	//static実体
	unique_ptr < GameText > GameText::m_inst = nullptr;
	const UINT GameText::N_ASCII = 128;
	const UINT GameText::N_ASCII_X = 16;
	const UINT GameText::N_ASCII_Y = 8;

	//-------------------------------------------------------------------------------
	//シングルトン

	//コンストラクタ
	GameText::GameText ()
		: m_D3DDev (nullptr), m_fontSizeIndex ( HDC_Font::FONT_SIZE_8 )
		, m_sizeTxAscii ( { 0, 0 } )
	{
	}

	//-------------------------------------------------------------------------------


	void GameText::Load ( D3DDEV d3dDevice )
	{
		m_D3DDev = d3dDevice;	//デバイスの解放は引数の元で行う

		//フォントの作成
		m_hdcFont.MakeFont ( fontSizeArray[ HDC_Font::FONT_SIZE_24 ] );
#if	0
		for ( UINT i = 0; i < HDC_Font::FONT_SIZE_NUM; ++i )
		{
			m_hdcFont[ i ].MakeFont ( fontSizeArray[ i ] );
		}
#endif	//0

		MakeAsciiTexture ();
	}

	void GameText::Rele ()
	{
		m_hdcFont.Rele ();
#if	0
		for ( UINT i = 0; i < HDC_Font::FONT_SIZE_NUM; ++i )
		{
			m_hdcFont[ i ].Rele ();
		}
#endif	//0

		RELEASE ( m_txAscii );
	}

	void GameText::Reset ( D3DDEV d3dDevice )
	{
		Rele ();
		Load ( d3dDevice );
	}

	//------------------------------------------
	//	文字列からテクスチャを作成
	//------------------------------------------
	void GameText::MakeStrTexture ( tstring& tstr, TX& texture, DxVertexRect& vertex )
	{
		HRESULT hr;
		UINT size = tstr.size();	//文字数
		UINT textureWidth = 0;		//文字幅の和によるテクスチャの総幅

		if ( size == 0 ) { return; }	//サイズが０のときは何もしない

		BYTE** pBmpArray = nullptr;
		GLYPHMETRICS* gmArray = nullptr;

		try 
		{
			pBmpArray = new BYTE* [size];
			gmArray = new GLYPHMETRICS [size];

			//一文字につき、ビットマップ(new)とGLYPHMETRICSを取得
			for ( UINT i = 0; i < size; i++ )
			{
				GetGlyph ( &tstr.at(i), &pBmpArray[i], &gmArray[i] );
				textureWidth += gmArray[i].gmCellIncX;		//総幅
			}

			//デバイスコンテキストに基づくテキストメトリクスを取得
			TEXTMETRIC tm;
			GetTextMetrics ( m_hdcFont.GetHDC(), &tm );
//			GetTextMetrics ( m_hdcFont[ m_fontSizeIndex ].GetHDC(), &tm );

			//頂点位置の更新
			vertex.SetWidth ( textureWidth * 1.f );
			vertex.SetHeight ( tm.tmHeight * 1.f );
			vertex.ApplyPos ();

			//テクスチャ確保
			//今までのテクスチャを破棄
			RELEASE ( texture );
			//空のテクスチャ作成 (今回作成したテクスチャは呼び出し元で解放する)
			hr = m_D3DDev->CreateTexture ( textureWidth, tm.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture, nullptr );
			if ( FAILED ( hr ) )
			{
				DXTRACE ( hr, TEXT("D3DPOOL_DEFAULT テクスチャの作成失敗") );
				hr = m_D3DDev->CreateTexture ( textureWidth, tm.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, nullptr );
				FAILED_DXTRACE_THROW( hr, TEXT("D3DPOOL_MANAGED テクスチャ作成に失敗\n") );
			}

			//書込
			//テクスチャをロックしてフォントビットマップを書込
			D3DLOCKED_RECT lockedRect;
			hr = texture->LockRect ( 0, &lockedRect, nullptr, D3DLOCK_DISCARD );
			if ( FAILED ( hr ) )
			{
				DXTRACE ( hr, TEXT("D3DLOCK_DISCARD ロックレクト失敗") );
				hr = texture->LockRect ( 0, &lockedRect, nullptr, 0 );
				FAILED_DXTRACE_THROW( hr, TEXT("ロックレクト失敗") );
			}

			//フォント情報の書込
			// GLYPHMETRICSのOriginは左上を示している
			int level = 17;

			//テクスチャを0で埋める
			ZeroMemory ( lockedRect.pBits, lockedRect.Pitch * tm.tmHeight );

			//テキストの最小限範囲(BlackBox)の部分についてα値を取得し、テクスチャの対応する位置に書き込む
			UINT posBaseX = 0;
			for ( UINT i = 0; i < size; i++ )
			{
				int bmp_w = gmArray[i].gmBlackBoxX + ( 4 - ( gmArray[i].gmBlackBoxX % 4 ) ) % 4;
				int bmp_h = gmArray[i].gmBlackBoxY;
				for ( int y = 0; y < bmp_h; y++ )
				{
					for ( int x = 0; x < bmp_w; x++ )
					{
						DWORD alpha = 255 * pBmpArray[i][x + (bmp_w * y)] / ( level - 1 );
						DWORD color = 0x00ffffff | (alpha << 24);
						memcpy ( (BYTE*)lockedRect.pBits + ( 4 * ( x + gmArray[i].gmptGlyphOrigin.x + posBaseX ) )
									+ ( lockedRect.Pitch * ( y + ( tm.tmAscent - gmArray[i].gmptGlyphOrigin.y ) ) ), 
								&color, 
								sizeof ( DWORD ) );
					}
				}
				posBaseX += gmArray[i].gmCellIncX;
			}

			//アンロック
			texture->UnlockRect ( 0 );

			//一時データの解放処理
			DeleteGlyph ( size, pBmpArray, gmArray );
		}
		catch ( LPCTSTR str )
		{
			OutputDebugString ( str );
			////TRACE_F ( str );
			DeleteGlyph ( size, pBmpArray, gmArray );
			//PostQuitMessage ( 0 );
		}
	}

	//------------------------------------------
	//	Ascii文字列から1枚テクスチャを作成
	//------------------------------------------
	void GameText::MakeAsciiTexture ()
	{
		HDC hdc = m_hdcFont.GetHDC ();

		//フォントに対するテキストメトリクスを取得
		TEXTMETRIC tm;
		::GetTextMetrics ( hdc, & tm );

		//グリフ(字体)メトリクスを取得
		const MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
		const UINT BMP_FMT = GGO_GRAY4_BITMAP;	//最大アンチエイリアス レベル17
		const UINT aaLv = 17;
		GLYPHMETRICS gm;
		short max_gm_x = 0;
//		UINT max_gm_x = 0;
		DWORD bmpsize [ N_ASCII ] = { 0 };	//各サイズ

		//対象文字コードに対し、ビットマップ指定をnullptrにしてサイズだけを取得する
		for ( UINT t = 0; t < N_ASCII; ++ t )
		{
			bmpsize [ t ] = ::GetGlyphOutline ( hdc, t, BMP_FMT, & gm, 0, nullptr, & mat );

			//最大幅を保存
			if ( max_gm_x < gm.gmCellIncX ) { max_gm_x = gm.gmCellIncX; }
//			if ( max_gm_x < gm.gmBlackBoxX ) { max_gm_x = gm.gmBlackBoxX; }
		}
		TRACE_F ( _T ( "max_gm_x = %d\n" ), max_gm_x );


		//テクスチャの作成
		UINT CH_W = max_gm_x;				//1文字サイズW
		UINT CH_H = tm.tmHeight;			//1文字サイズH
		UINT TX_W = CH_W * N_ASCII_X;		//テクスチャサイズW
		UINT TX_H = CH_H * N_ASCII_Y;		//テクスチャサイズH
		m_sizeTxChar.w = CH_W;
		m_sizeTxChar.h = CH_H;
		m_sizeTxAscii.w = TX_W;
		m_sizeTxAscii.h = TX_H;

		HRESULT hr;
		DWORD USAGE = D3DUSAGE_DYNAMIC;
		D3DFORMAT D3DFMT = D3DFMT_A8R8G8B8;
//		D3DPOOL POOL = D3DPOOL_DEFAULT;
		D3DPOOL POOL = D3DPOOL_MANAGED;
		hr = m_D3DDev->CreateTexture ( TX_W, TX_H, 1, USAGE, D3DFMT, POOL, & m_txAscii, nullptr );
		if ( FAILED ( hr ) )
		{
			DXTRACE ( hr, TEXT ( "D3DPOOL_DEFAULT テクスチャの作成失敗" ) );
			hr = m_D3DDev->CreateTexture ( TX_W, TX_H, 1, 0, D3DFMT, D3DPOOL_MANAGED, & m_txAscii, nullptr );
			FAILED_DXTRACE_THROW ( hr, TEXT ( "D3DPOOL_MANAGED テクスチャ作成に失敗\n" ) );
		}

		//ロックして書込
		D3DLOCKED_RECT lockedRect;
		hr = m_txAscii->LockRect ( 0, & lockedRect, nullptr, D3DLOCK_DISCARD );
		::ZeroMemory ( lockedRect.pBits, lockedRect.Pitch * TX_H/2 );
		


		//保存用ビットマップを確保してから再取得
		for ( UINT t = 0; t < N_ASCII; ++ t )
		{
			DWORD size = bmpsize [ t ];
			if ( 0 == size ) { continue; }

			unique_ptr < BYTE[] > ppBmp = make_unique < BYTE[] > ( size );
			::GetGlyphOutline ( hdc, t, BMP_FMT, & gm, size, ppBmp.get(), & mat );

			//テクスチャ位置
			const UINT P = sizeof ( DWORD );	//1ピクセルを表すバイト数
			const UINT LINE = P * TX_W;	//1ラインのバイト数

			//グリフデータの読込バイト列(4バイト境界)からxy平面に展開する
			UINT bmp_w = gm.gmBlackBoxX + ( P - ( gm.gmBlackBoxX % P ) ) % P;
			UINT bmp_h = gm.gmBlackBoxY;

			for ( UINT y = 0; y < bmp_h; ++ y )
			{
				for ( UINT x = 0; x < bmp_w; ++ x )
				{
					//----------------------------------------------
					//Src : BMP位置
					UINT offsetBmp = x + bmp_w * y;
					DWORD alpha = ppBmp [ offsetBmp ] * 255 / ( aaLv - 1 );
					DWORD color = 0x00ffffff | ( alpha << 24 );

					//----------------------------------------------
					//Dst : テクスチャ位置

					//tによる基準位置
					UINT by = LINE * CH_H * ( t / N_ASCII_X );
					UINT bx = P * CH_W * ( t % N_ASCII_X );
					UINT base_t = bx + by;

					//TextMetricsによる差分位置
					UINT tm_y = LINE * (tm.tmAscent - gm.gmptGlyphOrigin.y);
					UINT tm_x = P * ( gm.gmptGlyphOrigin.x );
					UINT tmpt = tm_x + tm_y;

					//x,yによる差分位置
					UINT oy = LINE * y;
					UINT ox = P * x;
					UINT xypt = ox + oy;

					//書込位置
					UINT offset = base_t + tmpt + xypt;
					LPBYTE adress = (LPBYTE)lockedRect.pBits + offset;

					//コピー
					memcpy_s ( adress, P, & color, P );
				}
			}
		}

		//アンロック
		hr = m_txAscii->UnlockRect ( 0 );
	}


	//--------------------------------------------------
	//一時グリフデータの解放
	void GameText::DeleteGlyph ( UINT size, BYTE** pBmpArray, GLYPHMETRICS* gmArray ) const 
	{
		if ( gmArray ) { delete[] gmArray; }
		gmArray = nullptr;
		if ( pBmpArray )
		{
			for ( UINT i = 0; i < size; i++ )
			{
				if ( pBmpArray[i] ) { delete[] pBmpArray[i]; }
				pBmpArray[i] = nullptr;
			}
			delete[] pBmpArray;
		}
		pBmpArray = nullptr;
	}


	//文字ビットマップデータ取得
	void GameText::GetGlyph ( PTCHAR ptch, BYTE** ppBmp, LPGLYPHMETRICS lpGm ) const
	{
		try
		{
			CONST MAT2 mat = {{0,1},{0,0},{0,0},{0,1}};
			UINT code = GetCode ( ptch );

			//対象ビットマップをnullptrで呼び出し、サイズを取得する
			DWORD bmpSize = ::GetGlyphOutline ( m_hdcFont.GetHDC(), code, GGO_GRAY4_BITMAP, lpGm, 0, nullptr, &mat );
//			DWORD bmpSize = ::GetGlyphOutline ( m_hdcFont[ m_fontSizeIndex ].GetHDC(), code, GGO_GRAY4_BITMAP, lpGm, 0, nullptr, &mat );
			//フォントがなかった場合のエラー処理
			if ( bmpSize == GDI_ERROR ) { throw TEXT("フォントビットマップの取得に失敗しました\n"); }

			//ビットマップを確保してから再取得
			*ppBmp = new BYTE[bmpSize];		//deleteは呼出側が行う
			::GetGlyphOutline ( m_hdcFont.GetHDC(), code, GGO_GRAY4_BITMAP, lpGm, bmpSize, *ppBmp, &mat );
//			::GetGlyphOutline ( m_hdcFont[ m_fontSizeIndex ].GetHDC(), code, GGO_GRAY4_BITMAP, lpGm, bmpSize, *ppBmp, &mat );
		}
		catch ( LPCTSTR str )
		{
			OutputDebugString ( str );
			////TRACE_F ( str );
		}
	}


	//文字コード取得
	UINT GameText::GetCode ( PTCHAR ptch ) const
	{
#if	_UNICODE

		//UNICODEの場合、文字コードは単純にワイド文字のUINT変換
		return (UINT)*ptch;

#else	//_UNICODE

		UINT code;
		//マルチバイト文字の場合、
		//1バイト文字のコードは1バイト目のUINT変換、
		//2バイト文字のコードは[先導コード]*256 + [文字コード]
		if ( IsDBCSeadByte(*ptch) ) { code = (BYTE)ptch[0] << 8 | (BYTE)ptch[1]; }
		else { code = ptch[0]; }
		return code;

#endif	//_UNICODE
	}


	VEC2 GameText::GetChToPos ( char ch )
	{
		float x = 1.f * m_sizeTxChar.w * (ch % N_ASCII_X);
		float y = 1.f * m_sizeTxChar.h * (ch / N_ASCII_X);
		return VEC2 ( x, y );
	}


}	//namespace GAME


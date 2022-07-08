//=================================================================================================
//
// ゲームテキスト　ヘッダ
//		ゲーム画面に表示するテキストのフォントなどを監理するクラス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "DirectX_Library.h"
#include "GameTask.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//フォントに関連付けたデバイスコンテキストハンドル
	class HDC_Font
	{
	public:
		enum FONT_SIZE
		{
			FONT_SIZE_8  = 0,
			FONT_SIZE_16 = 1,
			FONT_SIZE_24 = 2,
			FONT_SIZE_32 = 3,
			FONT_SIZE_64 = 4,
			FONT_SIZE_NUM = 5,
		};

	private:
		HFONT		m_font;				//フォント
		HFONT		m_oldFont;			//現状保存用フォント
		HDC			m_hdc;				//デバイスコンテキストハンドル

	public:
		HDC_Font ();
		HDC_Font ( const HDC_Font& rhs ) = delete;
		~HDC_Font ();

		void MakeFont ( UINT fontSize );
		void Rele ();

		HDC GetHDC () const;
	};

	const UINT fontSizeArray[ HDC_Font::FONT_SIZE_NUM ] = 
	{
		8, 
		16, 
		24, 
		32, 
		64,
	};


	//=================================================================================================
	//	ゲーム画面に表示するテキストのフォントなどを監理し、
	//	文字列からテクスチャを取得できる
	//	テクスチャの解放は呼び出し側で行う
	//=================================================================================================
	class GameText
	{
		//--------------------------------------------------
		//シングルトンパターン
		using P_GAME_TXT = unique_ptr < GameText >;
		static P_GAME_TXT		m_inst;
		GameText ();
		GameText ( const GameText& rhs ) = delete;
	public:
		~GameText () {}
		static void Create () { if ( m_inst ) { m_inst = P_GAME_TXT ( new GameText () ); } }
		static P_GAME_TXT & Inst () { return m_inst; }
		//--------------------------------------------------

	private:

		D3DDEV					m_D3DDev;		//Direct3D　デバイス
		HDC_Font				m_hdcFont;
		HDC_Font::FONT_SIZE		m_fontSizeIndex;

		//ASCIIコードテクスチャ
		TX		m_txAscii;
		static const UINT	N_ASCII;	//アスキー文字(表示用128種)
		static const UINT	N_ASCII_X;	//テクスチャ配置
		static const UINT	N_ASCII_Y;	//テクスチャ配置

	public:
		void Load ( D3DDEV d3dDevice );
		void Rele ();
		void Reset ( D3DDEV d3dDevice );

		//文字列をテクスチャに書込
		void MakeStrTexture ( tstring& tstr, TX& lpTexture, DxVertexRect& vertex );

		//Ascii文字列からテクスチャを作成
		void MakeAsciiTexture ();

		//文字データ取得
		//引数 [in]	 LPTCHAR				: 1文字
		//引数 [out] BYTE** ppBmp			: 1文字のビットマップデータ
		//引数 [out] LPGLYPHMETRICS lpGm	: グリフメトリクス
		void GetGlyph ( PTCHAR ptch, BYTE** ppBmp, LPGLYPHMETRICS lpGm ) const;

		//コード取得
		UINT GetCode ( PTCHAR ptch ) const;

		//一時グリフデータの解放
		void DeleteGlyph ( UINT size, BYTE** pBmpArray, GLYPHMETRICS* gmArray ) const;

		//フォントサイズの設定
		void SetFontSize ( HDC_Font::FONT_SIZE fontSize ) { m_fontSizeIndex = fontSize; }
	};


}	//namespace GAME


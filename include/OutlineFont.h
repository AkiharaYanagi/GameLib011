//=================================================================================================
//
//	アウトラインフォント
//		フォントを指定し、文字列からテクスチャを返す
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "Dx3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class OutlineFont
	{
		//--------------------------------------------------
		//シングルトンパターン
		static std::unique_ptr < OutlineFont >	m_inst;
		OutlineFont ();
		OutlineFont ( const OutlineFont& rhs ) = delete;
	public:
		~OutlineFont ();
		static std::unique_ptr < OutlineFont > & Inst () { return m_inst; }
		static void Create ();
		//--------------------------------------------------

	private:
		HDC			m_memDC;		//メモリデバイスコンテキスト
		D3DDEV		m_lpD3DDevice;	//Direct3D　デバイス

		TCHAR		m_fontName[ LF_FACESIZE ];	//フォント名(FaceName)
		int			m_fontSize;		//フォントサイズ
		int			m_penSize;		//ペンサイズ
		int			m_quality;		//アンチエイリアス(拡大→平均化)の度合
		DWORD		m_fillColor;
		DWORD		m_edgeColor;
		
		int			m_txW;			//テクスチャサイズW
		int			m_txH;			//テクスチャサイズH
		int			m_gmX;			//グリフメトリクスX
		int			m_gmY;			//グリフメトリクスY

		int			m_gmCellIncX;	//次の基準位置

	public:
		void Load ( D3DDEV pDev );
		void Reset ( D3DDEV pDev );

		void SetParam ( int fontSize, int penSize, int quolity );
		void SetFontFace ( LPCTSTR fontname );
		void SetColor ( DWORD fill, DWORD edge );

		TX Make ( LPCTSTR str, DWORD edgeColor, DWORD fillColor );
		TX MakeStrTx ( LPCTSTR str, DWORD edgeColor, DWORD fillColor );

		POINT GetSize () const { POINT ret = { m_txW, m_txH }; return ret; }
		POINT GetPos () const { POINT ret = { m_gmX, m_gmY }; return ret; }
		int GetGmCellIncX () const { return m_gmCellIncX; }

		//色構造体
		struct Color
		{
			BYTE A, R, G, B;
			DWORD color;
			Color ( DWORD color )
				: color ( color ),
				B ( color & 0xff ),
				G ( (color >> 8) & 0xff ),
				R ( (color >> 16) & 0xff ),
				A ( (color >> 24) & 0xff )
			{}
		};
	};


#define OLF				OutlineFont::Inst()
#define OLF_MAKE_STRTX	OutlineFont::Inst()->MakeStrTx


}	//namespace GAME


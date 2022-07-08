//=================================================================================================
//
//	アウトラインフォント
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class OutlineFont	: public GameTaskVector
	{
		//--------------------------------------------------
		//シングルトンパターン
		static unique_ptr < OutlineFont >	m_inst;
		OutlineFont ();
	public:
		OutlineFont ( const OutlineFont& rhs ) = delete;
		~OutlineFont ();
		static unique_ptr < OutlineFont > & Inst () { return m_inst; }
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
		void Load ( LPDIRECT3DDEVICE9 pDev );

		void SetParam ( int fontSize, int penSize, int quolity );
		void SetFontFace ( LPCTSTR fontname );

		TX Make ( LPCTSTR str, DWORD edgeColor, DWORD fillColor );

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


}	//namespace GAME


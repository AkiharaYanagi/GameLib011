//=================================================================================================
//
// GrpStr ヘッダファイル
//	単純な文字列のグラフィック
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
	//文字列から生成されるゲームテクスチャ
	class GameTextureFromString : public TxBs
	{
		tstring		m_str;
		
		int			m_fontSize;
		int			m_penSize;
		int			m_quality;
		DWORD		m_fillColor;
		DWORD		m_edgeColor;
		TCHAR		m_fontName [ LF_FACESIZE ];	//フォント名(FaceName)

	public:
		GameTextureFromString ();
		GameTextureFromString ( const GameTextureFromString& rhs ) = delete;
		~GameTextureFromString ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR str );

		void SetParam ( int fontSize, int penSize, int quolity );
		void SetFontFace ( LPCTSTR fontname );
		void SetColor ( DWORD fill, DWORD edge );
	};

	using TxStr = GameTextureFromString;
	using P_TxStr = shared_ptr < TxStr >;


	//-------------------------------------
	class GrpStr : public GrpApTx
	{
		P_TxStr		m_tx;

	public:
		GrpStr ();
		GrpStr ( const GrpStr & rhs ) = delete;
		~GrpStr ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR str );

		void SetFontParam ( int fontSize, int penSize, int quolity );
		void SetFontFace ( LPCTSTR fontname );
		void SetFontColor ( DWORD fill, DWORD edge );
	};

	using P_GrpStr = shared_ptr < GrpStr >;


}	//namespace GAME



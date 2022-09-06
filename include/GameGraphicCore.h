//=================================================================================================
//
//	ゲームグラフィック コア
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "GameTask.h"
#include "GameTexture.h"
#include "GameObject.h"
#include <vector>
#include "Fade.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//■=======================================================================
	// ゲームグラフィック　コア
	//		・ゲームプリミティブ(頂点のみ描画)も含んだグラフィック全般
	//■=======================================================================
	class GameGraphicCore : public GameTask
	{
	protected:
		bool		m_valid;		//有効フラグ
//		_CLR		m_color;		//色

	private:
		Fade		m_fade;			//フェード

	public:
		GameGraphicCore ();
		GameGraphicCore ( const GameGraphicCore & rhs ) = delete;
		~GameGraphicCore () {}

		virtual float GetZ () const = 0;

		//毎フレーム事前動作
		void PreMove ();

		//有効・無効
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () { return m_valid; }

		//色
//		void SetColor ( _CLR clr ) { m_color = clr; }
		void SetColor ( _CLR clr ) { m_fade.SetColor ( clr ); }
		_CLR GetColor () const { return m_fade.GetColor (); }

		//フェード
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			m_valid = true;
			m_fade.SetFade ( time, clr_start, clr_end ); 
		}
		void SetFadeIn  ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0x00ffffff, 0xffffffff );
		}
		void SetFadeOut ( UINT time ) 
		{
			m_valid = true;
			m_fade.SetFade ( time, 0xffffffff, 0x00ffffff );
		}
		void EndFade ( _CLR clr ) { m_fade.End ( clr ); }
	};


	//型指定
	typedef		GameGraphicCore			GrpCr;
	typedef		shared_ptr < GrpCr >	P_GrpCr;


}	//namespace GAME


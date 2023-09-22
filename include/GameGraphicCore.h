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

	private:
		Fade		m_fade;			//フェード

	public:
		GameGraphicCore ();
		GameGraphicCore ( const GameGraphicCore & rhs ) = delete;
		~GameGraphicCore () {}

		//基本動作
		virtual void TxLoad () {}		//読込
		virtual void TxRele () {}		//解放
		virtual void TxReset () {}		//再設定

		virtual void Draw () {}			//スプライト描画
		virtual void DrawVertex () {}	//頂点描画

		virtual float GetZ () const { return 0; };


		//毎フレーム事前動作
		void PreMove ();

		//有効・無効
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () { return m_valid; }

		//色
		void SetColor ( _CLR clr ) { m_fade.SetColor ( clr ); }
		_CLR GetColor () const { return m_fade.GetColor (); }

		//フェード
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			m_valid = true;
			m_fade.SetFade ( time, clr_start, clr_end ); 
		}
		void SetFadeIn ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0x00ffffff, 0xffffffff );
		}
		void SetFadeIn ( UINT time, _CLR endColor )
		{
			m_valid = true;
			_CLR startColor = _CLR ( endColor.r, endColor.g, endColor.b, 0 );
			m_fade.SetFade ( time, startColor, endColor );
		}
		void SetFadeOut ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0xffffffff, 0x00ffffff );
		}
		void SetFadeOut ( UINT time, _CLR startColor )
		{
			m_valid = true;
			_CLR endColor = _CLR ( startColor.r, startColor.g, startColor.b, 0 );
			m_fade.SetFade ( time, startColor, endColor );
		}
		void EndFade ( _CLR clr ) { m_fade.End ( clr ); }
	};


	//型指定
	using	GrpCr = GameGraphicCore;
	using	P_GrpCr = shared_ptr < GrpCr >;
	using	LP_GrpCr = list < P_GrpCr >;
	using	PLP_GrpCr = shared_ptr < LP_GrpCr >;


}	//namespace GAME


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
		_CLR		m_color;		//色

	private:
#if 0

		UINT		m_wait;			//表示時間（０なら常時）
		UINT		m_waitTimer;	//内部タイマ[F]

		UINT		m_fadeIn;		//フェードイン時間
		UINT		m_fadeInTimer;	

		UINT		m_fadeOut;		//フェードアウト時間
		UINT		m_fadeOutTimer;

#endif // 0

		_Fade		m_fade;			//フェード

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
		void SetColor ( _CLR clr ) { m_color = clr; }

		//フェード
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			m_fade.SetFade ( time, clr_start, clr_end );
		}
		void EndFade ( _CLR clr ) { m_fade.End ( clr ); }

#if 0

		//表示時間（０なら常時、１以上は時間経過後非表示）
		void SetWait ( UINT time );

		//フェード時間設定
		void SetFadeOut ( UINT time );
		void SetFadeIn ( UINT time );


	private:
		//---------------------------------------------------------------------
		//内部関数
		void _Wait ();
		void _FadeOut ();
		void _FadeIn ();

#endif // 0
	};


	//型指定
	typedef		GameGraphicCore			GrpCr;
	typedef		shared_ptr < GrpCr >	P_GrpCr;


}	//namespace GAME


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
		UINT		m_wait;			//表示時間（０なら常時）
		UINT		m_waitTimer;	//内部タイマ[F]

		UINT		m_fadeIn;		//フェードイン時間
		UINT		m_fadeInTimer;	

		UINT		m_fadeOut;		//フェードアウト時間
		UINT		m_fadeOutTimer;

	public:
		GameGraphicCore ();
		GameGraphicCore ( const GameGraphicCore & rhs ) = delete;
		~GameGraphicCore () {}

		virtual float GetZ () const = 0;

		void PreMove ();

		//有効・無効
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () { return m_valid; }

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
	};


	//型指定
	typedef		GameGraphicCore			GrpCr;
	typedef		shared_ptr < GrpCr >	P_GrpCr;


}	//namespace GAME


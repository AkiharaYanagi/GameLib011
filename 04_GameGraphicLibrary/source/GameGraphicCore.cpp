//=================================================================================================
//
//	ゲームグラフィック コア
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphicCore.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GameGraphicCore::GameGraphicCore () 
		: m_valid ( true ), m_color ( 0xffffffff ), 
		  m_wait ( 0 ), m_waitTimer ( 0 ), m_fadeIn ( 0 ), m_fadeOut ( 0 )
	{
	}

	void GameGraphicCore::PreMove ()
	{
		//ウェイトタイムが指定されているとき
		if (0 < m_wait)
		{
			_Wait ();
		}
		else if ( 0 < m_fadeOut )
		{
			_FadeOut ();	//フェードアウト
		}
		else if ( 0 < m_fadeIn )
		{
			_FadeIn ();	//フェードイン
		}
	}

	//表示時間（０なら常時）
	void GameGraphicCore::SetWait ( UINT time )
	{
		m_wait = time;
		m_waitTimer = 0;

		if (0 == time) { return; }

		m_valid = true;
	}

	void GameGraphicCore::_Wait ()
	{
		//待機：終了条件
		if ( ++ m_waitTimer == m_wait )
		{
			m_wait = 0;
			m_waitTimer = 0;
			m_valid = false;
		}
	}

	//フェードアウト設定
	void GameGraphicCore::SetFadeOut ( UINT time ) 
	{
		if (0 >= time) { return; }
		m_fadeOut = time; 
		m_fadeOutTimer = 0; 
	}
	
	void GameGraphicCore::_FadeOut ()
	{
		//フェードアウト：終了条件
		if ( ++ m_fadeOutTimer == m_fadeOut )
		{
			m_color.a = 1.f;
			m_fadeOut = 0;
			m_fadeOutTimer = 0;
			m_valid = false;
		}
		else
		{
			//α値を算出
			float alpha = 1.f - 1.f * m_fadeOutTimer / m_fadeOut;
			m_color.a = alpha;
		}
	}

	//フェードイン設定
	void GameGraphicCore::SetFadeIn ( UINT time ) 
	{
		if (0 >= time) { return; }
		m_fadeIn = time; 
		m_fadeInTimer = 0; 
		m_valid = true;
	}

	void GameGraphicCore::_FadeIn ()
	{
		//フェードイン：終了条件
		if ( ++ m_fadeInTimer == m_fadeIn )
		{
			m_color.a = 1.f;
			m_fadeIn = 0;
			m_fadeInTimer = 0;
			m_valid = true;
		}
		else
		{
			//α値を算出
			float alpha =  1.f * m_fadeInTimer / m_fadeIn;
			m_color.a = alpha;
		}

	}


}	//namespace GAME


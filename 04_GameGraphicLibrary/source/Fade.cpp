//=================================================================================================
//
//	フェード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Fade.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Fade::Fade ()
		: m_timer ( 0 ), m_time ( 0 )
		, m_color_present ( 0xffffffff )
		, m_color_start ( 0xffffffff ), m_color_end ( 0xffffffff )
	{
	}

	Fade::Fade ( const Fade & rhs )
	{
		m_timer = rhs.m_timer;
		m_time = rhs.m_time;
		m_color_present = rhs.m_color_present;
		m_color_start = rhs.m_color_start;
		m_color_end = rhs.m_color_end;
	}

	Fade::~Fade ()
	{
	}

	//毎フレーム動作(Move()内先頭で呼ぶ)
	void Fade::PreMove ()
	{
		if ( 0 < m_time )
		{
			_Fade_Do ();
		}
	}

	//フェードアウト設定
	void Fade::SetTime ( UINT time )
	{
		if ( 0 >= time ) { return; }
		m_time = time;
		m_timer = 0;

		m_color_present = m_color_start;
	}

	void Fade::_Fade_Do ()
	{
		//フェードアウト：終了条件
		if ( ++ m_timer == m_time )
		{
			m_color_present = m_color_end;
			m_time = 0;
			m_timer = 0;
		}
		else
		{
			//変化量を算出
			float d_a = ( m_color_end.a - m_color_start.a ) / m_time;
			float d_r = ( m_color_end.r - m_color_start.r ) / m_time;
			float d_g = ( m_color_end.g - m_color_start.g ) / m_time;
			float d_b = ( m_color_end.b - m_color_start.b ) / m_time;

			m_color_present += _CLR ( d_r, d_g, d_b, d_a );
		}
	}

	void Fade::End ( _CLR clr )
	{
		m_timer = 0;
		m_time = 0;
		m_color_present = clr;
	}

}	//namespace GAME


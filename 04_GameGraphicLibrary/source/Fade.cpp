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
		: m_timer ( 0 ), m_time ( 0 ), m_color_start ( 0xffffffff ), m_color_end ( 0xffffffff ),
		 m_active ( true )
	{
	}

	Fade::~Fade ()
	{
	}

	void Fade::PreMove ()
	{
		if ( 0 < m_time )
		{
			_Fade ();
		}
	}

	void Fade::Move ()
	{
		GrpAcv::Move ();
	}

	//フェードアウト設定
	void Fade::SetTime ( UINT time )
	{
		if (0 >= time) { return; }
		m_time = time; 
		m_timer = 0;

		m_color = m_color_start;
	}
	
	void Fade::_Fade ()
	{
		//フェードアウト：終了条件
		if ( ++ m_timer == m_time )
		{
			m_color = m_color_end;
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

			m_color += _CLR( d_r, d_g, d_b, d_a );
		}
	}


}	//namespace GAME


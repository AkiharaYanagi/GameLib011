//=================================================================================================
//
// Fade ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Timer.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Timer::Timer ()
	: m_active ( false ), m_time ( 0 ), m_targetTime ( 0 )
	{
	}

	Timer::~Timer ()
	{
	}

	void Timer::Move ()
	{
		if ( ! m_active ) { return; }

		if ( ++ m_time == m_targetTime )
		{
			m_time = 0;
			m_active = false;
		}

		GameTask::Move ();
	}


}	//namespace GAME


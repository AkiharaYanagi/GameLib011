//=================================================================================================
//
// Timer ヘッダファイル
//		GameTask状のカウントアップタイマ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameStructureLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Timer : public GameTask
	{
		bool	m_active;
		UINT	m_time;
		UINT	m_targetTime;

	public:
		Timer ();
		Timer ( UINT targetTime );	//目標時間
		Timer ( const Timer & rhs ) = delete;
		~Timer ();

		//@info Task型だが、手動でMove()のみを毎フレーム行えばAddpTask()の必要はない
		void Move ();

		//可動状態
		bool IsActive () const { return m_active; }

		//最終状態(同値になったらリセットされるので( 1 + m_time )で判定する)
		bool IsLast () const { return (m_targetTime == 1 + m_time); }

		void SetTime ( UINT i ) { m_time = 0; }
		UINT GetTime () const { return m_time; }
		
		//目標時間
		void SetTargetTime ( UINT time ) { m_targetTime = time; }
		UINT GetTargetTime () const { return m_targetTime; }

		//0からスタート
		void Start () { m_time = 0; m_active = true; }
		
		//前回の続きからスタート
		void ReStart () { m_active = true; }

		//ストップ
		void Stop () { m_active = false; }

		//クリア
		void Reset () { m_time = 0; m_active = false; }
	};

	using P_Timer = shared_ptr < Timer >;


}	//namespace GAME



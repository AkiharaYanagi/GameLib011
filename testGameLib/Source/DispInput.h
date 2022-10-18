//=================================================================================================
//
// DispInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
//#include "../../GameMain/GameConst.h"
//#include "../../CharaData/Chara.h"
//#include "../../FtgMain/G_Ftg.h"
//#include "../Input/CharaInput.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using VP_PRMRECT = vector < P_PrmRect >;
	using PVP_PRMRECT = shared_ptr < VP_PRMRECT >;
	using VPVP_PRMRECT = vector < PVP_PRMRECT >;

	class DispInput : public TASK_VEC
	{
		//キー入力表示個数
		static const UINT NUM_DISP_INPUT;

		P_PrmRect		m_bg;		//背景
		VPVP_PRMRECT	m_vpvpRect;	//キー種類 * [F]表示

		UINT			m_timer;
		float			m_vel;
		float			m_base;

	public:
		DispInput ();
		DispInput ( const DispInput & rhs ) = delete;
		~DispInput ();

		void InitDisp ( PLAYER_ID playerID );

		//入力更新
		void UpdateInput ( P_CharaInput pCharaInput );


	private:
		bool GetBoolInput ( P_CharaInput pCharaInput, int n, int i );
	};

}	//namespace GAME



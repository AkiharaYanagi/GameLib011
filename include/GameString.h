//=================================================================================================
//
//	文字列
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GameString	: public GameTaskVector
	{
		DxVertex4	m_vtx;
		TX			m_tx;
		tstring		m_str;

		vector < TX > m_vecTx;
		vector < P_Vx4 > m_vecVtx;

	public:
		GameString ();
		GameString ( const GameString & rhs ) = delete;
		~GameString ();

		void Load ();
		void Init ();
		void Move ();

		void DrawVertex ();

		void SetStr ( tstring str );
	};

	//型指定
	using	Str = GameString;
	using	P_Str = shared_ptr < Str >;


}	//namespace GAME


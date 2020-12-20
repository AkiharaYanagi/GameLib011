//=================================================================================================
//
//	ゲームウィンドウ内の文字列表示
//		頂点による矩形に１文字ごとのテクスチャを持つ
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
		tstring		m_str;
		DxVertex4	m_vtx;
		TX			m_tx;

		vector < TX > m_vecTx;
		vector < P_Vx4 > m_vecVtx;

		DWORD		m_fillColor;
		DWORD		m_edgeColor;

		bool		m_stream;
		UINT		m_timer;
		UINT		m_pitch;
		UINT		m_index;

	public:
		GameString ();
		GameString ( const GameString & rhs ) = delete;
		~GameString ();

		void Move ();
		void DrawVertex ();

		void SetStr ( tstring str );
		void SetPos ( VEC2 v );

		void On ();
		void Off ();
		void Stream ();
		void SetPitch ( UINT i ) { m_pitch = i; }

		void SetFillColor ( DWORD fillColor ) { m_fillColor = fillColor; }
		void SetEdgeColor ( DWORD edgeColor ) { m_edgeColor = edgeColor; }

	};

	//型指定
	using	Str = GameString;
	using	P_Str = shared_ptr < Str >;


}	//namespace GAME


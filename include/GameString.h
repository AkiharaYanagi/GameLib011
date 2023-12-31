//=================================================================================================
//
//	ゲームウィンドウ内の文字列表示
//		1文字ずつ流れるように表示できる
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
		VEC2		m_pos;

		vector < TX >	m_vecTx;
		vector < P_VxRct > m_vecVtx;

		DWORD		m_fillColor;
		DWORD		m_edgeColor;

		bool		m_stream;
		UINT		m_pitch;	// 1/1000 [F/char]
		UINT		m_timer;	// 1/1000
		UINT		m_index;
		UINT		m_count;

	public:
		GameString ();
		GameString ( const GameString & rhs ) = delete;
		~GameString ();

		void Load ();
		void Rele ();
		void Reset ();

		void Move ();
		void DrawVertex ();

		void SetStr ( tstring str );
		void SetPos ( VEC2 v );
		void ApplyPos ();

		void On ();
		void Off ();
		void Stream ();
		void Stream ( tstring str );
		void SetPitch ( UINT i ) { m_pitch = i; }

		void SetColor ( DWORD fill, DWORD edge ) {m_fillColor = fill; m_edgeColor = edge;}
		void SetFillColor ( DWORD fillColor ) { m_fillColor = fillColor; }
		void SetEdgeColor ( DWORD edgeColor ) { m_edgeColor = edgeColor; }

	private:
		void ResetStr ();

	};

	//型指定
	using	Str = GameString;
	using	P_Str = std::shared_ptr < Str >;


}	//namespace GAME


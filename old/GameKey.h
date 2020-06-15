//=================================================================================================
//
// GameKey ヘッダファイル
//
//	ゲームメインにおける1フレームのキー入力
//　8方向キー１つ、ボタン４つ
//
//	方向キーのコマンド指定では12369874順（反時計回り）
//
//	7 8 9
//	4   6
//	1 2 3
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <iostream>
#include <map>
using namespace std;

#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GameKey
	{
	public:
		//方向キー
		enum GAME_KEY_DIRECTION
		{
			NEUTRAL = 0,	//入力無
			DIR_1 = 1,
			DIR_2 = 2,
			DIR_3 = 3,
			DIR_6 = 4,
			DIR_9 = 5,
			DIR_8 = 6,
			DIR_7 = 7,
			DIR_4 = 8,

			//方向要素(Element)
			DIR_2E = 9,
			DIR_6E = 10,
			DIR_8E = 11,
			DIR_4E = 12,

			DIR_WILD = 13,		//条件として入力を要求しない
			DIR_NUM = 14		//個数
		};

		//Enum処理用配列
		static const GAME_KEY_DIRECTION gameKeyDirection [ DIR_NUM ];

		//ボタン
		static const UINT		GAME_KEY_BUTTON_NUM;	//4
		enum GAME_KEY_BUTTON
		{
			BTN_OFF = 0,		// 入力無
			BTN_ON = 1,			// 入力有
			BTN_WILD = 2		// どちらでも
		};

	private:
		GAME_KEY_DIRECTION		m_dir;
		GAME_KEY_BUTTON			m_button[4];

//#define	STR(var) #var	//引数にした変数から、変数名を示す文字列リテラルとして返す((#)が文字列化演算子)
		
		typedef map < tstring, GAME_KEY_DIRECTION > GAME_KEY_DIR_STR;
		typedef map < tstring, GAME_KEY_BUTTON > GAME_KEY_BTN_STR;

		//enumと文字列を変換するmap
		static GAME_KEY_DIR_STR		m_mapDirection;
		static GAME_KEY_BTN_STR		m_mapButton;

		//否定のフラグ
		bool		m_not;

	public:
		GameKey ();
		GameKey ( const GameKey & rhs );		//コピー可
		~GameKey ();

		//代入
		GameKey & operator = ( const GameKey & rhs );

		//比較
//		bool operator == ( const GameKey& rhs );

		//比較	this	入力
		//引数：	rhs		コマンド条件
		//		bDirRight	向き
		bool Compare ( const GameKey & rhs, bool bDirRight ) const;

		//方向キー
		void SetDir ( GAME_KEY_DIRECTION dir ) { m_dir = dir; }
		GAME_KEY_DIRECTION GetDir () const { return m_dir; }

		//ボタン
		void SetBtn ( UINT index, GAME_KEY_BUTTON button ) { m_button[index] = button; }
		GAME_KEY_BUTTON GetButton ( UINT index ) const { return m_button[index]; }

		//enumと文字列の変換
		static GAME_KEY_DIRECTION DirFromStr ( tstring str ) { return m_mapDirection [ str ]; }
		static GAME_KEY_BUTTON BtnFromStr ( tstring str ) { return m_mapButton [ str ]; }

		//否定のフラグ
		void SetNot ( bool b ) { m_not = b; }
		bool GetNot () const { return m_not; }
	};


	using SP_GameKey = shared_ptr < GameKey >;
	using V_GAME_KEY = vector < GameKey >;

}	//namespace GAME



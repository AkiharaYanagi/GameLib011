//=================================================================================================
//
// GameKey ソースファイル
//
//=================================================================================================


//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameKey.h"

//placement new
#include <new>


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//Enum処理用固定配列
	const UINT GameKey::GAME_KEY_BUTTON_NUM = 4;
	const GameKey::GAME_KEY_DIRECTION GameKey::gameKeyDirection [ DIR_NUM ] = 
	{
		NEUTRAL,
		DIR_1,
		DIR_2,
		DIR_3,
		DIR_6,
		DIR_9,
		DIR_8,
		DIR_7,
		DIR_4,
		DIR_2E,
		DIR_6E,
		DIR_8E,
		DIR_4E,
		DIR_WILD,		//条件として入力を要求しない
	};

	//名前文字列とEnum定義の連想配列
	GameKey::GAME_KEY_DIR_STR		GameKey::m_mapDirection;
	GameKey::GAME_KEY_BTN_STR		GameKey::m_mapButton;


	//コンストラクタ
	GameKey::GameKey () : 
		m_dir ( NEUTRAL ), m_not ( false )
	{
		//placement new による配列の初期化
		for ( UINT i = 0; i < GAME_KEY_BUTTON_NUM; ++i )
		{
			new ( m_button + i ) GAME_KEY_BUTTON ( BTN_OFF );
		}
		 
		//map
#if	1
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_1)), DIR_1 ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_2)), DIR_2 ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_3)), DIR_3 ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_6)), DIR_6 ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_9)), DIR_9 ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_8)), DIR_8 ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_7)), DIR_7 ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_4)), DIR_4 ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_2E)), DIR_2E ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_6E)), DIR_6E ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_8E)), DIR_8E ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_4E)), DIR_4E ) );
		m_mapDirection.insert ( GAME_KEY_DIR_STR::value_type ( _T(STR(DIR_WILD)), DIR_WILD ) );

#else	//0
		for ( UINT i = 0; i < DIR_NUM; ++i )
		{
			GAME_KEY_DIRECTION d = gameKeyDirection[i];
			tstring tstr = _T(STR( d ));
//			m_mapDirection[ STR( gameKeyDirection[i] ) ] = gameKeyDirection[i];
		}
#endif	//0

		m_mapButton[ _T(STR( BTN_OFF )) ] = BTN_OFF;
		m_mapButton[ _T(STR( BTN_ON )) ] = BTN_ON;
		m_mapButton[ _T(STR( BTN_WILD) ) ] = BTN_WILD;
	}

	GameKey::GameKey ( const GameKey& rhs )
	{
		m_dir = rhs.m_dir;
		for ( UINT i = 0; i < GAME_KEY_BUTTON_NUM; ++i )
		{
			m_button[i] = rhs.m_button[i];
		}
		m_not = rhs.m_not;
	}

	GameKey& GameKey::operator = ( const GameKey& rhs )
	{
		m_dir = rhs.m_dir;
		for ( UINT i = 0; i < GAME_KEY_BUTTON_NUM; ++i )
		{
			m_button[i] = rhs.m_button[i];
		}
		m_not = rhs.m_not;
		return (*this);
	}

	GameKey::~GameKey ()
	{
	}

//	bool GameKey::operator == ( const GameKey& rhs )
	bool GameKey::Compare ( const GameKey& rhs, bool bDirRight ) const 
	{
		//作業用
		GameKey gk = rhs;

		//比較するかどうか(条件がワイルドの時は比較しない)
		bool bWild_dir = false;
		bool bWild_button[4] = { false, false, false, false };

		//比較結果
		bool b_dir = false;
		bool b_button[4] = { false, false, false, false };

		//-----------------------------------------------------------------
		//方向

#if	0
		//左向きのとき左右を入れ替え
		//1<-->3 4<-->6 7<-->9
		if ( ! bDirRight )
		{
			switch ( gk.m_dir )
			{
			case GameKey::DIR_1:
				gk.m_dir = GameKey::DIR_3;
				break;
			case GameKey::DIR_4:
				gk.m_dir = GameKey::DIR_6;
				break;
			case GameKey::DIR_4E:
				gk.m_dir = GameKey::DIR_6E;
				break;
			case GameKey::DIR_7:
				gk.m_dir = GameKey::DIR_9;
				break;
			case GameKey::DIR_3:
				gk.m_dir = GameKey::DIR_1;
				break;
			case GameKey::DIR_6:
				gk.m_dir = GameKey::DIR_4;
				break;
			case GameKey::DIR_6E:
				gk.m_dir = GameKey::DIR_4E;
				break;
			case GameKey::DIR_9:
				gk.m_dir = GameKey::DIR_7;
				break;
			default:
				break;
			}
		}
#endif	//0

		//-----------------------------------------------------------------
		//条件がワイルドかどうか (両方がワイルドでない状態のみ比較)
		//方向
		if ( gk.m_dir != DIR_WILD && this->m_dir != DIR_WILD ) 
		{
			bWild_dir = true;	//比較する

			//要素判定
			switch ( gk.m_dir )
			{
			case GameKey::DIR_2E:
				if (		this->m_dir == GameKey::DIR_1  
						||	this->m_dir == GameKey::DIR_2
						||	this->m_dir == GameKey::DIR_3 ) { b_dir = true; }
				break;
			case GameKey::DIR_6E:
				if (		this->m_dir == GameKey::DIR_3  
						||	this->m_dir == GameKey::DIR_6
						||	this->m_dir == GameKey::DIR_9 ) { b_dir = true; }
				break;
			case GameKey::DIR_8E:
				if (		this->m_dir == GameKey::DIR_7  
						||	this->m_dir == GameKey::DIR_8
						||	this->m_dir == GameKey::DIR_9 ) { b_dir = true; }
				break;
			case GameKey::DIR_4E:
				if (		this->m_dir == GameKey::DIR_1  
						||	this->m_dir == GameKey::DIR_4
						||	this->m_dir == GameKey::DIR_7 ) { b_dir = true; }
				break;
			default:
				if ( this->m_dir == gk.m_dir ) { b_dir = true; }
				break;
			}
		}
		//-----------------------------------------------------------------
		//ボタン
		for ( UINT i = 0; i < GAME_KEY_BUTTON_NUM; ++i )
		{
			if ( gk.m_button[i] != BTN_WILD && this->m_button[i] != BTN_WILD ) 
			{
				bWild_button[i] = true;	//比較する
				if ( this->m_button[i] == gk.m_button[i] ) { b_button[i] = true; }
			}
		}

		//-----------------------------------------------------------------
		//まとめ

		//一つもチェックしない場合はfalse
		if ( ! bWild_dir && ! bWild_button[0] && ! bWild_button[1] && ! bWild_button[2] && ! bWild_button[3] ) { return false; }

		//いずれかを返す場合
		//すべてを満たすならtrue, 一つでも異なればfalse
		bool ret = true;
		if ( bWild_dir ) { ret &= b_dir; }
		if ( bWild_button[0] ) { ret &= b_button[0]; }
		if ( bWild_button[1] ) { ret &= b_button[1]; }
		if ( bWild_button[2] ) { ret &= b_button[2]; }
		if ( bWild_button[3] ) { ret &= b_button[3]; }

		//否定の場合は反転して返す（排他的論理和）
		return ret ^ gk.m_not;
	}


}	//namespace GAME


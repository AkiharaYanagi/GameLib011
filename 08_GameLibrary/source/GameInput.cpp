//=================================================================================================
//
// GameInput ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//シングルトン実体
	GameInput::P_GameInput	GameInput::m_inst;
	//------------------------------------------------

	GameKey GameInput::Get ( PLAYER_ID player_id, bool dirRight )
	{
		//現在の入力をゲームキーに直して保存
		GameKey gameKey;

		//上下前後
		bool bKey8 = false;	//上
		bool bKey2 = false;	//下
		bool bKey4 = false;	//後(右向き時)
		bool bKey6 = false;	//前(右向き時)

		if ( PLAYER_ID_1 == player_id )
		{
			bKey8 = IS_KEY ( P1_UP );
			bKey2 = IS_KEY ( P1_DOWN );
			if ( dirRight )	//右向き時
			{
				bKey4 = IS_KEY ( P1_LEFT );
				bKey6 = IS_KEY ( P1_RIGHT );
			}
			else	//左向き時
			{
				bKey4 = IS_KEY ( P1_RIGHT );
				bKey6 = IS_KEY ( P1_LEFT );
			}
		}
		else if ( PLAYER_ID_2 == player_id )
		{
			bKey8 = IS_KEY ( P2_UP );
			bKey2 = IS_KEY ( P2_DOWN );
			if ( dirRight )	//右向き時
			{
				bKey4 = IS_KEY ( P2_LEFT );
				bKey6 = IS_KEY ( P2_RIGHT );
			}
			else	//左向き時
			{
				bKey4 = IS_KEY ( P2_RIGHT );
				bKey6 = IS_KEY ( P2_LEFT );
			}
		}

		//----------------------------------------
		//@info
		// 3つ以上同時押しは優先順で処理
		// コマンド指定では12369874順
		//----------------------------------------

		//斜め優先
		if		( bKey8 && bKey4 )	{ gameKey.SetDir ( GameKey::DIR_7 ); }
		else if ( bKey8 && bKey6 )	{ gameKey.SetDir ( GameKey::DIR_9 ); }
		else if ( bKey6 && bKey2 )	{ gameKey.SetDir ( GameKey::DIR_3 ); }
		else if ( bKey4 && bKey2 )	{ gameKey.SetDir ( GameKey::DIR_1 ); }
		else if ( bKey8 )			{ gameKey.SetDir ( GameKey::DIR_8 ); }
		else if ( bKey6 )			{ gameKey.SetDir ( GameKey::DIR_6 ); }
		else if ( bKey4 )			{ gameKey.SetDir ( GameKey::DIR_4 ); }
		else if ( bKey2 )			{ gameKey.SetDir ( GameKey::DIR_2 ); }

		//ボタン
		bool bButton0 = false;
		bool bButton1 = false;
		bool bButton2 = false;
		bool bButton3 = false;
		if ( PLAYER_ID_1 == player_id )
		{
			bButton0 = IS_KEY ( P1_BUTTON1 );
			bButton1 = IS_KEY ( P1_BUTTON2 );
			bButton2 = IS_KEY ( P1_BUTTON3 );
			bButton3 = IS_KEY ( P1_BUTTON4 );
		}
		else if ( PLAYER_ID_2 == player_id )
		{
			bButton0 = IS_KEY ( P2_BUTTON1 );
			bButton1 = IS_KEY ( P2_BUTTON2 );
			bButton2 = IS_KEY ( P2_BUTTON3 );
			bButton3 = IS_KEY ( P2_BUTTON4 );
		}

		gameKey.SetBtn ( 0, ( bButton0 ) ? GameKey::BTN_ON : GameKey::BTN_OFF );
		gameKey.SetBtn ( 1, ( bButton1 ) ? GameKey::BTN_ON : GameKey::BTN_OFF );
		gameKey.SetBtn ( 2, ( bButton2 ) ? GameKey::BTN_ON : GameKey::BTN_OFF );
		gameKey.SetBtn ( 3, ( bButton3 ) ? GameKey::BTN_ON : GameKey::BTN_OFF );
	
		//返す
		return gameKey;
	}


}	//namespace GAME


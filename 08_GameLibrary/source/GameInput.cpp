//=================================================================================================
//
// GameInput �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameInput.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//�V���O���g������
	GameInput::P_GameInput	GameInput::m_inst;
	//------------------------------------------------

	GameKey GameInput::Get ( PLAYER_ID player_id, bool dirRight )
	{
		//���݂̓��͂��Q�[���L�[�ɒ����ĕۑ�
		GameKey gameKey;

		//�㉺�O��
		bool bKey8 = false;	//��
		bool bKey2 = false;	//��
		bool bKey4 = false;	//��(�E������)
		bool bKey6 = false;	//�O(�E������)

		if ( PLAYER_ID_1 == player_id )
		{
			bKey8 = IS_KEY ( P1_UP );
			bKey2 = IS_KEY ( P1_DOWN );
			if ( dirRight )	//�E������
			{
				bKey4 = IS_KEY ( P1_LEFT );
				bKey6 = IS_KEY ( P1_RIGHT );
			}
			else	//��������
			{
				bKey4 = IS_KEY ( P1_RIGHT );
				bKey6 = IS_KEY ( P1_LEFT );
			}
		}
		else if ( PLAYER_ID_2 == player_id )
		{
			bKey8 = IS_KEY ( P2_UP );
			bKey2 = IS_KEY ( P2_DOWN );
			if ( dirRight )	//�E������
			{
				bKey4 = IS_KEY ( P2_LEFT );
				bKey6 = IS_KEY ( P2_RIGHT );
			}
			else	//��������
			{
				bKey4 = IS_KEY ( P2_RIGHT );
				bKey6 = IS_KEY ( P2_LEFT );
			}
		}

		//----------------------------------------
		//@info
		// 3�ȏ㓯�������͗D�揇�ŏ���
		// �R�}���h�w��ł�12369874��
		//----------------------------------------

		//�΂ߗD��
		if		( bKey8 && bKey4 )	{ gameKey.SetDir ( GameKey::DIR_7 ); }
		else if ( bKey8 && bKey6 )	{ gameKey.SetDir ( GameKey::DIR_9 ); }
		else if ( bKey6 && bKey2 )	{ gameKey.SetDir ( GameKey::DIR_3 ); }
		else if ( bKey4 && bKey2 )	{ gameKey.SetDir ( GameKey::DIR_1 ); }
		else if ( bKey8 )			{ gameKey.SetDir ( GameKey::DIR_8 ); }
		else if ( bKey6 )			{ gameKey.SetDir ( GameKey::DIR_6 ); }
		else if ( bKey4 )			{ gameKey.SetDir ( GameKey::DIR_4 ); }
		else if ( bKey2 )			{ gameKey.SetDir ( GameKey::DIR_2 ); }

		//�{�^��
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
	
		//�Ԃ�
		return gameKey;
	}


}	//namespace GAME


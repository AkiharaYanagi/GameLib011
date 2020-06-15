//=================================================================================================
//
// _GameKeyCommand �\�[�X
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "_GameKeyCommand.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	_GameKeyCommand::_GameKeyCommand ()
	{
		for ( UINT i = 0; i < _GameKey::_LVR_NUM; ++ i )
		{
			m_Lvr[i] = GAME_KEY_WILD;
		}
		for ( UINT i = 0; i < _GameKey::_BTN_NUM; ++ i )
		{
			m_Btn[i] = GAME_KEY_WILD;
		}
	}

	_GameKeyCommand::_GameKeyCommand ( const _GameKeyCommand & rhs )
	{
		for ( UINT i = 0; i < _GameKey::_LVR_NUM; ++ i )
		{
			m_Lvr[i] = rhs.m_Lvr[i];
		}
		for ( UINT i = 0; i < _GameKey::_BTN_NUM; ++ i )
		{
			m_Btn[i] = rhs.m_Btn[i];
		}
	}

	_GameKeyCommand::~_GameKeyCommand ()
	{

	}


	bool _GameKeyCommand::CompareTarget ( _GameKey gameKeyData ) const
	{
		//���������C���h�̂Ƃ��͔�r���Ȃ�
		bool bWildLvr[_GameKey::_LVR_NUM] = { false };
		bool bWildBtn[_GameKey::_BTN_NUM] = { false };

		//��r����
		bool bLvr[_GameKey::_LVR_NUM] = { false };
		bool bBtn[_GameKey::_BTN_NUM] = { false };


		//��r
		for ( UINT i = 0; i < _GameKey::_LVR_NUM; ++ i )
		{
			bool b = gameKeyData.GetLvr ( i );
			bool pb = gameKeyData.GetPreLvr ( i );

			switch ( m_Lvr[i] )
			{
			case GAME_KEY_OFF:	bLvr[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bLvr[i] =   pb &&   b; break;
			case GAME_KEY_PUSH:	bLvr[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bLvr[i] =   pb && ! b; break;
			case GAME_KEY_WILD:	bWildLvr[i] = true; break;
			case GAME_KEY_IS:	bLvr[i] = ! b; break;
			case GAME_KEY_NIS:	bLvr[i] =   b; break;
			}
		}


		return false;
	}

	bool _GameKeyCommand::IsKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const
	{
		switch ( lvr_cmd )
		{
		case LVR_CMD_N: return IsNeutral ();
		case LVR_CMD_1: return Is ( _GameKey::LVR_1 );
		case LVR_CMD_2: return Is ( _GameKey::LVR_2 );
		case LVR_CMD_3: return Is ( _GameKey::LVR_3 );
		case LVR_CMD_6: return Is ( _GameKey::LVR_6 );
		case LVR_CMD_9: return Is ( _GameKey::LVR_9 );
		case LVR_CMD_8: return Is ( _GameKey::LVR_8 );
		case LVR_CMD_7: return Is ( _GameKey::LVR_7 );
		case LVR_CMD_4: return Is ( _GameKey::LVR_4 );
		case LVR_CMD_2E: return Is2E ();
		case LVR_CMD_6E: return Is6E ();
		case LVR_CMD_8E: return Is8E ();
		case LVR_CMD_4E: return Is4E ();
		}
		return false;
	}

	bool _GameKeyCommand::Is ( _GameKey::GAME_KEY_LEVER lvr ) const
	{
		return (GAME_KEY_ON == m_Lvr[lvr]) || (GAME_KEY_PUSH == m_Lvr[lvr]);
	}

	//���o�[�j���[�g�������ǂ���
	bool _GameKeyCommand::IsNeutral () const
	{
		//���ׂẴ��o�[�𑖍����āA�P�ł�OFF��RELE�łȂ�������false
		for ( UINT i = 0; i < _GameKey::_LVR_NUM; ++ i )
		{
			if ( GAME_KEY_OFF != m_Lvr [ i ] || GAME_KEY_RELE != m_Lvr [ i ] ) { return false; }
		}
		return true;
	}

	bool _GameKeyCommand::Is2E () const
	{
		return Is ( _GameKey::LVR_1 ) || Is ( _GameKey::LVR_2 ) || Is ( _GameKey::LVR_3 );
	}
	bool _GameKeyCommand::Is6E () const
	{
		return Is ( _GameKey::LVR_3 ) || Is ( _GameKey::LVR_6 ) || Is ( _GameKey::LVR_9 );
	}
	bool _GameKeyCommand::Is8E () const
	{
		return Is ( _GameKey::LVR_7 ) || Is ( _GameKey::LVR_8 ) || Is ( _GameKey::LVR_9 );
	}
	bool _GameKeyCommand::Is4E () const
	{
		return Is ( _GameKey::LVR_1 ) || Is ( _GameKey::LVR_4 ) || Is ( _GameKey::LVR_7 );
	}

}	//namespace GAME


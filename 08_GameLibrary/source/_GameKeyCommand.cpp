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
		for ( UINT i = 0; i < _GameKey::LVR_NUM; ++ i )
		{
			m_Lvr[i] = GAME_KEY_WILD;
		}
		for ( UINT i = 0; i < _GameKey::BTN_NUM; ++ i )
		{
			m_Btn[i] = GAME_KEY_WILD;
		}
	}

	_GameKeyCommand::_GameKeyCommand ( const _GameKeyCommand & rhs )
	{
		for ( UINT i = 0; i < _GameKey::LVR_NUM; ++ i )
		{
			m_Lvr[i] = rhs.m_Lvr[i];
		}
		for ( UINT i = 0; i < _GameKey::BTN_NUM; ++ i )
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
		bool bWildLvr[_GameKey::LVR_NUM] = { false };
		bool bWildBtn[_GameKey::BTN_NUM] = { false };

		//��r����
		bool bLvr[_GameKey::LVR_NUM] = { false };
		bool bBtn[_GameKey::BTN_NUM] = { false };

		//���o�[��r
		for ( UINT i = 0; i < _GameKey::LVR_NUM; ++ i )
		{
			bool b = gameKeyData.GetLvr ( i );
			bool pb = gameKeyData.GetPreLvr ( i );

			switch ( m_Lvr[i] )
			{
			case GAME_KEY_OFF:	bLvr[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bLvr[i] =   pb &&   b; break;
			case GAME_KEY_PUSH:	bLvr[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bLvr[i] =   pb && ! b; break;
			case GAME_KEY_IS:	bLvr[i] =   b; break;
			case GAME_KEY_NIS:	bLvr[i] = ! b; break;
			case GAME_KEY_WILD:	bWildLvr[i] = true; break;
			}
		}

		//�{�^����r
		for ( UINT i = 0; i < _GameKey::BTN_NUM; ++ i )
		{
			bool b = gameKeyData.GetBtn ( i );
			bool pb = gameKeyData.GetPreBtn ( i );

			switch ( m_Btn[i] )
			{
			case GAME_KEY_OFF:	bBtn[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bBtn[i] =   pb &&   b; break;
			case GAME_KEY_PUSH:	bBtn[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bBtn[i] =   pb && !   b; break;
			case GAME_KEY_IS:	bBtn[i] =   b; break;
			case GAME_KEY_NIS:	bBtn[i] = ! b; break;
			case GAME_KEY_WILD:	bWildBtn[i] = true; break;
			}
		}

		//���ׂĂ𑖍����P�ł� ���C���h�łȂ� ���� �Y�����Ȃ� �ꍇfalse��Ԃ�
		for ( UINT i = 0; i < _GameKey::LVR_NUM; ++ i )
		{
			if ( ! bWildLvr[i] && ! bLvr[i] ) { return false; }
		}
		for ( UINT i = 0; i < _GameKey::BTN_NUM; ++ i )
		{
			if ( ! bWildBtn[i] && ! bBtn[i] ) { return false; }
		}

		//���ׂēK����������true
		return true;
	}


	//�����w��̔�r
	bool _GameKeyCommand::CompareTarget ( _GameKey gameKeyData, bool dirRight ) const
	{
		//��r���邩�ǂ��� ( ���������C���h�̂Ƃ��͔�r���Ȃ� )
		bool bWildLvr[_GameKey::LVR_NUM] = { false };
		bool bWildBtn[_GameKey::BTN_NUM] = { false };

		//��r����
		bool bLvr[_GameKey::LVR_NUM] = { false };
		bool bBtn[_GameKey::BTN_NUM] = { false };

		//���E�ɂ�郌�o�[�C���f�b�N�X
		//	6 5 4				//	4 5 6
		//	7   3	�E��		����	//	3   7
		//	0 1 2				//	2 1 0
		const int lever_dir_R[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		const int lever_dir_L[] = { 2, 1, 0, 7, 6, 5, 4, 3 };


		//���o�[��r
		for ( UINT i = 0; i < _GameKey::LVR_NUM; ++ i )
		{
			int lr_index = dirRight ? lever_dir_R[i] : lever_dir_R[i];
			bool b =  gameKeyData.GetLvr ( lr_index );
			bool pb = gameKeyData.GetPreLvr ( lr_index );

			switch ( m_Lvr[i] )
			{
			case GAME_KEY_OFF:	bLvr[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bLvr[i] =   pb && b; break;
			case GAME_KEY_PUSH:	bLvr[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bLvr[i] =   pb && ! b; break;
			case GAME_KEY_IS:	bLvr[i] =   b; break;
			case GAME_KEY_NIS:	bLvr[i] = ! b; break;
			case GAME_KEY_WILD:	bWildLvr[i] = true; break;
			}
		}

		//�{�^����r
		for ( UINT i = 0; i < _GameKey::BTN_NUM; ++ i )
		{
			bool b = gameKeyData.GetBtn ( i );
			bool pb = gameKeyData.GetPreBtn ( i );

			switch ( m_Btn[i] )
			{
			case GAME_KEY_OFF:	bBtn[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bBtn[i] =   pb && b; break;
			case GAME_KEY_PUSH:	bBtn[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bBtn[i] =   pb && !   b; break;
			case GAME_KEY_IS:	bBtn[i] =   b; break;
			case GAME_KEY_NIS:	bBtn[i] = ! b; break;
			case GAME_KEY_WILD:	bWildBtn[i] = true; break;
			}
		}

		//���ׂĂ𑖍����P�ł� ���C���h�łȂ� ���� �Y�����Ȃ� �ꍇfalse��Ԃ�
		for ( UINT i = 0; i < _GameKey::LVR_NUM; ++ i )
		{
			if ( ! bWildLvr[i] && ! bLvr[i] ) { return false; }
		}
		for ( UINT i = 0; i < _GameKey::BTN_NUM; ++ i )
		{
			if ( ! bWildBtn[i] && ! bBtn[i] ) { return false; }
		}

		//���ׂēK����������true
		return true;
	}


	void _GameKeyCommand::SetaLvr ( GAME_KEY_STATE state_ary [] )
	{
		for ( UINT i = 0; i < _GameKey::BTN_NUM; ++ i )
		{
			m_Lvr [ i ] = state_ary [ i ];
		}
	}

	void _GameKeyCommand::SetaBtn ( GAME_KEY_STATE state_ary [] )
	{
		for ( UINT i = 0; i < _GameKey::BTN_NUM; ++ i )
		{
			m_Btn [ i ] = state_ary [ i ];
		}
	}


#if 0

	bool _GameKeyCommand::IsKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const
	{
		switch ( lvr_cmd )
		{
		case LVR_CMD_1: return Is ( _GameKey::LVR_1 );
		case LVR_CMD_2: return Is ( _GameKey::LVR_2 );
		case LVR_CMD_3: return Is ( _GameKey::LVR_3 );
		case LVR_CMD_6: return Is ( _GameKey::LVR_6 );
		case LVR_CMD_9: return Is ( _GameKey::LVR_9 );
		case LVR_CMD_8: return Is ( _GameKey::LVR_8 );
		case LVR_CMD_7: return Is ( _GameKey::LVR_7 );
		case LVR_CMD_4: return Is ( _GameKey::LVR_4 );
#if 0

		case LVR_CMD_2E: return Is2E ();
		case LVR_CMD_6E: return Is6E ();
		case LVR_CMD_8E: return Is8E ();
		case LVR_CMD_4E: return Is4E ();

#endif // 0
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
		for ( UINT i = 0; i < _GameKey::LVR_NUM; ++ i )
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
#endif // 0


}	//namespace GAME


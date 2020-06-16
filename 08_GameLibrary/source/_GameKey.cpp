//=================================================================================================
//
// _GameKeyCommand �\�[�X�t�@�C��
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
	_GameKey::_GameKey ()
	{
		for ( UINT i = 0; i < _LVR_NUM; ++ i )
		{
			Lvr[i] = false;
			PreLvr[i] = false;
		}
		for ( UINT i = 0; i < BTN_NUM; ++ i )
		{
			Btn[i] = false;
			PreBtn[i] = false;
		}
	}

	_GameKey::_GameKey ( const _GameKey & rhs )
	{
		for ( UINT i = 0; i < _LVR_NUM; ++ i )
		{
			Lvr[i] = rhs.Lvr[i];
			PreLvr[i] = rhs.PreLvr[i];
		}
		for ( UINT i = 0; i < BTN_NUM; ++ i )
		{
			Btn[i] = rhs.Btn[i];
			PreBtn[i] = rhs.PreBtn[i];
		}
	}

	_GameKey::~_GameKey ()
	{

	}

	void _GameKey::Update ()
	{
		//��������擪�Ɍ����ď㏑�����Ă���
		for ( UINT i = _LVR_NUM - 1; i > 0; -- i )
		{
			PreLvr [ i ] = Lvr [ i - 1 ];
		}
		//�擪�͎蓮�ŏ�����
		Lvr[0] = false;
	}

	void _GameKey::SetLvrOff ()
	{
		for ( UINT i = 0; i < _LVR_NUM; ++ i )
		{
			Lvr[i] = false;
		}
	}


}	//namespace GAME


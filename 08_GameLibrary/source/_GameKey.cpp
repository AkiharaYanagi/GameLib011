//=================================================================================================
//
// _GameKeyCommand ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "_GameKeyCommand.h"

//-------------------------------------------------------------------------------------------------
// 定義
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
		//末尾から先頭に向けて上書きしていく
		for ( UINT i = _LVR_NUM - 1; i > 0; -- i )
		{
			PreLvr [ i ] = Lvr [ i - 1 ];
		}
		//先頭は手動で初期化
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


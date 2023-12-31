//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TestLoadChara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TestLoadChara::TestLoadChara ()
	{
		m_pChara = make_shared < Chara > ();	//キャラデータ実体
		tstring filename ( _T ( "Sonia.dat" ) );
		LoadChara loadChara ( filename, * m_pChara );
	}

	TestLoadChara::~TestLoadChara ()
	{
	}


}	//namespace GAME


//=================================================================================================
//
//	Sequence ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Sequence.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Sequence::Sequence ()
	{
		m_pvpScript = make_shared < VP_Script > ();
	}

	Sequence::~Sequence ()
	{
	}

	void Sequence::Rele ()
	{
		for ( auto p : * m_pvpScript ) { p->Rele (); } m_pvpScript->clear (); m_pvpScript.reset ();
	}


}	//namespace GAME


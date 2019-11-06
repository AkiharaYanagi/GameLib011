//=================================================================================================
//
//	Chara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Chara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Chara::Chara ()
	{
		Make ();
	}

	Chara::~Chara ()
	{
	}

	void Chara::Make ()
	{
		m_pvpTxMain = make_shared < VP_TxBs > ();
		m_pvpAction = make_shared < VP_Action > ();
		m_pvpTxEf = make_shared < VP_TxBs > ();
		m_pvpEf = make_shared < VP_Effect > ();
	}

	void Chara::Rele ()
	{
		for ( auto p : * m_pvpTxMain ) { p->Rele (); } m_pvpTxMain->clear (); m_pvpTxMain.reset ();
		for ( auto p : * m_pvpAction ) { p->Rele (); } m_pvpAction->clear (); m_pvpAction.reset ();
		for ( auto p : * m_pvpTxEf ) { p->Rele (); } m_pvpTxEf->clear (); m_pvpTxEf.reset ();
		for ( auto p : * m_pvpEf ) { p->Rele (); } m_pvpEf->clear (); m_pvpEf.reset ();
	}

	void Chara::Reset ()
	{
		Rele ();
		Make ();
	}

}	//namespace GAME


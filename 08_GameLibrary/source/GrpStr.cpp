//=================================================================================================
//
// GrpEf ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GrpStr.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TxStr::GameTextureFromString ()
	{
	}

	TxStr::~GameTextureFromString ()
	{
	}

	void TxStr::Load ()
	{
		//文字列からテクスチャを作成
//		TX tx = OutlineFont::Inst ()->Make ( m_str.c_str (), 0xffff00ff, 0xffffffff );
		TX tx = OutlineFont::Inst ()->MakeStrTx ( m_str.c_str (), 0xffff00ff, 0xffffffff );
		TxBs::SetTexture ( tx );
	}

	void TxStr::Rele ()
	{
		RELEASE ( GetTexture () );
	}

	void TxStr::Reset ()
	{
		Rele ();
		Load ();
	}

	void TxStr::SetStr ( LPCTSTR str )
	{
		m_str.assign ( str );
	}


	//-------------------------------------
	GrpStr::GrpStr ()
	{
		m_tx = make_shared < TxStr > ();
	}

	GrpStr::~GrpStr ()
	{
	}

	void GrpStr::SetStr ( LPCTSTR str )
	{
		//文字列からテクスチャを作成
		m_tx->SetStr ( str );

		//グラフィックに指定
		GrpApTx::SetpTexture ( m_tx );
	}

	void GrpStr::Load ()
	{
		m_tx->Load ();
	}

	void GrpStr::Rele ()
	{
		m_tx->Rele ();
	}

	void GrpStr::Reset ()
	{
		m_tx->Reset ();
	}



}	//namespace GAME


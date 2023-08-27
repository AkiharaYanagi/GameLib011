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
		TX tx = OutlineFont::Inst ()->Make ( m_str.c_str (), 0x00ffffff, 0xffffffff );
		TxBs::SetTexture ( tx );
	}

	void TxStr::Rele ()
	{
	}

	void TxStr::Reset ()
	{
		Rele ();
		Load ();
	}

	void TxStr::SetStr ( LPCTSTR str )
	{
		m_str.assign ( str );
		Load ();
	}


	//-------------------------------------
	GrpStr::GrpStr ()
	{
	}

	GrpStr::~GrpStr ()
	{
	}

	void GrpStr::SetStr ( LPCTSTR str )
	{
		//文字列からテクスチャを作成
		P_TxStr txstr = make_shared < TxStr > ();
		txstr->SetStr ( str );

		//グラフィックに指定
		GrpApTx::SetpTexture ( txstr );
	}

}	//namespace GAME


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
	//-------------------------------------
	GrpStr::GrpStr ()
	{
		m_tx = make_shared < TxStr > ();
	}

	GrpStr::~GrpStr ()
	{
	}

	void GrpStr::Load ()
	{
		m_tx->Load ();

		D3DSURFACE_DESC dc;
		m_tx->GetTexture ()->GetLevelDesc ( 0, & dc );

#if 0
		P_PrmRect rect = make_shared < PrmRect > ();
		rect->SetSize ( 1.f * dc.Width, 1.f * dc.Height );
		rect->SetPos ( GetPos () );
		rect->SetZ ( Z_BG );
		rect->SetAllColor ( 0x80ff8080 );
		rect->Load ();
		GRPLST_INSERT ( rect );
#endif // 0
	}

	void GrpStr::Rele ()
	{
		m_tx->Rele ();
	}

	void GrpStr::Reset ()
	{
		m_tx->Reset ();
	}

	void GrpStr::SetStr ( LPCTSTR str )
	{
		//文字列からテクスチャを作成
		m_tx->SetStr ( str );

		//グラフィックに指定
		GrpApTx::SetpTexture ( m_tx );
	}

	void GrpStr::SetFontParam ( int fontSize, int penSize, int quolity )
	{
		m_tx->SetParam ( fontSize, penSize, quolity );
	}

	void GrpStr::SetFontFace ( LPCTSTR fontname )
	{
		m_tx->SetFontFace ( fontname );
	}

	void GrpStr::SetFontColor ( DWORD fill, DWORD edge )
	{
		m_tx->SetColor ( fill, edge );
	}



}	//namespace GAME


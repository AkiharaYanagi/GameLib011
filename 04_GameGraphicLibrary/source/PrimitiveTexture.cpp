//=================================================================================================
//
//	プリミティブ テクスチャ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "PrimitiveTexture.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	PrimitiveTexture::PrimitiveTexture ()
		: m_multiple ( true )
	{
		m_tx = make_shared < TxAcv > ();
	}

	PrimitiveTexture::~PrimitiveTexture ()
	{
	}

	void PrimitiveTexture::Load ()
	{
		m_tx->Load ();
		PrmRect::Load ();
	}
	void PrimitiveTexture::Rele ()
	{
		m_tx->Rele ();
		PrmRect::Rele ();
	}
	void PrimitiveTexture::Reset ()
	{
		m_tx->Reset ();
		PrmRect::Reset ();
	}

	void PrimitiveTexture::DrawVertex ()
	{
		if ( m_multiple )
		{
			PrmRect::DrawVertexMultiple ( m_tx->GetTexture () );
		}
		else
		{
			PrmRect::DrawVertex ( m_tx->GetTexture () );
		}
	}


}	//namespace GAME


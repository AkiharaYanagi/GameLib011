//=================================================================================================
//
// GrpStr �w�b�_�t�@�C��
//	�P���ȕ�����̃O���t�B�b�N
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameTexture.h"
#include "GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------
	class GrpStr : public GrpApTx
	{
		P_TxStr		m_tx;

	public:
		GrpStr ();
		GrpStr ( const GrpStr & rhs ) = delete;
		~GrpStr ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR str );
		void SetStrF ( LPCTSTR str, ... );

		void SetFontParam ( int fontSize, int penSize, int quolity );
		void SetFontFace ( LPCTSTR fontname );
		void SetFontColor ( DWORD fill, DWORD edge );

		USIZE GetSize () const { return m_tx->GetSize (); }
	};

	using P_GrpStr = std::shared_ptr < GrpStr >;


}	//namespace GAME



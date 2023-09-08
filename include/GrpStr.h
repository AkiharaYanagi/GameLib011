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
#include "Game.h"

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

		void SetFontParam ( int fontSize, int penSize, int quolity );
		void SetFontFace ( LPCTSTR fontname );
		void SetFontColor ( DWORD fill, DWORD edge );
	};

	using P_GrpStr = shared_ptr < GrpStr >;


}	//namespace GAME



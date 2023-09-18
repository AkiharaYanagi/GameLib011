//=================================================================================================
//
// GameGraphicList �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameGraphicList.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//----------------------------------------------------------------------------------------
	//@info
	//		SetSpritePostion ( VEC3 ) �ł̐ݒ��
	//		�X�v���C�g�����Ԃɂ���ăA���t�@�l�����S�ɓ����ɂ��Ă��܂����Ƃ́A
	//		�����ǋ��Ɖ���
	// ->
	//		DirectX �̎d�l
	//		���ߏ��(���l)�̂���I�u�W�F�N�g�������_�����O����Ƃ��ɂ́A
	//		�w��(Z�l�̑傫��)�̃I�u�W�F�N�g�����ׂă����_�����O���Ȃ���΂Ȃ�Ȃ�
	//->
	//		�O���t�B�b�N���ꌳ�Ǘ�����I�u�W�F�N�g�̍쐬
	//----------------------------------------------------------------------------------------

	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	UP_GrpLst	GrpLst::m_inst;

	//�R���X�g���N�^
	GameGraphicList::GameGraphicList ()
	{
		ml_GrpMain = make_shared < LP_GrpCr > ();
		ml_GrpSys = make_shared < LP_GrpCr > ();
	}

	GameGraphicList::~GameGraphicList ()
	{
		Rele ();
		ml_GrpMain.reset ();
		ml_GrpSys.reset ();
	}

	//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
	void GameGraphicList::InsertByZ_Main ( P_GrpCr pGrpCr )
	{
		InsertByZ ( ml_GrpMain, pGrpCr );
	}

	void GameGraphicList::InsertByZ_Sys ( P_GrpCr pGrpCr )
	{
		InsertByZ ( ml_GrpSys, pGrpCr );
	}

	void GameGraphicList::InsertByZ ( PLP_GrpCr plp_grp, P_GrpCr pGrpCr )
	{
		//�������P�������Ƃ��A�ʏ�̒ǉ�
		if ( 0 == plp_grp->size () ) { plp_grp->push_back ( pGrpCr ); return; }

		//Z�l���`�F�b�N���Ďw��ʒu�ɑ}��
		float z = pGrpCr->GetZ ();
		LP_GrpCr::iterator it = plp_grp->begin ();
		for ( ; plp_grp->end () != it; ++ it )
		{
			float pz = ( *it )->GetZ ();
			if ( z > pz )
			{
				plp_grp->insert ( it, pGrpCr );
				return;
			}
		}

		//���ׂĂ̒l��菬�����ꍇ�A�����ɒǉ�
		plp_grp->push_back ( pGrpCr );
	}


	void GameGraphicList::Load ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->Load (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->Load (); }
	}

	void GameGraphicList::Rele ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->Rele (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->Rele (); }
	}

	void GameGraphicList::Reset ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->Reset (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->Reset (); }
	}

	void GameGraphicList::Init ()
	{
#if 0
		for ( P_GrpCr p : *ml_GrpMain ) { p->Init (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->Init (); }
#endif // 0
	}

	void GameGraphicList::Move ()
	{
#if 0
		//�ꎞ��~����Move�������΂�
		if ( m_pause ) { return; }

		for ( P_GrpCr p : *ml_GrpMain ) { p->Move (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->Move (); }
#endif // 0
	}

	void GameGraphicList::Draw ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->Draw (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->Draw (); }
	}

	void GameGraphicList::DrawVertex ()
	{
		for ( P_GrpCr p : *ml_GrpMain ) { p->DrawVertex (); }
		for ( P_GrpCr p : *ml_GrpSys ) { p->DrawVertex (); }
	}

	void GameGraphicList::Clear ()
	{
		ml_GrpMain->clear ();
		ml_GrpSys->clear ();
	}

	void GameGraphicList::Clear_Main ()
	{
		ml_GrpMain->clear ();
	}

	void GameGraphicList::Clear_Sys ()
	{
		ml_GrpSys->clear ();
	}


}	//namespace GAME


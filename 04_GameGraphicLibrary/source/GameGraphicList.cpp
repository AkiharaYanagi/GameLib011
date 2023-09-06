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
//		: m_pGrpTaskList ( nullptr ), m_pause ( F )
	{
	}

	//�V�K���X�g���쐬���Ď擾
	P_TASK_LST GameGraphicList::NewTaskList ()
	{
//		m_pGrpTaskList = make_shared < GameTaskList > ();
//		return m_pGrpTaskList;
		return make_shared < GameTaskList > ();
	}

	//�V�K���X�g���쐬
	void GameGraphicList::MakeList ()
	{
//		m_pGrpTaskList = make_shared < GameTaskList > ();
	}

	//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
	void GameGraphicList::InsertByZ ( P_GrpCr pGrpCr )
	{
		//��������Ƃ��ʏ�̒ǉ�
//		if ( 0 == m_pGrpTaskList->GetSize () ) { m_pGrpTaskList->AddpTask ( pTask ); return; }
		if ( 0 == m_GrpLst.size () ) { m_GrpLst.push_back ( pGrpCr ); return; }


		//Z�l���`�F�b�N���Ďw��ʒu�ɑ}��
		float z = pGrpCr->GetZ ();

#if 0
		//���X�g�̃��[�v
		PLP_Task plpTask = m_pGrpTaskList->GetplpTask ();
		LP_Task::iterator it = begin ( * plpTask );
		for ( ; end ( * plpTask ) != it; ++ it )
		{
			//�O���t�B�b�N�^�X�N�̎擾
			P_GrpCr pg = dynamic_pointer_cast < GrpCr > ( * it );

			//Z�l�̎擾
			float gz = pg->GetZ ();

			//Z�l���Ώۂ��傫���Ƃ��A���̑O�ɑ}�����ďI��
			//(���l�̏ꍇ�͌�ɒǉ������)
			if ( z > gz )
			{
				m_pGrpTaskList->InsertTask ( it, pGrpCr );
				return;
			}
		}
#endif // 0

		list < P_GrpCr > ::iterator it = m_GrpLst.begin ();
		for ( ; m_GrpLst.end () != it; ++ it )
		{
			float pz = (*it)->GetZ ();
			if ( z > pz )
			{
				m_GrpLst.insert ( it, pGrpCr );
				return;
			}
		}

		//���ׂĂ̒l��菬�����ꍇ�A�����ɒǉ�
//		m_pGrpTaskList->AddpTask ( pGrpCr );
		m_GrpLst.push_back ( pGrpCr );
	}

	void GameGraphicList::Reset ()
	{
#if 0
		if ( nullptr == m_pGrpTaskList ) { return; }

		for ( auto p : *(m_pGrpTaskList->GetplpTask ()) )
		{
			p->Reset ();
		}
#endif // 0
	}

	void GameGraphicList::Clear ()
	{
//		m_pGrpTaskList->Clear ();

		//�����I���
//		m_pGrpTaskList.reset ();
	}

	void GameGraphicList::Load ()
	{
//		m_pGrpTaskList->Load ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->Load (); }
	}

	void GameGraphicList::Init ()
	{
//		m_pGrpTaskList->Init ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->Init (); }
	}

	void GameGraphicList::Move ()
	{
		//�ꎞ��~����Move�������΂�
		if ( m_pause ) { return; }

//		m_pGrpTaskList->Move ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->Move (); }
	}

	void GameGraphicList::Draw ()
	{
//		m_pGrpTaskList->Draw ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->Draw (); }
	}

	void GameGraphicList::DrawVertex ()
	{
//		m_pGrpTaskList->DrawVertex ();
		for ( P_GrpCr p_GrpBs : m_GrpLst ) { p_GrpBs->DrawVertex (); }
	}


}	//namespace GAME


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
	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	UP_GrpLst	GrpLst::m_inst;

	//�R���X�g���N�^
	GameGraphicList::GameGraphicList ()
		: m_pGrpTaskList ( nullptr )
	{
	}

	//�V�K���X�g���쐬
	P_TASK_LST GameGraphicList::NewTaskList ()
	{
		m_pGrpTaskList = make_shared < GameTaskList > ();
		return m_pGrpTaskList;
	}

	//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
	void GameGraphicList::InsertByZ ( P_GrpCr pTask )
	{
		//��������Ƃ��ʏ�̒ǉ�
		if ( 0 == m_pGrpTaskList->GetSize () ) { m_pGrpTaskList->AddpTask ( pTask ); return; }

		//Z�l���`�F�b�N���Ďw��ʒu�ɑ}��
		float z = pTask->GetZ ();

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
			if ( z > gz )
			{
				m_pGrpTaskList->InsertTask ( it, pTask );
				return;
			}
		}

		//���ׂĂ̒l��菬�����ꍇ�A�����ɒǉ�
		m_pGrpTaskList->AddpTask ( pTask );
	}

	void GameGraphicList::Reset ()
	{
		if ( nullptr == m_pGrpTaskList ) { return; }

		for ( auto p : *(m_pGrpTaskList->GetplpTask ()) )
		{
			p->Reset ();
		}
	}

	void GameGraphicList::Clear ()
	{
		m_pGrpTaskList->Clear ();
		//�����I���
//		m_pGrpTaskList.reset ();
	}

	void GameGraphicList::Load ()
	{
		m_pGrpTaskList->Load ();
	}

	void GameGraphicList::Init ()
	{
		m_pGrpTaskList->Init ();
	}


}	//namespace GAME


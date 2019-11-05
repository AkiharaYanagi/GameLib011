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
		: m_pTaskList ( nullptr )
	{
//		m_pTasklst = make_shared < GameTaskList > ();
	}

	//�R���X�g���N�^
	P_TASK_LST GameGraphicList::NewTaskList ()
	{
		TRACE_F ( _T ( "�� GameGraphicList : m_pTaskList.use_count = %d\n" ), m_pTaskList.use_count () );
		TRACE_F ( _T( "NewTaskList : %x -> "), m_pTaskList );
		m_pTaskList = make_shared < GameTaskList > ();
		TRACE_F ( _T ( "%x\n" ), m_pTaskList );
		TRACE_F ( _T ( "�� GameGraphicList : m_pTaskList.use_count = %d\n" ), m_pTaskList.use_count () );
		return m_pTaskList;
	}

	//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
	void GameGraphicList::InsertByZ ( P_GrpBs pTask )
	{
//		TRACE_F ( _T ( "InsertByZ : %x -> " ), m_pTaskList );
//		TRACE_F ( _T ( "%d\n" ), m_pTaskList->GetSize () );

		//��������Ƃ��ʏ�̒ǉ�
		if ( 0 == m_pTaskList->GetSize () ) { m_pTaskList->AddpTask ( pTask ); return; }

		//Z�l���`�F�b�N���Ďw��ʒu�ɑ}��
		float z = pTask->GetZ ();

		//���X�g�̃��[�v
		PLP_Task plpTask = m_pTaskList->GetplpTask ();
		LP_Task::iterator it = begin ( * plpTask );
		for ( ; end ( * plpTask ) != it; ++ it )
		{
			//�I�u�W�F�N�g�̎擾
			P_GrpBs pg = dynamic_pointer_cast < GrpBs > ( * it );

			//Z�l�̎擾
			float gz = pg->GetZ ();

			//Z�l���Ώۂ��傫���Ƃ��A���̑O�ɑ}�����ďI��
			if ( z > gz )
			{
				m_pTaskList->InsertTask ( it, pTask );
				return;
			}
		}

		//���ׂĂ̒l��菬�����ꍇ�A�����ɒǉ�
		m_pTaskList->AddpTask ( pTask );
	}

	void GameGraphicList::Reset ()
	{
		m_pTaskList->Reset ();
	}

	void GameGraphicList::Clear ()
	{
		m_pTaskList->Clear ();
		//�����I���
		m_pTaskList.reset ();
	}


}	//namespace GAME


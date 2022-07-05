
//=================================================================================================
//
// �t���[���i�s�̊ė��N���X
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	�w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "FrameControl.h"

// ���C�u���������݂̂ŎQ�Ƃ���w�b�_�t�@�C��
#include "GameSystem.h"		//�Q�[���V�X�e��(DirectX,�Q�[�����C��)
#include "DebugOutGameWindow.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

//----------------------------------------------
//	�萔�錾
//----------------------------------------------
const DWORD FrameControl::dwFps = 60;	//FPS
const DWORD FrameControl::waitOneFrameTime = 1000 * 0x10000 / dwFps;		//1�t���[���ɑ҂~���b�B���16�r�b�g�ɐ������A����16�r�b�g�ɏ�������ۑ�


	//------------------------------------------
	//	�R���X�g���N�^
	//------------------------------------------
	FrameControl::FrameControl() : m_gameSystem ( nullptr )
	{
		::timeBeginPeriod(1);		//�^�C�}�[�̕���\��1[ms]�ɐݒ�

		m_gameSystem = make_unique < GameSystem > ();
	}

	//------------------------------------------
	//	�f�X�g���N�^
	//------------------------------------------
	FrameControl::~FrameControl()
	{
		::timeEndPeriod(1);		//�^�C�}�[�̕���\�����ɖ߂�
	}

	//------------------------------------------
	//	�Q�[���V�X�e��������
	//------------------------------------------
	void FrameControl::SystemLoad ()
	{
		m_gameSystem->SystemLoad ();
	}

	//------------------------------------------
	//	�Ǎ�
	//------------------------------------------
	void FrameControl::Load ()
	{
		m_gameSystem->Load ();
	}

	//------------------------------------------
	//	���
	//------------------------------------------
	void FrameControl::Rele ()
	{
		m_gameSystem->Rele ();
	}

	//------------------------------------------
	//	�Đݒ�
	//------------------------------------------
	void FrameControl::Reset()
	{
		m_gameSystem->Reset();
	}

	//------------------------------------------
	//	������
	//------------------------------------------
	void FrameControl::Init()
	{
		m_frames = 0;
		m_beforeTime = 0;
		m_average = 0;
		
		//�Q�[���V�X�e���̏�����
		m_gameSystem->Init ();
	}

	//------------------------------------------
	//�t���[������(1�t���[���̏���)
	//------------------------------------------
	void FrameControl::Frame()
	{
		//1�t���[���̃��[�v
//		while ( m_bPermi )
//		while ( false )
		{
			static DWORD averageMove = 0;
			static DWORD averageDraw = 0;

#define	THREAD 0
#if	THREAD
			if ( ! m_bPermi )	//�X���b�h���t���O�ő��s���m�F����
			{
				////TRACE_F ( TEXT("�t���[������̃��[�v���ł������Am_bPermi��false�̂���break���܂����B\n") );
				break;
			}
#endif	//THREAD

			DWORD startTime = ::timeGetTime();

			//--------------------------
			//�t���[�����̓���
			m_gameSystem->Move ();
			//--------------------------

			//���ݎ�������o�ߎ��Ԃ��v�Z
			DWORD nowTime = ::timeGetTime();

			averageMove += nowTime - startTime;

			DWORD progressTime = nowTime - m_beforeTime;
			//���݃t���[�������痝�z���Ԃ��v�Z
			DWORD idealTime = (m_frames * waitOneFrameTime) >> 16;

			//1�t���[�����Ԃ̒���(�������鎞�͍��������A����ȊO��1����Sleep)
			DWORD sleepTime = ( idealTime > progressTime ) ? ( idealTime - progressTime ): 1;
			
			m_average += sleepTime;

			Sleep ( sleepTime );

			DWORD preDrawTime = ::timeGetTime();
			//--------------------------
			//�`�揈��
			m_gameSystem->Draw();
			//--------------------------
			DWORD postDrawTime = ::timeGetTime();

			averageDraw += postDrawTime - preDrawTime;


			//1000ms���Ɍ��݃t���[����(FPS)�̍X�V
			if ( progressTime >= 1000 )
			{
				static bool bFPS = false;
				if ( ::GetAsyncKeyState ( 'F' ) & 0x0001 ) { bFPS ^= true; }
				if ( bFPS )
				{
					averageMove = 0;
					averageDraw = 0;

					DBGOUT_WND->SetPos ( 10, 400, 000 );
					float avrg = 0;
					if ( 0 != m_frames ) { avrg = (float)m_average / m_frames; }
					DBGOUT_WND_F ( 10, _T("FPS:%02u, sleep:%05.2f"), m_frames, avrg );

					m_beforeTime = nowTime;
					m_frames = 0;
					m_average = 0;
				}
				else
				{
					DBGOUT_WND_F ( 10, _T ( "" ) );
				}
			}
			m_frames++;
		}

//		m_bActive = false;	//�X���b�h�I�����t���O�ɐݒ�

	}


	//�Q�[�����C���I�u�W�F�N�g�̐ݒ�
	void FrameControl::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_gameSystem->SetGameMain( ::move ( pGameMain ) ); 
	}


}	//namespace GAME



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
	const DWORD FrameControl::waitOneFrameTime = 1000 * 0x10000 / dwFps;	//1�t���[���ɑ҂~���b�B���16�r�b�g�ɐ������A����16�r�b�g�ɏ�������ۑ�

	bool FrameControl::m_bDispFPS = true;

	//------------------------------------------
	//	�R���X�g���N�^
	//------------------------------------------
	FrameControl::FrameControl() : m_gameSystem ( nullptr )
	{
		::timeBeginPeriod(1);		//�^�C�}�[�̕���\��1[ms]�ɐݒ�

		m_gameSystem = std::make_unique < GameSystem > ();
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

		DBGOUT_WND->DebugOutWnd_MoveTime ( 0 );
		DBGOUT_WND->DebugOutWnd_DrawTime ( 0 );
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
		m_averageSleep = 0;
		
		//�Q�[���V�X�e���̏�����
		m_gameSystem->Init ();
	}

	//------------------------------------------
	//�t���[������(1�t���[���̏���)
	//------------------------------------------
	void FrameControl::Frame()
	{
		static float averageSleep = 16.6f;
		static DWORD dwDispFps = 60;
		

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
			
			m_averageSleep += sleepTime;

			Sleep ( sleepTime );

			DWORD preDrawTime = ::timeGetTime();
			//--------------------------
			//�`�揈��
			m_gameSystem->Draw();
			//--------------------------
			DWORD postDrawTime = ::timeGetTime();

			averageDraw += postDrawTime - preDrawTime;

#if 0
			// �t���[���v�Z�͏�ɍs���A�\�������؂�ւ���
			//F6�Ő؂�ւ�
			if ( ::GetAsyncKeyState ( VK_F6 ) & 0x0001 )
			{
				m_bDispFPS ^= true;
				DBGOUT_WND->SetbDisp_FPS( m_bDispFPS );
			}
			if ( m_bDispFPS )
			{
				DBGOUT_WND->DebugOutWnd_FPS ( _T("FPS:%02u, sleep:%05.2f"), dwDispFps, averageSleep );
			}
			else
			{
				DBGOUT_WND->SetbDisp_FPS ( false );
				DBGOUT_WND->DebugOutWnd_FPS ( _T ( "") );
			}
#endif // 0
			DBGOUT_WND->DebugOutWnd_FPS ( dwDispFps );
			DBGOUT_WND->DebugOutWnd_SleepTime ( averageSleep );


			// 'F7'�L�[��Move, Draw �������� �\���ؑ�
#if 0
			static bool bMoveDrawTimer = true;
			if ( ::GetAsyncKeyState ( VK_F7 ) & 0x0001 )
			{
				bMoveDrawTimer ^= true;
				DBGOUT_WND->SetbDisp_MoveTime ( bMoveDrawTimer );
				DBGOUT_WND->SetbDisp_DrawTime ( bMoveDrawTimer );
				if ( bMoveDrawTimer )
				{
					//60[F]�̕���
					DBGOUT_WND->DebugOutWnd_MoveTime ( _T ( "MoveTime = %05.2f [ms/F]" ), 1.f * averageMove / m_frames );
					DBGOUT_WND->DebugOutWnd_DrawTime ( _T ( "DrawTime = %05.2f [ms/F]" ), 1.f * averageDraw / m_frames );
				}
				else
				{
					DBGOUT_WND->SetbDisp_MoveTime ( false );
					DBGOUT_WND->SetbDisp_DrawTime ( false );
					DBGOUT_WND->DebugOutWnd_MoveTime ( _T ( "" ) );
					DBGOUT_WND->DebugOutWnd_DrawTime ( _T ( "" ) );
				}
			}
#endif // 0


			//1000ms���Ɍ��݃t���[����(FPS)�̍X�V
			if ( progressTime >= 1000 )
			{
#if 0
				if ( bMoveDrawTimer )
				{
					//60[F]�̕���
					DBGOUT_WND->DebugOutWnd_MoveTime ( _T ( "MoveTime = %05.2f [ms/F]" ), 1.f * averageMove / m_frames );
					DBGOUT_WND->DebugOutWnd_DrawTime ( _T ( "DrawTime = %05.2f [ms/F]" ), 1.f * averageDraw / m_frames );
				}
				else
				{
					DBGOUT_WND->DebugOutWnd_MoveTime ( _T ( "" ) );
					DBGOUT_WND->DebugOutWnd_DrawTime ( _T ( "" ) );
				}
#endif // 0
				float moveTime = 0;
				float drawTime = 0;
				if ( m_frames != 0 )
				{
					moveTime = 1.f * averageMove / m_frames;
					drawTime = 1.f * averageDraw / m_frames;
				}
				DBGOUT_WND->DebugOutWnd_MoveTime ( moveTime );
				DBGOUT_WND->DebugOutWnd_DrawTime ( drawTime );
				DBGOUT_WND->DebugOutWnd_SleepTime ( averageSleep );

				averageMove = 0;
				averageDraw = 0;


				if ( 0 != m_frames )
				{
					dwDispFps = m_frames;
					averageSleep = (float)m_averageSleep / m_frames; 
				}

				m_beforeTime = nowTime;
				m_frames = 0;
				m_averageSleep = 0;
			}

			++ m_frames;
		}

//		m_bActive = false;	//�X���b�h�I�����t���O�ɐݒ�

	}


	//�Q�[�����C���I�u�W�F�N�g�̐ݒ�
	void FrameControl::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_gameSystem->SetGameMain( ::move ( pGameMain ) ); 
	}


	//�f�o�b�O�\�������ׂ�ON
	void FrameControl::FullDebugMode ()
	{
		m_bDispFPS = T;
//		GameSystem::FullDebugMode ();
	}

	//�f�o�b�O�\�������ׂ�OFF
	void FrameControl::NoDebugMode ()
	{
		m_bDispFPS = F;
///		GameSystem::NoDebugMode ();
	}

	//�A�[�J�C�u�쐬
	void FrameControl::SetFlag_MakeArchive ( bool b ) 
	{
		GameSystem::SetFlag_MakeArchive ( b ); 
	}

}	//namespace GAME


//=================================================================================================
//
// Application�Ǘ��N���X�@�\�[�X�R�[�h
//
//=================================================================================================

//------------------------------------------------
//	windows�A�v���P�[�V�����̊Ǘ�
//		�E�A�v���P�[�V�����̏������@���������[�N���o�A���d�N���h�~�Ȃ�
//		�E�E�B���h�E�̏�����
//		�E�E�B���h�E�v���V�[�W��
//		�E��ʃt�H�[�J�X�O��ɂ��Đݒ�
//------------------------------------------------

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Application.h"

// ���C�u���������݂̂ŎQ�Ƃ���w�b�_�t�@�C��
#include "FrameControl.h"		//�t���[������ƃQ�[�����C��

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//�ÓI�ϐ�
	//------------------------------------------
	//�ÓIthis�|�C���^
	shared_ptr < Application > Application::m_pThis = nullptr;
	//�������t���O
	bool Application::m_init = false;

	//-------------------------------------------------------------------------------------------------
	// �R���X�g���N�^
	//-------------------------------------------------------------------------------------------------
	Application::Application ( ResourceName rcName )
		: m_rcName ( rcName )	//, m_InitFromCursorPos ( false )
	{
		//���������[�N���o
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

		//���d�N���`�F�b�N
#define MULTI_ACT 0
#if	MULTI_ACT
		try 
		{
			//�~���[�e�b�N�X�ɂ�鑽�d�N���̖h�~
			m_hMutex = CreateMutex ( nullptr, false, rcName.mutexText );
			if ( ::GetLastError () == ERROR_ALREADY_EXISTS )
			{
				throw _T("�~���[�e�b�N�X�ɂ�鑽�d�N���̖h�~\n");
			}
		}
		catch ( LPCTSTR str )
		{
			TRACE_F ( str );
			MessageBox ( nullptr, TEXT("������2�ȏ���s���邱�Ƃ͂ł��܂���B"), TEXT("���d�N���̖h�~"), MB_OK );
			Rele ();
			PostQuitMessage(0);
		}
#endif	//MULTI_ACT

		//----------------------------------
		//�t���[������I�u�W�F�N�g�̐���
		m_pFrameControl = make_unique < FrameControl > ();

		//�ݒ�t�@�C���̏������ƓǍ�
		AppSettingFile::Create ();
		AppSettingFile::Inst()->Load ();
	}


	//-------------------------------------------------------------------------------------------------
	// �f�X�g���N�^
	//-------------------------------------------------------------------------------------------------
	Application::~Application ()
	{
		Rele ();

#if MULTI_ACT
		//���d�N���h�~�̃~���[�e�b�N�X�����
		ReleaseMutex ( m_hMutex );
		CloseHandle ( m_hMutex );
#endif	//MULTI_ACT
	}


	//-------------------------------------------------------------------------------------------------
	// �A�v���P�[�V�����̏�����
	// �����FhInst		�C���X�^���X�n���h��
	// �ߒl�F���� = true, ���s = false
	//-------------------------------------------------------------------------------------------------
	bool Application::AppInit ( HINSTANCE hInst )
	{
		//----------------------------------
		//this�|�C���^�̕ۑ�	
		m_pThis = shared_from_this ();
	
		//----------------------------------
		//�E�B���h�E�̏�����
		if ( ! _WinInit ( hInst ) )
		{
			TRACE_F ( _T("�E�B���h�E�̏������Ɏ��s\n") );
			return false;
		}

		//----------------------------------
		//�Q�[���V�X�e��������
		m_pFrameControl->SystemLoad ();

		//----------------------------------
		//�X���b�h�֘A
#define APP_THREAD 0
#if APP_THREAD
		m_bPermi = true;		//�X���b�h���t���O
		m_bActive = true;		//�X���b�h�ғ��t���O

		//�`��X���b�h�̊J�n
		UINT threadID;		//�X���b�hID
		_beginthreadex ( nullptr, 0, DrawThread, (LPVOID)this, 0, &threadID );
#endif // APP_THREAD
		//----------------------------------

		return true;
	}

	//�Ǎ�
	void Application::Load ()
	{
		m_pFrameControl->Load ();	//�Ǎ�
	}

	//������
	void Application::Init ()
	{
		m_pFrameControl->Init ();	//������
		m_init = true;		//�������t���O
	}


	//-------------------------------------------------------------------------------------------------
	// �A�v���P�[�V�����̉��
	//-------------------------------------------------------------------------------------------------
	void Application::Rele ()
	{
#if APP_THREAD
		//�X���b�h���
		//////TRACE_F ( TEXT("�t���[������X���b�h�F���\n") );
		m_bActive = false;	//�X���b�h�I�����t���O�ɐݒ�
#endif // APP_THREAD

		m_pFrameControl->Rele ();	//���
		m_init = false;		//�������t���O
	}


	//-------------------------------------------------------------------------------------------------
	// �A�v���P�[�V�����̍Đݒ�
	//-------------------------------------------------------------------------------------------------
	void Application::Reset ()
	{
		//��x�����������Ă��Ȃ��ꍇ���Z�b�g���Ȃ�
		if ( ! m_init ) { return; }

		//�I�u�W�F�N�g�̍Đݒ�
		//�v���V�[�W����CreateWindow()���this�|�C���^�̕ۑ����g���Ȃ��̂�
		//static��m_pThis��p����
		m_pThis->m_pFrameControl->Reset ();
	}


	//-------------------------------------------------------------------------------------------------
	// (�������p) �E�B���h�E�̏�����
	// �����FhInstance		�C���X�^���X�n���h��
	// �ߒl�F���������true�A���s�����false
	//-------------------------------------------------------------------------------------------------
	bool Application::_WinInit ( HINSTANCE hInst )
	{
		//�E�B���h�E�N���X�̓o�^
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof ( WNDCLASSEX );
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)Application::WinProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = LoadIcon ( hInst, m_rcName.ICON_ID );
		wcex.hIconSm = LoadIcon ( hInst, m_rcName.ICON_ID );
		wcex.hCursor = LoadCursor ( nullptr, IDC_ARROW );
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = m_rcName.windowClassName;

		ATOM atom = RegisterClassExW ( & wcex );
		//LPCTSTR windowsClassName = (LPCTSTR)atom;

		//�ݒ肩��E�B���h�E�T�C�Y�̎w��
		int window_w = (int)AppSettingFile::Inst()->GetWindowW ();
		int window_h = (int)AppSettingFile::Inst()->GetWindowH ();

		//�E�B���h�E�̍쐬
		m_hWnd = CreateWindowW ( 
			m_rcName.windowClassName, m_rcName.TitleBar,
			WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
			0, 0, window_w, window_h,
			nullptr, nullptr, hInst, nullptr );
		if ( ! m_hWnd ) { return false; }

		//�E�B���h�E�n���h���̕ۑ�
		HWnd::Set ( m_hWnd );

		//�E�B���h�E�T�C�Y�w��
		POINT pos = GetWindowInitPos ();
		POINT size = GetWindowInitSize ();
		::SetWindowPos ( m_hWnd, HWND_TOP, pos.x, pos.y, size.x, size.y, SWP_SHOWWINDOW );
//		::ShowWindow ( m_hWnd, SW_SHOW );
		
		TRACE_F ( _T("ApplicationManager:: hWnd = %d\n"), m_hWnd );

		return true;
	}


	//-------------------------------------------------------------------------------------------------
	// �E�B���h�E �v���V�[�W��
	//-------------------------------------------------------------------------------------------------
	LRESULT CALLBACK Application::WinProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		switch ( uMsg )
		{
		case WM_DESTROY:	//�E�B���h�E�I�����b�Z�[�W
			//////TRACE_F(TEXT("WM_DESTROY\n"));
//			pThis->m_bPermi = false;	//�X���b�h���t���O��false�ɂ���
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
			//////TRACE_F(TEXT("WM_PAINT\n"));
			break;

		case WM_ACTIVATE:		//�E�B���h�E�̃A�N�e�B�u��Ԃ��ω�
			//////TRACE_F(TEXT("WM_ACTIVATE : "));
			switch ( LOWORD ( wParam ) )
			{
			case WA_INACTIVE:		//��A�N�e�B�u�ɂȂ���
				//////TRACE_F(TEXT("WA_INACTIVE\n"));
				break;

			case WA_ACTIVE:		//�}�E�X�ȊO�ŃA�N�e�B�u�ɂȂ���
				//////TRACE_F(TEXT("WA_ACTIVE\n"));
				Reset ();	//�Đݒ�
				break;

			case WA_CLICKACTIVE:	//�}�E�X�N���b�N�ŃA�N�e�B�u�ɂȂ���
				//////TRACE_F(TEXT("WA_CLICKACTIVE\n"));
				Reset ();	//�Đݒ�
				break;
			}
			break;

#if	0
		case WM_ACTIVATEAPP:	//�A�N�e�B�u�E�B���h�E�ł͂Ȃ��A�v���P�[�V�����ɑ�����E�B���h�E���A�N�e�B�u�ɂȂ���
			//////TRACE_F(TEXT("WM_ACTIVATEAPP\n"));
			break;
#endif	//0

#if	0
		case WM_MOUSEMOVE:
			DebugOutGameWindow::instance()->DebugOutf ( TEXT("%d,%d"), LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
#endif	//0

		}
		return DefWindowProc( hWnd, (unsigned int)uMsg, wParam, lParam );
	}


	//-------------------------------------------------------------------------------------------------
	// �E�B���h�E ���b�Z�[�W�̃��C�����[�v
	// �����F���b�Z�[�W�̃|�C���^
	//-------------------------------------------------------------------------------------------------
	void Application::MainLoop ( MSG * pMsg )
	{
		while ( true )
		{
			if ( PeekMessage( pMsg, nullptr, 0, 0, PM_REMOVE ) )	//Window���b�Z�[�W������Ƃ��̏���
			{
				if ( pMsg->message == WM_QUIT )
				{
					break;
				}
				TranslateMessage ( pMsg );
				DispatchMessage ( pMsg );
			}
			else	//���b�Z�[�W�ȊO�̏���
			{
				m_pFrameControl->Frame ();	//�t���[������ƃQ�[�����C��
			}
		}
	}


#if	APP_THREAD
	//------------------------------------------
	//�t���[������X���b�h (static)
	//------------------------------------------
	UINT WINAPI ApplicationManager::DrawThread ( void* vdParam )
	{
		//this�|�C���^�̎擾
		Application* pThis = reinterpret_cast<Application*>( vdParam );

		pThis->Frame();	//�t���[������ƃQ�[�����C��

		return 0;
	}
#endif	//APP_THREAD


	//------------------------------------------------------------------------
	void Application::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_pFrameControl->SetGameMain ( ::move ( pGameMain ) );
		
		//@todo Load()�̈ʒu�𒲐�
		Load ();	//�Ǎ�
		Init ();	//������
	}

	//------------------------------------------------------------------------
	POINT Application::GetWindowInitPos ()
	{
		//-------------------------------------------------
		//�J�[�\���ʒu���珉���ʒu��ݒ肷��
		if ( START_POS_CURSOR == AppSettingFile::Inst()->GetWindowStartPos () )
		{
			//�J�[�\���ʒu�̎擾
			POINT cursorPos;
			::GetCursorPos ( & cursorPos );
			cursorPos.x -= 300;
			cursorPos.y -= 10;
			return cursorPos;
		}

		//-------------------------------------------------
		//��ʒ����z�u
		POINT pos = { 0, 0 };

		//�ݒ肩��E�B���h�E�T�C�Y�̎w�� (�T�C�Y�����v�Z���邽��int�ɃL���X�g)
		int window_w = (int)AppSettingFile::Inst ()->GetWindowW ();
		int window_h = (int)AppSettingFile::Inst ()->GetWindowH ();

		//�������j�^�̎擾
		int targetDisp = (int)AppSettingFile::Inst ()->GetDisplayNum ();	//�O����
		int n = ::GetSystemMetrics ( SM_CMONITORS );	//1����

		m_count = 0;
		V_RECT vecRect ( n );

		::EnumDisplayMonitors ( NULL, NULL, MonitorEnumProc, (LPARAM)&vecRect );

		if ( targetDisp + 1 <= n )
		{
			vecRect [ targetDisp ];
			pos = CenterWndOfRect ( vecRect [ targetDisp ], window_w, window_h );
		}
		else
		{
			//�v���C�}�����j�^�̍�Ɨ̈�T�C�Y���擾
			RECT workRect;
			::SystemParametersInfo ( SPI_GETWORKAREA, 0, &workRect, 0 );
	#if 0
			int wWidth = workRect.right - workRect.left;
			int wHeight = workRect.bottom - workRect.top;
			int wPos_x = ( wWidth / 2 ) - ( window_w / 2 );
			int wPos_y = ( wHeight / 2 ) - ( window_h / 2 );

			pos.x = wPos_x;
			pos.y = wPos_y;
	#endif // 0
			pos = CenterWndOfRect ( workRect, window_w, window_h );
		}

		return pos;
	}

	POINT Application::CenterWndOfRect ( const RECT & rect, int wx, int wy ) const
	{
		int rW = rect.right - rect.left;
		int rH = rect.bottom - rect.top;
		int wPos_x = ( rW / 2 ) - ( wx / 2 );
		int wPos_y = ( rH / 2 ) - ( wy / 2 );
		return POINT { rect.left + wPos_x, rect.top + wPos_y };
	}

	int Application::m_count;


	BOOL CALLBACK Application::MonitorEnumProc ( HMONITOR hMnt, HDC hdc, LPRECT lpRect, LPARAM dwParam )
	{
		V_RECT* pr = (V_RECT*)dwParam;
		
		MONITORINFOEX mntInfo;
		mntInfo.cbSize = sizeof ( mntInfo );
		GetMonitorInfo ( hMnt, & mntInfo );

		::CopyRect ( &(*pr)[ m_count ], & mntInfo.rcMonitor );
		++ m_count;

		return TRUE;
	}

	POINT Application::GetWindowInitSize ()
	{
		//�E�B���h�E���[�h���̃T�C�Y�␳
		RECT windowRect, clientRect;

		//�E�B���h�E���A����
		::GetWindowRect ( m_hWnd, & windowRect );
		TRACE_F ( _T ( "windowRect = ( %d, %d, %d, %d ) \n" ), windowRect.left, windowRect.top, windowRect.right, windowRect.bottom );
		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		//�N���C�A���g���A����
		::GetClientRect ( m_hWnd, & clientRect );
		TRACE_F ( _T ( "clientRect = ( %d, %d, %d, %d ) \n" ), clientRect.left, clientRect.top, clientRect.right, clientRect.bottom );
		int clientWidth = clientRect.right - clientRect.left;
		int clientHeight = clientRect.bottom - clientRect.top;

		//�^�C�g���o�[�␳�T�C�Y
		POINT size;
		size.x = windowWidth + ( windowWidth - clientWidth );
		size.y = windowHeight + ( windowHeight - clientHeight );

		return size;
	}

	void Application::FullDebugMode ()
	{
		FrameControl::FullDebugMode ();
	}

	void Application::NoDebugMode ()
	{
		FrameControl::NoDebugMode ();
	}

}	//namespace GAME


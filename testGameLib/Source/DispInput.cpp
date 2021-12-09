//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const UINT DispInput::NUM_DISP_INPUT = 60;

	DispInput::DispInput ()
		: m_timer ( 0 ), m_vel ( 1.f )
	{
		//背景
		m_bg = make_shared < PrmRect > ();
		m_bg->SetRect ( 20, 10, 80, 600 );
		m_bg->SetAllColor ( 0x80808080 );
		AddpTask ( m_bg );


		//矩形管理 ( 8種類 * 60[FPS] )

		//縦 60FPS
		for ( UINT n = 0; n < NUM_DISP_INPUT; ++ n )
		{
			PVP_PRMRECT pvpRect = make_shared < VP_PRMRECT > ();
			m_vpvpRect.push_back ( pvpRect );

			//横 8種類
			for ( UINT i = 0; i < INPUT_NUM; ++ i )
			{
				P_PrmRect pRect = make_shared < PrmRect > ();
				pvpRect->push_back ( pRect );
				pRect->SetRect ( 20.f + 20 * i, 10.f + 20 * n, 10.f, 10.f );

				if ( 0 == rand () % 2 )
				{
					pRect->SetValid ( F );
				}

				AddpTask ( pRect );
			}
		}


		m_cursor = make_shared < PrmRect > ();
		m_cursor->SetSize ( 10, 10 );
		m_cursor->SetPos ( 20, 20 );
		AddpTask ( m_cursor );

	}

	DispInput::~DispInput ()
	{
	}

	void DispInput::Move ()
	{
		++ m_timer;



		POINT pt = { 0, 0 };
		//		pt = DXINP->GetMousePoint ();
		::GetCursorPos ( & pt );
		DBGOUT_WND_F ( 3, _T ( "%d, %d" ), pt.x, pt.y );

		//カーソルをクライアント位置に直す
		::ScreenToClient ( HWnd::Get (), & pt );
		DBGOUT_WND_F ( 4, _T ( "%d, %d" ), pt.x, pt.y );

		m_cursor->SetPos ( pt.x, pt.y );


		//1マス分移動したら上にシフト
		if ( 0 < m_timer )
		{
			bool b[INPUT_NUM] = { F };
			bool b_prev[INPUT_NUM] = { F };

			int n = 0;
			for ( PVP_PRMRECT pvpRect : m_vpvpRect )
			{
				int i = 0;
				for ( P_PrmRect pRect : (*pvpRect) )
				{
					b[i] = pRect->GetValid ();
					pRect->SetValid ( b_prev [ i ] );
					b_prev[i] = b[i];
					++ i;
				}
				++ n;
			}

			m_timer = 0;
		}

		//現入力
		(*m_vpvpRect[0])[0]->SetValid ( IS_KEY ( P1_LEFT	) );
		(*m_vpvpRect[0])[1]->SetValid ( IS_KEY ( P1_UP		) );
		(*m_vpvpRect[0])[2]->SetValid ( IS_KEY ( P1_RIGHT	) );
		(*m_vpvpRect[0])[3]->SetValid ( IS_KEY ( P1_DOWN	) );
		(*m_vpvpRect[0])[4]->SetValid ( IS_KEY ( P1_BUTTON1	) );
		(*m_vpvpRect[0])[5]->SetValid ( IS_KEY ( P1_BUTTON2	) );
		(*m_vpvpRect[0])[6]->SetValid ( IS_KEY ( P1_BUTTON3	) );
		(*m_vpvpRect[0])[7]->SetValid ( IS_KEY ( P1_BUTTON4	) );


		//表示位置
		int n = 0;
		for ( PVP_PRMRECT pvpRect : m_vpvpRect )
		{
			int i = 0;
			for ( P_PrmRect pRect : (*pvpRect) )
			{
				pRect->SetRect ( 20.f + 10 * i, 10.f + 10 * n + m_vel * m_timer, 10.f, 10.f );
				++ i;
			}
			++ n;
		}


		TASK_VEC::Move ();
	}


}	//namespace GAME


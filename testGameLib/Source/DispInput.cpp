//=================================================================================================
//
// DispInput ソースファイル
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
	//キー入力表示個数
	//@todo CharaInputの入力保存数と同一なので統合する
	const UINT DispInput::NUM_DISP_INPUT = 20;

	//コンストラクタ
	DispInput::DispInput ()
		: m_timer ( 0 ), m_vel ( 1.f ), m_base ( 10 )
	{
		//---------------------------------------------------------------
		//キー入力
		//背景
		m_bg = make_shared < PrmRect > ();
		m_bg->SetRect ( m_base, 200, 80, 10 * NUM_DISP_INPUT );
		m_bg->SetZ ( Z_SYS );
		m_bg->SetAllColor ( 0x8080c080 );
		GRPLST_INSERT ( m_bg );

		//矩形管理 ( 8種類 * 60[FPS] )
		//縦 60FPS
		for ( UINT frame = 0; frame < NUM_DISP_INPUT; ++ frame )
		{
			PVP_PRMRECT pvpRect = make_shared < VP_PRMRECT > ();
			m_vpvpRect.push_back ( pvpRect );

			//横 8種類
			for ( UINT i = 0; i < INPUT_NUM; ++ i )
			{
				P_PrmRect pRect = make_shared < PrmRect > ();
				pvpRect->push_back ( pRect );
				pRect->SetRect ( m_base + 20 * i, 10.f + 20 * frame, 10.f, 10.f );
				pRect->SetZ ( Z_SYS - 0.01f );

				//初期値ランダム
				if ( 0 == rand () % 2 )
				{
					pRect->SetValid ( F );
				}

				GRPLST_INSERT ( pRect );
			}
		}
	}

	DispInput::~DispInput ()
	{
	}

	//表示初期化
	void DispInput::InitDisp ( PLAYER_ID playerID )
	{
		//位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_base = 10;
		}
		else
		{
			m_base = 1280 - 10 - 80;
		}
		m_bg->SetRect ( m_base, 200, 80, 10 * NUM_DISP_INPUT );
	}

	//更新
	void DispInput::UpdateInput ( P_CharaInput pCharaInput )
	{
		//---------------------------------------------------------------
		//キー入力
		++ m_timer;

		//1マス分移動したら上にシフト
		if ( 0 < m_timer )
		{
			bool b[INPUT_NUM] = { F };
			bool b_prev[INPUT_NUM] = { F };

			int frame = 0;
			for ( PVP_PRMRECT pvpRect : m_vpvpRect )
			{
				int index = 0;
				for ( P_PrmRect pRect : (*pvpRect) )
				{
					b[index] = pRect->GetValid ();
					pRect->SetValid ( b_prev[index] );
					b_prev[index] = b[index];
					++ index;
				}
				++ frame;
			}

			m_timer = 0;
		}

		//現入力
		V_GAME_KEY vKey = pCharaInput->GetvGameKey ();

		//表示位置
		int frame = 0;
		for ( PVP_PRMRECT pvpRect : m_vpvpRect )
		{
			int index = 0;
			for ( P_PrmRect pRect : (*pvpRect) )
			{
				pRect->SetValid ( GetBoolInput ( pCharaInput, frame, index ) );
				pRect->SetRect ( m_base + 10 * index, 200.f + 10 * frame + m_vel * m_timer, 10.f, 10.f );
				++ index;
			}
			++ frame;
		}
		//---------------------------------------------------------------
	}

	//-------------------------------------
	//内部利用
	//n:キー種類, i:[F]
	bool DispInput::GetBoolInput ( P_CharaInput pCharaInput, int n, int i )
	{
		//現入力
		V_GAME_KEY vKey = pCharaInput->GetvGameKey ();

		bool ret = false;
		switch ( i )
		{
		case 0: ret = vKey[n].GetLvr ( _GameKey::LVR_4 ); break;
		case 1: ret = vKey[n].GetLvr ( _GameKey::LVR_8 ); break;
		case 2: ret = vKey[n].GetLvr ( _GameKey::LVR_6 ); break;
		case 3: ret = vKey[n].GetLvr ( _GameKey::LVR_2 ); break;
		case 4: ret = vKey[n].GetBtn ( _GameKey::BTN_0 ); break;
		case 5: ret = vKey[n].GetBtn ( _GameKey::BTN_1 ); break;
		case 6: ret = vKey[n].GetBtn ( _GameKey::BTN_2 ); break;
		case 7: ret = vKey[n].GetBtn ( _GameKey::BTN_3 ); break;
		default: break;
		}
		return ret;
	}


}	//namespace GAME


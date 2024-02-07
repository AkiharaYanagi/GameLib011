
//=================================================================================================
//
// フレーム進行の監理クラス
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FrameControl.h"

// ライブラリ内部のみで参照するヘッダファイル
#include "GameSystem.h"		//ゲームシステム(DirectX,ゲームメイン)
#include "DebugOutGameWindow.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//----------------------------------------------
	//	定数宣言
	//----------------------------------------------
	const DWORD FrameControl::dwFps = 60;	//FPS
	const DWORD FrameControl::waitOneFrameTime = 1000 * 0x10000 / dwFps;	//1フレームに待つミリ秒。上位16ビットに整数部、下位16ビットに小数部を保存

	bool FrameControl::m_bDispFPS = true;

	//------------------------------------------
	//	コンストラクタ
	//------------------------------------------
	FrameControl::FrameControl() : m_gameSystem ( nullptr )
	{
		::timeBeginPeriod(1);		//タイマーの分解能を1[ms]に設定

		m_gameSystem = std::make_unique < GameSystem > ();
	}

	//------------------------------------------
	//	デストラクタ
	//------------------------------------------
	FrameControl::~FrameControl()
	{
		::timeEndPeriod(1);		//タイマーの分解能を元に戻す
	}

	//------------------------------------------
	//	ゲームシステム初期化
	//------------------------------------------
	void FrameControl::SystemLoad ()
	{
		m_gameSystem->SystemLoad ();

		DBGOUT_WND->DebugOutWnd_MoveTime ( 0 );
		DBGOUT_WND->DebugOutWnd_DrawTime ( 0 );
	}

	//------------------------------------------
	//	読込
	//------------------------------------------
	void FrameControl::Load ()
	{
		m_gameSystem->Load ();
	}

	//------------------------------------------
	//	解放
	//------------------------------------------
	void FrameControl::Rele ()
	{
		m_gameSystem->Rele ();
	}

	//------------------------------------------
	//	再設定
	//------------------------------------------
	void FrameControl::Reset()
	{
		m_gameSystem->Reset();
	}

	//------------------------------------------
	//	初期化
	//------------------------------------------
	void FrameControl::Init()
	{
		m_frames = 0;
		m_beforeTime = 0;
		m_averageSleep = 0;
		
		//ゲームシステムの初期化
		m_gameSystem->Init ();
	}

	//------------------------------------------
	//フレーム制御(1フレームの処理)
	//------------------------------------------
	void FrameControl::Frame()
	{
		static float averageSleep = 16.6f;
		static DWORD dwDispFps = 60;
		

		//1フレームのループ
//		while ( m_bPermi )
//		while ( false )
		{
			static DWORD averageMove = 0;
			static DWORD averageDraw = 0;

#define	THREAD 0
#if	THREAD
			if ( ! m_bPermi )	//スレッド許可フラグで続行を確認する
			{
				////TRACE_F ( TEXT("フレーム制御のループ中でしたが、m_bPermiがfalseのためbreakしました。\n") );
				break;
			}
#endif	//THREAD

			DWORD startTime = ::timeGetTime();

			//--------------------------
			//フレーム毎の動作
			m_gameSystem->Move ();
			//--------------------------

			//現在時刻から経過時間を計算
			DWORD nowTime = ::timeGetTime();

			averageMove += nowTime - startTime;

			DWORD progressTime = nowTime - m_beforeTime;
			//現在フレーム数から理想時間を計算
			DWORD idealTime = (m_frames * waitOneFrameTime) >> 16;

			//1フレーム時間の調整(早すぎる時は差分だけ、それ以外は1だけSleep)
			DWORD sleepTime = ( idealTime > progressTime ) ? ( idealTime - progressTime ): 1;
			
			m_averageSleep += sleepTime;

			Sleep ( sleepTime );

			DWORD preDrawTime = ::timeGetTime();
			//--------------------------
			//描画処理
			m_gameSystem->Draw();
			//--------------------------
			DWORD postDrawTime = ::timeGetTime();

			averageDraw += postDrawTime - preDrawTime;

#if 0
			// フレーム計算は常に行い、表示だけ切り替える
			//F6で切り替え
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


			// 'F7'キーでMove, Draw 処理時間 表示切替
#if 0
			static bool bMoveDrawTimer = true;
			if ( ::GetAsyncKeyState ( VK_F7 ) & 0x0001 )
			{
				bMoveDrawTimer ^= true;
				DBGOUT_WND->SetbDisp_MoveTime ( bMoveDrawTimer );
				DBGOUT_WND->SetbDisp_DrawTime ( bMoveDrawTimer );
				if ( bMoveDrawTimer )
				{
					//60[F]の平均
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


			//1000ms毎に現在フレーム数(FPS)の更新
			if ( progressTime >= 1000 )
			{
#if 0
				if ( bMoveDrawTimer )
				{
					//60[F]の平均
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

//		m_bActive = false;	//スレッド終了をフラグに設定

	}


	//ゲームメインオブジェクトの設定
	void FrameControl::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_gameSystem->SetGameMain( ::move ( pGameMain ) ); 
	}


	//デバッグ表示をすべてON
	void FrameControl::FullDebugMode ()
	{
		m_bDispFPS = T;
//		GameSystem::FullDebugMode ();
	}

	//デバッグ表示をすべてOFF
	void FrameControl::NoDebugMode ()
	{
		m_bDispFPS = F;
///		GameSystem::NoDebugMode ();
	}

	//アーカイブ作成
	void FrameControl::SetFlag_MakeArchive ( bool b ) 
	{
		GameSystem::SetFlag_MakeArchive ( b ); 
	}

}	//namespace GAME



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
const DWORD FrameControl::waitOneFrameTime = 1000 * 0x10000 / dwFps;		//1フレームに待つミリ秒。上位16ビットに整数部、下位16ビットに小数部を保存


	//------------------------------------------
	//	コンストラクタ
	//------------------------------------------
	FrameControl::FrameControl() : m_gameSystem ( nullptr )
	{
		::timeBeginPeriod(1);		//タイマーの分解能を1[ms]に設定

		m_gameSystem = make_unique < GameSystem > ();
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
		m_average = 0;
		
		//ゲームシステムの初期化
		m_gameSystem->Init ();
	}

	//------------------------------------------
	//フレーム制御(1フレームの処理)
	//------------------------------------------
	void FrameControl::Frame()
	{
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
			
			m_average += sleepTime;

			Sleep ( sleepTime );

			DWORD preDrawTime = ::timeGetTime();
			//--------------------------
			//描画処理
			m_gameSystem->Draw();
			//--------------------------
			DWORD postDrawTime = ::timeGetTime();

			averageDraw += postDrawTime - preDrawTime;


			//1000ms毎に現在フレーム数(FPS)の更新
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

//		m_bActive = false;	//スレッド終了をフラグに設定

	}


	//ゲームメインオブジェクトの設定
	void FrameControl::SetGameMain ( UP_GameMainBase pGameMain )
	{
		m_gameSystem->SetGameMain( ::move ( pGameMain ) ); 
	}


}	//namespace GAME


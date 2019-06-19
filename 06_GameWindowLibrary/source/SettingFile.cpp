//=================================================================================================
//
// 設定ファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "SettingFile.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	SettingFile::P_SettingFile	SettingFile::m_inst;

	SettingFile::SettingFile ()
	{
		try
		{
			TCHAR path [ MAX_PATH ];
			::GetCurrentDirectory ( MAX_PATH, path );
			TRACE_F ( path );

			//入力ストリームを生成
			ifstream ifstrm( _T("Setting.dat"), ios::in );
			
			//見つからないときデフォルトの値を設定して終了
			if ( ! ifstrm )
			{
				SetDefault ();
			}
			
			//読込
			ifstrm.read ( (char*)& m_bFullscreen, sizeof(bool) );
			UINT size = sizeof ( UINT );
			ifstrm.read ( (char*)& m_window_x, sizeof ( UINT ) );
			ifstrm.read ( (char*)& m_window_y, sizeof ( UINT ) );

			//終了
			ifstrm.close ();
		}
		catch (...)
		{
		}
	}

	SettingFile::~SettingFile ()
	{
	}
	
	void SettingFile::SetDefault ()
	{
		m_bFullscreen = false;
		m_window_x = 640;
		m_window_x = 480;
	}


}	//namespace GAME


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
	SettingFile::_UP_StgFl	SettingFile::m_inst;

	SettingFile::SettingFile ()
	{
		try
		{
			TCHAR path [ MAX_PATH ];
			::GetCurrentDirectory ( MAX_PATH, path );
			TRACE_F ( path );

			//入力ストリームを生成
			ifstream ifstrm( _T("GameSetting.dat"), ios::in );
			
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
			ifstrm.read ( (char*)& m_input1pPlayer, sizeof(bool) );
			ifstrm.read ( (char*)& m_input2pPlayer, sizeof(bool) );

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
		m_window_x = 1280;
		m_window_y = 960;
		m_input1pPlayer = true;
		m_input2pPlayer = true;
	}


}	//namespace GAME


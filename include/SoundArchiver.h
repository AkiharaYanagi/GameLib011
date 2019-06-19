//=================================================================================================
//
// SoundArchiver ヘッダファイル
//
//		Debugモード時にSoundディレクトリにあるwaveファイルをsound.datに書き出し、
//		Debugモード, Releaseモード時にsound.datからwaveを読み込む
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>

#include "DebugLibrary.h"
#include "DxSound.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//========================================================
	//	◆ サウンドアーカイブ フォーマット
	//	----
	//	UINT	4byte	//サイズ
	//	BYTE	...		//バイナリデータ
	//	----
	//	n個の列挙
	//	検索するときは定数添字
	//========================================================

	class SoundArchiver
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_SoundArchiver = unique_ptr < SoundArchiver >;
		static P_SoundArchiver		m_inst;
		SoundArchiver ();
		SoundArchiver ( const SoundArchiver& rhs ) = delete;
	public:
		~SoundArchiver ();
		static void Create () { if ( ! m_inst ) { m_inst = P_SoundArchiver ( new SoundArchiver () ); } }
		static P_SoundArchiver & instance () { return m_inst; }
	//--------------------------------------------------

	private:
		static const TCHAR			m_archiveFileName[];
		static const TCHAR			m_archiveDirName[];
		static const TCHAR			m_searchCondition[];

		HANDLE						m_hFile;

		UINT	m_count;		//読込個数

	public:
		void Make ();

		void Open ();
		void Close ();

		void Play ( UINT id );
		void PlayLoop ( UINT id );
		void Stop ( UINT id );
	};

	//外部利用定義
	#define		SOUND	SoundArchiver::instance()


}	//namespace GAME


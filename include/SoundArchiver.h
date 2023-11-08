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
		static LPCTSTR	m_archiveFileName;	//作成するサウンドアーカイブファイル名

		static LPCTSTR	m_archiveDirName;	//アーカイブ作成のため読み込むディレクトリ名
		static LPCTSTR	m_searchCondition;	//アーカイブ作成のため読み込むファイル名条件

		static LPCTSTR	m_archiveDirName_SE;	//アーカイブ作成のため読み込むディレクトリ名
		static LPCTSTR	m_searchCondition_SE;	//アーカイブ作成のため読み込むファイル名条件

//		HANDLE		m_hFile;	//読込ファイルハンドル
//		UINT		m_count;	//読込個数

		DWORD		m_nBGM;
		DWORD		m_nSE;

	public:
		void Make ();
		void Open ();

		//------------------------------------------------------------------
#if 0
		void Play ( UINT id );
		void PlayLoop ( UINT id );
		void Stop ( UINT id );
#endif // 0
		void Play_BGM ( UINT BGM_ID );
		void Play_Loop_BGM ( UINT BGM_ID );
		void Stop_BGM ( UINT BGM_ID );

		void Play_SE ( UINT SE_ID );

	private:

		//条件のファイル数え上げ
		UINT CountFileNum ( LPCTSTR condition );

		//作成
		void _Make ( HANDLE hWriteFile, LPCTSTR dirname, LPCTSTR condition );
	};

	//外部利用定義
	#define		SOUND	SoundArchiver::instance()


}	//namespace GAME


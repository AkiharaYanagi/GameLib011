//=================================================================================================
//
// ファイルアーカイバ
//		Debugモード時にArchiveディレクトリにあるファイルをarchive.datに書き出し、
//		Debugモード, Releaseモード時にarchive.datからファイルポインタを読み込む
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <iostream>
#include <map>
#include "DebugLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	//========================================================
	//	◆アーカイブデータ　ヘッダフォーマット
	//	DWORD			fileNum		//ファイルの個数
	//	ARCHIVE_HEADER	...			//fileNum分だけ列挙
	//	BYTE			...			//バイナリデータ
	//========================================================

	//ファイル内配置
	struct ARCHIVE_ALIGN
	{
		DWORD		offset;			//(ヘッダを除く)データ開始位置からのポインタ位置オフセット
		DWORD		fileSize;		//ファイルサイズ
	};

	//書込用
	struct ARCHIVE_HEADER
	{
		TCHAR			fileName[ MAX_PATH ];	//ファイル名
		ARCHIVE_ALIGN	align;					//配置
	};

	//検索用
	struct ARCHIVE_HEADER_SEARCH
	{
		tstring			fileName;		//ファイル名
		ARCHIVE_ALIGN	align;			//配置
	};

	//戻値用
	struct ARCHIVE_FILE_USE
	{
		LPCVOID		filePointer;		//ファイルポインタ
		DWORD		fileSize;			//ファイルサイズ
	};

	//map型宣言
	using ARCHIVE_MAP = std::map < tstring, ARCHIVE_ALIGN* >;


	//アーカイバクラス
	class Archiver
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_Archiver = unique_ptr < Archiver >;
		static P_Archiver	m_inst;
		Archiver ();
		Archiver ( const Archiver & rhs ) = delete;
	public:
		~Archiver ();
		static void Create () { if ( ! m_inst ) { m_inst = P_Archiver ( new Archiver () ); } }
		static P_Archiver & instance() { return m_inst; }	//インスタンス取得
	//--------------------------------------------------

	private:
		HANDLE						m_hFile;
		HANDLE						m_hMap;		//ファイルマッピング

		DWORD						m_fileNum;
		ARCHIVE_HEADER_SEARCH*		m_archiveHeader;
		ARCHIVE_MAP					m_map;
		LPVOID						m_pFile;
		
		static const TCHAR			m_archiveFileName[];
		static const TCHAR			m_archiveDirName[];
		static const TCHAR			m_searchCondition[];
		static const TCHAR			m_mapName[];

	public:
		//アーカイブファイル作成
		void Make ();

		//アーカイブファイル読込
		void Open ();

		//アーカイブファイル閉
		void Close ();

		//元のファイル名からアーカイブ内のファイルポインタを得る
		ARCHIVE_FILE_USE GetFilePointer ( LPCTSTR fileName );
	};




}	//namespace GAME


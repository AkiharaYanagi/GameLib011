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
	//	◆アーカイブバイナリファイル　ヘッダフォーマット
	//	DWORD				fileNum		//ファイルの個数
	//	ARCHIVE_HEADER[]	...			//fileNum分だけ列挙
	//	BYTE				...			//バイナリデータ
	//========================================================

	//ファイル内配置
	//mapにおいて[名前]をキーにで取得したいデータ
	struct ARCHIVE_ALIGN
	{
		DWORD		offset;		//(ヘッダを除く)データ開始位置からのポインタ位置オフセット
		DWORD		fileSize;	//ファイルサイズ
	};

	//書込用(大きさが定数のTCHAR[]を用いる)
	struct ARCHIVE_HEADER
	{
		TCHAR			fileName[ MAX_PATH ];	//ファイル名
		ARCHIVE_ALIGN	align;					//配置
	};
	using ACV_H = ARCHIVE_HEADER;

	//検索用(文字列操作がしやすいtstringを用いる)
	struct ARCHIVE_HEADER_SEARCH
	{
		tstring			fileName;	//ファイル名
		ARCHIVE_ALIGN	align;		//配置
	};
	using ACV_H_SRC = ARCHIVE_HEADER_SEARCH;

	//戻値用
	struct ARCHIVE_FILE_USE
	{
		LPCVOID		filePointer;	//ファイルポインタ
		DWORD		fileSize;		//ファイルサイズ
	};
	using ACV_FL_USE = ARCHIVE_FILE_USE;

	//map型宣言
	using ARCHIVE_MAP = std::map < tstring, ARCHIVE_ALIGN >;


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
		HANDLE					m_hMap;		//データのファイルマッピングハンドル
		LPVOID					m_pFile;	//ファイルマッピングの開始アドレス

		ARCHIVE_MAP				m_map;		//実データ検索用マップ

		//Releaseモードでは記録されない
		//アーカイブファイルのデータヘッダを参照する
		vector < ACV_H_SRC >	m_vFilename;	//対象データファイル名リスト

		//ファイル列挙のとき、Find()においてディレクトリで再帰するのでカウントは外側に記録する
		DWORD					m_current_offset;	//現在オフセット位置
		
		static const TCHAR		ARCHIVE_FILE_NAME[];
		static const TCHAR		ARCHIVE_DIR_NAME[];
		static const TCHAR		SEARCH_CONDITION[];
		static const TCHAR		MAP_NAME[];

	public:
		void Make ();		//アーカイブファイル作成
		void Open ();		//アーカイブファイル読込
		void Close ();		//アーカイブファイル閉

		//元のファイル名からアーカイブ内のファイルポインタを得る
		ACV_FL_USE GetFilePointer ( LPCTSTR fileName );

	private:
		//ファイル検索の再帰
		void Find ( LPCTSTR path );
	};




}	//namespace GAME


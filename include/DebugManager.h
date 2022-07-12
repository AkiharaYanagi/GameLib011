﻿//=================================================================================================
//
// デバッグマネージャ　ヘッダ
//		テキストファイルとデバッグウィンドウへの出力
//		デバッグテキストファイル(log.txt)出力
//		IDEデバッグ出力
//		シングルトンパターンを用いてグローバルからオブジェクトにアクセスする
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "GameLibConst.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0
	//=================================================================================================
	//デバッグ用スタティックオブジェクト
	class DebugOut
	{
	public:
		DebugOut () = delete;		//実体化禁止
		~DebugOut () = default;

		//フォーマット文字列
		template < typename... Args >
		static LPCTSTR f ( LPCTSTR tstr, const Args&... args );
	};
	
	template < typename... Args >
	LPCTSTR DebugOut::f ( LPCTSTR tstr, const Args&... args )
	{
		Format::f ( tstr, args );
		TOSS toss = Format::RefToss ();
		return toss.str ().c_str ();
	}
#endif // 0


//=================================================================================================
	//デバッグテキストファイル出力
	class DebugOutFile
	{
	//--------------------------------------------------
	//シングルトンパターン
		using P_DebugOutFile = unique_ptr < DebugOutFile >;
		static P_DebugOutFile m_inst;
		DebugOutFile ();
		DebugOutFile ( const DebugOutFile & rhs ) = delete;
	public:
		~DebugOutFile ();
		static P_DebugOutFile & instance () { return m_inst; }
		static void Create () { if ( ! m_inst ) { m_inst = P_DebugOutFile ( new DebugOutFile () ); } }
	//--------------------------------------------------

	private:
		tofstream	m_tofstrm;	//出力ファイル

	public:
		void DebugOutf ( LPCTSTR format, ... );
	};

//シングルトンアクセス用
#define DBGOUT_FL	DebugOutFile::instance()
#define DBGOUT_FL_F	DebugOutFile::instance()->DebugOutf


//=================================================================================================
	//IDEデバッグウィンドウ出力 [ TRACE() ]
	class DebugOutTrace
	{
#if 0
		//--------------------------------------------------
		//シングルトンパターン
		DebugOutTrace () = default;
		DebugOutTrace ( const DebugOutTrace & rhs ) = delete;
		static unique_ptr < DebugOutTrace > m_inst;
	public:
		~DebugOutTrace() = default;
		static unique_ptr < DebugOutTrace > & instance() { return m_inst; }
		static void Create () { if ( ! m_inst ) m_inst = unique_ptr < DebugOutTrace > ( new DebugOutTrace () ); }
		//--------------------------------------------------
#endif // 0

		DebugOutTrace () = delete;	//staticクラスとして実体化禁止

	public:

		//文字列フォーマットを表示(Unicode)
		static void DebugOutf ( LPCTSTR format, ... );

		//文字列フォーマットを表示(char*)
		static void DebugOutchf ( LPCSTR format, ... );

		//GetLastError()からのWIN32APIのエラーメッセージ表示
		//引数：呼出側で__FILE__, __LINE__を指定
		static void OutputLastError ( LPCSTR file, DWORD line );
	};


//シングルトンアクセス用
//#define TRACE_F		DebugOutTrace::instance()->DebugOutf
//#define TRACE_CHF	DebugOutTrace::instance()->DebugOutchf
#define TRACE_F		DebugOutTrace::DebugOutf
#define TRACE_CHF	DebugOutTrace::DebugOutchf


}	//namespace GAME


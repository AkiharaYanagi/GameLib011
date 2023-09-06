//=================================================================================================
//
// ゲームタスク　ヘッダ
//
//		スマートポインタに変更
//
//		ゲームに用いる基本オブジェクト構造の定義
//
//		ゲームタスク			：ゲームメインに用いるオブジェクトの基本型で最小単位。
//		ゲームタスクベクタ		：フレーム毎でゲームタスクの基本インターフェースを一括して行う配列
//		ゲームタスクアサイン	：フレーム毎で特定の一つにゲームタスクの基本インターフェースを実行する配列
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
using namespace std;

#include "DebugManager.h"
#include "GameTask.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//=========================================================================
	// ゲームタスク
	//=========================================================================
	class GameTask
	{
	public:
		GameTask () = default;
		GameTask ( const GameTask& rhs ) = delete;
		virtual ~GameTask () = default;

		//定義無しでも用いるため純粋仮想関数にはしない
#if	0
		virtual void Load () = 0;
		virtual void Rele () = 0;
		virtual void Init () = 0;
		virtual void Move () = 0;
		virtual void Draw () = 0;
#endif	//0

		virtual void Load () {}		//読込(初回、または再設定時などの解放後１回のみ)
		virtual void Rele () {}		//動的な一時領域の解放(恒常的なメモリ確保はコンストラクタ～デストラクタで行う)
		virtual void Reset () {}	//再設定( Rele(); Load(); Init(); )

		virtual void Init () {}		//初期化(繰り返してもよい)
		virtual void Move () {}		//フレーム毎動作

		//->描画はGraphicListに移項
#if 0
		virtual void Draw () {}		//フレーム毎描画(スプライト)
		virtual void DrawVertex () {}	//フレーム毎描画(頂点)
#endif // 0
	};

	//型定義
	using P_Task = shared_ptr < GameTask >;
	using VP_Task = vector < P_Task >;
	using PVP_Task = shared_ptr < VP_Task >;
	using LP_Task = list < P_Task >;
	using PLP_Task = shared_ptr < LP_Task >;


	//=========================================================================
	// ゲームタスクベクタ
	//	ゲームタスクの基本インターフェースを一括して行う
	//=========================================================================
	class GameTaskVector : public GameTask
	{
		PVP_Task		m_pvpTask;

	public:
		GameTaskVector ();
		GameTaskVector ( const GameTaskVector & rhs ) = delete;
		virtual ~GameTaskVector ();

		virtual void Load();		//読込(初回、または再設定時などの解放後１回のみ)
		virtual void Rele();		//動的な一時領域の解放(恒常的なメモリ確保はコンストラクタ～デストラクタで行う)
		virtual void Reset();		//再設定( Rele(); Load(); Init(); )

		virtual void Init();		//初期化(繰り返してもよい)※再設定時(フォーカスの変更など)に毎回行う
		virtual void Move();		//フレーム毎動作

#if 0
		virtual void Draw();		//フレーム毎描画(スプライト)
		virtual void DrawVertex ();		//フレーム毎描画(頂点)
#endif // 0

		//初期化
		void Clear();
		
		//配列サイズの取得
		size_t GetSize () { return m_pvpTask->size (); }

		//配列ポインタの取得
		PVP_Task GetpvpTask () { return m_pvpTask; }

		//タスクの追加（サイズの変更も自動的に行う）
		//	※実体のある変数から&でスマートポインタを直接扱わない
		void AddpTask ( P_Task pTask );

		//タスクの取得（サイズの変更も自動的に行う）
		P_Task GetpTask ( UINT index );

		//アクセサ		
		P_Task operator [] ( UINT index );

		//タスクの挿入
		void InsertTask ( P_Task pTask, UINT index );

		//タスクの取外
		void EraseTask ( P_Task pTask );
		void EraseTask ( const VP_Task::iterator it );

		//指定オブジェクトを最前列描画にする
		//	指定したオブジェクトが無い場合なにもしない
		void Top ( P_Task pTask );

		//指定オブジェクトを最背列描画にする
		//	指定したオブジェクトが無い場合なにもしない
		void End ( P_Task pTask );
	};

	using TASK_VEC = GameTaskVector;
	using P_TASK_VEC = shared_ptr < TASK_VEC >;


	//=========================================================================
	// ゲームタスクリスト
	//	ゲームタスクの基本インターフェースを一括して行う
	//	生成・削除が多いときに用いる
	//=========================================================================
	class GameTaskList : public GameTask
	{
		PLP_Task	m_plpTask;

	public:
		GameTaskList ();
		GameTaskList ( const GameTaskList & rhs ) = delete;
		virtual ~GameTaskList ();

		virtual void Load ();		//読込(初回、または再設定時などの解放後１回のみ)
		virtual void Rele ();		//動的な一時領域の解放(恒常的なメモリ確保はコンストラクタ～デストラクタで行う)
		virtual void Reset ();		//再設定( Rele(); Load(); Init(); )

		virtual void Init ();		//初期化(繰り返してもよい)※再設定時(フォーカスの変更など)に毎回行う
		virtual void Move ();		//フレーム毎動作
#if 0
		virtual void Draw ();		//フレーム毎描画(スプライト)
		virtual void DrawVertex ();		//フレーム毎描画(頂点)
#endif // 0

		//初期化
		void Clear ();

		//配列サイズの取得
		size_t GetSize () { return m_plpTask->size (); }

		//配列ポインタの取得
		PLP_Task GetplpTask () { return m_plpTask; }

		//タスクの追加
		void AddpTask ( P_Task pTask );

		//タスクの挿入
		void InsertTask ( LP_Task::iterator it, P_Task pTask );

		//タスクの取外
		void EraseTask ( P_Task pTask );
		void EraseTask ( const LP_Task::iterator it );

		//指定オブジェクトを最前列描画にする
		//	指定したオブジェクトが無い場合なにもしない
		void Top ( P_Task pTask );

		//指定オブジェクトを最背列描画にする
		//	指定したオブジェクトが無い場合なにもしない
		void End ( P_Task pTask );
	};

	using TASK_LST = GameTaskList;
	using P_TASK_LST = shared_ptr < TASK_LST >;


#if 0
	//-------------------------------------------------------------------------------------------------
	// ゲームタスクアサイン
	//	特定の一つにゲームタスクの基本インターフェースを実行する配列
	//-------------------------------------------------------------------------------------------------
	class GameTaskAssign : public GameTaskVector
	{
		UINT		m_index;			//現在インデックス

	public:
		GameTaskAssign();
//		GameTaskAssign(const GameTaskVector& rhs);
		virtual ~GameTaskAssign();

		virtual void Move();		//特定の一つにフレーム毎動作
		virtual void Draw();		//特定の一つにフレーム毎描画(スプライト)

		//タスクの取得
		shared_ptr < GameTask > GetTask() { return GameTaskVector::GetTask ( m_index ); }

		//インデックスの設定
		void SetIndex ( UINT index ) 
		{
			assert ( index < GetSize() );
			m_index = index;
		}
		UINT GetIndex () { return m_index; }

		//タスクのポインタからインデックスを指定する
		void SetIndex ( shared_ptr < GameTask > p );

		//次へ
		void Next () {
			if ( m_index + 1 < GetSize () ) { ++m_index; }	//個数は１から添字は０から
			else { m_index = 0; } 
		}
	};
#endif // 0


}	//namespace GAME



//=================================================================================================
//
// ゲームメイン(ベース)	ヘッダ
//
//					ゲーム内容における主となる挙動を記述する。
//
//	Load () 読込(外部リソースなど1回のみ初期化)
//	↓
//	Init()	初期化(複数回行う可能性のある)
//	↓
//	Move()	フレーム毎の動作
//	↓↑
//　Draw()	フレーム毎の描画
//	↓
//	Rele()	解放
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "GameStructureLibrary.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//=========================================================================
	//	ゲームメインのインターフェースクラス　継承して用いる
	//=========================================================================
	class GameMainBase : public GameTaskVector
	{
	public:
		GameMainBase() {}
		GameMainBase ( const GameMainBase & rhs ) = delete;
		virtual ~GameMainBase() = 0;
#if	0
		virtual void Load () = 0;		//解放
		virtual void Rele () = 0;		//解放
		virtual void Init() = 0;		//初期化
		virtual void Move() = 0;		//フレーム毎動作
		virtual void Draw() = 0;		//フレーム毎描画(スプライト)
		virtual void DrawVertex() = 0;	//フレーム毎描画(頂点)
		virtual void Reset() = 0;		//再設定
#endif	//0
	};

	//純粋仮想デストラクタ
	inline GameMainBase::~GameMainBase() {
//		TRACE_F(TEXT("ゲームメインインターフェースピュアバーチャルデストラクタ\n"));
	}


	using UP_GameMainBase = unique_ptr < GameMainBase >;


	//=========================================================================
	//	何もしないテスト用ゲームメイン
	//=========================================================================
	class GameMainTest : public GameMainBase
	{
	public:
		GameMainTest() = default;
		GameMainTest(const GameMainTest& rhs) = delete;
		virtual ~GameMainTest();

		void Load () {}		//読込
		void Rele(){}		//解放
		void Reset(){}		//再設定

		void Init(){}		//初期化
		void Move(){}		//フレーム毎動作
		void Draw(){}		//フレーム毎描画(スプライト)
		void DrawVertex(){}	//フレーム毎描画(頂点)
	};

	inline GameMainTest::~GameMainTest() {
		//TRACE_F(TEXT("ゲームメインテストデストラクタ\n"));
	}


	using UP_GameMainTest = unique_ptr < GameMainTest >;


}	//namespace GAME


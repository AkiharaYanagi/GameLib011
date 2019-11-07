//=================================================================================================
//
//	Chara ヘッダファイル
//		キャラクタのデータを管理する
//		イメージ、スクリプト、コマンド
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
#include "Action.h"
#include "Effect.h"
#include "Behavior.h"
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	キャラ 実行上データ ver105
	//	
	//	キャラ	
	//		┣[]イメージ
	//		┣[]Efイメージ
	//		┃
	//		┣[]アクション
	//	new	┃	┣[]スクリプト
	//		┃		┣[]ブランチ
	//		┃		┣[]Efジェネレート
	//		┃
	//		┣[]Ef
	//		┃	┣[]スクリプト new
	//		┃		┣[]ブランチ
	//		┃		┣[]Efジェネレート
	//		┃
	//		┣[]コマンド
	//		┣基本状態アクションID
	//		┃	┣立ち, 構え, 打合, 避け, よろけ, ダメージ, ダウン, 勝利
	//		┃
	//
	//==================================================================================


	class Chara
	{
//		Behavior		m_bhvMain;		//メイン スクリプト
		PVP_TxBs		m_pvpTxMain;	//メインイメージ テクスチャ配列
		PVP_Action		m_pvpAction;	//アクション配列

//		Behavior		m_bhvEf;		//EF スクリプト
		PVP_TxBs		m_pvpTxEf;		//EFイメージ テクスチャ配列
		PVP_Effect		m_pvpEf;		//エフェクト配列

		VP_Command		m_vpCommand;		//コマンド配列

		UINT	m_bsAction [ BASIC_ACTION_NUM ];		//基本アクション

	public:
		Chara ();
		Chara ( const Chara & rhs ) = delete;
		~Chara ();

		void Make ();
		void Rele ();
		void Reset ();

		//-----------------------------------------------------------------
		//メインイメージ テクスチャ配列ポインタ
		PVP_TxBs GetpvpMainTexture () const { return m_pvpTxMain; }

		//メインイメージ テクスチャ配列に追加
		void AddpMainTexture ( P_TxBs pTexture ) { m_pvpTxMain->push_back ( pTexture ); }

		//メインイメージ テクスチャポインタの取得
		P_TxBs GetpMainTexture ( UINT index ) { return m_pvpTxMain->at ( index ); }

		//-----------------------------------------------------------------
		//Efイメージ テクスチャ配列ポインタ
		PVP_TxBs GetpvpEfTexture () const { return m_pvpTxEf; }

		//Efイメージ テクスチャ配列に追加
		void AddpEfTexture ( P_TxBs pTexture ) { m_pvpTxEf->push_back ( pTexture ); }

		//Efイメージ テクスチャポインタの取得
		P_TxBs GetpEfTexture ( UINT index ) { return m_pvpTxEf->at ( index ); }

		//-----------------------------------------------------------------
		//アクション配列ポインタを取得
		PVP_Action GetpvpAction () { return m_pvpAction; }

		//アクション配列に追加
		void AddpAction ( P_Action pAction ) { m_pvpAction->push_back ( pAction ); }

		//アクションポインタを取得
		P_Action GetpAction ( UINT index ) { return m_pvpAction->at ( index ); }

		//---------------------------------------------------------------------
		//基本アクションID
		UINT GetBsAction ( BASIC_ACTION index ) const { return m_bsAction[ index ]; }
		void SetBsAction ( BASIC_ACTION index, UINT actionID ) { m_bsAction [ index ] = actionID; }

		//-----------------------------------------------------------------
		//エフェクト配列に追加
		void AddpEffect ( P_Effect pEffect ) { m_pvpEf->push_back ( pEffect ); }

		//エフェクト配列ポインタを取得
		PVP_Effect GetpvpEffect () { return m_pvpEf; }

		//エフェクトポインタを取得
		P_Effect GetpEffect ( UINT index ) { return m_pvpEf->at ( index ); }

		//---------------------------------------------------------------------
		//スクリプトポインタを取得
		P_Script GetpScript ( UINT indexAction, UINT indexScript ) { return m_pvpAction->at ( indexAction )->GetpScript( indexScript ); }

		//次スクリプトが存在するかどうか
		bool IsNextScript ( UINT indexAction, UINT indexScript )
		{
			return m_pvpAction->at ( indexAction )->IsNextScript( indexScript );
		}

		//---------------------------------------------------------------------
		//コマンド配列に追加
		void AddpCommand ( P_Command pCommand ) { m_vpCommand.push_back ( pCommand ); }

		//コマンドを取得
		P_Command GetpCommand ( UINT indexCommand ) const { return m_vpCommand[indexCommand]; }

	};

	using P_Chara = shared_ptr < Chara >;
	using VP_Chara = vector < P_Chara >;
	using PVP_Chara = shared_ptr < VP_Chara >;


}	//namespace GAME



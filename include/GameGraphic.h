//=================================================================================================
//
// ゲームグラフィック　クラス　ヘッダ
//		グラフィックを扱うオブジェクトを定義する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "GameTask.h"
#include "GameTexture.h"
#include "GameObject.h"
#include <vector>
#include "GameGraphicCore.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
using namespace std;

namespace GAME
{
	//■=======================================================================
	// ゲームグラフィック　ベース
	//		・複数テクスチャと複数オブジェクトを持つグラフィック
	//		・テクスチャが指定されていないときは何もしない
	//		・純粋仮想関数を持つので実体化は不可
	//		・継承先
	//			GameGraphicFromFile
	//			GameGraphicFromArchive
	//			GameGraphicApprovedTexture
	//		　のいずれかを用いる
	//■=======================================================================
	class GameGraphicBase	: public GameGraphicCore
	{
		//オブジェクト位置
		P_VEC3		m_pCenter;		//スプライト中心位置
		P_VEC3		m_pPosition;	//スプライト表示位置

		//オブジェクト配列
		PVP_Object	m_pvpObject;
		UINT		m_indexObject;

		//テクスチャ配列(インデックスはオブジェクトが持つ)
		PVP_TxBs	m_pvpTexture;

	public:
		GameGraphicBase ();
		GameGraphicBase ( const GameGraphicBase & rhs ) = delete;
		virtual ~GameGraphicBase ();

		//純粋仮想関数
		virtual void Load () = 0;	//読込
		virtual void Rele () = 0;	//解放
		virtual void Reset () = 0;	//再設定

		virtual void Move();	//フレーム毎動作
		virtual void Draw();	//フレーム毎描画

		//---------------------------------------------------------------------
		//スプライト中心位置
		void SetSpriteCenter ( VEC3 center ) { (* m_pCenter) = center; }
		VEC3 GetSpriteCenter () { return (* m_pCenter); }
		//スプライト表示位置 /* Z: 1.f == 最背面, 0.f == 最前面 */
		void SetSpritePosition ( VEC3 position ) { (* m_pPosition) = position; }
		VEC3 GetSpritePosition () { return (* m_pPosition); }
		void SetZ ( float z ) { m_pPosition->z = z; }
		float GetZ () const { return m_pPosition->z; }

		//---------------------------------------------------------------------
		//オブジェクトvectorのポインタ
		PVP_Object GetpvpObject () { return m_pvpObject; }

		//クリア
		void ClearObject ();

		//再設定(最初の１つをクリアしてから個数を追加)
		virtual void ResetObjectNum ( UINT n ) { ClearObject (); AddObject ( n ); }

		//追加
		virtual void AddObject () { m_pvpObject->push_back ( make_shared < GameObject > () ); }
		virtual void AddObject ( UINT n ) { for ( UINT i = 0; i < n; ++i ) { AddObject (); } }
		virtual void AddpObject ( P_Object p ) { m_pvpObject->push_back ( p ); }

		void SetAllValid ( bool b );		//すべて可動切替
		void SetAllPos ( VEC2 vec );		//すべて位置指定
		void SetAllColor ( D3DXCOLOR color );		//すべての色を指定

		//---------------------------------------------------------------------
		//オブジェクト直接先頭制御
		void SetPos ( VEC2 v ) { m_pvpObject->at ( 0 )->SetPos ( v ); }
		void SetPos ( float x, float y ) { m_pvpObject->at ( 0 )->SetPos ( x, y ); }
		VEC2 GetPos () const { return m_pvpObject->at ( 0 )->GetPos (); }

		void SetScaling ( VEC2 v ) { m_pvpObject->at ( 0 )->SetScaling ( v ); }
		void SetScaling ( float x, float y ) { m_pvpObject->at ( 0 )->SetScaling ( x, y ); }
		void SetScalingCenter ( VEC2 v ) { m_pvpObject->at ( 0 )->SetScalingCenter ( v ); }

		void SetRotationCenter ( VEC2 v ) { m_pvpObject->at ( 0 )->SetRotationCenter ( v ); }
		void SetRadian ( float f ) { m_pvpObject->at ( 0 )->SetRadian ( f ); }

		//オブジェクト指定
		void SetiPos ( UINT i, VEC2 v ) { m_pvpObject->at ( i )->SetPos ( v ); }

		//---------------------------------------------------------------------
		//テクスチャの設定

		//テクスチャポインタを追加
		void AddpTexture ( P_TxBs pTexture );

		//テクスチャを設定
		void SetpTexture ( P_TxBs pTexture );

		//Clear
		void ClearTexture () { m_pvpTexture->clear (); }

		//テクスチャの先頭を返す
		P_TxBs GetpTexture () { return m_pvpTexture->at ( 0 ); }

		//テクスチャ配列ポインタを返す
		PVP_TxBs GetpvpTexture () { return m_pvpTexture; }

		//先頭のみ指定
		void SetIndexTexture ( UINT i )
		{
			m_pvpObject->at ( 0 )->SetIndexTexture ( i );
		}

		//テクスチャの中心位置 (Load()後のみ)
		VEC2 GetCenterOfTexture ( UINT index ) const ;

		//---------------------------------------------------------------------

		//オブジェクトを用いたフェード


		//@todo
		//オブジェクトが２つ以上のときフェードで入替
		void FadeChangeOb ( UINT i0, UINT i1 );


	};

	//型指定
	typedef		GameGraphicBase			GrpBs;
	typedef		shared_ptr < GrpBs >	P_GrpBs;


	//■=======================================================================
	// ゲームグラフィック フロムファイル
	// (画像ファイル指定)
	//		GameTextureFromFileを用いて名前を指定して直接画像ファイルから読込
	//		１つのテクスチャを保持し、管理する
	//■=======================================================================
	class GameGraphicFromFile : public GrpBs
	{
		VP_TxBs	m_vpTexture;

	public:
		GameGraphicFromFile ();
		GameGraphicFromFile ( const GameGraphicFromFile& rhs ) = delete;	//コピー禁止
		virtual ~GameGraphicFromFile ();

		virtual void Load();	//読込
		virtual void Rele();	//解放
		virtual void Reset();	//再設定

		//テクスチャの読込ファイル名を指定
//		void SetFileName ( LPCTSTR fileName ) { m_pTextureFromFile->SetFileName ( fileName ); }

		//テクスチャを追加
		void AddTexture ( LPCTSTR fileName );
	};

	typedef		GameGraphicFromFile		GrpFl;
	typedef		shared_ptr < GrpFl >	P_GrpFl;


	//■=======================================================================
	// ゲームグラフィック フロムアーカイブ
	// (アーカイブ利用)
	//		GameTextureFromArchiveを用いて名前を指定してアーカイブから読込
	//		GameGraphicBaseがテクスチャとマトリクスのvectorを持つ
	//■=======================================================================
	class GameGraphicFromArchive : public GrpBs
	{
		VP_TxBs	m_vpTexture;

	public:
		GameGraphicFromArchive ();
		GameGraphicFromArchive ( const GameGraphicFromArchive& rhs ) = delete;	//コピー禁止
		virtual ~GameGraphicFromArchive ();

		virtual void Load();	//読込
		virtual void Rele();	//解放
		virtual void Reset();	//再設定

		//テクスチャを追加
		void AddTexture ( LPCTSTR fileName );
	};

	typedef		GameGraphicFromArchive	GrpAcv;
	typedef		shared_ptr < GrpAcv >	P_GrpAcv;


	//■=======================================================================
	// ゲームグラフィック　アプロブドテクスチャ
	//		既に読み込んであるテクスチャを指定する
	//		GameGraphicBaseがテクスチャとマトリクスのvectorを持つ
	//■=======================================================================
	class GameGraphicApprovedTexture	: public GrpBs
	{
		P_TxBs	m_pTexture;		//読込済みテクスチャ(解放・再設定は設定元で行う)

	public:
		GameGraphicApprovedTexture ();
		GameGraphicApprovedTexture ( const GameGraphicApprovedTexture& rhs ) = delete;	//コピー禁止
		virtual ~GameGraphicApprovedTexture ();

		//読込・解放・再設定はテクスチャ側で行う
		//テクスチャを解放しない仮想関数

		//GraphicBaseのClear()のみ行う
		virtual void Load();	//読込
		virtual void Rele();	//解放
		virtual void Reset();	//再設定

		//テクスチャ
		void SetpTexture ( P_TxBs pTexture )
		{
			GrpBs::SetpTexture ( pTexture );
		}
	};

	typedef		GameGraphicApprovedTexture	GrpApTx;
	typedef		shared_ptr < GrpApTx >	P_GrpApTx;


}	//namespace GAME


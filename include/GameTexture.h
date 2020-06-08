//=================================================================================================
//
// ゲームテクスチャ　ヘッダ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "Dx3D.h"
#include "Archiver.h"
#include "GameTask.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//--------------------------------------------------------
	//ゲームテクスチャ　ベース
	//		テクスチャの基本
	//		・純粋仮想関数を持つので実体化は不可
	//--------------------------------------------------------
	class GameTextureBase
	{
		TX		m_lpTexture;		//テクスチャ(確保・解放は継承先で行う)
//		_CLR	m_color;			//カラー
		UINT	m_textureIndex;		//テクスチャインデックス
	
	public:
		GameTextureBase ();
		GameTextureBase ( const GameTextureBase& obj ) = delete;		//コピー禁止
		virtual ~GameTextureBase ();

		virtual void Load () = 0;		//テクスチャ読み込み
		virtual void Rele () = 0;		//解放
		virtual void Reset () = 0;		//再設定

		//インデックスを指定
		void SetTextureIndex( UINT i )	{ m_textureIndex = i; }
		UINT GetTextureIndex() const	{ return m_textureIndex; }

		//テクスチャの設定
		void SetTexture ( TX lpTexture ) { m_lpTexture = lpTexture; }
		TX	GetTexture() const { return m_lpTexture; }

		//カラーもグラフィックオブジェクトに移設
#if 0
		//カラーの設定
		void SetColor ( D3DXCOLOR color ) { m_color = color; }
		D3DXCOLOR	GetColor () const { return m_color; }
		
		//α値のみの設定
		void SetAlpha ( float alpha ) 
		{ 
			m_color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, alpha ); 
		}		
#endif // 0
	};

	typedef GameTextureBase			TxBs;
	typedef shared_ptr < TxBs >		P_TxBs;
	typedef vector < P_TxBs >		VP_TxBs;
	typedef shared_ptr < VP_TxBs >	PVP_TxBs;


	//--------------------------------------------------------
	//ゲームテクスチャ　フロムファイル
	//		直接ファイルから名前を指定してテクスチャを作成し管理する
	//--------------------------------------------------------
	class GameTextureFromFile : public TxBs
	{
		TX			m_lpTexture;		//テクスチャ
		tstring		m_strFilename;		//読込ファイル名
	
	public:
		GameTextureFromFile ();
		GameTextureFromFile ( tstring filename ) { m_strFilename = filename; }
		GameTextureFromFile ( const GameTextureFromFile& obj ) = delete;		//コピー禁止
		virtual ~GameTextureFromFile ();

		virtual void Load ();	//テクスチャ読み込み
		virtual void Rele ();	//解放
		virtual void Reset ();	//再設定

		//読込ファイル名を指定
		void SetFileName ( LPCTSTR filename ) { m_strFilename.assign ( filename ); }
		void SetFileName ( tstring filename ) { m_strFilename = filename; }
	};
	
	typedef GameTextureFromFile		TxFl;
	typedef shared_ptr < TxFl >		P_TxFl;
	typedef vector < P_TxFl >		VP_TxFl;
	typedef shared_ptr < VP_TxFl >	PVP_TxFl;


	//--------------------------------------------------------
	//ゲームテクスチャ　フロムアーカイブ
	//		archive.dat内のファイル名を指定してテクスチャを作成し管理する
	//		読込はLoad時に行う
	//		Debugモード時にはarchiveディレクトリ内のファイルを指定する
	//--------------------------------------------------------
	class GameTextureFromArchive : public TxBs
	{
		TX			m_lpTexture;		//テクスチャ
		tstring		m_strFileName;		//読込ファイル名
	
	public:
		GameTextureFromArchive ();
		GameTextureFromArchive ( const GameTextureFromArchive& obj ) = delete;		//コピー禁止
		virtual ~GameTextureFromArchive ();

		virtual void Load ();	//テクスチャ読み込み
		virtual void Rele ();	//解放
		virtual void Reset ();	//再設定

		//読込ファイル名を指定
		void SetFileName ( LPCTSTR fileName ) { m_strFileName.assign ( fileName ); }
		void SetFileName ( tstring fileName ) { m_strFileName = fileName; }
	};

	typedef GameTextureFromArchive	TxAcv;
	typedef shared_ptr < TxAcv >	P_TxAcv;
	typedef vector < P_TxAcv >		VP_TxAcv;
	typedef shared_ptr < VP_TxAcv >	PVP_TxAcv;


	//--------------------------------------------------------
	//ゲームテクスチャ　フロムメモリ
	//		アーカイブ等のメモリ上からテクスチャを作成し管理する
	//		読込は実体化して即時に行う
	//		アーカイブ読込時のみ新規作成され、再設定はアーカイブ側で行う
	//--------------------------------------------------------
	class GameTextureFromMemory : public TxBs
	{
		TX		m_lpTexture;		//テクスチャ

	public:
		GameTextureFromMemory ( LPCVOID pSrcData, UINT SrcDataSize );
		GameTextureFromMemory ( const GameTextureFromMemory& obj ) = delete;		//コピー禁止
		virtual ~GameTextureFromMemory ();

		virtual void Load ();	//テクスチャ読み込み
		virtual void Rele ();	//解放
		virtual void Reset ();	//再設定
	};

	typedef GameTextureFromMemory	TxMem;
	typedef shared_ptr < TxMem >	P_TxMem;
	typedef vector < P_TxMem >		VP_TxMem;
	typedef shared_ptr < VP_TxMem >	PVP_TxMem;


}	//namespace GAME


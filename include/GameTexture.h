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
#include "OutlineFont.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------------------------
	//ゲームテクスチャ　ベース
	//--------------------------------------------------------
	class GameTextureBase
	{
		TX		m_lpTexture;		//テクスチャ(確保・解放は継承先で行う)
		UINT	m_textureIndex;		//テクスチャインデックス
	
	public:
		GameTextureBase ();
		GameTextureBase ( const GameTextureBase& obj ) = delete;		//コピー禁止
		virtual ~GameTextureBase ();

		virtual void Load () {};		//テクスチャ読み込み
		virtual void Rele () {};		//解放
		virtual void Reset () {};		//再設定

		//インデックスを指定
		void SetTextureIndex( UINT i )	{ m_textureIndex = i; }
		UINT GetTextureIndex() const	{ return m_textureIndex; }

		//テクスチャの設定
		void SetTexture ( TX lpTexture ) { m_lpTexture = lpTexture; }
		
		//取得
		TX&	GetTexture () { return m_lpTexture; }
		USIZE GetSize () const;	//テクスチャが存在しない場合(0,0)を返す
	};

	using TxBs = GameTextureBase;
	using P_TxBs = std::shared_ptr < TxBs >;
	using VP_TxBs = std::vector < P_TxBs >;
	using PVP_TxBs = std::shared_ptr < VP_TxBs >;


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
		GameTextureFromFile ( tstring filename ) : m_lpTexture(nullptr) { m_strFilename = filename; }
		GameTextureFromFile ( const GameTextureFromFile& obj ) = delete;		//コピー禁止
		virtual ~GameTextureFromFile ();

		virtual void Load ();	//テクスチャ読み込み
		virtual void Rele ();	//解放
		virtual void Reset ();	//再設定

		//読込ファイル名を指定
		void SetFileName ( LPCTSTR filename ) { m_strFilename.assign ( filename ); }
		void SetFileName ( tstring filename ) { m_strFilename = filename; }
	};
	
	using TxFl = GameTextureFromFile;
	using P_TxFl = std::shared_ptr < TxFl >;
	using VP_TxFl = std::vector < P_TxFl >;
	using PVP_TxFl = std::shared_ptr < VP_TxFl >;


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

	using TxAcv= GameTextureFromArchive;
	using P_TxAcv= std::shared_ptr < TxAcv >;
	using VP_TxAcv= std::vector < P_TxAcv >;
	using PVP_TxAcv= std::shared_ptr < VP_TxAcv >;


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

	using TxMem = GameTextureFromMemory;
	using P_TxMem = std::shared_ptr < TxMem >;
	using VP_TxMem = std::vector < P_TxMem >;
	using PVP_TxMem = std::shared_ptr < VP_TxMem >;


	//--------------------------------------------------------
	//ゲームテクスチャ　フロムストリング
	//		文字列から生成されるゲームテクスチャ
	//--------------------------------------------------------
	class GameTextureFromString : public TxBs
	{
		tstring		m_str;

		int			m_fontSize;
		int			m_penSize;
		int			m_quality;
		DWORD		m_fillColor;
		DWORD		m_edgeColor;
		TCHAR		m_fontName [ LF_FACESIZE ];	//フォント名(FaceName)

	public:
		GameTextureFromString ();
		GameTextureFromString ( const GameTextureFromString& rhs ) = delete;
		~GameTextureFromString ();

		void Load ();
		void Rele ();
		void Reset ();

		void SetStr ( LPCTSTR lpctstr );
		tstring& GetStr () { return m_str; }

		void SetParam ( int fontSize, int penSize, int quolity );
		void SetFontFace ( LPCTSTR fontname );
		void SetColor ( DWORD fill, DWORD edge );
	};

	using TxStr = GameTextureFromString;
	using P_TxStr = std::shared_ptr < TxStr >;


}	//namespace GAME


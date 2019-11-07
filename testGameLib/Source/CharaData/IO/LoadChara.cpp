//=================================================================================================
//
// LoadChara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "LoadChara.h"
#include "../../CharaData/Branch.h"	//ActionとCommandを扱うためChara.hとは独立

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	LoadChara
	//		スクリプトとイメージリストを保存したキャラデータ ".dat"ファイル から、Charaを読み込む
	//==================================================================================
	LoadChara::LoadChara ( const tstring & filename, Chara & chara ) 
	{
		try
		{
			_Load ( filename, chara );
		}
		catch ( LPCTSTR lpctstr )
		{
			TRACE_F ( lpctstr );
		}
		catch (...)
		{
			TRACE_F ( _T("Error LoadChara.\n") );
		}
	}

	//----------------------------------
	//	デストラクタ
	//----------------------------------
	LoadChara::~LoadChara ()
	{
	}


	//------------------------------------------
	//	try用実行関数
	//------------------------------------------
	void LoadChara::_Load ( const tstring & filename, Chara & chara )
	{
		//初期化
		chara.Reset ();

		//拡張子を.datかどうか確認
		const int NX = 4;	//拡張子の文字数
		if ( 0 != filename.compare ( filename.size() - NX, NX, _T(".dat"), 0, NX ) )
		{
			throw _T("拡張子エラー\n"); 
		}

		//------------------------------------------
		//@info  tifstream ではなく ifstream
		//		バイナリファイルなのでchar型で扱う
		//------------------------------------------


		//---------------------------------------------------------------------
		//ファイルストリーム開始
		ifstream ifstrm ( filename.c_str(), ios::binary );

		//ファイルが存在しないとき何もしない
		if ( ifstrm.fail () ) { throw _T("ファイルが存在しません。"); } 

		//キャラアーカイブファイル形式のバージョン
		UINT version = 0;	//読込用
		ifstrm.read ( (char*)& version, sizeof ( UINT ) );
		if ( CHARA_VERSION != version ) { throw _T("キャラアーカイブのバージョンが異なります。"); } 

		//---------------------------------------------------------------------
		//スクリプト部のサイズ
		UINT scriptSize = 0;
		ifstrm.read ( (char*)& scriptSize, sizeof ( UINT ) );

		//一時読込
		char* scriptBuf = new char [ scriptSize ];
		ifstrm.read ( scriptBuf, scriptSize );

		//Documentを生成
		Document document ( scriptBuf, scriptSize );

		//一時読込の破棄
		delete[] scriptBuf;

		//キャラデータに変換
		m_utl._DocumentToChara ( document, chara );

		//---------------------------------------------------------------------
		//グラフィックアーカイブの読込	(スクリプトの続きからEOFまで)

		//メインイメージ
		_LoadImage ( ifstrm, chara.GetpvpMainTexture() );

		//Efイメージ
		_LoadImage ( ifstrm, chara.GetpvpEfTexture() );

		//---------------------------------------------------------------------
		//ファイルストリーム終了
		ifstrm.close ();
	}

	//------------------------------------------------------------
	//イメージアーカイブ読込
	void LoadChara::_LoadImage ( ifstream & ifstrm, PVP_TxBs pvpTexture )
	{
		//イメージの個数でループ
		UINT size = pvpTexture->size ();
		for ( UINT i = 0; i < size; ++ i )
		{
			//イメージの個別サイズを読込
			UINT imageSize = 0;
			ifstrm.read ( (char*)&imageSize, sizeof ( UINT ) );

			//一時領域の確保から、イメージ本体の読込
			char* imageBuf = new char [ imageSize ];
			ifstrm.read ( imageBuf, imageSize );

			//メモリ上のデータからゲームテクスチャに変換
			P_TxMem pGameTexture = make_shared < TxMem > ( (LPCVOID)imageBuf, imageSize );

			//一時領域は解放する
			delete[] imageBuf;

			//キャラ内部のテクスチャリストに加える
			(*pvpTexture) [ i ] = pGameTexture;
		}
	}


}	//namespace GAME


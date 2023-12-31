//=================================================================================================
//
//	ASCIIをテクスチャ化しまとめたクラス
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ASCII_Texture.h"
#include "GameText.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const UINT ASCII_Texture::N_ASCII = 128;


	ASCII_Texture::ASCII_Texture ()
	{
		ascii_tx.resize ( N_ASCII );
		ascii_w.resize ( N_ASCII );
	}

	ASCII_Texture::~ASCII_Texture ()
	{

	}

	void ASCII_Texture::Load ()
	{
		//ASCII文字１個ごとにテクスチャを作成しておく
		TCHAR tch = L' ';		//0x20 スペース からスタート
		for ( char c = ' '; c < N_ASCII; ++ c )
		{
			tstring tstr ( 1, tch );
			GameText::Inst ()->MakeStrTexture ( tstr, ascii_tx [ c ] );
			++ tch;
		}

		//幅も記録しておく
		tch = L' ';		//0x20 スペース からスタート
		for ( char c = ' '; c < N_ASCII; ++ c )
		{
			ascii_w [ c ] = GameText::Inst ()->_MakeAsciiWidth ( c );
			++ tch;
		}
	}

	void ASCII_Texture::Rele ()
	{
	}

	void ASCII_Texture::Reset ()
	{
		Rele ();
		Load ();
	}

}	//namespace GAME


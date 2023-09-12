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
		for ( int i = 0; i < N_ASCII; ++ i )
		{
			ascii_tx.push_back ( TX () );
		}
	}

	ASCII_Texture::~ASCII_Texture ()
	{

	}

	void ASCII_Texture::Load ()
	{
		TCHAR test_tch = '0';
		TCHAR tch = L' ';		//0x20 スペース
		for ( char c = ' '; c < N_ASCII; ++ c )
		{
			size_t converted = 0;
			size_t size = 1;
//			mbstowcs_s ( & converted, & tch, size, & c, _TRUNCATE );


			tstring tstr ( 1, tch );
			GameText::Inst ()->MakeStrTexture ( tstr, ascii_tx [ c ] );
//			GameText::Inst ()->GetAsciiTx ( c );

			++ test_tch;
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

	TX ASCII_Texture::GetTx ( char ascii ) const
	{
		return ascii_tx [ ascii ];
	}

}	//namespace GAME


//=================================================================================================
//
//	ASCIIをテクスチャ化しまとめたクラス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "Dx3D.h"
#include "DxVertex.h"
#include "GameTexture.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class ASCII_Texture
	{
		static const UINT	N_ASCII;	//アスキー文字(表示用128種)
		std::vector < TX > 		ascii_tx;	//テクスチャ
		std::vector < LONG > 	ascii_w;	//グリフメトリクス幅
		//@info テクスチャは２の倍数に正規化されているので元の幅を保存しておく

	public:
		ASCII_Texture ();
		ASCII_Texture ( const ASCII_Texture & rhs ) = delete;
		~ASCII_Texture ();

		void Load ();
		void Rele ();
		void Reset ();

		TX GetTx ( char ascii ) const { return ascii_tx [ ascii ]; }
		LONG GetW ( char ascii ) const { return ascii_w [ ascii ]; }
	};


}	//namespace GAME


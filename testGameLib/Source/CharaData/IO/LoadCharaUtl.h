//=================================================================================================
//
// LoadCharaUtl ヘッダファイル
//	LoadCharaで用いるUtility関数群
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "IOCharaDefine.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class LoadCharaUtl
	{
		//------------------------------------------------------------
		//エレメントポインタからindex番目のアトリビュートのValueをUINTに直して返す
		UINT _ElemToUINT ( const P_Element pElem, UINT indexAttr );

		//エレメントポインタからアクションを読み込む
		void _ElemToImageList ( const P_Element pElem, Chara & chara );	//配列

		//エレメントポインタからアクションを読み込む
		void _ElemToActionArray ( const P_Element pElem, Chara & chara );	//配列
		void _ElemToAction ( const P_Element pElem, const P_Action & pAction );

		//エレメントポインタからスクリプトを読み込む
		void _ElemToScript ( const P_Element pElem, const P_Script pScript, UINT frame );

		//エレメントポインタからコマンドを読み込む
		void _ElemToCommandArray ( const P_Element pElem, Chara & chara );	//配列
		void _ElemToCommand ( const P_Element pElem, const P_Command & pCommand );

		//エレメントポインタからゲームキーを読み込む
		void _ElemToGameKey ( const P_Element pElem, GameKey & gamekey );

		//基本状態アクションID
		void _ElemToBasicActionID ( const P_Element pElem, Chara & chara );

		//エレメントポインタからエフェクトを読み込む
		void _ElemToEffectArray ( const P_Element pElem, Chara & chara );	//配列
		void _ElemToEffect ( const P_Element pElem, const P_Effect & pEffect );


		//エレメントポインタからブランチを読み込む
		void _ElemToBranchArray ( const P_Element pElem, const P_Script & pScript );	//配列
		void _ElemToBranch ( const P_Element pElem, const P_Branch & pBranch );

		//エレメントポインタからEFジェネレートを読み込む
		void _ElemToEfGnrtArray ( const P_Element pElem, const P_Script & pScript );	//配列
		void _ElemToEfGnrt ( const P_Element pElem, const P_EfGnrt & pEfGnrt );

		//------------------------------------------------------------
		//アトリビュート変換
		bool _AttrToBool ( const P_Attribute pAttr );
		UINT _AttrToUINT ( const P_Attribute pAttr );
		int  _AttrToInt ( const P_Attribute pAttr );
		float  _AttrToFloat ( const P_Attribute pAttr );
		VEC2 _AttrToVec2 ( const P_Attribute pa0, const P_Attribute pa1 );
		RECT _AttrToRect
		( 
			const P_Attribute pa0, const P_Attribute pa1,  
			const P_Attribute pa2, const P_Attribute pa3  
		);
		CLC_ST _AttrToCLC_ST ( const P_Attribute pAttr );

		//------------------------------------------------------------
		//枠読込
#if 0
		//引数：エレメントポインタ, スクリプトポインタ, 枠を設定するScript内の関数ポインタ
		void _LoadRect ( const P_Element pElem, P_Script pScript, void(Script::* const pFuncAddRect)( RECT ) );
#endif // 0
		//関数型を定義
		//	クラスScriptにおけるRectを設定する関数：戻値void, 引数RECT
		using FP_SetRect = std::function < void ( RECT ) >;

		//引数：エレメントポインタ, スクリプトポインタ, 枠を設定するScript内の関数ポインタ
		void _LoadRect ( const P_Element pElem, P_Script pSrcipt, FP_SetRect fp_SetRect );
		//引数：エレメントポインタ, 枠を設定するScript内の関数ポインタ
		void _LoadRect ( const P_Element pElem, FP_SetRect fp_SetRect );

		//枠の読込
		void _LoadRectAll ( const PVP_Element pvpElem, const P_Script & pScript );

		//------------------------------------------------------------
		//ブランチ (アクションとコマンドの読込後、indexから実効オブジェクトのポインタを取得して設定する)
		void _LoadBranch ( Chara & chara );

		//----------------------------------
		//データ読込　一時変数
		UINT	m_nMainImage;		//メインイメージリストの個数
		UINT	m_nEfImage;		//Efイメージリストの個数

		//イメージアーカイブ読込
		void _LoadImage ( ifstream* pIfstrm, PVP_TxBs pvpTexture, UINT numImage );

	public:
		LoadCharaUtl () = default;
		LoadCharaUtl ( const LoadCharaUtl & rhs ) = delete;
		~LoadCharaUtl () = default;

		//Documentからキャラに変換する
		void _DocumentToChara ( const Document & document, Chara & chara );
	};


}	//namespace GAME



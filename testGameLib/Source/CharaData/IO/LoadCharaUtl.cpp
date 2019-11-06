//=================================================================================================
//
// LoadCharaUtl ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "LoadCharaUtl.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//========================================================
	//ドキュメントからスクリプトに変換する
	//========================================================
	void LoadCharaUtl::_DocumentToChara ( const Document & document, Chara & chara )
	{
		//ルート下の操作用一時エレメント配列
		const PVP_Element pvpElmtRt = document.Root()->GetpvpElement ();

		//---------------------------------------------------------------
		//メインイメージリストのエレメント
		P_Element pElemMainImage = pvpElmtRt->at ( EL_MAIN_IMAGE_LIST );
		UINT sizeMainTexture = _ElemToUINT ( pElemMainImage, 0 );
		chara.GetpvpMainTexture()->resize ( sizeMainTexture );

		//Efイメージリストのエレメント
		P_Element pElemEfImage = pvpElmtRt->at ( EL_EF_IMAGE_LIST );
		UINT sizeEfTexture = _ElemToUINT ( pElemEfImage, 0 );
		chara.GetpvpEfTexture()->resize ( sizeEfTexture );

		//---------------------------------------------------------------
		//アクション配列のエレメント
		P_Element pElemVecAction = pvpElmtRt->at ( EL_ACTION );
		_ElemToActionArray ( pElemVecAction, chara );

		//---------------------------------------------------------------
		//コマンド配列のエレメント
		P_Element pElemVecCommand = pvpElmtRt->at ( EL_COMMAND );
		_ElemToCommandArray ( pElemVecCommand, chara );

		//---------------------------------------------------------------
		//ブランチ (アクションとコマンドの読込後、indexから実効オブジェクトのポインタを取得して設定する)
		_LoadBranch ( chara );

		//---------------------------------------------------------------
		//基本状態アクションIDのエレメント
		P_Element pElemVecBsActionID = pvpElmtRt->at ( EL_BASIC_ACTION );
		_ElemToBasicActionID ( pElemVecBsActionID, chara );

		//---------------------------------------------------------------
		//エフェクト配列のエレメント
		//---------------------------------------------------------------
		P_Element pElemVecEf = pvpElmtRt->at ( EL_EFFECT );
		_ElemToEffectArray ( pElemVecEf, chara );
	}



	//-------------------------------------------------------------------
	//	内部使用関数
	//-------------------------------------------------------------------
	//エレメントポインタからindex番目のアトリビュートのValueをUINTに直して返す
	UINT LoadCharaUtl::_ElemToUINT ( const P_Element pElem, UINT indexAttr )
	{
		UINT ui = 0;
		try
		{
			const PVP_Attribute pvpAttr = pElem->GetpvpAttribute();
			tistringstream tiss ( (*pvpAttr)[ indexAttr ]->GetValue() );
			tiss >> ui;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _ElemToUINT.\n") );
		}
		return ui;
	}

	//エレメントポインタからアクション配列を読み込む
	void LoadCharaUtl::_ElemToActionArray ( const P_Element pElem, Chara & chara )
	{
		const PVP_Element pvpElemAction = pElem->GetpvpElement();
		for ( P_Element pe : * pvpElemAction )
		{
			P_Action pAction = make_shared < Action > ();	//代入用の新規アクション
			_ElemToAction ( pe, pAction );		//エレメントからアクションに読込
			chara.AddpAction ( pAction );			//キャラにアクションを追加
		}
	}

	//エレメントポインタからアクションを読み込む
	void LoadCharaUtl::_ElemToAction ( const P_Element pElem, const P_Action & pAction )
	{
		//attribute配列ポインタ
		const PVP_Attribute pvpAttrAction = pElem->GetpvpAttribute ();

		//アクション "名前"
		pAction->SetName ( pvpAttrAction->at ( ATTR_ACTION_NAME )->GetValue() );

		//UINT 次アクションID (終了時における次アクションのリスト内インデックス)
		pAction->SetNextID ( _AttrToUINT ( pvpAttrAction->at ( ATTR_ACTION_NEXT ) ) );

		//int 消費バランス値
//		pAction->SetBalance ( _AttrToInt ( (*pvpAttrAction)[ATTR_ACTION_BALANCE] ) );

		//アクション属性
		UINT indexCategory = _AttrToUINT ( (*pvpAttrAction)[ATTR_ACTION_CATEGORY] );
		ACTION_CATEGORY category = static_cast < ACTION_CATEGORY > ( indexCategory );
		pAction->SetCategory ( category );

		//---------------------------
		//<Action>内のElement
		//	<Script>　...不定数
		const PVP_Element pvpElemScript = pElem->GetpvpElement ();
		UINT _frame = 0;
		for ( P_Element pe : *pvpElemScript )
		{
			P_Script pScript = make_shared < Script > ();		//設定用スクリプトを生成
			_ElemToScript ( pe, pScript, _frame ++ );		//エレメントからスクリプトを読込
			pAction->AddpScript ( pScript );			//アクションにスクリプトを追加
		}
	}

	//エレメントポインタからエフェクト配列を読み込む
	void LoadCharaUtl::_ElemToEffectArray ( const P_Element pElem, Chara & chara )
	{
		const PVP_Element pvpElemEffect = pElem->GetpvpElement();
		for ( P_Element pe : * pvpElemEffect )
		{
			P_Effect pEffect = make_shared < Effect > ();	//代入用の新規エフェクト
			_ElemToEffect ( pe, pEffect );		//エレメントからエフェクトに読込
			chara.AddpEffect ( pEffect );			//キャラにエフェクトを追加
		}
	}

	//エレメントポインタからエフェクトを読み込む
	void LoadCharaUtl::_ElemToEffect ( const P_Element pElem, const P_Effect & pEffect )
	{
		//attribute配列ポインタ
		const PVP_Attribute pvpAttrAction = pElem->GetpvpAttribute ();

		//---------------------------
		//<Effect>内のElement
		//	<Script>　...不定数
		const PVP_Element pvpElemScript = pElem->GetpvpElement ();
		UINT _frame = 0;
		for ( P_Element pe : * pvpElemScript )
		{
			P_Script pScript = make_shared < Script > ();		//設定用スクリプトを生成
			_ElemToScript ( pe, pScript, _frame ++ );		//エレメントからスクリプトを読込
			pEffect->AddpScript ( pScript );			//エフェクトにスクリプトを追加
		}
	}


	void LoadCharaUtl::_ElemToScript ( const P_Element pElem, const P_Script pScript, UINT frame )
	{
		//-----------------------------------------------------------------------------
		//作業用アトリビュート配列ポインタ
		const PVP_Attribute p = pElem->GetpvpAttribute();

		//フレーム数
		pScript->SetFrame ( frame );

		//イメージID
		UINT imageID = _AttrToUINT ( p->at ( ATTR_SCRIPT_IMAGE_ID ) );
		pScript->SetImageIndex ( imageID );

		//Pos
		VEC2 pos = _AttrToVec2( p->at ( ATTR_SCRIPT_POS_X ), p->at ( ATTR_SCRIPT_POS_Y ) );
		pScript->SetPos ( pos );

		//Vel
		VEC2 vel = _AttrToVec2( p->at ( ATTR_SCRIPT_VEL_X ), p->at ( ATTR_SCRIPT_VEL_Y ) );
		pScript->SetVel ( vel );

		//Acc
		VEC2 acc = _AttrToVec2( p->at ( ATTR_SCRIPT_ACC_X ), p->at ( ATTR_SCRIPT_ACC_Y ) );
		pScript->SetAcc ( acc );

		//計算状態
		CLC_ST clcSt = _AttrToCLC_ST ( p->at ( ATTR_SCRIPT_CLCST ) );
		pScript->SetCalcState ( clcSt );

		//power
		int power = _AttrToInt ( p->at ( ATTR_SCRIPT_POWER ) );
		pScript->SetPower ( power );

		//-----------------------------------------------------------------------------
		//スクリプト内部のエレメント
		const PVP_Element pvpElemInScript = pElem->GetpvpElement ();

		//ブランチ配列のエレメント
		P_Element pElemVecBranch = pvpElemInScript->at ( ELEM_SCRIPT_BRANCH );
		_ElemToBranchArray ( pElemVecBranch, pScript );

		//EFジェネレート配列のエレメント
		P_Element pElemVecEfGnrt = pvpElemInScript->at ( ELEM_SCRIPT_EFGNRT );
		_ElemToEfGnrtArray ( pElemVecEfGnrt, pScript );

		//枠読込
		_LoadRectAll ( pvpElemInScript, pScript );
	}

	//エレメントポインタからコマンド配列を読み込む
	void LoadCharaUtl::_ElemToCommandArray ( const P_Element pElem, Chara & chara )
	{
		const PVP_Element pvpElemCommand = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElemCommand )
		{
			P_Command pCommand = make_shared < Command > ();	//代入用の新規作成
			_ElemToCommand ( pe, pCommand );			//エレメントからコマンドに読込
			chara.AddpCommand ( pCommand );			//キャラに追加
		}
	}

	//エレメントポインタからコマンドを読み込む
	void LoadCharaUtl::_ElemToCommand ( const P_Element pElem, const P_Command & pCommand )
	{
		//------------------------------------------------------------
		//アトリビュート配列
		const PVP_Attribute pvpAttrCommand = pElem->GetpvpAttribute ();

		//Name
		const P_Attribute pAttrCommand = pvpAttrCommand->at ( ATTR_COMMAND_NAME );
		tstring strName = pAttrCommand->GetValue ();
		pCommand->SetName ( strName );

		//Limit
		UINT limitTime = _AttrToUINT ( pvpAttrCommand->at ( ATTR_COMMAND_LIMIT ) );
		pCommand->SetLimitTime ( limitTime );

		//------------------------------------------------------------
		//エレメント

		//子ElementはGameKeyを不定数保持
		const PVP_Element pvpElemGameKey = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElemGameKey )
		{
			GameKey gameKey;	//コピー可
			_ElemToGameKey ( pe, gameKey );
			pCommand->AddGameKey ( gameKey );
		}
	}

	//エレメントポインタからゲームキーを読み込む
	void LoadCharaUtl::_ElemToGameKey ( const P_Element pElem, GameKey & gamekey )
	{
		//作業用
		const PVP_Attribute pvpAttrGameKey = pElem->GetpvpAttribute ();

		//否定フラグ
		gamekey.SetNot ( _AttrToBool ( pvpAttrGameKey->at ( ELEM_GAMEKEY_NOT ) ) );

		//文字列を読み込んでENUMに変換する
		//・Dir
		gamekey.SetDir ( GameKey::DirFromStr ( pvpAttrGameKey->at ( ELEM_GAMEKEY_DIR )->GetValue () ) );

		//・Btn
		for ( UINT j = 0; j < GameKey::GAME_KEY_BUTTON_NUM; ++ j )
		{
			tstring strGameKey = pvpAttrGameKey->at ( ELEM_GAMEKEY_BTN + j )->GetValue();
			gamekey.SetBtn ( j, GameKey::BtnFromStr ( strGameKey ) );
		}
	}
	
	//エレメントポインタからブランチを読み込む
	void LoadCharaUtl::_ElemToBranchArray ( const P_Element pElem, const P_Script & pScript )
	{
		PVP_Element pvpElemBlanch = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElemBlanch )
		{
			P_Branch pBranch = make_shared < Branch > ();	//代入用に新規作成
			_ElemToBranch ( pe, pBranch );
			pScript->AddpBranch ( pBranch );			//スクリプトに追加
		}
	}

	void LoadCharaUtl::_ElemToBranch ( const P_Element pElem, const P_Branch & pBranch )
	{
		//ブランチのアトリビュート
		const PVP_Attribute pa = pElem->GetpvpAttribute();
		UINT indexCommand = _AttrToUINT ( pa->at ( ATTR_BRANCH_COMMAND_INDEX ) );
		pBranch->SetIndexCommand ( indexCommand );		//条件コマンドインデックス
		UINT indexAction = _AttrToUINT ( pa->at ( ATTR_BRANCH_ACTION_INDEX ) );
		pBranch->SetIndexAction ( indexAction );		//遷移先アクションインデックス
		UINT indexFrame = _AttrToUINT ( pa->at ( ATTR_BRANCH_FRAME_INDEX ) );
		pBranch->SetIndexFrame ( indexFrame );		//遷移先スクリプトインデックス
	}
	
	//エレメントポインタからEFジェネレートを読み込む
	void LoadCharaUtl::_ElemToEfGnrtArray ( const P_Element pElem, const P_Script & pScript )
	{
		//EFジェネレート配列のエレメント配列
		const PVP_Element pvpElemEfGnrt = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElemEfGnrt )
		{
			P_EfGnrt pEfGnrt = make_shared < EffectGenerate > ();			//代入用に新規作成
			_ElemToEfGnrt ( pe, pEfGnrt );
			pScript->AddpEfGnrt ( pEfGnrt );			//スクリプトに追加
		}
	}

	void LoadCharaUtl::_ElemToEfGnrt ( const P_Element pElem, const P_EfGnrt & pEfGnrt )
	{
		///EFジェネレートのアトリビュート
		const PVP_Attribute pa = pElem->GetpvpAttribute();

		//アトリビュート列挙
		enum { NAME, INDEX, POS_X, POS_Y, POS_Z, GNRT, LOOP, SYNC, };

		//指定Efインデックス
		pEfGnrt->SetIndex ( _AttrToUINT ( pa->at ( INDEX ) ) );

		//生成位置
		pEfGnrt->SetPos ( _AttrToVec2 ( pa->at ( POS_X ), pa->at ( POS_Y ) ) );

		//z位置
		pEfGnrt->SetZ ( _AttrToFloat ( pa->at ( POS_Z ) ) );

		//生成
		pEfGnrt->SetGnrt ( _AttrToBool ( pa->at ( GNRT ) ) );

		//繰返
		pEfGnrt->SetLoop ( _AttrToBool ( pa->at ( LOOP ) ) );

		//同期
		pEfGnrt->SetSync ( _AttrToBool ( pa->at ( SYNC ) ) );
	}

	
	//------------------------------------------------------------
	//(internal) アトリビュートポインタからValueをboolに直して返す
	bool LoadCharaUtl::_AttrToBool ( const P_Attribute pAttr )
	{
		bool b = false;
		try
		{
			b = pAttr->GetValue().compare ( _T("True") ) == 0;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _AttrToBool.\n") );
		}
		return b;
	}

	//(internal) アトリビュートポインタからValueをUINTに直して返す
	UINT LoadCharaUtl::_AttrToUINT ( const P_Attribute pAttr )
	{
		UINT ui = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> ui;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _AttrToUINT.\n") );
		}
		return ui;
	}

	//(internal) アトリビュートポインタからValueをintに直して返す
	int LoadCharaUtl::_AttrToInt ( const P_Attribute pAttr )
	{
		int i = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> i;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _AttrToInt.\n") );
		}
		return i;
	}

	//(internal) アトリビュートポインタからValueをfloatに直して返す
	float LoadCharaUtl::_AttrToFloat ( const P_Attribute pAttr )
	{
		float f = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> f;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _AttrToFloat.\n") );
		}
		return f;
	}

	//(internal) アトリビュートポインタ２つからValueをVEC2に直して返す
	VEC2 LoadCharaUtl::_AttrToVec2 ( const P_Attribute pa0, const P_Attribute pa1 )
	{
		return VEC2 ( _AttrToFloat ( pa0 ), _AttrToFloat ( pa1 ) );
	}

	//(internal) アトリビュートポインタ４つからValueをRECTに直して返す
	//引数：x, y, w, h
	RECT LoadCharaUtl::_AttrToRect ( const P_Attribute pa0, const P_Attribute pa1, const P_Attribute pa2, const P_Attribute pa3 )
	{
		//x0, y0, x1, y1に直す
		int x = _AttrToInt ( pa0 );
		int y = _AttrToInt ( pa1 );
		int w = _AttrToInt ( pa2 );
		int h = _AttrToInt ( pa3 );

		RECT rect = { x, y, x + w, y + h };
		return rect;
	}

	//(internal) アトリビュートポインタからValueをCLC_STに直して返す
	CLC_ST LoadCharaUtl::_AttrToCLC_ST ( const P_Attribute pAttr )
	{
		CLC_ST clcSt;
		tstring str = pAttr->GetValue ();
		if ( 0 == str.compare ( _T ( "CLC_MAINTAIN" ) ) ) { clcSt = CLC_MAINTAIN; }
		else if ( 0 == str.compare ( _T ( "CLC_SUBSTITUDE" ) ) ) { clcSt = CLC_SUBSTITUDE; }
		else if ( 0 == str.compare ( _T ( "CLC_ADD" ) ) ) { clcSt = CLC_ADD; }
		return clcSt;
	}
	
	
	//枠読込
#if 0
	//関数ポインタ
	void LoadCharaUtl::_LoadRect ( const P_Element pElemRect, P_Script pScript, void (Script::* const pFuncAddRect)(RECT) )
	{
		//アトリビュートはサイズのみ
		const PVP_Attribute pvecpAttrVecRect = pElemRect->GetpvpAttribute();
		UINT sizeRect = _AttrToUINT ( (*pvecpAttrVecRect)[0] );

		const PVP_Element pvecpElemRect = pElemRect->GetpvpElement();

		//枠
		for ( UINT i = 0; i < sizeRect; ++i )
		{
			//エレメント
			P_Element pElem = (*pvecpElemRect)[i];

			//アトリビュート
			const PVP_Attribute pa = pElem->GetpvpAttribute();
			RECT rect = _AttrToRect ( (*pa)[0], (*pa)[1], (*pa)[2], (*pa)[3] );
			
			//関数ポインタで各枠に設定
			(pScript->*pFuncAddRect)( rect );
		}
	}
#endif // 0
	//引数：エレメントポインタ, スクリプトポインタ, 枠を設定するScript内の関数ポインタ
	//設定用関数をstd::functionで指定
	void LoadCharaUtl::_LoadRect ( const P_Element pElemRect, P_Script pScript, FP_SetRect fp_SetRect )
	{
		//アトリビュートはサイズのみ
		const PVP_Attribute pvpAttrVecRect = pElemRect->GetpvpAttribute ();
		UINT sizeRect = _AttrToUINT ( (*pvpAttrVecRect)[0] );

		//エレメント
		const PVP_Element pvpElemRect = pElemRect->GetpvpElement ();

		//枠
		for ( UINT i = 0; i < sizeRect; ++i )
		{
			//エレメント
			P_Element pElem = (*pvpElemRect)[i];

			//アトリビュート
			const PVP_Attribute pa = pElem->GetpvpAttribute();
			RECT rect = _AttrToRect ( (*pa)[0], (*pa)[1], (*pa)[2], (*pa)[3] );
			
			//FP_SetRectはpScriptと関連付けてあるのでそのまま呼び出す
			fp_SetRect ( rect );
		}
	}

	//引数：エレメントポインタ, 枠を設定するScript内の関数ポインタ
	void LoadCharaUtl::_LoadRect ( const P_Element pElemRect, FP_SetRect fp_SetRect )
	{
		const PVP_Element pvpElemRect = pElemRect->GetpvpElement ();
		for ( P_Element pElem : * pvpElemRect )
		{
			const PVP_Attribute pa = pElem->GetpvpAttribute();
			RECT rect = _AttrToRect ( pa->at(0), pa->at(1), pa->at(2), pa->at(3) );
			fp_SetRect ( rect );	//FP_SetRectはpScriptと関連付けてあるのでそのまま呼び出す
		}
	}

	void LoadCharaUtl::_LoadRectAll ( const PVP_Element pvpElem, const P_Script & pScript )
	{
#if 0
		//関数ポインタで指定する
		_LoadRect ( (*cpvpElemInScript)[CRECT], pScript, &Script::AddCRect );
		_LoadRect ( (*cpvpElemInScript)[ARECT], pScript, &Script::AddARect );
		_LoadRect ( (*cpvpElemInScript)[HRECT], pScript, &Script::AddHRect );
		_LoadRect ( (*cpvpElemInScript)[ORECT], pScript, &Script::AddORect );
#endif // 0
#if 0
		//bind
		FP_SetRect func_c = std::bind ( & Script::AddCRect, pScript, std::placeholders::_1 );
		FP_SetRect func_a = std::bind ( & Script::AddARect, pScript, std::placeholders::_1 );
		FP_SetRect func_h = std::bind ( & Script::AddHRect, pScript, std::placeholders::_1 );
		FP_SetRect func_o = std::bind ( & Script::AddORect, pScript, std::placeholders::_1 );
#endif // 0

		//ラムダ式
		FP_SetRect func_a = [ pScript ] ( RECT r ) { pScript->AddARect ( r ); };
		FP_SetRect func_c = [ pScript ] ( RECT r ) { pScript->AddCRect ( r ); };
		FP_SetRect func_h = [ pScript ] ( RECT r ) { pScript->AddHRect ( r ); };
		FP_SetRect func_o = [ pScript ] ( RECT r ) { pScript->AddORect ( r ); };

		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_CRECT ), pScript, func_c );
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_ARECT ), pScript, func_a );
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_HRECT ), pScript, func_h );
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_ORECT ), pScript, func_o );
	}

	//ブランチ (アクションとコマンドの読込後、indexから実効オブジェクトのポインタを取得して設定する)
	void LoadCharaUtl::_LoadBranch ( Chara & chara )
	{
#if 0
		UINT sizeAction = chara.GetpvpAction()->size();
		for ( UINT indexAction = 0; indexAction < sizeAction; ++indexAction )
		{
			UINT sizeScript = chara.GetpAction ( indexAction )->SizeScript();
			for ( UINT indexScript = 0; indexScript < sizeScript; ++indexScript )
			{
				P_Script pScript = chara.GetpScript ( indexAction, indexScript );
				PVP_Branch pvpBranch = pScript->GetpvpBranch ();
				UINT sizeBranch = pvpBranch->size();
				for ( UINT indexBranch = 0; indexBranch < sizeBranch; ++indexBranch )
				{
					P_Branch pBranch = pvpBranch->at ( indexBranch );
					pBranch->SetpSequence ( chara.GetpAction ( pBranch->GetIndexAction() ) );
					pBranch->SetpCommand ( chara.GetpCommand ( pBranch->GetIndexCommand() ) );
				}
			}
		}
#endif // 0

		PVP_Action pvpAction = chara.GetpvpAction ();
		for ( P_Action pAc : * pvpAction )
		{
			PVP_Script pvpScript = pAc->GetpvpScript ();
			for ( P_Script pSc : * pvpScript )
			{
				PVP_Branch pvpBranch = pSc->GetpvpBranch ();
				for ( P_Branch pBr : * pvpBranch )
				{
					UINT i = pBr->GetIndexAction ();
					P_Action a = chara.GetpAction ( i );
					TRACE_F ( _T ( "%d, %s\n" ), i, a->GetName().c_str() );
					pBr->SetpSequence ( chara.GetpAction ( pBr->GetIndexAction () ) );
					pBr->SetpCommand ( chara.GetpCommand ( pBr->GetIndexCommand () ) );
				}
			}
		}
	}

	//基本状態アクションID
	void LoadCharaUtl::_ElemToBasicActionID ( const P_Element pElem, Chara & chara )
	{
		//基本状態アクションID (nameは飛ばす)
		const PVP_Element pvpElemBasicAction = pElem->GetpvpElement ();
//		P_Element pElemBasicAction = pvpElemBasicAction->at ( 0 );
		for ( UINT i = 0; i < BASIC_ACTION_NUM; ++ i )
		{
			UINT n = _ElemToUINT ( pvpElemBasicAction->at ( i ), 0 );
			chara.SetBsAction ( static_cast < BASIC_ACTION > ( i ), n );
		}
	}

	//------------------------------------------------------------
	//イメージアーカイブ読込
	void LoadCharaUtl::_LoadImage ( ifstream* pIfstrm, PVP_TxBs pvpTexture, UINT numImage )
	{
		//イメージの個数でループ
		for ( UINT i = 0; i < numImage; ++ i )
		{
			//イメージの個別サイズを読込
			UINT imageSize = 0;
			pIfstrm->read ( (char*)&imageSize, sizeof ( UINT ) );

			//一時領域の確保から、イメージ本体の読込
			char* imageBuf = new char [ imageSize ];
			pIfstrm->read ( imageBuf, imageSize );

			//メモリ上のデータからゲームテクスチャに変換
			P_TxMem pGameTexture = make_shared < TxMem > ( (LPCVOID)imageBuf, imageSize );

			//一時領域は解放する
			delete[] imageBuf;

			//キャラ内部のテクスチャリストに加える
			pvpTexture->push_back ( pGameTexture );
		}
	}


}	//namespace GAME


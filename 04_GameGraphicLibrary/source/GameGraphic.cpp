//=================================================================================================
//
// ゲームグラフィック　クラス　
//		ゲームで用いる画像を扱うオブジェクトを定義する。
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//■=======================================================================
	// ゲームグラフィック　ベース
	//■=======================================================================

	//コンストラクタ
	GameGraphicBase::GameGraphicBase ()
		:	m_indexObject ( 0 )
	{
		//----------------------------------------------
		//オブジェクト配列
		m_pvpObject = std::make_shared < VP_Object > ();

		//オブジェクト個数は１以上なので自動で１つ生成する
		m_pvpObject->push_back ( std::make_shared < GameObject > () );

		//----------------------------------------------
		//テクスチャ配列
		m_pvpTexture = std::make_shared < VP_TxBs > ();

		//テクスチャは０以上なので自動生成しない
		//特にゲームグラフィック　アプロブドテクスチャはテクスチャは０のみ

		//----------------------------------------------
		m_pCenter = std::make_shared < VEC3 > ( 0.f, 0.f, 0.f );
		m_pPosition = std::make_shared < VEC3 > ( 0.f, 0.f, Z_DEFALT );
	}

	//デストラクタ
	GameGraphicBase::~GameGraphicBase ()
	{
		//オブジェクトの解放
		ClearObject ();

		//テクスチャ自体の解放は外で行う
		m_pvpTexture->clear ();
	}

	//グラフィックオブジェクトの解放
	void GameGraphicBase::ClearObject ()
	{
		m_pvpObject->clear ();
	}

	//すべてのオブジェクトへの操作：表示状態
	void GameGraphicBase::SetAllValid ( bool b )
	{
		for ( P_Object p : *m_pvpObject ) { p->SetValid ( b ); }
	}

	//すべてのオブジェクトへの操作：位置指定
	void GameGraphicBase::SetAllPos ( VEC2 vec )
	{
		for ( P_Object p : *m_pvpObject ) { p->SetPos ( vec ); }
	}

	//すべてのオブジェクトへの操作：色指定
	void GameGraphicBase::SetAllColor ( D3DXCOLOR color )
	{
		for ( P_Object p : (*m_pvpObject ) ) { p->SetColor ( color ); }
	}

	//フレーム毎動作
	void GameGraphicBase::Move ()
	{
		//コアの前動作
		GameGraphicCore::PreMove ();

		//オブジェクトの動作
		for ( P_Object pOb : *m_pvpObject ) { pOb->PreMove (); }
		for ( P_Object pOb : *m_pvpObject ) { pOb->Move (); }
	}

	//フレーム毎描画
	void GameGraphicBase::Draw ()
	{
		//テクスチャが設定されていないとき何もしない
		if ( 0 == m_pvpTexture->size() ) { return; }

		//全体有効フラグ
		if ( ! m_valid ) { return; }

		//オブジェクトの数だけ描画
		for ( P_Object pob : * m_pvpObject )
		{
			//有効フラグ
			if ( ! pob->GetValid () ) { continue; }

			//テクスチャ指定
			UINT indexTexture = pob->GetIndexTexture ();
			if ( ! m_pvpTexture->at ( indexTexture ) ) { continue; }


			//全体カラー優先
			_CLR clr = GameGraphicCore::GetColor ();
			if ( clr == _CLR ( 0xffffffff ) )
			{
				//全体カラーが通常表示(0xffffffff)のときオブジェクトのカラーを参照する
				clr = pob->GetColor ();
			}

			//スプライト描画
			Dx3D::instance ()->BeginSprite ();	//スプライト描画開始
			Dx3D::instance()->DrawSprite
			(
				m_pvpTexture->at ( indexTexture )->GetTexture(),
				pob->GetcpMatrix(),
				nullptr,
				m_pCenter.get (), 
				m_pPosition.get (), 
				clr
			);
			Dx3D::instance ()->EndSprite ();		//スプライト描画終了
#if 0
			P_Object po = m_pvpObject->at ( i );
			//有効フラグ
			if ( ! m_pvpObject->at ( i )->GetValid () ) { continue; }

			//テクスチャ指定
			UINT indexTexture = m_pvpObject->at ( i )->GetIndexTexture ();
			if ( ! m_pvpTexture->at ( indexTexture ) ) { continue; }


			//全体カラー優先
			_CLR clr = GameGraphicCore::GetColor ();
			if ( clr == _CLR ( 0xffffffff ) )
			{
				//全体カラーが通常表示(0xffffffff)のときオブジェクトのカラーを参照する
				clr = m_pvpObject->at ( i )->GetColor ();
			}

			Dx3D::instance()->DrawSprite
			(
				m_pvpTexture->at ( indexTexture )->GetTexture(),
				m_pvpObject->at ( i )->GetcpMatrix(),
				nullptr,
				m_pCenter.get (), 
				m_pPosition.get (), 
				clr
			);
#endif // 0
		}
	}

	//--------------------------------------------------------------------
	//テクスチャ

	//テクスチャポインタを追加
	void GameGraphicBase::AddpTexture ( P_TxBs pTexture )
	{
		m_pvpTexture->push_back ( pTexture );
	}

	//テクスチャを設定
	void GameGraphicBase::SetpTexture ( P_TxBs pTexture )
	{
		m_pvpTexture->at ( 0 ) = pTexture;
	}

	//テクスチャの中心位置 (Load()後のみ)
	VEC2 GameGraphicBase::GetCenterOfTexture ( UINT index ) const
	{
		VEC2 ret = VEC2 ( 0, 0 );
		if ( m_pvpTexture->size () <= index ) { return ret; }

		TX tx = m_pvpTexture->at ( index )->GetTexture ();
		if ( nullptr == tx ) { return ret; }

		D3DSURFACE_DESC desc;
		m_pvpTexture->at ( index )->GetTexture ()->GetLevelDesc ( 0, &desc );
		ret.x = 0.5f * desc.Width;
		ret.y = 0.5f * desc.Height;
		return ret;
	}

	//オブジェクトが２つ以上のときフェードで入替
	void GameGraphicBase::FadeChangeOb ( UINT time, UINT index_out, UINT index_in )
	{
		//範囲チェック
		UINT n = m_pvpObject->size ();
		if ( n <= index_out ) { return; }
		if ( n <= index_in ) { return; }
		if ( index_in == index_out ) { return; }
	
		//
		( *m_pvpObject ) [ index_out ]->SetFade ( time, 0xffffffff, 0x00ffffff );
		( *m_pvpObject ) [ index_in  ]->SetFade ( time, 0x00ffffff, 0xffffffff );
	}



	//■=======================================================================
	// ゲームグラフィック フロムファイル
	//■=======================================================================
	GameGraphicFromFile::GameGraphicFromFile ()
	{
	}

	GameGraphicFromFile::~GameGraphicFromFile ()
	{
		Rele ();
		//テクスチャ配列の解放
		m_vpTexture.clear ();
	}

	void GameGraphicFromFile::TxLoad ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			m_vpTexture[i]->Load ();
		}
	}

	void GameGraphicFromFile::TxRele ()
	{
		//テクスチャの解放
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			if ( m_vpTexture[i] )
			{
				m_vpTexture[i]->Rele ();
			}
		}
	}

	void GameGraphicFromFile::TxReset ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			m_vpTexture[i]->Reset ();
		}
	}

	void GameGraphicFromFile::AddTexture ( LPCTSTR fileName )
	{
		tstring tstr ( fileName );
		AddTexture ( tstr );
	}

	void GameGraphicFromFile::AddTexture ( tstring fileName )
	{
		P_TxFl pTexture = std::make_shared < TxFl > ();
		pTexture->SetFileName ( fileName );
		m_vpTexture.push_back ( pTexture );
		GameGraphicBase::AddpTexture ( pTexture );
	}


	//■=======================================================================
	// ゲームグラフィック フロムアーカイブ
	//■=======================================================================
	GameGraphicFromArchive::GameGraphicFromArchive ()
	{
	}

	GameGraphicFromArchive::~GameGraphicFromArchive ()
	{
		Rele ();
		m_vpTexture.clear ();
	}

	void GameGraphicFromArchive::TxLoad ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			m_vpTexture[i]->Load ();
		}
	}

	void GameGraphicFromArchive::TxRele ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			if ( m_vpTexture[i] )
			{
				m_vpTexture[i]->Rele ();
			}
		}
	}

	void GameGraphicFromArchive::TxReset ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			m_vpTexture[i]->Reset ();
		}
	}

	void GameGraphicFromArchive::AddTexture ( LPCTSTR fileName )
	{
		tstring tstr ( fileName );
		AddTexture ( tstr );
	}

	void GameGraphicFromArchive::AddTexture ( tstring fileName )
	{
		P_TxAcv pTexture = std::make_shared < TxAcv > ();
		pTexture->SetFileName ( fileName );
		m_vpTexture.push_back ( pTexture );
		AddpTexture ( pTexture );
	}


	//■=======================================================================
	// ゲームグラフィック　アプロブドテクスチャ
	//■=======================================================================
	GameGraphicApprovedTexture::GameGraphicApprovedTexture ()
		: m_pTexture ( nullptr )
	{
		//空テクスチャを配置
		GameGraphicBase::AddpTexture ( nullptr );
	}

	GameGraphicApprovedTexture::~GameGraphicApprovedTexture ()
	{
	}

	void GameGraphicApprovedTexture::TxLoad ()
	{
	}

	void GameGraphicApprovedTexture::TxRele ()
	{
	}

	void GameGraphicApprovedTexture::TxReset ()
	{
	}


}	//namespace GAME


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
	:	m_wait ( 0 ), m_timer ( 0 ), m_fadeIn ( 0 ), m_fadeOut ( 0 ), 
		m_indexObject ( 0 ), m_valid ( true )
	{
		//----------------------------------------------
		//オブジェクト配列
		m_pvpObject = make_shared < VP_Object > ();

		//オブジェクト個数は１以上なので自動で１つ生成する
		m_pvpObject->push_back ( make_shared < GameObject > () );

		//----------------------------------------------
		//テクスチャ配列
		m_pvpTexture = make_shared < VP_TxBs > ();

		//テクスチャは０以上なので自動生成しない
		//特にゲームグラフィック　アプロブドテクスチャはテクスチャは０のみ

		//----------------------------------------------
		m_pCenter = make_shared < VEC3 > ( 0.f, 0.f, 0.f );
		m_pPosition = make_shared < VEC3 > ( 0.f, 0.f, Z_DEFALT );
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
	void GameGraphicBase::SetValid ( bool b )
	{
		for ( P_Object p : *m_pvpObject ) { p->SetValid ( b ); }
		m_valid = b;
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

	//表示時間（０なら常時）
	void GameGraphicBase::SetWait ( UINT n )
	{
		m_wait = n;
		m_timer = 0;

		if ( 0 == n ) { return; }
		
#if 0
		UINT sizeMatrix = m_pvpObject->size();
		for ( UINT i = 0; i < sizeMatrix; ++i )
		{
			m_pvpObject->at ( i )->SetValid ( true );
		}
#endif // 0
		for ( P_Object p : (*m_pvpObject) ) { p->SetValid ( true ); }
		m_valid = true;
	}

	//フレーム毎動作
	void GameGraphicBase::Move ()
	{
		//ウェイトタイムが指定されているとき
		if ( 0 != m_wait )
		{
			_Fade ();	//フェード
		}


		//マトリックスの動作
		for ( P_Object pOb : *m_pvpObject ) { pOb->Move (); }
	}

	void GameGraphicBase::_Fade ()
	{
		if ( 0 < m_fadeOut )	//フェードアウト優先
		{
			if ( m_fadeOut > m_timer )
			{
				//α値を算出
				UINT alpha = (UINT)(0xff * (1.f - (1.f / m_fadeOut) * m_timer));
				_CLR color = _CLR ( alpha << 24 ^ 0x00ffffff );
//				if ( m_pvpTexture->at ( 0 ) ) { m_pvpTexture->at ( 0 )->SetColor ( color ); }
				for ( P_Object p : * m_pvpObject ) { p->SetColor ( color ); }
			}
			else if ( m_fadeOut == m_timer )	//終了
			{
#if 0

				m_pvpTexture->at ( 0 )->SetColor ( _CLR ( 0x00ffffff ) );
				UINT sizeObject = m_pvpObject->size ();
				for ( UINT i = 0; i < sizeObject; ++i )
				{
					m_pvpObject->at ( i )->SetValid ( false );
				}
#endif // 0
				for ( P_Object p : *m_pvpObject ) { p->SetColor ( _CLR ( 0x00ffffff ) ); p->SetValid ( false ); }
				m_valid = false;
				m_fadeOut = 0;
			}
		}
		else if ( 0 < m_fadeIn )
		{
			if ( m_fadeIn > m_timer )
			{
				//α値を算出
				UINT alpha = (0xff / m_fadeIn) * m_timer;
				_CLR color = _CLR ( alpha << 24 ^ 0x00ffffff );
				for ( P_Object p : *m_pvpObject ) { p->SetColor ( color ); }
			}
			else if ( m_fadeIn == m_timer )	//終了
			{
//				if ( m_pvpTexture->at ( 0 ) ) { m_pvpTexture->at ( 0 )->SetColor ( _CLR ( 0xffffffff ) ); }
				for ( P_Object p : *m_pvpObject ) { p->SetColor ( _CLR ( 0xffffffff ) ); }
				m_fadeIn = 0;
			}
		}

		//タイマの終了
		if ( m_wait == m_timer )
		{
			UINT sizeObject = m_pvpObject->size ();
			for ( UINT i = 0; i < sizeObject; ++i )
			{
				m_pvpObject->at ( i )->SetValid ( false );
			}
			m_valid = false;
		}
		else
		{
			++ m_timer;
		}
	}

	//フレーム毎描画
	void GameGraphicBase::Draw ()
	{
		//テクスチャが設定されていないとき何もしない
		if ( 0 == m_pvpTexture->size() ) { return; }

		//マトリックスの数だけ描画
		for ( UINT i = 0; i < m_pvpObject->size (); ++i )
		{
			//有効フラグ
			if ( ! m_pvpObject->at ( i )->GetValid () ) { continue; }
			UINT indexTexture = m_pvpObject->at ( i )->GetIndexTexture ();

			if ( ! m_pvpTexture->at ( indexTexture ) ) { continue; }

			P_Object po = m_pvpObject->at ( i );

			Dx3D::instance()->DrawSprite
			(
				m_pvpTexture->at ( indexTexture )->GetTexture(),
				m_pvpObject->at ( i )->GetcpMatrix(),
				nullptr,
				m_pCenter.get (), 
				m_pPosition.get (), 
				m_pvpObject->at ( i )->GetColor ()
			);
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

	void GameGraphicFromFile::Load ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			m_vpTexture[i]->Load ();
		}
	}

	void GameGraphicFromFile::Rele ()
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

	void GameGraphicFromFile::Reset ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			m_vpTexture[i]->Reset ();
		}
	}

	void GameGraphicFromFile::AddTexture ( LPCTSTR fileName )
	{
		shared_ptr < GameTextureFromFile > pTexture = make_shared < GameTextureFromFile > ();
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
#if 0

		for ( UINT i = 0; i < m_pvpTexture->size(); ++i )
		{
			if ( m_pvpTexture[i] )
			{
				delete m_pvpTexture[i];
				m_pvpTexture[i] = nullptr;
			}
		}

#endif // 0
		m_vpTexture.clear ();
	}

	void GameGraphicFromArchive::Load ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			m_vpTexture[i]->Load ();
		}
	}

	void GameGraphicFromArchive::Rele ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			if ( m_vpTexture[i] )
			{
				m_vpTexture[i]->Rele ();
			}
		}
	}

	void GameGraphicFromArchive::Reset ()
	{
		for ( UINT i = 0; i < m_vpTexture.size(); ++i )
		{
			m_vpTexture[i]->Reset ();
		}
	}

	void GameGraphicFromArchive::AddTexture ( LPCTSTR fileName )
	{
		shared_ptr < GameTextureFromArchive > pTexture = make_shared < GameTextureFromArchive > ();
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

	void GameGraphicApprovedTexture::Load ()
	{
	}

	void GameGraphicApprovedTexture::Rele ()
	{
	}

	void GameGraphicApprovedTexture::Reset ()
	{
		Rele ();
	}


}	//namespace GAME


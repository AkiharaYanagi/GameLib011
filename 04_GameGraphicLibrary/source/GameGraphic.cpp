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

namespace GAME
{
	//=======================================================================
	// GameGraphicBase
	//=======================================================================
	
	//コンストラクタ
	GameGraphicBase::GameGraphicBase ()
		:	m_wait ( 0 ), m_timer ( 0 ), m_fadeIn ( 0 ), m_fadeOut ( 0 ), 
			m_indexObject ( 0 ), m_valid ( true )
	{
		//----------------------------------------------
		//オブジェクト配列
		m_pvpObject = make_shared < VP_Object > ();

		//オブジェクトは１つ以上なので自動で一つ生成する
		m_pvpObject->push_back ( make_shared < GameObject > () );

		//----------------------------------------------
		//テクスチャ配列
		m_pvpTexture = make_shared < VP_TxBs > ();

		//テクスチャは０以上なので自動生成しない
		//特にゲームグラフィック　アプロブドテクスチャはテクスチャは０のみ

		//----------------------------------------------
		m_pCenter = make_shared < VEC3 > ( 0.f, 0.f, 0.f );
		m_pPosition = make_shared < VEC3 > ( 0.f, 0.f, 0.f );
		m_pPosition->z = 0.5f; 
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
		UINT sizeObject = m_pvpObject->size();
		for ( UINT i = 0; i < sizeObject; ++i )
		{
			m_pvpObject->at ( i )->SetValid ( b );
		}
		m_valid = b;
	}

	//すべてのオブジェクトへの操作：位置指定
	void GameGraphicBase::SetAllPos ( VEC2 vec )
	{
		UINT sizeMatrix = m_pvpObject->size ();
		for ( UINT i = 0; i < sizeMatrix; ++i )
		{
			m_pvpObject->at ( i )->GetpMatrix ()->SetPos ( vec );
		}
	}

	//すべてのオブジェクトへの操作：色指定
	void GameGraphicBase::SetAllColor ( D3DXCOLOR color )
	{
		for ( P_Object p : (*m_pvpObject ) )
		{
			p->SetColor ( color );
		}
	}

	//表示時間（０なら常時）
	void GameGraphicBase::SetWait ( UINT n )
	{
		if ( 0 != n )
		{
			m_wait = n;
			m_timer = 0;

			UINT sizeMatrix = m_pvpObject->size();
			for ( UINT i = 0; i < sizeMatrix; ++i )
			{
				m_pvpObject->at ( i )->SetValid ( true );
			}
			m_valid = true;
		}
	}

	//フレーム毎動作
	void GameGraphicBase::Move ()
	{
		//タイマ
		if ( 0 != m_wait )
		{
			//フェード
			if ( 0 < m_fadeOut )			//フェードアウト優先
			{
				if ( m_fadeOut > m_timer )
				{
					//α値を算出
					UINT alpha = (UINT)( 0xff * ( 1.f - ( 1.f / m_fadeOut ) * m_timer ) );
					D3DXCOLOR color = D3DXCOLOR ( alpha << 24 ^ 0x00ffffff );
					if ( m_pvpTexture->at ( 0 ) ) { m_pvpTexture->at ( 0 )->SetColor ( color ); }
				}
				else if ( m_fadeOut == m_timer )	//終了
				{
					m_pvpTexture->at ( 0 )->SetColor ( D3DXCOLOR ( 0x00ffffff ) );
					UINT sizeObject = m_pvpObject->size();
					for ( UINT i = 0; i < sizeObject; ++i )
					{
						m_pvpObject->at ( i )->SetValid ( false );
					}
					m_valid = false;
					m_fadeOut = 0;
				}
			}
			else if ( 0 < m_fadeIn )
			{
				if ( m_fadeIn > m_timer )
				{
					//α値を算出
					UINT alpha = ( 0xff / m_fadeIn ) * m_timer;
					D3DXCOLOR color = D3DXCOLOR ( alpha << 24 ^ 0x00ffffff );
					if ( m_pvpTexture->at ( 0 ) ) { m_pvpTexture->at ( 0 )->SetColor ( color ); }
				}
				else if ( m_fadeIn == m_timer )	//終了
				{
					if ( m_pvpTexture->at ( 0 ) ) { m_pvpTexture->at ( 0 )->SetColor ( D3DXCOLOR ( 0xffffffff ) ); }
					m_fadeIn = 0;
				}
			}

			//タイマの終了
			if ( m_wait == m_timer )
			{
				UINT sizeObject = m_pvpObject->size();
				for ( UINT i = 0; i < sizeObject; ++i )
				{
					m_pvpObject->at ( i )->SetValid ( false );
				}
				m_valid = false;
			}
			else
			{
				++m_timer;
			}
		}


		//マトリックスの動作
		UINT size = m_pvpObject->size();
		for ( UINT i = 0; i < size; ++i )
		{
			m_pvpObject->at ( i )->Move ();
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
#if 0


	//テクスチャの先頭を返す
	shared_ptr < GameTextureBase > GameGraphicBase::GetpTexture ()
	{
		if ( m_pvpTexture->size () == 0 ) { return nullptr; }
		return m_pvpTexture [ m_indexTexture ];
	}

	//テクスチャを次のインデックスに進める
	//末尾のときは何もしない
	void GameGraphicBase::NextTexture ()
	{
		if ( m_indexTexture < m_pvpTexture->size () - 1 )
		{
			++m_indexTexture;
		}
	}
#endif // 0

	//テクスチャの中心位置 (Load()後のみ)
	VEC2 GameGraphicBase::GetCenterOfTexture ( UINT index ) const
	{
		VEC2 ret = VEC2 ( 0, 0 );
		if ( m_pvpTexture->size () <= index ) { return ret; }

		D3DSURFACE_DESC desc;
		m_pvpTexture->at ( index )->GetTexture ()->GetLevelDesc ( 0, &desc );
		ret.x = 0.5f * desc.Width;
		ret.y = 0.5f * desc.Height;
		return ret;
	}


	//-------------------------------------------------------------------------------------------------
	// GameGraphicFromFile
	//-------------------------------------------------------------------------------------------------
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


	//-------------------------------------------------------------------------------------------------
	// GameGraphicFromArchive
	//-------------------------------------------------------------------------------------------------
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


	//-------------------------------------------------------------------------------------------------
	// GameGraphicApprovedTexture
	//-------------------------------------------------------------------------------------------------
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


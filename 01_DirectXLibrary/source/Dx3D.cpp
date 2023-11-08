//=================================================================================================
//
// Direct3D の実装
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Dx3D.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	Dx3D::P_Dx3D	Dx3D::m_inst;

	//------------------------------------------
	//	コンストラクタ
	//------------------------------------------
	Dx3D::Dx3D ()
		: m_lpD3D ( nullptr ), m_lpD3DDevice ( nullptr ), m_lpSprite ( nullptr )
		, m_lpBackBuffer ( nullptr ), m_lpTexture ( nullptr ), m_lpTextureSurface ( nullptr ), m_lpOffScreenSurface ( nullptr )
		, m_fullscreen ( false )
		, m_window_x ( 1280 ), m_window_y ( 960 ), m_displayNum ( 0 )
	{
	}

	//------------------------------------------
	//	デストラクタ
	//------------------------------------------
	Dx3D::~Dx3D ()
	{
		Rele ();
	}

	//-------------------------------------------------------------------------------------------------
	//	Direct3Dの初期化
	//-------------------------------------------------------------------------------------------------
	void Dx3D::Load ()
	{
		try
		{
			_Load ();
		}
		catch ( LPCTSTR str )
		{
			OutputDebugString ( str );
			Rele ();
			PostQuitMessage ( 0 );
			return;
		}
	}

	void Dx3D::_Load ()
	{
		HRESULT hr;		//戻値

		//すでに生成していたら例外
		if ( m_lpD3D != nullptr ) { throw _T("Direct3Dオブジェクトの二重生成"); }

		//D3Dオブジェクトの作成
		m_lpD3D = Direct3DCreate9( D3D_SDK_VERSION );
		if ( m_lpD3D == nullptr ) { throw _T("Direct3Dオブジェクトの作成"); }

		//対応ディスプレイモードの個数を取得
		int n = ::GetSystemMetrics ( SM_CMONITORS );	//個数の数え上げは1個から
		if ( n - 1 < m_displayNum ) { m_displayNum = n - 1; }
//		UINT nDisplayMode = m_lpD3D->GetAdapterModeCount ( D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8 );
		UINT nDisplayMode = m_lpD3D->GetAdapterModeCount ( m_displayNum, D3DFMT_X8R8G8B8 );
		D3DDISPLAYMODE dsplMd;
		std::vector < D3DDISPLAYMODE >	vDsplMode;
		for ( UINT i = 0; i < nDisplayMode; ++i )
		{
//			m_lpD3D->EnumAdapterModes ( D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, & dsplMd );
			m_lpD3D->EnumAdapterModes ( m_displayNum, D3DFMT_X8R8G8B8, i, & dsplMd );
			vDsplMode.push_back ( dsplMd );
		}

		//現在のディスプレイモードの取得
		D3DDISPLAYMODE displayMode;
//		hr = m_lpD3D->GetAdapterDisplayMode ( D3DADAPTER_DEFAULT, &displayMode );
		hr = m_lpD3D->GetAdapterDisplayMode ( m_displayNum, &displayMode );
		FAILED_DXTRACE_THROW ( hr, _T("現在のディスプレイモードの取得") );

#if	0
		//デバイスタイプのテスト
		hr = m_lpD3D->CheckDeviceType ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, d3ddm.Format, TRUE );
		FAILED_DXTRACE_THROW ( hr, _T("デバイスタイプのテスト") );

		//デバイスフォーマットのテスト
		hr = m_lpD3D->CheckDeviceFormat ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
			d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 );
//				d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16_LOCKABLE );
		FAILED_DXTRACE_THROW ( hr, _T("デバイスフォーマットのテスト") );
#endif	//0
		
		//D3Dデバイスパラメータの設定	
		// [フルスクリーン] / [ウィンドウ]の選択
		D3DPRESENT_PARAMETERS preParam;
		if ( m_fullscreen )
		{
			preParam = GetParamFullscreen ( displayMode );
		}
		else
		{
			preParam = GetParamWindow ( displayMode );
		}


		//デバイスの作成
		_CreateDeviceSequentially ( & preParam );


		//zバッファ
		m_lpD3DDevice->SetRenderState ( D3DRS_ZENABLE, D3DZB_TRUE );

		//深度バッファテスト
		D3DCAPS9 caps;
		hr = m_lpD3DDevice->GetDeviceCaps ( &caps );
		FAILED_DXTRACE_THROW ( hr, _T("デバイス能力の取得") );
		hr = m_lpD3D->CheckDeviceFormat (	caps.AdapterOrdinal,
											caps.DeviceType,
											D3DFMT_X8R8G8B8,
											D3DUSAGE_DEPTHSTENCIL,
											D3DRTYPE_SURFACE,
											D3DFMT_D16 );
//												D3DFMT_D16_LOCKABLE );
		FAILED_DXTRACE_THROW ( hr, _T("デバイスフォーマットのテスト") );
		hr = m_lpD3D->CheckDepthStencilMatch (	caps.AdapterOrdinal,
												caps.DeviceType,
												D3DFMT_X8R8G8B8,
												D3DFMT_X8R8G8B8,
												D3DFMT_D16 );
//													D3DFMT_D16_LOCKABLE );
		FAILED_DXTRACE_THROW ( hr, _T("深度バッファテスト") );
#if	0
#endif	//0

		//スプライトの作成
		hr = D3DXCreateSprite ( m_lpD3DDevice, &m_lpSprite );
		FAILED_DXTRACE_THROW ( hr, _T("スプライトの作成") );


		//-----------------------------------
		//ゲームウィンドウサイズ(原寸・書込対象)1280*960に書き込み、ウィンドウサイズ(表示上・変更可能)に縮小
		//デバイスの作成時にバックバッファの大きさ指定を ( GAME_WINDOW_WIDTH, WINDOW_WIDTH ) にする

		//デバイスのバックバッファを取得
		hr = m_lpD3DDevice->GetBackBuffer ( 0, 0, D3DBACKBUFFER_TYPE_MONO, &m_lpBackBuffer );
		FAILED_DXTRACE_THROW ( hr, _T("バックバッファの取得") );


		//バックバッファの深度バッファを取得
		hr = m_lpD3DDevice->GetDepthStencilSurface ( & m_lpBackDepthSurface );


		//バックバッファのサーフェスデスクリプションの取得
		D3DSURFACE_DESC desc;
		hr = m_lpBackBuffer->GetDesc( &desc );
		FAILED_DXTRACE_THROW ( hr, _T("サーフェスデスクリプションの取得") );

		//書込用一時テクスチャの作成
		const UINT GW = GAME_WINDOW_WIDTH;
		const UINT GH = GAME_WINDOW_HEIGHT;

		DWORD US = D3DUSAGE_RENDERTARGET;
		D3DPOOL PL = D3DPOOL_DEFAULT;
		hr = m_lpD3DDevice->CreateTexture ( GW, GH, MP_LV_1, US, desc.Format, PL, &m_lpTexture, nullptr );
		FAILED_DXTRACE_THROW ( hr, _T("テクスチャの作成") );

		//テクスチャにおけるサーフェスへのポインタを取得する
		hr = m_lpTexture->GetSurfaceLevel ( 0, &m_lpTextureSurface );
		FAILED_DXTRACE_THROW ( hr, _T("テクスチャにおけるサーフェスへのポインタを取得する") );

		//テクスチャサーフェスのデスクリプションを取得
		hr = m_lpTextureSurface->GetDesc( &desc );
		FAILED_DXTRACE_THROW ( hr, _T("テクスチャサーフェスのデスクリプションを取得") );

		//オフスクリーンサーフェスの作成
		hr = m_lpD3DDevice->CreateOffscreenPlainSurface( GW, GH, desc.Format, D3DPOOL_DEFAULT, &m_lpOffScreenSurface, nullptr );
		FAILED_DXTRACE_THROW ( hr, _T("サーフェスの作成") );

	}

	//-------------------------------------------------------------------------------------------------
	// Direct3Dの解放
	//-------------------------------------------------------------------------------------------------
	void Dx3D::Rele()
	{
		RELEASE ( m_lpBackDepthSurface );

		RELEASE ( m_lpOffScreenSurface );
		RELEASE ( m_lpTextureSurface );
		RELEASE( m_lpTexture );
		RELEASE( m_lpBackBuffer );

		RELEASE( m_lpSprite );
		RELEASE( m_lpD3DDevice );
		RELEASE( m_lpD3D );
	}


	//-------------------------------------------------------------------------------------------------
	// Direct3Dの再設定 (ウィンドウ切り替え時など) (初期化済みであることが条件)
	//-------------------------------------------------------------------------------------------------
	void Dx3D::Reset()
	{
		if ( nullptr == m_lpD3D ) { return; }
		if ( nullptr == m_lpD3DDevice ) { return; }
		if ( nullptr == m_lpSprite ) { return; }

		Rele ();
		Load ();
	}


	//------------------------------------------
	// 描画開始
	//------------------------------------------
	void Dx3D::BeginScene()
	{
		if ( ! m_lpD3DDevice ) { return; }


		m_lpD3DDevice->SetDepthStencilSurface ( m_lpBackDepthSurface );


		//書き込み対象を一時テクスチャサーフェスに変更
//		m_lpD3DDevice->SetRenderTarget ( 0, m_lpTextureSurface );
//		m_lpD3DDevice->SetRenderTarget ( 0, m_lpOffScreenSurface );

		//バックバッファをクリア
//		DWORD FLAG = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
		DWORD FLAG = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
//		m_lpD3DDevice->Clear ( 0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB ( 210, 250, 250 ), 0, 0 );
//		m_lpD3DDevice->Clear ( 0, nullptr, FLAG, D3DCOLOR_XRGB ( 210, 250, 250 ), 1.f, 0 );
		m_lpD3DDevice->Clear ( 0, nullptr, FLAG, D3DCOLOR_XRGB ( 80, 80, 80 ), 1.f, 0 );

		//バックバッファ,zバッファをクリア
		/* zバッファをクリアするときは引数float zの値を1.0fにする */
//		m_lpD3DDevice->Clear ( 0, nullptr, flag, 0xffa0a0a0, 1.0f, 0 );

		//描画開始
		m_lpD3DDevice->BeginScene ();
	}


	//------------------------------------------
	// 描画終了
	//------------------------------------------
	void Dx3D::EndScene()
	{
		if ( ! m_lpD3DDevice ) { return; }

		//描画終了
		m_lpD3DDevice->EndScene ();

#if 0

//		m_lpD3DDevice->Clear ( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffa0ffa0, 1.0f, 0 );

		//書き込みをバックバッファサーフェスに戻す
		m_lpD3DDevice->SetRenderTarget ( 0, m_lpBackBuffer );

		m_lpD3DDevice->BeginScene ();
		DWORD flag = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
		//		m_lpD3DDevice->Clear ( 0, nullptr, D3DCLEAR_TARGET, 0xffa0a0a0, 0, 0 );
//		m_lpD3DDevice->Clear ( 0, nullptr, flag, 0xffa0a0ff, 1.0f, 0 );
//		m_lpD3DDevice->Clear ( 0, nullptr, D3DCLEAR_TARGET, 0xffa0a0ff, 1.0f, 0 );
		m_lpD3DDevice->EndScene ();

		//テクスチャサーフェスからデバイスのバックバッファに転送
		RECT rectSrc;
//		SetRect ( &rectSrc, 0+(int)m_zoom, 0+(int)(m_zoom * 0.67), 640-(int)m_zoom, 480-(int)(m_zoom * 0.67) );
//		SetRect ( &rectSrc, 0, 0, 320, 240 );
//		SetRect ( &rectSrc, 0, 0, 640, 480 );
//		SetRect ( &rectSrc, 0, 0, 960, 720 );
		SetRect ( &rectSrc, 0, 0, 1280, 960 );
		//		SetRect ( &rectSrc, 0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT );
		
		D3DSURFACE_DESC desc;
		m_lpTextureSurface->GetDesc ( &desc );

		RECT rectDest;
//		SetRect ( &rectDest, 0, 0, m_window_x, m_window_y );
//		SetRect ( &rectDest, 0, 0, 320, 240 );
//		SetRect ( &rectDest, 0, 0, 640, 480 );
//		SetRect ( &rectDest, 0, 0, 960, 720 );
		SetRect ( &rectDest, 0, 0, 1280, 960 );
//		SetRect ( &rectDest, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
		D3DSURFACE_DESC bcdesc;
		m_lpBackBuffer->GetDesc ( &bcdesc );

		HRESULT hr;
		hr = m_lpD3DDevice->StretchRect ( m_lpTextureSurface, &rectSrc, m_lpBackBuffer, &rectDest, D3DTEXF_NONE );
//		hr = m_lpD3DDevice->StretchRect ( m_lpOffScreenSurface, &rectSrc, m_lpBackBuffer, &rectDest, D3DTEXF_NONE );

		RECT tRect = { 110, 240, 880, 600 };
//		hr = m_lpD3DDevice->StretchRect ( m_lpTextureSurface, &rectSrc, m_lpBackBuffer, &tRect, D3DTEXF_NONE );
#endif // 0

		//バックバッファを表示
		m_lpD3DDevice->Present ( nullptr, nullptr, nullptr, nullptr );
	}


	//------------------------------------------
	// スプライト描画開始
	//------------------------------------------
	void Dx3D::BeginSprite()
	{
		if ( ! m_lpSprite ) { return; }
		m_lpSprite->Begin ( D3DXSPRITE_ALPHABLEND );	//スプライト描画開始

		//zバッファ
		m_lpD3DDevice->SetRenderState ( D3DRS_ZENABLE, D3DZB_TRUE );
	}


	//------------------------------------------
	// スプライト描画終了
	//------------------------------------------
	void Dx3D::EndSprite()
	{
		if ( ! m_lpSprite ) { return; }
		m_lpSprite->End ();	//スプライト描画終了
	}


	//------------------------------------------
	// スプライト描画
	//------------------------------------------
	void Dx3D::DrawSprite ( TX lpTexture, const D3DXMATRIX* pMatrix, const RECT* rect,
							const VEC3 *pCenter, const VEC3 *pPosition, _CLR color )
	{
		if ( ! m_lpSprite ) { return; }
		if ( pMatrix == nullptr ) { return; }

		m_lpSprite->SetTransform ( pMatrix );
		m_lpSprite->Draw ( lpTexture, rect, pCenter, pPosition, color );
	}


	//------------------------------------------
	// 頂点描画
	//------------------------------------------
	void Dx3D::DrawVertex (
		TX lpTexture, UINT streamNumber, VXBUF lpVertexBuffer, UINT offsetBytes, UINT stride,
		DWORD FVF, D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT primitiveCount )
	{
		//テクスチャの指定
		m_lpD3DDevice->SetTexture ( 0, lpTexture );

#if	1
		//テクスチャ設定
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

		//レンダリングステート
		m_lpD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, TRUE );
		m_lpD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_lpD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		//zバッファ
		m_lpD3DDevice->SetRenderState ( D3DRS_ZENABLE, D3DZB_TRUE );

#endif	//0

		m_lpD3DDevice->SetStreamSource ( streamNumber, lpVertexBuffer, offsetBytes, stride );
		m_lpD3DDevice->SetFVF ( FVF );
		m_lpD3DDevice->DrawPrimitive ( primitiveType, startVertex, primitiveCount );
	}


	//------------------------------------------
	// 頂点描画(乗算)
	//------------------------------------------
	void Dx3D::DrawVertexMultiple (
		TX lpTexture, UINT streamNumber, VXBUF lpVertexBuffer, UINT offsetBytes, UINT stride,
		DWORD FVF, D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT primitiveCount )
	{
		//テクスチャ設定

		//Stage0：色
		m_lpD3DDevice->SetTexture ( 0, lpTexture );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
#if 0
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		m_lpD3DDevice->SetTextureStageState ( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );

		//Stage1: 形
		m_lpD3DDevice->SetTexture ( 1, lpTexture );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_COLORARG1, D3DTA_CURRENT );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_ALPHAARG2, D3DTA_CURRENT );
#endif // 0

		//Stage1: 乗算後、ディフューズで半透明
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_COLOROP, D3DTOP_BLENDDIFFUSEALPHA );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_COLORARG1, D3DTA_CURRENT );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
#if 0
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_ALPHAOP, D3DTOP_BLENDDIFFUSEALPHA );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_ALPHAARG1, D3DTA_CURRENT );
		m_lpD3DDevice->SetTextureStageState ( 1, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
#endif // 0

		//レンダリングステート
//		m_lpD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, FALSE );
		m_lpD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, TRUE );

		//乗算
		m_lpD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_ZERO );
		m_lpD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR );
#if 0

		m_lpD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_lpD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
//		m_lpD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_ONE );
#endif // 0

		//zバッファ
		m_lpD3DDevice->SetRenderState ( D3DRS_ZENABLE, D3DZB_TRUE );

		//描画
		m_lpD3DDevice->SetStreamSource ( streamNumber, lpVertexBuffer, offsetBytes, stride );
		m_lpD3DDevice->SetFVF ( FVF );
		m_lpD3DDevice->DrawPrimitive ( primitiveType, startVertex, primitiveCount );
	}


	//-----------------------------------------------------------------------
	//テクスチャの作成
	void Dx3D::CreateTextureFromMem ( LPCVOID pSrcData, UINT SrcDataSize, TX * ppTexture )
	{
//		TRACE_F ( _T ( "filePointer%d, fileSize = %d\n" ), pSrcData, SrcDataSize );
		//メモリからテクスチャの作成
		HRESULT hr = D3DXCreateTextureFromFileInMemory ( m_lpD3DDevice, pSrcData, SrcDataSize, ppTexture );
		if ( FAILED ( hr ) )
		{ 
			DXTRACE ( hr, TEXT("D3DXCreateTextureFromFileInMemory：テクスチャ読込の失敗") ); 
		}
	}

	//=========================================================================================
	//	内部関数
	//=========================================================================================

	//D3Dデバイスパラメータの設定 [ウィンドウモード]
	D3DPRESENT_PARAMETERS Dx3D::GetParamWindow ( D3DDISPLAYMODE dm )
	{
		D3DPRESENT_PARAMETERS param;
		ZeroMemory( & param, sizeof ( param ) );

/*◆*/	param.Windowed			= TRUE;

//		param.BackBufferWidth	= m_window_x;
//		param.BackBufferHeight	= m_window_y;
		param.BackBufferWidth	= GAME_WINDOW_WIDTH;
		param.BackBufferHeight	= GAME_WINDOW_HEIGHT;
		param.BackBufferFormat	= dm.Format;	//バックバッファのピクセルフォーマット(デフォルトアダプタと同一にする)
		param.BackBufferCount	= 1;
		param.SwapEffect		= D3DSWAPEFFECT_DISCARD;
//		param.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//垂直同期待ちをする
		param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//垂直同期待ちをしない
//		param.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
//		param.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		param.AutoDepthStencilFormat = D3DFMT_D16;	//深度ステンシルのフォーマット
//		param.AutoDepthStencilFormat = D3DFMT_D16_LOCKABLE;	//深度ステンシルのフォーマット
		param.EnableAutoDepthStencil = TRUE;		//深度を用いる

		return param;
	}

	//D3Dデバイスパラメータの設定 [フルスクリーンモード]
	D3DPRESENT_PARAMETERS Dx3D::GetParamFullscreen ( D3DDISPLAYMODE dm )
	{
		//フルスクリーンデバイス
		D3DPRESENT_PARAMETERS fparam;
		ZeroMemory ( & fparam, sizeof ( fparam ) );

/*◇*/	fparam.Windowed			= FALSE;

		fparam.BackBufferWidth	= GAME_WINDOW_WIDTH;
		fparam.BackBufferHeight	= GAME_WINDOW_HEIGHT;
		fparam.BackBufferFormat	= dm.Format;	//バックバッファのピクセルフォーマット(デフォルトアダプタと同一にする)
		fparam.BackBufferCount	= 1;
		fparam.SwapEffect		= D3DSWAPEFFECT_DISCARD;
		fparam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//垂直同期待ちをしない
		fparam.AutoDepthStencilFormat = D3DFMT_D16;	//深度ステンシルのフォーマット
		fparam.EnableAutoDepthStencil = TRUE;		//深度を用いる
	
		return fparam;
	}

	//デバイスの作成
	HRESULT Dx3D::_CreateDevice ( D3DDEVTYPE type, DWORD behavior, D3DPRESENT_PARAMETERS* pparam )
	{
//		return m_lpD3D->CreateDevice ( D3DADAPTER_DEFAULT, type, HWnd::Get (), behavior, pparam, & m_lpD3DDevice );
		return m_lpD3D->CreateDevice ( m_displayNum, type, HWnd::Get (), behavior, pparam, & m_lpD3DDevice );
	}

	//各種組み合わせ順次 デバイスの作成
	void Dx3D::_CreateDeviceSequentially ( D3DPRESENT_PARAMETERS* pparam )
	{
		HRESULT hr;

		hr = _CreateDevice ( D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING, pparam );
		DXTRACE ( hr, _T("HAL HARDWARE_VERTEXPROCESSING デバイスの作成") );
		if ( SUCCEEDED ( hr ) )	{ return; }

		hr = _CreateDevice ( D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING, pparam );
		DXTRACE ( hr, _T("HAL SOFTWARE_VERTEXPROCESSING デバイスの作成") );
		if ( SUCCEEDED ( hr ) )	{ return; }

		hr = _CreateDevice ( D3DDEVTYPE_REF, D3DCREATE_HARDWARE_VERTEXPROCESSING, pparam );
		DXTRACE ( hr, _T("REF HARDWARE_VERTEXPROCESSING デバイスの作成") );
		if ( SUCCEEDED ( hr ) )	{ return; }

		hr = _CreateDevice ( D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING, pparam );
		DXTRACE ( hr, _T("REF SOFTWARE_VERTEXPROCESSING デバイスの作成") );
		if ( SUCCEEDED ( hr ) )	{ return; }
		
		//すべての組み合わせで失敗
		FAILED_DXTRACE_THROW ( hr, _T("Direct3D デバイスの作成に失敗") );
	}


}	//namespace GAME


//=================================================================================================
//
// Direct3D(グラフィックス)の管理クラス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"		//DirectX共通
#include "DxDefine.h"			//DirectX内外共通
#include <d3d9.h>				//Direct3D
#include <d3dx9.h>				//Direct3DX
#include <memory>
using namespace std;

#include "DebugLibrary.h"		//デバッグの利用
#include "HWnd.h"				//ウィンドウハンドルの取得
#include "GameLibConst.h"		//ゲームライブラリ共通

//-------------------------------------------------------------------------------------------------
// ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
	//------------------------------------------
	//Direct3D の管理クラス
	//------------------------------------------
	class Dx3D
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using P_Dx3D = std::unique_ptr < Dx3D >;
		static P_Dx3D		m_inst;		//シングルトンインスタンス(実体は.cppで定義)
		Dx3D ();		//private コンストラクタで通常の実体化は禁止
		Dx3D ( const Dx3D& rhs ) = delete;		//コピーコンストラクタは削除
	public:
		~Dx3D();		//デストラクタはstd::unique_ptrのためpublic
		static void Create() { if ( ! m_inst ) { m_inst = P_Dx3D ( new Dx3D () ); } }
		static P_Dx3D& instance () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------

	private:
		LPDIRECT3D9				m_lpD3D;				//Direct3D　オブジェクト
		LPDIRECT3DDEVICE9		m_lpD3DDevice;			//Direct3D　デバイス
		LPD3DXSPRITE			m_lpSprite;				//スプライト

		LPDIRECT3DSURFACE9		m_lpBackBuffer;			//バックバッファサーフェス
		LPDIRECT3DTEXTURE9		m_lpTexture;			//サーフェス用のテクスチャ	
		LPDIRECT3DSURFACE9		m_lpTextureSurface;		//テクスチャとするサーフェスポインタ
		LPDIRECT3DSURFACE9		m_lpOffScreenSurface;			//オフスクリーンサーフェスポインタ

		LPDIRECT3DSURFACE9		m_lpBackDepthSurface;		//深度バッファサーフェスポインタ

		//------------------------------------------------------------
		//外部パラメータ指定
		bool					m_fullscreen;			//[フルスクリーン] / [ウィンドウ]
//		double					m_zoom;					//拡大値(0-320)
//		D3DXVECTOR2				m_focus;				//スクリーン表示位置の原点
		UINT	m_window_x;		//外部指定ウィンドウサイズX
		UINT	m_window_y;		//外部指定ウィンドウサイズY
		int		m_displayNum;	//ディスプレイ番号

		//------------------------------------
		//内部関数
		void _Load ();

		//デバイスパラメータ
		D3DPRESENT_PARAMETERS GetParamWindow ( D3DDISPLAYMODE dm );
		D3DPRESENT_PARAMETERS GetParamFullscreen ( D3DDISPLAYMODE dm );

		//デバイスの作成
		HRESULT _CreateDevice ( D3DDEVTYPE type, DWORD behavior, D3DPRESENT_PARAMETERS* pparam );
		
		//各種組み合わせ順次　デバイスの作成
		void _CreateDeviceSequentially ( D3DPRESENT_PARAMETERS* pparam );

	public:
		void Load();	//読込
		void Rele();	//解放
		void Reset();	//再設定

		//------------------------------------------------------------
		//外部パラメータ指定
		//ウィンドウサイズ
		void SetWindowSize ( UINT x, UINT y ) { m_window_x = x; m_window_y = y; }
		//フルスクリーン
		void SetFullscreen ( bool b ) { m_fullscreen = b; }
		//ディスプレイ番号
		void SetDisplayNum ( int n ) { m_displayNum = n; }

		//------------------------------------------------------------

		//デバイスの取得 
		D3DDEV		GetDevice() { return m_lpD3DDevice; }
		//スプライトの取得
		LPD3DXSPRITE			GetSprite() { return m_lpSprite; }

		//描画開始
		void BeginScene();
		//描画終了
		void EndScene();

		//スプライト描画開始
		void BeginSprite();
		//スプライト描画終了
		void EndSprite();

		//スプライト描画
		void DrawSprite 
		(
			TX lpTexture, const D3DXMATRIX* pMatrix, const RECT* rect,
			const VEC3 *pCenter, const VEC3 *pPosition, _CLR Color
		);

		//頂点描画
		void DrawVertex
		(
			TX lpTexture,
			UINT streamNumber, VXBUF lpVertexBuffer, UINT offsetBytes, UINT stride,
			DWORD FVF, D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT primitiveCount
		);

		//頂点描画(乗算)
		void DrawVertexMultiple
		(
			TX lpTexture,
			UINT streamNumber, VXBUF lpVertexBuffer, UINT offsetBytes, UINT stride,
			DWORD FVF, D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT primitiveCount
		);

		//稼動状態の確認
		bool	IsActive () { return ( m_lpD3D && m_lpD3DDevice && m_lpSprite ); }

		//フォーカスの取得
//		D3DXVECTOR2 GetFocus() { return m_focus; }
//		void SetFocus(D3DXVECTOR2 vec) { m_focus = vec; }

		//ズーム
//		void ZoomIn() { m_zoom += 10.0; if ( m_zoom > 319.9 ) m_zoom = 319.9; }
//		void ZoomOut() { m_zoom -= 10.0; if ( m_zoom < 0.0 ) m_zoom = 0.0; }

		//テクスチャの作成
		void CreateTextureFromMem ( LPCVOID pSrcData, UINT SrcDataSize, TX* ppTexture );
	};

	//シングルトンアクセス
	#define DX3D Dx3D::instance()

}	//namespace GAME


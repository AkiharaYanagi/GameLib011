//=================================================================================================
//
// DirectXにおける頂点の定義
//
//=================================================================================================


#ifndef		__DXVERTEX_HEADER_INCLUDE__
#define		__DXVERTEX_HEADER_INCLUDE__


//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"	//DirectX共通
#include "Dx3D.h"
#include <list>


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	//-------------------------------------------------------------------------------------------------
	// 定数
	//-------------------------------------------------------------------------------------------------
	#define FVF_CUSTOM ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )


	//-------------------------------------------------------------------------------------------------
	// 構造体
	//-------------------------------------------------------------------------------------------------
	struct CUSTOM_VERTEX
	{
		float x, y, z;	//頂点座標
		float rhw;		//除算数
		DWORD color;	//色
		float u, v;		//テクスチャ座標
	};


	//-------------------------------------------------------------------------------------------------
	// 頂点バッファと処理クラス
	//-------------------------------------------------------------------------------------------------
	class DxVertex
	{
		LPDIRECT3DVERTEXBUFFER9		m_lpVertexBuffer;		//頂点バッファ
		CUSTOM_VERTEX*				m_vertex;				//頂点
		UINT						m_vertexNum;			//頂点数

		bool						m_update;				//更新フラグ (move()時にapplyPos()を行うかどうか)

		D3DXCOLOR					m_color;				//共通基本色
		float						m_z;					//共通z位置

	public:
		DxVertex ();
		DxVertex ( UINT vertexNum );	//頂点数を指定するコンストラクタ
		DxVertex ( const DxVertex& rhs );
		virtual ~DxVertex ();

		virtual void Load ();
		virtual void Rele ();
		virtual void Reset ();
		virtual void Move ();

		void DrawVertex ( LPDIRECT3DTEXTURE9 lpTexture );

		virtual void ApplyPos () {};

		//頂点バッファ作成
		void CreateVertexBuffer ();

		//頂点バッファ取得
		LPDIRECT3DVERTEXBUFFER9 GetBuffer () { return m_lpVertexBuffer; }

		//頂点バッファに頂点を書込
		void SetVertexBuffer ();

		//頂点数を設定
		void SetVertexNum ( UINT num );
		UINT GetVertexNum () { return m_vertexNum; }
		//頂点数を再設定
		void ResetVertexNum ( UINT num );
		//頂点を初期化
		void Clear ();

		//頂点設定
		void SetVertex ( UINT index, float x, float y, float z, float rhw, DWORD color, float u, float v );

		//位置の設定
		void SetPos ( UINT index, float x, float y, float z );
		void SetPosXY ( UINT index, float x, float y );

		//Z軸
		void SetAllZ ( float z );
		float GetAllZ () const { return m_z; }

		//色の設定
		void SetAllColor ( D3DXCOLOR color );
		void SetColor ( UINT vertexNum, D3DXCOLOR color );

		//除算数の設定
		void SetRhw ( UINT index, float rhw );

		//テクスチャ座標の設定
		void SetTexturePos ( UINT index, float u, float v );

		//更新フラグ
		void SetUpdate ( bool b ) { m_update = b; }
		bool GetUpdate () const { return m_update; }
	};



	//特定の形を持つ頂点集合
	class DxParticularVertex : public DxVertex
	{
		D3DXVECTOR2					m_pos;					//位置

	public:
		DxParticularVertex ();
		DxParticularVertex ( UINT vertexNum );	//頂点数を指定するコンストラクタ
		DxParticularVertex ( const DxParticularVertex& rhs );
		~DxParticularVertex () {}

		//位置
		void SetPos ( float x, float y ) { m_pos.x = x; m_pos.y = y; }
		void SetPos ( D3DXVECTOR2& vec ) { m_pos = vec; }
		D3DXVECTOR2 GetPos () const { return m_pos; }
	};

//-------------------------------------------------------------------------------------------------
	//４頂点(矩形)
	class DxVertex4 : public DxParticularVertex
	{
		enum { VERTEX_NUM = 4 };
		float					m_w;		//幅
		float					m_h;		//高さ

	public:
		DxVertex4 ();
		DxVertex4 ( const DxVertex4& rhs );
		~DxVertex4 ();

		//位置指定
		void SetRect ( float x, float y, float w, float h ) { SetPos ( x, y ); m_w = w; m_h = h; }
		void SetWidth ( float w ) { m_w = w; }
		void SetHeight ( float h ) { m_h = h; }
		void SetSize ( float w, float h ) { m_w = w; m_h = h; }

		void ApplyPos ();	//位置を適用して頂点をつくる
	};


//-------------------------------------------------------------------------------------------------
	//４頂点(自由位置)
	class DxVertexFree4 : public DxVertex
	{
		enum { VERTEX_NUM = 4 };
		D3DXVECTOR2				m_vec[4];

	public:
		DxVertexFree4 ();
		DxVertexFree4 ( const DxVertexFree4& rhs );
		~DxVertexFree4 ();

		//位置指定
		void SetPoint ( UINT i, D3DXVECTOR2 vec ) { m_vec[i] = vec; }

		void ApplyPos ();	//位置を適用して頂点をつくる
	};


//-------------------------------------------------------------------------------------------------
	//擬似線分
	class DxVertexLine : public DxVertex
	{
		enum { VERTEX_NUM = 4 };
		D3DXVECTOR2				m_vec[2];
		float					m_w;		//幅

	public:
		DxVertexLine ();
		DxVertexLine ( const DxVertexLine& rhs );
		~DxVertexLine ();

		//位置指定
		void SetPoint ( D3DXVECTOR2 vec0, D3DXVECTOR2 vec1 ) { m_vec[0] = vec0; m_vec[1] = vec1; }
		void SetPoint ( float x0, float y0, float x1, float y1 ) 
			{ m_vec[0].x = x0; m_vec[0].y = y0; m_vec[1].x = x1; m_vec[1].y = y1; }
		void SetWidth ( float w ) { m_w = w; }

		void ApplyPos ();	//位置を適用して頂点をつくる
	};


//-------------------------------------------------------------------------------------------------
	//３頂点(正三角形)
	class DxVertex3 : public DxParticularVertex
	{
		enum { VERTEX_NUM = 3 };
		float					m_w;		//一辺の長さ
		float					m_rad;		//回転角度[rad]

	public:
		DxVertex3 ();
		DxVertex3 ( const DxVertex3& rhs );
		~DxVertex3 ();

		//位置指定
		void SetTriangle ( float x, float y, float w, float rad ) { SetPos ( x, y ); m_w = w; m_rad = rad; }
		void SetWidth ( float w ) { m_w = w; }
		void SetRadian ( float rad ) { m_rad = rad; }

		void ApplyPos ();	//位置を適用して頂点をつくる
	};
//-------------------------------------------------------------------------------------------------
	//多頂点
	class _DxPoliVertex : public DxVertex
	{
		float					m_w;		//一辺の長さ

		//３点
		D3DXVECTOR2				m_vec[3];
		//->４角×２個		
		//->６頂点

	public:
		_DxPoliVertex ();
		_DxPoliVertex ( const _DxPoliVertex& rhs );
		~_DxPoliVertex ();

		void ApplyPos ();	//位置を適用して頂点をつくる

		//２点から４角点を計算する
		//引数：
		//rectVec[]		(out) ４角点
		//vec[]			(in) 始点と終点
		void SetRectVec ( D3DXVECTOR2 rectVec[], D3DXVECTOR2 vec[] ) const;

		//２直線から交点を求める
		//引数：
		//crossVec		(out) 交点
		//vec			(in) (vec0,vec1)と(vec2,vec3)の２直線
		void SetCrossVec ( D3DXVECTOR2& crossVec,
			const D3DXVECTOR2& vec0, const D3DXVECTOR2& vec1, 
			const D3DXVECTOR2& vec2, const D3DXVECTOR2& vec3 ) const;

		//test 点設定
		void SetVec ( D3DXVECTOR2 vec ) { m_vec[2] = vec; ApplyPos (); }
	};


	class DxPoliVertex : public DxVertex
	{
		float					m_w;		//一辺の長さ

		//ｎ点
//		UINT					m_maxVec;		//点の最大数
//		UINT					m_numVec;		//点の個数
//		D3DXVECTOR2*			m_vec;
		//４(ｎ－１)角点
		//２ｎ頂点

		std::list < D3DXVECTOR2 >	m_listVec;		//点のリスト

	public:
		DxPoliVertex ();
		DxPoliVertex ( const DxPoliVertex& rhs );
		~DxPoliVertex ();

		virtual void Load ();	//初期化を後にするオーバーライド
		virtual void Rele ();
		virtual void Reset ();

		//点の最大数を設定する
//		void SetMaxVec ( UINT max );

		//点を追加する
		void AddVec ( D3DXVECTOR2& vec );

		//点を削除する
		void DelVec ();

		//点をすべて削除する
		void ClearVec ();

//		void _ApplyPos ();	//位置を適用して頂点をつくる
		void ApplyPos ();	//位置を適用して頂点をつくる

		//２点から４角点を計算する
		//引数：
		//rectVec[]		(out) ４角点
		//vec[]			(in) 始点と終点
		void SetRectVec ( D3DXVECTOR2 rectVec[], D3DXVECTOR2 vec[] ) const;

		//２直線から交点を求める
		//引数：
		//crossVec		(out) 交点
		//vec			(in) (vec0,vec1)と(vec2,vec3)の２直線
		void SetCrossVec ( D3DXVECTOR2& crossVec,
			const D3DXVECTOR2& vec0, const D3DXVECTOR2& vec1, 
			const D3DXVECTOR2& vec2, const D3DXVECTOR2& vec3 ) const;

		//点設定
		void SetVec ( UINT index, const D3DXVECTOR2& vec );

		//線の太さの設定
		void SetWidth ( float w ) { m_w = w; }
	};


//-------------------------------------------------------------------------------------------------


}	//namespace GAME


#endif		//__DXVERTEX_HEADER_INCLUDE__



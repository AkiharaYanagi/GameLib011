//=================================================================================================
//
// DirectXにおける頂点の定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"	//DirectX共通
#include "Dx3D.h"
#include "DxDefine.h"
#include <list>

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
	//-------------------------------------------------------------------------------------------------
	// 定数
	//-------------------------------------------------------------------------------------------------
	//VERTEXの状態を定義
	#define FVF_CUSTOM ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

	//-------------------------------------------------------------------------------------------------
	// 構造体
	//-------------------------------------------------------------------------------------------------
	//頂点の定義
	struct CUSTOM_VERTEX
	{
		float x, y, z;	//頂点座標
		float rhw;		//除算数
		DWORD color;	//色 (D3DXCOLORではなく、DWORD指定)
		float u, v;		//テクスチャ座標
	};
	using VX = CUSTOM_VERTEX;

	//頂点を配列で保存
	using V_VX = vector < VX >;

	//-------------------------------------------------------------------------------------------------
	// 頂点バッファと処理クラス
	//-------------------------------------------------------------------------------------------------
	class DxVertex
	{
		VXBUF		m_lpVertexBuffer;	//頂点バッファ
		V_VX		m_vVx;				//頂点配列
		bool		m_update;			//更新フラグ (move()時にapplyPos()を行うかどうか)
		DWORD		m_color;			//共通基本色
		float		m_z;				//共通z位置
		bool		m_valid;			//有効フラグ

	public:
		DxVertex ();
		DxVertex ( UINT vertexNum );	//頂点数を指定するコンストラクタ
		DxVertex ( const DxVertex& rhs ) = delete;
		virtual ~DxVertex ();

		virtual void Load ();
		virtual void Rele ();
		virtual void Reset ();
		virtual void Move ();

		void DrawVertex ( TX lpTexture );

		//基準位置から頂点を設定する
		virtual void ApplyPos () {};

		//頂点バッファ作成
		void CreateVertexBuffer ();

		//頂点バッファ取得
		VXBUF GetBuffer () { return m_lpVertexBuffer; }

		//頂点バッファに頂点を書込
		void SetVertexBuffer ();

		//頂点数を設定
		void SetVertexNum ( UINT num );
		UINT GetVertexNum () { return m_vVx.size (); }
		//頂点数を再設定
		void ResetVertexNum ( UINT num );
		//頂点を初期化
		void Clear ();

		//頂点設定
		void SetVertex ( VX& vertex, float x, float y, float z, float rhw, DWORD color, float u, float v );
		void SetVertex ( UINT index, float x, float y, float z, float rhw, DWORD color, float u, float v );

		//位置の設定
		void SetPos ( UINT index, float x, float y, float z );
		void SetPosXY ( UINT index, float x, float y );

		//Z軸
		void SetAllZ ( float z );
		float GetAllZ () const { return m_z; }

		//色の設定
		void SetAllColor ( DWORD color );
		void SetColor ( UINT vertexNum, DWORD color );

		//除算数の設定
		void SetRhw ( UINT index, float rhw );

		//テクスチャ座標の設定
		void SetTexturePos ( UINT index, float u, float v );

		//更新フラグ
		void SetUpdate ( bool b ) { m_update = b; }
		bool GetUpdate () const { return m_update; }

		//有効フラグ
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () const { return m_valid; }
	};

	using P_Vertex = shared_ptr < DxVertex >;



//-------------------------------------------------------------------------------------------------
	//ある位置を基点に特定の形を持つ頂点集合
	class DxParticularVertex : public DxVertex
	{
		VEC2		m_pos;		//基準位置

	public:
		DxParticularVertex () = delete;
		DxParticularVertex ( UINT vertexNum );	//頂点数を指定するコンストラクタ
		DxParticularVertex ( const DxParticularVertex& rhs ) = delete;
		~DxParticularVertex () {}

		//位置
		void SetPos ( float x, float y ) { m_pos.x = x; m_pos.y = y; }
		void SetPos ( VEC2& vec ) { m_pos = vec; }
		VEC2 GetPos () const { return m_pos; }
	};

	using P_PtclVx = shared_ptr < DxParticularVertex >;


//-------------------------------------------------------------------------------------------------
	//４頂点(矩形)
	class DxVertex4 : public DxParticularVertex
	{
		enum { VERTEX_NUM = 4 };
		float					m_w;		//幅
		float					m_h;		//高さ

	public:
		DxVertex4 ();
		DxVertex4 ( const DxVertex4& rhs ) = delete;
		~DxVertex4 ();

		//位置指定
		void SetRect ( float x, float y, float w, float h ) { SetPos ( x, y ); m_w = w; m_h = h; }
		void SetWidth ( float w ) { m_w = w; }
		void SetHeight ( float h ) { m_h = h; }
		void SetSize ( float w, float h ) { m_w = w; m_h = h; }

		void ApplyPos ();	//位置を適用して頂点をつくる
	};

	using P_Vx4 = shared_ptr < DxVertex4 >;


//-------------------------------------------------------------------------------------------------
	//４頂点(自由位置)
	class DxVertexFree4 : public DxVertex
	{
		enum { VERTEX_NUM = 4 };
		VEC2		m_vec[4];

	public:
		DxVertexFree4 ();
		DxVertexFree4 ( const DxVertexFree4& rhs ) = delete;
		~DxVertexFree4 ();

		//位置指定
		void SetPoint ( UINT i, VEC2 vec ) { m_vec[i] = vec; }

		void ApplyPos ();	//位置を適用して頂点をつくる
	};

	using P_VxF4 = shared_ptr < DxVertexFree4 >;


//-------------------------------------------------------------------------------------------------
	//擬似線分
	class DxVertexLine : public DxVertex
	{
		enum { VERTEX_NUM = 4 };
		VEC2		m_vec[2];
		float		m_w;		//幅

	public:
		DxVertexLine ();
		DxVertexLine ( const DxVertexLine& rhs ) = delete;
		~DxVertexLine ();

		//位置指定
		void SetPoint ( D3DXVECTOR2 vec0, D3DXVECTOR2 vec1 ) { m_vec[0] = vec0; m_vec[1] = vec1; }
		void SetPoint ( float x0, float y0, float x1, float y1 ) 
			{ m_vec[0].x = x0; m_vec[0].y = y0; m_vec[1].x = x1; m_vec[1].y = y1; }
		void SetWidth ( float w ) { m_w = w; }

		void ApplyPos ();	//位置を適用して頂点をつくる
	};

	using P_VxLine = shared_ptr < DxVertexLine >;


//-------------------------------------------------------------------------------------------------
	//３頂点(正三角形)
	class DxVertex3 : public DxParticularVertex
	{
		enum { VERTEX_NUM = 3 };
		float					m_w;		//一辺の長さ
		float					m_rad;		//回転角度[rad]

	public:
		DxVertex3 ();
		DxVertex3 ( const DxVertex3& rhs ) = delete;
		~DxVertex3 ();

		//位置指定
		void SetTriangle ( float x, float y, float w, float rad ) { SetPos ( x, y ); m_w = w; m_rad = rad; }
		void SetWidth ( float w ) { m_w = w; }
		void SetRadian ( float rad ) { m_rad = rad; }

		void ApplyPos ();	//位置を適用して頂点をつくる
	};

	using P_VxTri = shared_ptr < DxVertex3 >;


	//-------------------------------------------------------------------------------------------------
	//多頂点
	class _DxPoliVertex : public DxVertex
	{
		float					m_w;		//一辺の長さ

		//３点
		VEC2				m_vec[3];
		//->４角×２個		
		//->６頂点

	public:
		_DxPoliVertex ();
		_DxPoliVertex ( const _DxPoliVertex& rhs ) = delete;
		~_DxPoliVertex ();

		void ApplyPos ();	//位置を適用して頂点をつくる

		//２点から４角点を計算する
		//引数：
		//rectVec[]		(out) ４角点
		//vec[]			(in) 始点と終点
		void SetRectVec ( VEC2 rectVec[], VEC2 vec[] ) const;

		//２直線から交点を求める
		//引数：
		//crossVec		(out) 交点
		//vec			(in) (vec0,vec1)と(vec2,vec3)の２直線
		void SetCrossVec ( VEC2& crossVec,
			const VEC2& vec0, const VEC2& vec1,
			const VEC2& vec2, const VEC2& vec3 ) const;

		//test 点設定
		void SetVec ( VEC2 vec ) { m_vec[2] = vec; ApplyPos (); }
	};

	using _P_VxPori = shared_ptr < _DxPoliVertex >;



	class DxPoliVertex : public DxVertex
	{
		float					m_w;		//一辺の長さ

		//ｎ点
//		UINT					m_maxVec;		//点の最大数
//		UINT					m_numVec;		//点の個数
//		D3DXVECTOR2*			m_vec;
		//４(ｎ－１)角点
		//２ｎ頂点

		std::list < VEC2 >	m_listVec;		//点のリスト

	public:
		DxPoliVertex ();
		DxPoliVertex ( const DxPoliVertex& rhs ) = delete;
		~DxPoliVertex ();

		virtual void Load ();	//初期化を後にするオーバーライド
		virtual void Rele ();
		virtual void Reset ();

		//点の最大数を設定する
//		void SetMaxVec ( UINT max );

		//点を追加する
		void AddVec ( VEC2& vec );

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
		void SetRectVec ( VEC2 rectVec[], VEC2 vec[] ) const;

		//２直線から交点を求める
		//引数：
		//crossVec		(out) 交点
		//vec			(in) (vec0,vec1)と(vec2,vec3)の２直線
		void SetCrossVec ( VEC2& crossVec,
			const VEC2& vec0, const VEC2& vec1,
			const VEC2& vec2, const VEC2& vec3 ) const;

		//点設定
		void SetVec ( UINT index, const VEC2& vec );

		//線の太さの設定
		void SetWidth ( float w ) { m_w = w; }
	};

	using P_VxPori = shared_ptr < DxPoliVertex >;


//-------------------------------------------------------------------------------------------------


}	//namespace GAME


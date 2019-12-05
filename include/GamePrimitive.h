//=================================================================================================
//
// ゲームプリミティブオブジェクト　クラス　ヘッダ
//
//		頂点処理のグラフィックを扱うオブジェクト
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "DxVertex.h"
#include "GameTask.h"
#include "GameText.h"
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//プリミティブグラフィック
	//-------------------------------------------------------------------------------------------------
	class GamePrimitive : public GameGraphicBase
	{
		DxVertex*		m_vertex;				//頂点集合クラスポインタ
		bool			m_valid;				//有効フラグ

	public:
		GamePrimitive ();
		GamePrimitive ( DxVertex* vertex );
		GamePrimitive ( const GamePrimitive& rhs ) = delete;
		virtual ~GamePrimitive ();

		void Load ();
		void Rele ();
		void Reset ();
		void Move ();

		//引数：テクスチャなし
		void DrawVertex ();
		//引数：テクスチャあり
		void DrawVertex ( LPDIRECT3DTEXTURE9& texture );

		//頂点監理クラスの設定
		void SetVertex ( DxVertex* vertex ) { assert ( vertex ); m_vertex = vertex; }
		
		//有効・無効
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () { return m_valid; }

		//頂点色の設定
		void SetAllColor ( _CLR color ) { m_vertex->SetAllColor ( color ); m_vertex->SetVertexBuffer (); }

		void SetAllZ ( float z ) { m_vertex->SetAllZ ( z ); m_vertex->SetVertexBuffer (); }

		void SetUpdate ( bool b ) { m_vertex->SetUpdate ( b ); }
	};

	//-------------------------------------------------------------------------------------------------
	//パティキュラプリミティブグラフィック
	//	ある位置を基点に特定の形を持つ頂点集合を用いる
	//-------------------------------------------------------------------------------------------------
	class GameParticularPrimitive : public GamePrimitive
	{
		DxParticularVertex*			m_vertex;				//頂点集合クラスポインタ

	public:
		GameParticularPrimitive () :m_vertex ( nullptr ) {}
		GameParticularPrimitive ( DxParticularVertex* vertex ) : GamePrimitive ( vertex ) { m_vertex = vertex; }
		GameParticularPrimitive ( const GameParticularPrimitive& rhs ) = delete;
		virtual ~GameParticularPrimitive () {}

		void SetVertex ( DxParticularVertex* vertex ) { GamePrimitive::SetVertex ( vertex ); m_vertex = vertex; }

		//位置
		void SetPos ( float x, float y ) { m_vertex->SetPos ( x, y ); }
		void SetPos ( VEC2& vec ) { m_vertex->SetPos ( vec ); }
		VEC2 GetPos () const { return m_vertex->GetPos (); }
	};


	//-------------------------------------------------------------------------------------------------
	//プリミティブレクト
	//	四角形描画
	//-------------------------------------------------------------------------------------------------
	//	３　　　１
	//
	//	↓　＼　↓
	//
	//	４　　　２

	class GamePrimitiveRect : public GameParticularPrimitive
	{
		DxVertex4		m_vertex;

	public:
		GamePrimitiveRect ();
		GamePrimitiveRect ( const GamePrimitiveRect& rhs ) = delete;
		virtual ~GamePrimitiveRect ();

		DxVertex4& GetVertex4 () { return m_vertex; }
		DxVertex4* GetpVertex4 () { return &m_vertex; }

		void SetColor ( UINT index, D3DXCOLOR color)
		{
			m_vertex.SetColor ( index, color );
		}

		//位置の設定
		void SetZero () { m_vertex.SetRect ( 0, 0, 0, 0 ); }
		void SetRect ( float x, float y, float w, float h ) { m_vertex.SetRect ( x, y, w, h ); }
		void SetWidth ( float w ) { m_vertex.SetWidth ( w ); }
		void SetHeight ( float h ) { m_vertex.SetHeight ( h ); }
		void SetSize ( float w, float h ) { m_vertex.SetSize ( w, h ); }
	};

	typedef GamePrimitiveRect		PrmRect;
	typedef shared_ptr < PrmRect >	P_PrmRect;


	//-------------------------------------------------------------------------------------------------
	//プリミティブ4
	//	四角形(自由位置)描画
	//-------------------------------------------------------------------------------------------------
	//	３　　　１
	//
	//	↓　＼　↓
	//
	//	４　　　２

	class GamePrimitive4 : public GamePrimitive
	{
		DxVertexFree4		m_vertex;

	public:
		GamePrimitive4 ();
		GamePrimitive4 ( const GamePrimitive4& rhs ) = delete;
		virtual ~GamePrimitive4 ();

		//位置の設定
		void SetPoint ( UINT i, D3DXVECTOR2 vec ) { m_vertex.SetPoint ( i, vec ); }
	};


	//-------------------------------------------------------------------------------------------------
	//プリミティブライン
	//	擬似線分
	//-------------------------------------------------------------------------------------------------
	class GamePrimitiveLine : public GamePrimitive
	{
		DxVertexLine		m_vertex;

	public:
		GamePrimitiveLine ();
		GamePrimitiveLine ( const GamePrimitiveLine& rhs ) = delete;
		virtual ~GamePrimitiveLine ();

		//位置の設定
		void SetPoint ( D3DXVECTOR2 vec0, D3DXVECTOR2 vec1 ) { m_vertex.SetPoint ( vec0, vec1 ); }
		void SetPoint ( float x0, float y0, float x1, float y1 )  { m_vertex.SetPoint ( x0, y0, x1, y1 ); }
		void SetWidth ( float w ) { m_vertex.SetWidth ( w ); }
	};


	//-------------------------------------------------------------------------------------------------
	//プリミティブトライアングル
	//	正三角形描画
	//-------------------------------------------------------------------------------------------------
	class GamePrimitiveTriangle : public GameParticularPrimitive
	{
		DxVertex3		m_vertex;

	public:
		GamePrimitiveTriangle ();
		GamePrimitiveTriangle ( const GamePrimitiveTriangle& rhs ) = delete;
		virtual ~GamePrimitiveTriangle ();

		//位置の設定
		void SetTriangle ( float x, float y, float w, float rad ) { m_vertex.SetTriangle ( x, y, w, rad ); }
		void SetWidth ( float w ) { m_vertex.SetWidth ( w ); }
		void SetRadian ( float h ) { m_vertex.SetRadian ( h ); }
	};

	
	//-------------------------------------------------------------------------------------------------
	//プリミティブ　テキスト
	//	テキスト描画
	//-------------------------------------------------------------------------------------------------
	class GamePrimitiveText : public GamePrimitiveRect
	{
		LPDIRECT3DTEXTURE9		m_texture;				//テクスチャ
		tstring					m_tstr;					//文字列

//		HDC_Font::FONT_SIZE		m_fontSize;

		enum FONT_SIZE
		{
			FONT_SIZE_8  = 0,
			FONT_SIZE_16 = 1,
			FONT_SIZE_24 = 2,
			FONT_SIZE_32 = 3,
			FONT_SIZE_64 = 4,
			FONT_SIZE_NUM = 5,
		};
		FONT_SIZE				m_fontSize;

	public:
		GamePrimitiveText ();
		GamePrimitiveText ( const GamePrimitiveText& rhs ) = delete;
		virtual ~GamePrimitiveText ();

		void Load ();
		void Rele ();
		void Reset ();
		void DrawVertex ();

		void SetStr ( tstring& tstr );
		void SetStr ( LPCTSTR lpctstr );
		LPCTSTR GetStr () const { return m_tstr.c_str (); }

		//可変長引数によるフォーマット指定
		void SetStrf ( LPCTSTR format, ... );

//		void SetFontSize ( HDC_Font::FONT_SIZE fontSize ) { m_fontSize = fontSize; }
		void SetFontSize ( FONT_SIZE fontSize ) { m_fontSize = fontSize; }
	};


	//-------------------------------------------------------------------------------------------------
	//プリミティブ　ポリライン
	//	太さを持つ多角線
	//-------------------------------------------------------------------------------------------------
	class _GamePrimitivePoliLine : public GamePrimitive
	{
		_DxPoliVertex		m_vertex;

	public:
		_GamePrimitivePoliLine ();
		_GamePrimitivePoliLine ( const _GamePrimitivePoliLine& rhs ) = delete;
		~_GamePrimitivePoliLine ();
		
		void Load ();

		void SetVec ( D3DXVECTOR2 vec ) { m_vertex.SetVec ( vec ); }
	};

	class GamePrimitivePoliLine : public GamePrimitive
	{
		DxPoliVertex		m_vertex;

	public:
		GamePrimitivePoliLine ();
		GamePrimitivePoliLine ( const GamePrimitivePoliLine& rhs ) = delete;
		~GamePrimitivePoliLine ();
		
		void Load ();

		void SetVec ( UINT index, D3DXVECTOR2& vec ) { m_vertex.SetVec ( index, vec ); }
		void AddVec ( D3DXVECTOR2& vec ) { m_vertex.AddVec ( vec ); }
		void DelVec () { m_vertex.DelVec (); }
		void ClearVec () { m_vertex.ClearVec (); }
		void SetWidth ( float w ) { m_vertex.SetWidth ( w ); }
	};


}	//namespace GAME


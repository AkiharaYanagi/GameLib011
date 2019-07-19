//=================================================================================================
//
// ゲームドキュメント　ヘッダファイル
//		
//		ElementタグとAttributeの包含によって記述されるxml模倣のツリー状データ構造
//		<Element.name Attribute.name="Attribute.value"></Element.name>
//		
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include <memory>
#include <vector>
using namespace std;

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//----------------------------------------------------------
	//アトリビュート
	//	名前と値を持つ
	//----------------------------------------------------------
	class Attribute
	{
		tstring		m_name;
		tstring		m_value;

	public:
		Attribute ( tstring name, tstring value ) :	m_name ( name ), m_value ( value ) {}
		Attribute ( const Attribute& rhs ) = delete;		//コピー禁止
		~Attribute () = default;

		void Clear () {}
		void Print ()
		{
			tostringstream oss;
			oss << m_name.c_str() << (" = ") << m_value.c_str() << (", ");
			OutputDebugString ( oss.str().c_str() );
		}
		tstring GetName () const { return m_name; }
		tstring GetValue () const { return m_value; }
	};

	typedef shared_ptr < Attribute >	P_Attribute;
	typedef vector < P_Attribute >		VP_Attribute;
	typedef shared_ptr < VP_Attribute >	PVP_Attribute;


	//----------------------------------------------------------
	//エレメント
	//	０以上のアトリビュートと０以上のエレメントを持つ
	//----------------------------------------------------------
	class Element;
	typedef shared_ptr < Element >		P_Element;
	typedef vector < P_Element >		VP_Element;
	typedef shared_ptr < VP_Element >	PVP_Element;

	class Element
	{
		tstring			m_name;			//名前
		PVP_Attribute	m_attributes;	//自身のアトリビュート配列
		PVP_Element		m_elements;		//自身のエレメント配列
		P_Element		m_pParent;		//親エレメントのポインタ

	public:
		Element ();
		Element ( const Element& rhs ) = delete;		//コピー禁止
		~Element () { Clear (); }

		//アトリビュート配列の先頭を取得
		const PVP_Attribute GetpvpAttribute () const { return m_attributes; }

		//エレメント配列の先頭を取得
		const PVP_Element GetpvpElement () const { return m_elements; }

		//親エレメントのポインタ
		void SetpParent ( P_Element pElement ) { m_pParent = pElement; }
		P_Element GetpParent () { return m_pParent; }

		//アトリビュート配列の追加
		void AddpAttribute ( P_Attribute pAttribute ) { m_attributes->push_back ( pAttribute ); }

		//エレメント配列の追加
		void AddpElement ( P_Element pElement ) { m_elements->push_back ( pElement ); }

		void Clear ();

		void SetName ( tstring str ) { m_name.assign ( str ); }
		tstring GetName () const { return m_name; }

		void Print ();
	};


	//----------------------------------------------------------
	//ドキュメント
	//	木構造であるエレメントの根となるrootを持つ
	//----------------------------------------------------------
	class Document
	{
		P_Element		root;

	public:
		enum STATE
		{
			START,
			ELEMENT_START,
			ELEMENT,
			ELEMENT_END,
			ATTRIBUTE_NAME_START,
			ATTRIBUTE_NAME_END,
			ATTRIBUTE_VALUE_START,
			ATTRIBUTE_VALUE,
			ATTRIBUTE_VALUE_END,
			ELEMENT_CLOSING,
			END,
		};

		//コンストラクタ
		Document () = default;
		Document ( const Document& rhs ) = delete;	//コピー禁止	
		
		//ドキュメントファイル名から読込
		Document ( tstring fileName );

		//テキストストリームから読込
		Document ( tistringstream& tiss );

		//バイナリデータから読込
		Document ( char* buf, UINT size );

		//デストラクタ
		~Document ();

		void DocumentFromStream ( tistream& tistrm );			//引数：入力ストリーム
//		void DocumentFromBinary ( TCHAR* buf );			//引数：テキストデータ
		void Print () { root->Print(); }

		const P_Element Root () const { return root; }
	};


}	//namespace GAME



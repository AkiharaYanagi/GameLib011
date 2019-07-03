//=================================================================================================
//
// Document ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Document.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//----------------------------------------------------------
	// Attribute
	//----------------------------------------------------------
	//ヘッダのみ

	//----------------------------------------------------------
	// Element
	//----------------------------------------------------------
	Element::Element () : m_pParent ( nullptr )
	{
		m_attributes = make_shared < VP_Attribute > ();
		m_elements = make_shared < VP_Element > ();
	}

	void Element::Clear ()
	{
		for ( P_Attribute attr : (*m_attributes) ) { attr->Clear (); }
		m_attributes->clear ();

		for ( P_Element elem : (*m_elements) ) { elem->Clear (); }
		m_elements->clear();
	}


	void Element::Print ()
	{
		if ( m_pParent ) 
		{
			OutputDebugString ( m_pParent->GetName().c_str() );
			OutputDebugString ( _T(" -> ") );
		}
		OutputDebugString ( m_name.c_str() );
		OutputDebugString ( _T(" : ") );

		for ( P_Attribute attribute : (*m_attributes ) )
		{
			attribute->Print ();
		}

//		OutputDebugString ( _T("\n") );

		for ( P_Element element : (*m_elements) )
		{
			element->Print ();
		}
	}



	//----------------------------------------------------------
	// Document
	//----------------------------------------------------------

	//ドキュメントファイル名から読込
	Document::Document ( tstring fileName )
	{
		root = make_shared < Element > ();
		root->SetName (_T("root") );

		//ファイルストリームを作成
		tifstream ifstrm ( fileName.c_str(), ios::in );
		if ( ! ifstrm ) { return; }

		DocumentFromStream ( ifstrm );

		ifstrm.close ();
	}

	//テキストストリームから読込
	Document::Document ( tistringstream& tiss )
	{
		root = make_shared < Element > ();
		root->SetName (_T("root") );
		DocumentFromStream ( tiss );
	}

	//入力ストリームから読込
	void Document::DocumentFromStream ( tistream& tistrm )
	{
		if ( ! tistrm ) { return; }

		tstring str = _T("");
		STATE mode = START;
		P_Element element = root;
		P_Element nextElement = nullptr;
		tstring strElementName = _T("");
		tstring strAttributeName = _T("");
		tstring strAttributeValue = _T("");

		while ( tistrm )
		{
			tistrm.unsetf ( ios::skipws );			//空白の読み飛ばしをOFFにする

			//一文字ずつ解析
			unsigned short c = tistrm.get();
			switch ( mode )
			{
			case START:
				if ( c == '<' )
				{
					mode = ELEMENT_START;
				}
				break;

			case ELEMENT_START:
				if ( c == '/' )	//終了タグ
				{
					//親エレメントに戻る
					if ( element->GetpParent () == nullptr )
					{
						mode = END;						//ルートなら終了
					}
					else
					{
						element = element->GetpParent ();
						mode = ELEMENT_CLOSING;
					}
				}
				else	//開始タグ
				{
					//終了タグの前にもう一度開始タグが始まると子エレメントとなる

					//エレメント新規作成
					nextElement = make_shared < Element > ();
					element->AddpElement ( nextElement );
					nextElement->SetpParent ( element );
					element = nextElement;

					mode = ELEMENT;

					//最初の一文字
					strElementName += c;
				}
				break;

			case ELEMENT:
				if ( c == ' ' )	//Name終了
				{
					element->SetName ( strElementName );		//名前をセット
					strElementName.clear ();

					mode = ATTRIBUTE_NAME_START;
				}
				else if ( c == '>' )		//読み飛ばす
				{
					//アトリビュートなしでエレメント終了
					mode = ELEMENT_END;
				}
				else	//通常文字列
				{
					strElementName += c;
				}
				break;

			case ATTRIBUTE_NAME_START:
				if ( c == '=' )
				{
					mode = ATTRIBUTE_VALUE_START;
				}
				else	//通常文字
				{
					strAttributeName += c;
				}
				break;

			case ATTRIBUTE_VALUE_START:
				if ( c == '\"' )
				{
					mode = ATTRIBUTE_VALUE;
				}
				break;

			case ATTRIBUTE_VALUE:
				if ( c == '\"' )
				{
					mode = ATTRIBUTE_VALUE_END;
				}
				else
				{
					strAttributeValue += c;
				}
				break;

			case ATTRIBUTE_VALUE_END:
				if ( c == ' ' )	//区切り(次のアトリビュートへ)
				{
					//アトリビュートをエレメントに加える
					P_Attribute pAttribute = make_shared < Attribute > ( strAttributeName, strAttributeValue );
					element->AddpAttribute ( pAttribute );
					strAttributeName = _T("");
					strAttributeValue = _T("");

					mode = ATTRIBUTE_NAME_START;
				}
				else if ( c == '>' )	//エレメント内で最後のアトリビュート
				{
					//アトリビュートをエレメントに加える
					P_Attribute pAttribute = make_shared < Attribute > ( strAttributeName, strAttributeValue );
					element->AddpAttribute ( pAttribute );
					strAttributeName = _T("");
					strAttributeValue = _T("");

					mode = ELEMENT_END;
				}
				break;

			case ELEMENT_END:
				if ( c == '<' )
				{
					mode = ELEMENT_START;
				}
				break;

			case ELEMENT_CLOSING:
				if ( c == '>' )
				{
					mode = START;
				}
				break;

			case END:
				break;

			default:
				break;
			}
		}

//		tistrm.close ();
	}


	//バイナリデータから読込
	Document::Document ( char* buf, UINT size )
	{
		root = make_shared < Element > ();
		UINT pos = 0;

		tstring str = _T("");
		STATE mode = START;
		P_Element element = root;
		P_Element nextElement = nullptr;
		tstring strElementName = _T("");
		tstring strAttributeName = _T("");
		tstring strAttributeValue = _T("");

		while ( pos != size )
		{
			//一文字ずつ解析
			char c = buf[pos++];

//			TRACE_F ( _T("%c"), c );

			switch ( mode )
			{
			case START:
				if ( c == '<' )
				{
					mode = ELEMENT_START;
				}
				break;

			case ELEMENT_START:
				if ( c == '/' )	//終了タグ
				{
					//親エレメントに戻る
					if ( element->GetpParent () == nullptr )
					{
						mode = END;						//ルートなら終了
					}
					else
					{
						element = element->GetpParent ();
						mode = ELEMENT_CLOSING;
					}
				}
				else	//開始タグ
				{
					//終了タグの前にもう一度開始タグが始まると子エレメントとなる

					//エレメント新規作成
					nextElement = make_shared < Element > ();
					element->AddpElement ( nextElement );
					nextElement->SetpParent ( element );
					element = nextElement;

					mode = ELEMENT;

					//最初の一文字
					strElementName += c;
				}
				break;

			case ELEMENT:
				if ( c == ' ' )	//Name終了
				{
					element->SetName ( strElementName );		//名前をセット
					strElementName.clear ();

					mode = ATTRIBUTE_NAME_START;
				}
				else if ( c == '>' )		//読み飛ばす
				{
					//アトリビュートなしでエレメント終了
					mode = ELEMENT_END;
				}
				else	//通常文字列
				{
					strElementName += c;
				}
				break;

			case ATTRIBUTE_NAME_START:
				if ( c == '=' )
				{
					mode = ATTRIBUTE_VALUE_START;
				}
				else	//通常文字
				{
					strAttributeName += c;
				}
				break;

			case ATTRIBUTE_VALUE_START:
				if ( c == '\"' )
				{
					mode = ATTRIBUTE_VALUE;
				}
				break;

			case ATTRIBUTE_VALUE:
				if ( c == '\"' )
				{
					mode = ATTRIBUTE_VALUE_END;
				}
				else
				{
					strAttributeValue += c;
				}
				break;

			case ATTRIBUTE_VALUE_END:
				if ( c == ' ' )	//区切り(次のアトリビュートへ)
				{
					//アトリビュートをエレメントに加える
					P_Attribute pAttribute = make_shared < Attribute > ( strAttributeName, strAttributeValue );
					element->AddpAttribute ( pAttribute );
					strAttributeName = _T("");
					strAttributeValue = _T("");

					mode = ATTRIBUTE_NAME_START;
				}
				else if ( c == '>' )	//エレメント内で最後のアトリビュート
				{
					//アトリビュートをエレメントに加える
					P_Attribute pAttribute = make_shared < Attribute > ( strAttributeName, strAttributeValue );
					element->AddpAttribute ( pAttribute );
					strAttributeName = _T("");
					strAttributeValue = _T("");

					mode = ELEMENT_END;
				}
				break;

			case ELEMENT_END:
				if ( c == '<' )
				{
					mode = ELEMENT_START;
				}
				break;

			case ELEMENT_CLOSING:
				if ( c == '>' )
				{
					mode = START;
				}
				break;

			case END:
				break;

			default:
				assert ( 0 );
				break;
			}
		}
	}

	Document::~Document()
	{
		root->Clear ();
	}


}	//namespace GAME


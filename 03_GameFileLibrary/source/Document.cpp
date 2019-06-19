//=================================================================================================
//
// Document �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Document.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//----------------------------------------------------------
	// Attribute
	//----------------------------------------------------------
	//�w�b�_�̂�

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
#if 0
		for ( P_Attribute attribute : (*m_attributes) )
		{
			attribute->Clear ();
			delete attribute;
		}
#endif // 0
		m_attributes->clear ();

#if 0
		for ( Element* element : m_elements )
		{
			element->Clear ();
			delete element;
		}
#endif // 0
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

	//�h�L�������g�t�@�C��������Ǎ�
	Document::Document ( tstring fileName )
	{
		root->SetName (_T("root") );

		//�t�@�C���X�g���[�����쐬
		tifstream ifstrm ( fileName.c_str(), ios::in );
		if ( ! ifstrm ) { return; }

		DocumentFromStream ( ifstrm );

		ifstrm.close ();
	}

	//�e�L�X�g�X�g���[������Ǎ�
	Document::Document ( tistringstream& tiss )
	{
		root->SetName (_T("root") );
		DocumentFromStream ( tiss );
	}

	//���̓X�g���[������Ǎ�
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
			tistrm.unsetf ( ios::skipws );			//�󔒂̓ǂݔ�΂���OFF�ɂ���

			//�ꕶ�������
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
				if ( c == '/' )	//�I���^�O
				{
					//�e�G�������g�ɖ߂�
					if ( element->GetpParent () == nullptr )
					{
						mode = END;						//���[�g�Ȃ�I��
					}
					else
					{
						element = element->GetpParent ();
						mode = ELEMENT_CLOSING;
					}
				}
				else	//�J�n�^�O
				{
					//�I���^�O�̑O�ɂ�����x�J�n�^�O���n�܂�Ǝq�G�������g�ƂȂ�

					//�G�������g�V�K�쐬
					nextElement = make_shared < Element > ();
					element->AddpElement ( nextElement );
					nextElement->SetpParent ( element );
					element = nextElement;

					mode = ELEMENT;

					//�ŏ��̈ꕶ��
					strElementName += c;
				}
				break;

			case ELEMENT:
				if ( c == ' ' )	//Name�I��
				{
					element->SetName ( strElementName );		//���O���Z�b�g
					strElementName.clear ();

					mode = ATTRIBUTE_NAME_START;
				}
				else if ( c == '>' )		//�ǂݔ�΂�
				{
					//�A�g���r���[�g�Ȃ��ŃG�������g�I��
					mode = ELEMENT_END;
				}
				else	//�ʏ핶����
				{
					strElementName += c;
				}
				break;

			case ATTRIBUTE_NAME_START:
				if ( c == '=' )
				{
					mode = ATTRIBUTE_VALUE_START;
				}
				else	//�ʏ핶��
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
				if ( c == ' ' )	//��؂�(���̃A�g���r���[�g��)
				{
					//�A�g���r���[�g���G�������g�ɉ�����
					P_Attribute pAttribute = make_shared < Attribute > ( strAttributeName, strAttributeValue );
					element->AddpAttribute ( pAttribute );
					strAttributeName = _T("");
					strAttributeValue = _T("");

					mode = ATTRIBUTE_NAME_START;
				}
				else if ( c == '>' )	//�G�������g���ōŌ�̃A�g���r���[�g
				{
					//�A�g���r���[�g���G�������g�ɉ�����
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


	//�o�C�i���f�[�^����Ǎ�
	Document::Document ( char* buf, UINT size )
	{
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
			if ( 0 == pos % 10000 )
			{
				int i = 0;
			}

			//�ꕶ�������
			char c = buf[pos++];

//			////DebugOutTrace::instance()->DebugOutf ( _T("%c"), c );

			switch ( mode )
			{
			case START:
				if ( c == '<' )
				{
					mode = ELEMENT_START;
				}
				break;

			case ELEMENT_START:
				if ( c == '/' )	//�I���^�O
				{
					//�e�G�������g�ɖ߂�
					if ( element->GetpParent () == nullptr )
					{
						mode = END;						//���[�g�Ȃ�I��
					}
					else
					{
						element = element->GetpParent ();
						mode = ELEMENT_CLOSING;
					}
				}
				else	//�J�n�^�O
				{
					//�I���^�O�̑O�ɂ�����x�J�n�^�O���n�܂�Ǝq�G�������g�ƂȂ�

					//�G�������g�V�K�쐬
					nextElement = make_shared < Element > ();
					element->AddpElement ( nextElement );
					nextElement->SetpParent ( element );
					element = nextElement;

					mode = ELEMENT;

					//�ŏ��̈ꕶ��
					strElementName += c;
				}
				break;

			case ELEMENT:
				if ( c == ' ' )	//Name�I��
				{
					element->SetName ( strElementName );		//���O���Z�b�g
					strElementName.clear ();

					mode = ATTRIBUTE_NAME_START;
				}
				else if ( c == '>' )		//�ǂݔ�΂�
				{
					//�A�g���r���[�g�Ȃ��ŃG�������g�I��
					mode = ELEMENT_END;
				}
				else	//�ʏ핶����
				{
					strElementName += c;
				}
				break;

			case ATTRIBUTE_NAME_START:
				if ( c == '=' )
				{
					mode = ATTRIBUTE_VALUE_START;
				}
				else	//�ʏ핶��
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
				if ( c == ' ' )	//��؂�(���̃A�g���r���[�g��)
				{
					//�A�g���r���[�g���G�������g�ɉ�����
					P_Attribute pAttribute = make_shared < Attribute > ( strAttributeName, strAttributeValue );
					element->AddpAttribute ( pAttribute );
					strAttributeName = _T("");
					strAttributeValue = _T("");

					mode = ATTRIBUTE_NAME_START;
				}
				else if ( c == '>' )	//�G�������g���ōŌ�̃A�g���r���[�g
				{
					//�A�g���r���[�g���G�������g�ɉ�����
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


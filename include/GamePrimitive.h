//=================================================================================================
//
// �Q�[���v���~�e�B�u�I�u�W�F�N�g�@�N���X�@�w�b�_
//
//		���_�����̃O���t�B�b�N�������I�u�W�F�N�g
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���@�C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugManager.h"
#include "DxVertex.h"
#include "GameTask.h"
#include "GameText.h"
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//�v���~�e�B�u�O���t�B�b�N
	//-------------------------------------------------------------------------------------------------
	class GamePrimitive : public GameGraphicBase
	{
		DxVertex*		m_vertex;				//���_�W���N���X�|�C���^
		bool			m_valid;				//�L���t���O

	public:
		GamePrimitive ();
		GamePrimitive ( DxVertex* vertex );
		GamePrimitive ( const GamePrimitive& rhs ) = delete;
		virtual ~GamePrimitive ();

		void Load ();
		void Rele ();
		void Reset ();
		void Move ();

		//�����F�e�N�X�`���Ȃ�
		void DrawVertex ();
		//�����F�e�N�X�`������
		void DrawVertex ( LPDIRECT3DTEXTURE9& texture );

		//���_�ė��N���X�̐ݒ�
		void SetVertex ( DxVertex* vertex ) { assert ( vertex ); m_vertex = vertex; }
		
		//�L���E����
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () { return m_valid; }

		//���_�F�̐ݒ�
		void SetAllColor ( _CLR color ) { m_vertex->SetAllColor ( color ); m_vertex->SetVertexBuffer (); }

		void SetAllZ ( float z ) { m_vertex->SetAllZ ( z ); m_vertex->SetVertexBuffer (); }

		void SetUpdate ( bool b ) { m_vertex->SetUpdate ( b ); }
	};

	//-------------------------------------------------------------------------------------------------
	//�p�e�B�L�����v���~�e�B�u�O���t�B�b�N
	//	����ʒu����_�ɓ���̌`�������_�W����p����
	//-------------------------------------------------------------------------------------------------
	class GameParticularPrimitive : public GamePrimitive
	{
		DxParticularVertex*			m_vertex;				//���_�W���N���X�|�C���^

	public:
		GameParticularPrimitive () :m_vertex ( nullptr ) {}
		GameParticularPrimitive ( DxParticularVertex* vertex ) : GamePrimitive ( vertex ) { m_vertex = vertex; }
		GameParticularPrimitive ( const GameParticularPrimitive& rhs ) = delete;
		virtual ~GameParticularPrimitive () {}

		void SetVertex ( DxParticularVertex* vertex ) { GamePrimitive::SetVertex ( vertex ); m_vertex = vertex; }

		//�ʒu
		void SetPos ( float x, float y ) { m_vertex->SetPos ( x, y ); }
		void SetPos ( VEC2& vec ) { m_vertex->SetPos ( vec ); }
		VEC2 GetPos () const { return m_vertex->GetPos (); }
	};


	//-------------------------------------------------------------------------------------------------
	//�v���~�e�B�u���N�g
	//	�l�p�`�`��
	//-------------------------------------------------------------------------------------------------
	//	�R�@�@�@�P
	//
	//	���@�_�@��
	//
	//	�S�@�@�@�Q

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

		//�ʒu�̐ݒ�
		void SetZero () { m_vertex.SetRect ( 0, 0, 0, 0 ); }
		void SetRect ( float x, float y, float w, float h ) { m_vertex.SetRect ( x, y, w, h ); }
		void SetWidth ( float w ) { m_vertex.SetWidth ( w ); }
		void SetHeight ( float h ) { m_vertex.SetHeight ( h ); }
		void SetSize ( float w, float h ) { m_vertex.SetSize ( w, h ); }
	};

	typedef GamePrimitiveRect		PrmRect;
	typedef shared_ptr < PrmRect >	P_PrmRect;


	//-------------------------------------------------------------------------------------------------
	//�v���~�e�B�u4
	//	�l�p�`(���R�ʒu)�`��
	//-------------------------------------------------------------------------------------------------
	//	�R�@�@�@�P
	//
	//	���@�_�@��
	//
	//	�S�@�@�@�Q

	class GamePrimitive4 : public GamePrimitive
	{
		DxVertexFree4		m_vertex;

	public:
		GamePrimitive4 ();
		GamePrimitive4 ( const GamePrimitive4& rhs ) = delete;
		virtual ~GamePrimitive4 ();

		//�ʒu�̐ݒ�
		void SetPoint ( UINT i, D3DXVECTOR2 vec ) { m_vertex.SetPoint ( i, vec ); }
	};


	//-------------------------------------------------------------------------------------------------
	//�v���~�e�B�u���C��
	//	�[������
	//-------------------------------------------------------------------------------------------------
	class GamePrimitiveLine : public GamePrimitive
	{
		DxVertexLine		m_vertex;

	public:
		GamePrimitiveLine ();
		GamePrimitiveLine ( const GamePrimitiveLine& rhs ) = delete;
		virtual ~GamePrimitiveLine ();

		//�ʒu�̐ݒ�
		void SetPoint ( D3DXVECTOR2 vec0, D3DXVECTOR2 vec1 ) { m_vertex.SetPoint ( vec0, vec1 ); }
		void SetPoint ( float x0, float y0, float x1, float y1 )  { m_vertex.SetPoint ( x0, y0, x1, y1 ); }
		void SetWidth ( float w ) { m_vertex.SetWidth ( w ); }
	};


	//-------------------------------------------------------------------------------------------------
	//�v���~�e�B�u�g���C�A���O��
	//	���O�p�`�`��
	//-------------------------------------------------------------------------------------------------
	class GamePrimitiveTriangle : public GameParticularPrimitive
	{
		DxVertex3		m_vertex;

	public:
		GamePrimitiveTriangle ();
		GamePrimitiveTriangle ( const GamePrimitiveTriangle& rhs ) = delete;
		virtual ~GamePrimitiveTriangle ();

		//�ʒu�̐ݒ�
		void SetTriangle ( float x, float y, float w, float rad ) { m_vertex.SetTriangle ( x, y, w, rad ); }
		void SetWidth ( float w ) { m_vertex.SetWidth ( w ); }
		void SetRadian ( float h ) { m_vertex.SetRadian ( h ); }
	};

	
	//-------------------------------------------------------------------------------------------------
	//�v���~�e�B�u�@�e�L�X�g
	//	�e�L�X�g�`��
	//-------------------------------------------------------------------------------------------------
	class GamePrimitiveText : public GamePrimitiveRect
	{
		LPDIRECT3DTEXTURE9		m_texture;				//�e�N�X�`��
		tstring					m_tstr;					//������

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

		//�ϒ������ɂ��t�H�[�}�b�g�w��
		void SetStrf ( LPCTSTR format, ... );

//		void SetFontSize ( HDC_Font::FONT_SIZE fontSize ) { m_fontSize = fontSize; }
		void SetFontSize ( FONT_SIZE fontSize ) { m_fontSize = fontSize; }
	};


	//-------------------------------------------------------------------------------------------------
	//�v���~�e�B�u�@�|�����C��
	//	�����������p��
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


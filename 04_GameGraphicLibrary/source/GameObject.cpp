//=================================================================================================
//
// GameObject ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	GameObject::GameObject ()
		: m_valid ( true ), m_indexTexture ( 0 ), m_color ( 0xffffffff )
	{
	}

	GameObject::GameObject ( const GameObject& rhs )
	{
		m_matrix = rhs.m_matrix;
		m_valid = rhs.m_valid;
		m_indexTexture = rhs.m_indexTexture;
		m_color = rhs.m_color;
	}

	GameObject::~GameObject ()
	{
	}

	void GameObject::PreMove ()
	{
		m_fade.PreMove ();
		m_color = m_fade.GetColor ();
	}

	void GameObject::Move ()
	{
		m_matrix.Move ();
	}

}	//namespace GAME


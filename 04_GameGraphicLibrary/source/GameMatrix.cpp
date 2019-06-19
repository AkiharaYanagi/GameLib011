//=================================================================================================
//
// ゲームマトリクス
//
//=================================================================================================

//
//	テクスチャを複数保持したクラスを用いる
//

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameMatrix.h"


namespace GAME
{


//-------------------------------------------------------------------------------------------------
	//テクスチャなしマトリックス
	GameMatrix::GameMatrix ()
	{
		m_vecDisp			= VEC2 ( 0.0f, 0.0f );	//スクリーン表示位置
		m_scalingCenter		= VEC2 ( 0.0f, 0.0f );	//回転時の中心座標
		m_scaling			= VEC2 ( 1.0f, 1.0f );	//スケーリング
		m_scalingRotation	= 0.0f;							//拡大回転の要素
		m_rotationCenter	= VEC2 ( 0.0f, 0.0f );	//回転時の中心座標
//		m_nDegree			= 0;							//角度
		m_radian			= 0;							//角度[rad]
		m_vecPos			= VEC2 ( 0.0f, 0.0f );	//自オブジェクト位置
		m_valid				= true;							//有効・無効フラグ
		m_indexTexture		= 0;							//テクスチャインデックス
	}

	GameMatrix::GameMatrix ( const GameMatrix& rhs )
	{
		m_vecDisp			= rhs.m_vecDisp;
		m_scalingCenter		= rhs.m_scalingCenter;
		m_scaling			= rhs.m_scaling;
		m_scalingRotation	= rhs.m_scalingRotation;
		m_rotationCenter	= rhs.m_rotationCenter;
//		m_nDegree			= rhs.m_nDegree;
		m_radian			= rhs.m_radian;
		m_vecPos			= rhs.m_vecPos;
		m_valid				= rhs.m_valid;
		m_indexTexture		= rhs.m_indexTexture;
	}

	//変換行列の作成
	void GameMatrix::Move()
	{
		m_vecDisp = m_vecPos;
//		D3DXMatrixTransformation2D ( &m_matrix, &m_scalingCenter, m_scalingRotation, 
//			&m_scaling, &m_rotationCenter, D3DXToRadian(m_nDegree), &m_vecDisp );
		D3DXMatrixTransformation2D ( &m_matrix, &m_scalingCenter, m_scalingRotation, 
			&m_scaling, &m_rotationCenter, m_radian, &m_vecDisp );
	}


#if	0
//-------------------------------------------------------------------------------------------------
	//テクスチャなしマトリックス配列
	GameMatrixArray::GameMatrixArray() : m_matrix(nullptr), m_index(0)
	{
	}

	GameMatrixArray::~GameMatrixArray()
	{
		m_matrixVector.clear();
		Clear ();
	}

	void GameMatrixArray::Init ()
	{
//		for ( UINT i = 0; i < m_size; i++ ) { if ( m_taskArray[i] ) m_taskArray[i]->Init (); }
		GameTaskVector::Init ();
	}

	void GameMatrixArray::Move ()
	{
//		for ( UINT i = 0; i < m_size; i++ ) { if ( m_taskArray[i] ) m_taskArray[i]->Move (); }
		GameTaskVector::Move ();
	}

	void GameMatrixArray::Clear ()
	{
		if ( m_matrix ) { delete[] m_matrix; }
		m_matrix = nullptr;
		m_index = 0;
	}

	//最大マトリックス数を指定する
	void GameMatrixArray::SetMaxMatrix ( UINT max )
	{
		Clear ();
		GameTaskVector::SetMax( max );
		m_matrix = new GameMatrix* [max];
		for ( UINT i = 0; i < max; i++ ) { m_matrix[i] = nullptr; }
	}

	void GameMatrixArray::SetGameMatrix ( GameMatrix* p )
	{
		assert ( m_index < GetMax() );

		m_matrix[m_index] = p;
//		SetTask( m_matrix[m_index] );
		m_matrixVector.push_back ( p );

		++m_index;
		if ( m_index >= GetMax() ) { int i = 0; }
	}

	GameMatrix* GameMatrixArray::GetGameMatrix ( UINT index )
	{
		if ( index >= m_index ) { int i = 0; }
		assert ( index < m_index );
//		return m_matrix[index]; 

		return m_matrixVector [ index ];
	}
#endif	//0


}	//namespace GAME



//=================================================================================================
//
// Command �w�b�_�t�@�C��
//	�Q�[�����̓L�[�̔z������̑g�ݍ��킹�ŕێ�����
//	���ۂɓ��͂��ꂽ���̂̋L�^�ƁA�X�N���v�g����̏����ɗp����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Const.h"
#include "Game.h"
#include "GameKey.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Command
	{
		tstring			m_name;			//���O
		V_GAME_KEY		m_vecGameKey;	//�L�[�z��
		UINT			m_limitTime;	//���͎�t����

	public:
		Command ();
		Command ( const Command & rhs ) = delete;	//�R�s�[�֎~
		~Command ();

		//��r
		bool Compare ( const V_GAME_KEY & vecGameKey, bool dirRight );

		//���O
		tstring GetName () const { return m_name; }
		void SetName ( tstring name ) { m_name.assign ( name ); }

		//�L�[�z��
//		V_GAME_KEY * GetpVecGameKey () { return & m_vecGameKey; }
		void AddGameKey ( GameKey key ) { m_vecGameKey.push_back ( key ); }

		//���͎�t����
		UINT GetLimitTime () const { return m_limitTime; }
		void SetLimitTime ( UINT limitTime ) { m_limitTime = limitTime; }
	};

	using WP_Command = weak_ptr < Command >;
	using P_Command = shared_ptr < Command >;
	using VP_Command = vector < P_Command >;

}	//namespace GAME


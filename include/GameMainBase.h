//=================================================================================================
//
// �Q�[�����C��(�x�[�X)	�w�b�_
//
//					�Q�[�����e�ɂ������ƂȂ鋓�����L�q����B
//
//	Load () �Ǎ�(�O�����\�[�X�Ȃ�1��̂ݏ�����)
//	��
//	Init()	������(������s���\���̂���)
//	��
//	Move()	�t���[�����̓���
//	����
//�@Draw()	�t���[�����̕`��
//	��
//	Rele()	���
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "GameStructureLibrary.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//=========================================================================
	//	�Q�[�����C���̃C���^�[�t�F�[�X�N���X�@�p�����ėp����
	//=========================================================================
	class GameMainBase : public GameTaskVector
	{
	public:
		GameMainBase() {}
		GameMainBase ( const GameMainBase & rhs ) = delete;
		virtual ~GameMainBase() = 0;
#if	0
		virtual void Load () = 0;		//���
		virtual void Rele () = 0;		//���
		virtual void Init() = 0;		//������
		virtual void Move() = 0;		//�t���[��������
		virtual void Draw() = 0;		//�t���[�����`��(�X�v���C�g)
		virtual void DrawVertex() = 0;	//�t���[�����`��(���_)
		virtual void Reset() = 0;		//�Đݒ�
#endif	//0
	};

	//�������z�f�X�g���N�^
	inline GameMainBase::~GameMainBase() {
//		TRACE_F(TEXT("�Q�[�����C���C���^�[�t�F�[�X�s���A�o�[�`�����f�X�g���N�^\n"));
	}


	using UP_GameMainBase = unique_ptr < GameMainBase >;


	//=========================================================================
	//	�������Ȃ��e�X�g�p�Q�[�����C��
	//=========================================================================
	class GameMainTest : public GameMainBase
	{
	public:
		GameMainTest() = default;
		GameMainTest(const GameMainTest& rhs) = delete;
		virtual ~GameMainTest();

		void Load () {}		//�Ǎ�
		void Rele(){}		//���
		void Reset(){}		//�Đݒ�

		void Init(){}		//������
		void Move(){}		//�t���[��������
		void Draw(){}		//�t���[�����`��(�X�v���C�g)
		void DrawVertex(){}	//�t���[�����`��(���_)
	};

	inline GameMainTest::~GameMainTest() {
		//TRACE_F(TEXT("�Q�[�����C���e�X�g�f�X�g���N�^\n"));
	}


	using UP_GameMainTest = unique_ptr < GameMainTest >;


}	//namespace GAME


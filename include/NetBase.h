//=================================================================================================
//
// NetBase �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include <thread>
#include <mutex>
#include "Network.h"
#include "NetCommon.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//���b�N
	static mutex	g_mtx;			//�r������p�~���[�e�b�N�X
	#define LOCK	std::lock_guard < mutex > lock ( g_mtx )

	//�ڑ����
	enum NETWORK_STATE
	{
		NS_START,		//�J�n���
		NS_WAIT,		//�ҋ@���	
		NS_CONNECT,		//�ڑ���	
		NS_ACT,			//���C������
		NS_DISCONNECT,	//�ؒf��
		NS_SEND_ERROR,	//���M�G���[
		NS_DRECV_ERROR,	//��M�G���[
	};

	enum
	{
		FRAME_PER_SECOND = 60,
	};

	//�l�b�g���[�N��{
	class NetBase
	{
	//--------------------------------------------------
	//�X���b�h
	private:
		static thread		m_thread;		//�X���b�h
		static bool			m_bPermi;		//�X���b�h����
		static bool			m_bActive;		//�X���b�h�ғ����

	public:
		NetBase ();
		NetBase ( const NetBase & rhs ) = delete;
		~NetBase ();

//		static void ThreadFunc ();		//�X���b�h�֐�
#if 0
		virtual void StartThread ( std::function < void () > threadFunc );		//�X���b�h���J�n
#endif // 0
		virtual void End ();		//�X���b�h���I��

		//����Ԃ̎擾�ƕύX(���b�N�t)
		static const bool GetPermi () { LOCK; return m_bPermi; }
		static void SetPermi ( bool b ) { LOCK; m_bPermi = b; }

		//�ғ���Ԃ̎擾�ƕύX(���b�N�t)
		static const bool GetActive () { LOCK; return m_bActive; }
		static void SetActive( bool b ) { LOCK; m_bActive = b; }
		//---------------------------------------------

		//---------------------------------------------
		//�l�b�g���[�N
	private:
		//�ʐM���
		static NETWORK_STATE	m_netwrokState;

	public:
		//��Ԃ̎擾�ƕύX
		static const NETWORK_STATE GetState () { LOCK; return m_netwrokState; }
		static void SetState ( NETWORK_STATE state ) { LOCK; m_netwrokState = state; }

		//---------------------------------------------
		//���C��
	private:
		//���L������
		static bool			m_bInput;	//���̓t���O
		static NET_GAME_INPUT	m_netInput;	//�Q�[������
		static UINT			m_myFrame;	//�t���[������
		static UINT			m_netFrame;	//�t���[������

		//���C���X���b�h��������
		static tstring		m_nameMain;	//�N���C�A���g��

	public:

		//���̓t���O
		static bool GetInput () { LOCK; return m_bInput; }
		static void SetInput ( bool b ) { LOCK; m_bInput = b; }
		//�Q�[������
		static NET_GAME_INPUT GetNetInput () { LOCK; return m_netInput; }
		static void SetNetInput ( char buf[] );

		//�t���[������
		static void FrameAsyncWait ( UINT frame );
	};


}	//namespace GAME



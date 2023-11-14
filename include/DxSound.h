//=================================================================================================
//
// Direct Sound クラス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"		//DirectX共通
#include <mmsystem.h>
#include <mmeapi.h>
#include <mmreg.h>
#include <dsound.h>				//DirectSound
#include "HWnd.h"

#include <vector>
using namespace std;

//-------------------------------------------------------------------------------------------------
// ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "winmm.lib")

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//複数再生用に配列で保持し、ポインタを返す
	//サウンドバッファポインタ
	class LPDxSoundBuffer
	{
		vector < LPDIRECTSOUNDBUFFER >		m_vpSB;
		UINT	m_count;	//内部カウント
		bool	m_stop;		//停止フラグ
		LONG	m_vol;		//ボリューム

	public:
		LPDxSoundBuffer () : m_count ( 0 ), m_stop ( false ), m_vol ( DSBVOLUME_MAX )
		{
			m_vpSB.resize ( 1 );
		}
		LPDxSoundBuffer ( const LPDxSoundBuffer & rhs ) = delete;		//コピー禁止
		~LPDxSoundBuffer () {}

		void SetSoundBuffer ( LPDIRECTSOUND lpDxSound, DSBUFFERDESC* pDesc, char* pData );
		void SetSoundBufferEx ( UINT nBuf, LPDIRECTSOUND lpDxSound, DSBUFFERDESC* pDesc, char* pData );
		
		//再生
		//	dwReserved1		:０のみ
		//	dwPriority		:優先度
		//	dwFlags			:フラグ [ループ] DSBPLAY_LOOPING, 
		void Play ( DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags );
		void Stop ();

		void Move ();	//毎回の更新
	};

	using PP_DXSNDBUF = std::shared_ptr < LPDxSoundBuffer >;


	//------------------------------------------
	//	Direct Sound
	//------------------------------------------
	class DxSound
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_DxSound = std::unique_ptr < DxSound >;
		static P_DxSound	m_inst;
		DxSound ();
		DxSound ( const DxSound & obj ) = delete;
	public:
		~DxSound ();
		static void Create () { if ( ! m_inst ) { m_inst = P_DxSound ( new DxSound () ); } }
		static P_DxSound & instance () { return m_inst; }
	//--------------------------------------------------

	private:

		LPDIRECTSOUND			m_lpDS;			//DirectSoundインターフェース
//		IDirectSoundBuffer8*	m_lpDSBuffer;	//サウンドバッファ
//		LPDIRECTSOUNDBUFFER		m_lpDSBuffer;	//サウンドバッファ
//		IDirectSoundBuffer*		m_lpBuf;		//セカンダリバッファ

		//サウンドバッファを使用する数だけ確保する
//		vector < LPDIRECTSOUNDBUFFER >		m_vecSoundBuffer;

		//同時再生用に１種類に複数確保
//		vector < LPDxSoundBuffer * >	m_vLPDSB;
		vector < PP_DXSNDBUF >	mvpp_DXSNDBUF;

	public:
		void Load ();
		void Move ();

		//ファイルパスから
		//Waveファイルオープン関数
		bool OpenWaveFromFile ( LPTSTR filepath, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize );

		//メモリ上からWaveファイルをオープン
		//	HPSTR pchBuffer : 読込バッファ
		//	LONG memSize : 読込バッファサイズ
		bool OpenWaveFromMem ( HPSTR pchBuffer, LONG memSize, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize );
		
		//グローバルで事前に複数waveファイルを読込しておく
		void LoadWaveFromFile ( LPTSTR filepath );
		void LoadWaveFromMem ( HPSTR pchBuffer, LONG memSize );

		//同時再生バッファ数を指定
		void LoadWaveFromMemEx ( UINT nBuf, HPSTR pchBuffer, LONG memSize );


		//使用するときはIDを指定する
		void Play ( UINT id );
		void PlayLoop ( UINT id );
		void Stop ( UINT id );

	private:
		bool MMIO_Open ( LPCTSTR filepath, MMIOINFO& mmioInfo, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize );
		bool MMIOtoMem ( HMMIO hMmio, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize );
	};


}	//namespace GAME


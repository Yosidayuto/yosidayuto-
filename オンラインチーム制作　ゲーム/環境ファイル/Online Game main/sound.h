//=============================================================================
//
// 音の処理 [sound.h]
// Author : 俵谷 健太郎
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// サウンドクラス(オブジェクトクラス派生)
//*****************************************************************************
class CSound
{
public:
	CSound();												// コンストラクタ
	~CSound();												// デストラクタ
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,							// タイトルBGM
		SOUND_LABEL_BGM_LOAD,								// ロードBGM
		SOUND_LABEL_BGM_GAME,								// ゲームBGM
		SOUND_LABEL_BGM_RESULT,								// リザルトBGM
		SOUND_LABEL_SE_BUTTON,								// ボタンSE
		SOUND_LABEL_SE_CLEAN,								// 掃除SE
		SOUND_LABEL_SE_BYTE,								// 噛みつきSE
		SOUND_LABEL_SE_WINNER,								// 勝者SE
		SOUND_LABEL_MAX,
	} SOUND_LABEL;											// サウンドファイル

	HRESULT Init(HWND hWnd);								// 初期化処理
	void Uninit(void);										// 終了処理
	HRESULT Play(SOUND_LABEL label);						// セグメント再生
	void Stop(SOUND_LABEL label);							// セグメント停止(ラベル指定)
	void Stop(void);										// セグメント停止(全て)

private:
	typedef struct
	{
		char *pFilename;									// ファイル名
		int nCntLoop;										// ループカウント
	}PARAM;													// パラメータ構造体定義

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static PARAM m_aParam[SOUND_LABEL_MAX];					// 各音素材のパラメータ


};





#endif // !_SOUND_H_








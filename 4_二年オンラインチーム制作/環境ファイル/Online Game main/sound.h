//=============================================================================
//
// ���̏��� [sound.h]
// Author : �U�J �����Y
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �T�E���h�N���X(�I�u�W�F�N�g�N���X�h��)
//*****************************************************************************
class CSound
{
public:
	CSound();												// �R���X�g���N�^
	~CSound();												// �f�X�g���N�^
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,							// �^�C�g��BGM
		SOUND_LABEL_BGM_LOAD,								// ���[�hBGM
		SOUND_LABEL_BGM_GAME,								// �Q�[��BGM
		SOUND_LABEL_BGM_RESULT,								// ���U���gBGM
		SOUND_LABEL_SE_BUTTON,								// �{�^��SE
		SOUND_LABEL_SE_CLEAN,								// �|��SE
		SOUND_LABEL_SE_BYTE,								// ���݂�SE
		SOUND_LABEL_SE_WINNER,								// ����SE
		SOUND_LABEL_MAX,
	} SOUND_LABEL;											// �T�E���h�t�@�C��

	HRESULT Init(HWND hWnd);								// ����������
	void Uninit(void);										// �I������
	HRESULT Play(SOUND_LABEL label);						// �Z�O�����g�Đ�
	void Stop(SOUND_LABEL label);							// �Z�O�����g��~(���x���w��)
	void Stop(void);										// �Z�O�����g��~(�S��)

private:
	typedef struct
	{
		char *pFilename;									// �t�@�C����
		int nCntLoop;										// ���[�v�J�E���g
	}PARAM;													// �p�����[�^�\���̒�`

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static PARAM m_aParam[SOUND_LABEL_MAX];					// �e���f�ނ̃p�����[�^


};





#endif // !_SOUND_H_








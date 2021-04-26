//=============================================================================
//
// �� [sound.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <xaudio2.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�t�@�C��
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		//�^�C�g��BGM
		SOUND_LABEL_BGM_STAGE_1,		//�X�e�[�W�PBGM
		SOUND_LABEL_BGM_STAGE_2,		//�X�e�[�W�QBGM
		SOUND_LABEL_BGM_STAGE_3,		//�X�e�[�W�RBGM
		SOUND_LABEL_BGM_DECISION,		//���艹
		SOUND_LABEL_BGM_MESSAGE,		//�Z���t���o��Ƃ�
		SOUND_LABEL_BGM_TUTORIAL,		//�`���[�g���A�����o��Ƃ�
		SOUND_LABEL_BGM_REACHED,		//�I�u�W�F�N�g���w��̈ʒu�ɒu���ꂽ�Ƃ�
		SOUND_LABEL_BGM_SHOW_POSE,		//�|�[�Y�\����
		SOUND_LABEL_BGM_CHOICE,			//�|�[�Y�I����
		SOUND_LABEL_BGM_ERROR,			//�G���[��
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;
	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif
//=============================================================================
// �T�E���h���� [sound.h]
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�N���X
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();
	// �T�E���h�t�@�C��
	typedef enum
	{
		//BGM
		LABEL_BGM_TITLE = 0,	//�^�C�g��
		LABEL_BGM_SELECT,		//�Z���N�g
		LABEL_BGM_STAGE_1,		//�X�e�[�W�P
		LABEL_BGM_STAGE_2,		//�X�e�[�W�Q
		LABEL_BGM_STAGE_3,		//�X�e�[�W�R
		LABEL_BGM_BOSS_1,		//�{�X�P
		LABEL_BGM_BOSS_2,		//�{�X�Q
		LABEL_BGM_BOSS_3,		//�{�X�R
		LABEL_BGM_RANKING,		//�����L���O
		//SE
		LABEL_SE_CLICK,			//�N���b�N
		LABEL_SE_CANCEL,		//�L�����Z��
		LABEL_SE_START,			//�X�^�[�g
		LABEL_SE_SHOTS,			//�V���b�g
		LABEL_SE_LASER,			//���[�U�[
		LABEL_SE_HOMING,		//�z�[�~���O
		LABEL_SE_DIE,			//���񂾂Ƃ��i�܂��j
		LABEL_SE_WARNING,		//���[�j���O
		LABEL_SE_BOSS_DIE_1,	//���񂾃{�X(1��3)
		LABEL_SE_BOSS_DIE_2,	//���񂾃{�X(2)
		LABEL_SE_RESULT,		//���U���g�t�@���t�@�[��
		LABEL_MAX,
	}LABEL;


	HRESULT	Init(HWND hWnd);			//����������
	void	Uninit(void);				//�I������
	HRESULT Play(LABEL label);			//�X�^�[�g����
	void	Stop(LABEL label);			//�X�g�b�v�����i�P�����j
	void	Stop(void);					//�X�g�b�v�����i�S���j
private:
	//�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//�ϐ�
	IXAudio2				*m_pXAudio2;					// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice	*m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice		*m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE					*m_apDataAudio[LABEL_MAX];		// �I�[�f�B�I�f�[�^
	DWORD					m_aSizeAudio[LABEL_MAX];		// �I�[�f�B�I�f�[�^�T�C�Y
		
	// �e���f�ނ̃p�����[�^
	typedef struct
	{
		char	*pFilename;	// �t�@�C����
		int		nCntLoop;	// ���[�v�J�E���g
	}PARAM;

	static PARAM m_aParam[LABEL_MAX];
};
#endif

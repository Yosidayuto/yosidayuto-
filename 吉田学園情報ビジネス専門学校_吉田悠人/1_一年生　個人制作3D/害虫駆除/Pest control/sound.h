//=============================================================================
// �T�E���h���� [sound.h]
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �X�^�[�g���
	SOUND_LABEL_BGM001,			// �`���[�g���A�����
	SOUND_LABEL_BGM002,			// �퓬���
	SOUND_LABEL_BGM003,			//�Q�[���N���A
	SOUND_LABEL_BGM004,			//�Q�[���I�[�o�[

	SOUND_LABEL_SE_SELECT,		//�I����a
	SOUND_LABEL_SE_DECIDED,		//���艹a
	SOUND_LABEL_SE_DAMAGE,		//�v���C���[�_���[�W
	SOUND_LABEL_SE_DAMAGEBOOS,	//���J�f�Ƀ_���[�W
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_ITEM,		//�A�C�e���擾��
	SOUND_LABEL_SE_MAGIC1,		//��U��
	SOUND_LABEL_SE_MAGIC2,		//���U��

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

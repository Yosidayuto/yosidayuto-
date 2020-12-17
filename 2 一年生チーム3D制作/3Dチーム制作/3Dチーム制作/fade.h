#pragma once
#ifndef _FADE_H
#define _FADE_H

/*�C���N���[�h�t�@�C��*/
#include"main.h"
/*�\����*/
typedef enum
{
	FADE_NONE = 0,		//�����Ȃ����
	FADE_IN,			//�t�F�[�h����
	FADE_OUT,			//�t�F�[�h�A�E�g����
	FADE_MAX
}FADE;
/*�v���g�^�C�v�錾*/
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdaFade(void);
void DrawFade(void);

void SetFade(MODE modeNext);


FADE GetFade(void);

#endif
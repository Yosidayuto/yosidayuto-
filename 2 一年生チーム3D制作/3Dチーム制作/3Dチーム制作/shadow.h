#pragma once
#ifndef  SHADOW_H
#define  SHADOW_H
#include"main.h"

#define SHADOW_SIZE (15)
#define MAX_SHADOW (100)
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXVECTOR3 rot;	//��]���
	D3DXMATRIX mtxWorld;//�s��v�Z
	bool use;			//�g�p����
}SHADOW;

/*�v���g�^�C�v�錾*/
void InitShadow(void);
void UninitShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos);
void DrawShadow(void);

#endif
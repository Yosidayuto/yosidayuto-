#pragma once
#ifndef  BOMB_H
#define  BOMB_H

#define BOMB_SION (50)

#define MAX_BOMB (128)//�X�R�A�p�l���̍ő吔
#include"main.h"
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nCntBomb;
}BOMB;

void InintBomb(void);
void UninitBomb(void);
void UpdateBomb(void);
void DrawBomb(void);
void SetBomb(D3DXVECTOR3 pos);
#endif
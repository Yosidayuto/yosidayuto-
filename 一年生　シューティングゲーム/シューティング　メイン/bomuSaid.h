#pragma once
#ifndef  BOMUSAID_H
#define  BOMUSAID_H

#define BOMUSAID_SION_Y (50)
#define BOMUSAID_SION_X (30)

#define MAX_BOMUSAID (3*4-1)//�X�R�A�p�l���̍ő吔
#include"main.h"
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nCntBomuSaid;
}BOMUSAID;

void InintBomuSaid(void);
void UninitBomuSaid(void);
void UpdateBomuSaid(void);
void DrawBomuSaid(void);
void SetBomuSaid(D3DXVECTOR3 pos);
#endif
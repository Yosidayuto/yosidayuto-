#pragma once
#ifndef  SCORE_H
#define  SCORE_H

#define SCORE_SION_Y (50)
#define SCORE_SION_X (10)
						
#define MAX_SCORE (3*4-1)//�X�R�A�p�l���̍ő吔
#include"main.h"
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nScoreCnt;
}SCORE;

void InintScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(D3DXVECTOR3 pos);
void ScoreUp(int Score);
#endif
#pragma once
#ifndef  SCORE_H
#define  SCORE_H

#define SCORE_SION_Y (50)
#define SCORE_SION_X (10)
						
#define MAX_SCORE (3*4-1)//スコアパネルの最大数
#include"main.h"
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;
	bool bUse;//使用しているかどうか
	int nScoreCnt;
}SCORE;

void InintScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(D3DXVECTOR3 pos);
void ScoreUp(int Score);
#endif
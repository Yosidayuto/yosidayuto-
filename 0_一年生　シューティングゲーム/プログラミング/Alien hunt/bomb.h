#pragma once
#ifndef  BOMB_H
#define  BOMB_H

#define BOMB_SION (50)

#define MAX_BOMB (128)//スコアパネルの最大数
#include"main.h"
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;
	bool bUse;//使用しているかどうか
	int nCntBomb;
}BOMB;

void InintBomb(void);
void UninitBomb(void);
void UpdateBomb(void);
void DrawBomb(void);
void SetBomb(D3DXVECTOR3 pos);
#endif
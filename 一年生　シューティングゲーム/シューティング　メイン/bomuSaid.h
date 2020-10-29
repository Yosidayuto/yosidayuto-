#pragma once
#ifndef  BOMUSAID_H
#define  BOMUSAID_H

#define BOMUSAID_SION_Y (50)
#define BOMUSAID_SION_X (30)

#define MAX_BOMUSAID (3*4-1)//スコアパネルの最大数
#include"main.h"
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;
	bool bUse;//使用しているかどうか
	int nCntBomuSaid;
}BOMUSAID;

void InintBomuSaid(void);
void UninitBomuSaid(void);
void UpdateBomuSaid(void);
void DrawBomuSaid(void);
void SetBomuSaid(D3DXVECTOR3 pos);
#endif
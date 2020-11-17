#ifndef  LIFE_H
#define  LIFE_H

#define LIFE_SION_Y (50)
#define LIFE_SION_X (30)

#define MAX_LIFE (5*4-1)//スコアパネルの最大数
#include"main.h"
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;
	bool bUse;//使用しているかどうか
	int nCntLife;
}LIFE;

void InintLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos);
#endif
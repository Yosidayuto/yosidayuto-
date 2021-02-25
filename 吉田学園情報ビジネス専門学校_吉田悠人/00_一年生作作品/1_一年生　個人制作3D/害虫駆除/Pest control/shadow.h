#pragma once
#ifndef  SHADOW_H_
#define  SHADOW_H_
#include"main.h"

#define SHADOW_SIZE (5)
#define MAX_SHADOW (100)
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXVECTOR3 rot;	//回転情報
	D3DXMATRIX mtxWorld;//行列計算
	bool use;			//使用判定
}SHADOW;

/*プロトタイプ宣言*/
void InitShadow(void);
void UninitShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos);
void DrawShadow(void);

#endif
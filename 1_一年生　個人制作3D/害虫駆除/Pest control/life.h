#pragma once
#ifndef  LIFE_H_
#define  LIFE_H_

#define LIFE1_SION_Y (60)
#define LIFE1_SION_X (300)

#define LIFE_SION (50)
#include"main.h"
/*構造体*/
typedef enum
{
	LIFE_TEXTURE_0 = 0,
	LIFE_TEXTURE_1,
	LIFE_TEXTURE_2,
	LIFE_TEXTURE_3,
	LIFE_TEXTURE_MAX,
}  LIFE_TEXTURE;
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;	//回転情報
	D3DXMATRIX mtxWorld;//行列計算
	bool bUse;//使用しているかどうか

}LIFE;

void InintLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

#endif
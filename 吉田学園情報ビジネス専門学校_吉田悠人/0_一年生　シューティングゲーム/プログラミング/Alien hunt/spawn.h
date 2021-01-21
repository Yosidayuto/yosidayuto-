#pragma once
#pragma once
#ifndef _SPAWN_H_
#define _SPAWN_H_
#define MOVE_SPAWN (0.5f)
#define SPAWN_SIZE (50)
#define MAX_SPAWN (128)	
#include"main.h"
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	bool bUse;										//使用されているか
}SPAWN;



/*プロトタイプ宣言*/
void InitSpawn(void);
void UninitSpawn(void);
void UpdateSpawn(void);
void DrawWpawn(void);
void SetWpawn(D3DXVECTOR3 pos);
#endif

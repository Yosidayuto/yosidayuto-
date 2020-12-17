#pragma once
#ifndef  WALL_H
#define  WALL_H
#include"main.h"
#define MAX_WALL (100)
#define WALL_X (500)
#define WALL_Y (100)

/*構造体*/

typedef enum
{/*呼び出すテクスチャの数*/
	WALL_TEXTURE_0 = 0,
	WALL_TEXTURE_1,
	WALL_TEXTURE_MAX,
}  WALL_TEXTURE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXVECTOR3 dir;	//回転情報
	D3DXMATRIX mtxWorld;//行列計算
	bool buse;			//使用判定
}WALL;

void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos);//位置と方向
void DrawWall(void);
#endif
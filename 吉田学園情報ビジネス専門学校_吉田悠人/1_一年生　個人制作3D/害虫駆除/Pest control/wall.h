#pragma once
#ifndef  WALL_H_
#define  WALL_H_
#include"main.h"
#define MAX_WALL (100)
#define WALL_X (500)
#define WALL_Y (300)

/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報

	D3DXVECTOR3 dir;	//回転情報

	D3DXMATRIX mtxWorld;//行列計算


	bool use;			//使用判定
}WALL;

void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 dir);//位置と方向
void DrawWall(void);
#endif
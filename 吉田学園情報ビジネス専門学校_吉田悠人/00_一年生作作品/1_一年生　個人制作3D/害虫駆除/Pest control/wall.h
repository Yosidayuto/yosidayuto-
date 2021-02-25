#pragma once
#ifndef  WALL_H_
#define  WALL_H_
#include"main.h"
#define MAX_WALL (100)
#define WALL_X (500)
#define WALL_Y (300)

/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���

	D3DXVECTOR3 dir;	//��]���

	D3DXMATRIX mtxWorld;//�s��v�Z


	bool use;			//�g�p����
}WALL;

void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 dir);//�ʒu�ƕ���
void DrawWall(void);
#endif
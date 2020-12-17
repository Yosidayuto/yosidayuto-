#pragma once
#ifndef  WALL_H
#define  WALL_H
#include"main.h"
#define MAX_WALL (100)
#define WALL_X (500)
#define WALL_Y (100)

/*�\����*/

typedef enum
{/*�Ăяo���e�N�X�`���̐�*/
	WALL_TEXTURE_0 = 0,
	WALL_TEXTURE_1,
	WALL_TEXTURE_MAX,
}  WALL_TEXTURE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXVECTOR3 dir;	//��]���
	D3DXMATRIX mtxWorld;//�s��v�Z
	bool buse;			//�g�p����
}WALL;

void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos);//�ʒu�ƕ���
void DrawWall(void);
#endif
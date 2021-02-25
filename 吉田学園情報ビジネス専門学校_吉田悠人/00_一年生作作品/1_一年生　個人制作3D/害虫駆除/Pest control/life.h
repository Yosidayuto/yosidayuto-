#pragma once
#ifndef  LIFE_H_
#define  LIFE_H_

#define LIFE1_SION_Y (60)
#define LIFE1_SION_X (300)

#define LIFE_SION (50)
#include"main.h"
/*�\����*/
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
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;	//��]���
	D3DXMATRIX mtxWorld;//�s��v�Z
	bool bUse;//�g�p���Ă��邩�ǂ���

}LIFE;

void InintLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

#endif
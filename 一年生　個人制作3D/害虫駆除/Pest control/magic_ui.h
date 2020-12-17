#pragma once
#ifndef  MAGIC_UI_H_
#define  MAGIC_UI_H_

#define MAGIC_UI_SION 200
#define MAGIC_UI_SION2 75
#define MAGIC_UI_SION_WATER 130
#define MAGIC_UI_SION_FIRE 100
#define MAGIC_UI_SION_GRASS 110
#define MAGIC_UI_SION_SRAR 100

#include"main.h"
/*�\����*/
typedef enum
{
	MAGIC_UI_TEXTURE_0 = 0,
	MAGIC_UI_TEXTURE_1,
	MAGIC_UI_TEXTURE_2,
	MAGIC_UI_TEXTURE_3,
	MAGIC_UI_TEXTURE_4,
	MAGIC_UI_TEXTURE_5,
	MAGIC_UI_TEXTURE_6,
	MAGIC_UI_TEXTURE_7,
	MAGIC_UI_TEXTURE_8,
	MAGIC_UI_TEXTURE_MAX,
}  MAGIC_UI_TEXTURE;
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;	//��]���
	D3DXMATRIX mtxWorld;//�s��v�Z
	bool bUse;//�g�p���Ă��邩�ǂ���
}MAGIC_UI;
typedef struct
{
	int Number[4];
}MAGIC_NUMBER;

void InintMafic_Ui(void);
void UninitMafic_Ui(void);
void UpdateMafic_Ui(void);
void DrawMafic_Ui(void);
void Magic_Number(int Magic_Number, int Magic);
MAGIC_NUMBER*GetMagic_Number();
#endif
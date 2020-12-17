#pragma once
#ifndef  ITEM_H_
#define  ITEM_H_
#include"main.h"
#define ITEM_SIZE (20)
#define MAX_ITEM (100)
/*�\����*/
typedef enum
{
	TITLE_TYPE_0 = 0,
	TITLE_TYPE_1,
	TITLE_TYPE_2,
	TITLE_TYPE_3,
	TITLE_TYPE_MAX,
} ITEM_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXVECTOR3 dir;	//��]���
	D3DXMATRIX mtxWorld;//�s��v�Z
	int nType;			//�A�C�e���̎��
	bool use;			//�g�p����
}ITEM;

/*�v���g�^�C�v�錾*/
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void SetItem(D3DXVECTOR3 pos,int nType);
void DrawItem(void);
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
#endif
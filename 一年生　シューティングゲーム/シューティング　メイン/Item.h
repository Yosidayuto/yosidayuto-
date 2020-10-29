#pragma once
#ifndef _ITEM_H
#define _ITEM_H

/*�C���N���[�h�t�@�C��*/
#include"main.h"

#define MAX_ITEM_SIZ (50)

/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�J���[
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}ITEM;

/*�v���g�^�C�v�錾*/
void InitItem(void);
void UninitItem(void);
void UpdaItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos,D3DXVECTOR3 move/*�ړ���*/, D3DXCOLOR col);



#endif

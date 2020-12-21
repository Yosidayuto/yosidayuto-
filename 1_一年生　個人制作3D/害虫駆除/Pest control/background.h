#pragma once
#ifndef  BACKGROUND_H_
#define  BACKGROUND_H_

#include"main.h"
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXVECTOR3 rot;	//��]���
	D3DXVECTOR3 size;	//�T�C�Y���
	D3DXMATRIX mtxWorld;//�s��v�Z�p
	LPD3DXMESH pMeshBlock;//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatBlock;//�}�e���A�����ւ̃|�C���^
	DWORD nNumMatBlock;//�}�e���A���̐�
	bool bsed;			//�g�p����
}BACKGROUND;
/*�v���g�^�C�v�錾*/
void InitBackground(void);
void UninitBackground(void);
void UpdateBackground(void);
void DrawBackground(void);
void SetBackground(D3DXVECTOR3 pos);

#endif
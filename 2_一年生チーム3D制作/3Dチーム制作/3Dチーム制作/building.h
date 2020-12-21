#pragma once
#ifndef  BUILDING_H_
#define  BUILDING_H_

#include"main.h"
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXVECTOR3 rot;	//��]���
	D3DXVECTOR3 size;	//�T�C�Y���

	D3DXMATRIX mtxWorld;//�s��v�Z�p
	LPD3DXMESH pMeshBuilding;//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatBuilding;//�}�e���A�����ւ̃|�C���^
	DWORD nNumMatBuilding;//�}�e���A���̐�

	bool used;			//�g�p����
}BUILDING;
/*�v���g�^�C�v�錾*/
void InitBuilding(void);
void UninitBuilding(void);
void UpdateBuilding(void);
void DrawBuilding(void);
void SetBuilding(D3DXVECTOR3 pos, D3DXVECTOR3 size);
bool CollisionBuilding(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif
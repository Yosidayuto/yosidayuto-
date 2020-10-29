#ifndef  GOAl_H
#define  GOAl_H

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
	bool buse;			//�g�p����
}GOAl;
/*�v���g�^�C�v�錾*/
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif
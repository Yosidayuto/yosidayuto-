#ifndef  BLOCK_H_
#define  BLOCK_H_

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
	bool used;			//�g�p����
}BLOCK;
/*�v���g�^�C�v�錾*/
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif
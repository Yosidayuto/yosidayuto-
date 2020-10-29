#ifndef  BLOCK_H
#define  BLOCK_H

#include"main.h"

#define MAX_BLOCK (100)
/*�\����*/
typedef struct
{
	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
}SEARCH_BOX;
typedef struct
{
	D3DXVECTOR3			pos;			//�ʒu���
	D3DXVECTOR3			posold;			//�ʒu�̌Â����
	D3DXVECTOR3			rot;			//��]���
	D3DXVECTOR3			size;			//�T�C�Y���

	D3DXMATRIX			mtxWorld;		//�s��v�Z�p
	LPD3DXMESH			pMeshBlock;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		pBuffMatBlock;	//�}�e���A�����ւ̃|�C���^
	DWORD				nNumMatBlock;	//�}�e���A���̐�
	SEARCH_BOX			box;
	bool				used;			//�g�p����
}BLOCK;
/*�v���g�^�C�v�錾*/
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool CollisionBlockEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool ColRayBox(D3DXVECTOR3* pos, D3DXVECTOR3* dir, SEARCH_BOX* border, D3DXMATRIX* mat, float& output, D3DXVECTOR3* colPos = 0);
BLOCK*GetBlock();
#endif
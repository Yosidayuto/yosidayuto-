
#pragma once
#ifndef  MESHFIELD2_H
#define  MESHFIELD2_H

#include"main.h"

#define MESHFIE2L_X_BLOCK 8				//X�����̃u���b�N��
#define MESHFIEL2_Y_BLOCK 10			//Y�����̃u���b�N��
#define MESHFIEL2_VERTEX_NUM ((MESHFIE2L_X_BLOCK+1)*(MESHFIEL2_Y_BLOCK+1))									//���_
#define MESHFIEL2_INDEX_NUM (((((MESHFIE2L_X_BLOCK-1)*2)+4)*MESHFIEL2_Y_BLOCK)+(2*(MESHFIEL2_Y_BLOCK-1)))	//�C���f�b�N�X
#define MESHFIEL2_PRIMITIVE_NUM (MESHFIE2L_X_BLOCK*MESHFIEL2_Y_BLOCK*2)+((MESHFIEL2_Y_BLOCK-1)*4)			//�|���S��

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu���
	D3DXVECTOR3 rot;//�������
	bool bUse;
	D3DXMATRIX mtxWorld;//�s��v�Z�p
	LPDIRECT3DTEXTURE9 g_pTextureMeshField2;//���b�V���t�B�[���h�̃e�N�X�`��
	LPD3DXMESH pMeshMeshField2;//���b�V�����ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField2;//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuffMeshField2;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	DWORD nNumMatMeshField2;//�}�e���A�����̐�
}MESHFIELD2;

/*�v���g�^�C�v�錾*/
void InitMeshField2(void);
void UninitMeshField2(void);
void UpdateMeshField2(void);
void DrawMeshField2(void);

void SetMeshField2(D3DXVECTOR3 pos);

#endif
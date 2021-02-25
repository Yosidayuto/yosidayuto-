#include "main.h"
#include "meshfield.h"

#define MAX_SIZE 100
//�O���[�o���ϐ�
/*���b�V���t�B�[���h�̃e�N�X�`��*/
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;
/*�C���f�b�N�X�o�b�t�@�ւ̃|�C���g*/
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
/*�|���S���̈ʒu*/
D3DXVECTOR3 g_posMeshField;
/*�|���S���̌���*/
D3DXVECTOR3 g_rotMeshField;
/*�|���S���̃��[���h�}�g���b�N�X*/
D3DXMATRIX g_mtxWorldMeshField;

void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIEL_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);
	VERTEX_3D*pVtx = NULL;
	/*���_�o�b�t�@�̐����i���O�p�`�͈ӎ����Ȃ��j*/
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	/*���_���W�̐ݒ�*/
	pVtx[0].pos = D3DXVECTOR3(-MAX_SIZE / 2	, 2, MAX_SIZE / 2);
	pVtx[1].pos = D3DXVECTOR3(0				, 2, MAX_SIZE / 2);
	pVtx[2].pos = D3DXVECTOR3(MAX_SIZE / 2	, 2, MAX_SIZE / 2);
	pVtx[3].pos = D3DXVECTOR3(-MAX_SIZE / 2	, 2, 0 / 2);
	pVtx[4].pos = D3DXVECTOR3(0				, 2, 0 / 2);
	pVtx[5].pos = D3DXVECTOR3(MAX_SIZE / 2	, 2, 0 / 2);
	pVtx[6].pos = D3DXVECTOR3(-MAX_SIZE / 2	, 2, -MAX_SIZE / 2);
	pVtx[7].pos = D3DXVECTOR3(0				, 2, -MAX_SIZE / 2);
	pVtx[8].pos = D3DXVECTOR3(MAX_SIZE / 2	, 2, -MAX_SIZE / 2);
	/*�e���_�̖@���̐ݒ�i�x�N�g���̑傫���͂P�ɂ���K�v������j*/
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	/*���_�J���[�̐ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	/*�e�N�X�`��*/
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0);
	pVtx[2].tex = D3DXVECTOR2(1, 0);
	pVtx[3].tex = D3DXVECTOR2(0, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0, 1);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1);
	pVtx[8].tex = D3DXVECTOR2(1, 1);
	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffMeshField->Unlock();
	/*�e�N�X�`���̐ݒ�*/
	D3DXCreateTextureFromFile(pDevice, "data/image/NRR2016150966_1[1].jpg", &g_pTextureMeshField);
	/*�C���f�b�N�X�o�b�t�@�i�|���S���o�b�t�@�j�̐���*/
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIEL_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);
	/*�C���f�b�N�X�o�b�t�@�����b�N*/
	WORD*pldx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pldx, 0);
	/*�C���f�b�N�X�w��*/
	pldx[0] = 3;
	pldx[1] = 0;
	pldx[2] = 4;
	/*--------*/
	pldx[3] = 1;
	pldx[4] = 5;
	pldx[5] = 2;
	/*--------*/
	pldx[6] = 2;
	pldx[7] = 6;
	/*--------*/
	pldx[8] = 6;
	pldx[9] = 3;
	pldx[10] = 7;
	/*--------*/
	pldx[11] = 4;
	pldx[12] = 8;
	pldx[13] = 5;
	/*--------*/
	
	g_pIdxBuffMeshField->Unlock();
}
void UninitMeshField(void)
{
	/*���_�o�b�t�@�̉��*/
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}
void UpdateMeshField(void)
{

}
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*���[���h�}�g���N�X�̏���������*/
	D3DXMatrixIdentity(&g_mtxWorldMeshField);
	/*�����𔽉f*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);
	/*�ʒu�𔽉f*/
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);
	/*���[���h�}�g���N�X�̐ݒ�*/
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);
	/*�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�*/
	pDevice->SetIndices(g_pIdxBuffMeshField);
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�*/
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_3D);
	/*�e�N�X�`���̕`��*/
	pDevice->SetTexture(0, g_pTextureMeshField);
	/*�|���S���`��*/
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIEL_VERTEX_NUM,0, MESHFIEL_PRIMITIVE_NUM);


	pDevice->SetTexture(0, NULL);
}

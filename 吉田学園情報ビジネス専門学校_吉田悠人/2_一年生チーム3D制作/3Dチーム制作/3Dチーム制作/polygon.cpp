#include "main.h"
#include "polygon.h"
//�O���[�o���ϐ�
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
/*�|���S���̈ʒu*/
D3DXVECTOR3 g_posPolygon;
/*�|���S���̌���*/
D3DXVECTOR3 g_rotPolygon;
/*�|���S���̃��[���h�}�g���b�N�X*/
D3DXMATRIX g_mtxWorldPolygon;
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*���_�o�b�t�@�̐���*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);
	VERTEX_3D*pVtx = NULL;
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	/*���_���W�̐ݒ�*/
	pVtx[0].pos = D3DXVECTOR3(-POLYGONX /2, 0, POLYGONZ /2);
	pVtx[1].pos = D3DXVECTOR3(POLYGONX /2, 0, POLYGONZ /2);
	pVtx[2].pos = D3DXVECTOR3(-POLYGONX /2, 0, -POLYGONZ /2);
	pVtx[3].pos = D3DXVECTOR3(POLYGONX /2, 0, -POLYGONZ /2);
	/*�e���_�̖@���̐ݒ�i�x�N�g���̑傫���͂P�ɂ���K�v������j*/
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	/*���_�J���[�̐ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffPolygon->Unlock();
}
void UninitPolygon(void)
{
	
	/*���_�o�b�t�@�̉��*/
	if(g_pVtxBuffPolygon!=NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}
void UpdatePolygon(void)
{
	
	g_posPolygon = D3DXVECTOR3(0, 0, 0);
}
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�s��v�Z�p�̃}�g���N�X
	/*���[���h�}�g���N�X�̏���������*/
	D3DXMatrixIdentity(&g_mtxWorldPolygon);
	/*�����𔽉f*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);
	/*�ʒu�𔽉f*/
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);
	/*���[���h�}�g���N�X�̐ݒ�*/
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�*/
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_3D);
	/*�|���S���̕`��*/
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
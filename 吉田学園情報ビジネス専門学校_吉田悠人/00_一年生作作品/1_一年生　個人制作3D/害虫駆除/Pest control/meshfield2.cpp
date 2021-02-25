#include "main.h"
#include "meshfield2.h"

#define MAX_SIZE 100
//�O���[�o���ϐ�
/*���b�V���t�B�[���h�̃e�N�X�`��*/
LPDIRECT3DTEXTURE9 g_pTextureMeshField2 = NULL;
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField2 = NULL;
/*�C���f�b�N�X�o�b�t�@�ւ̃|�C���g*/
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField2 = NULL;
/*�|���S���̈ʒu*/
D3DXVECTOR3 g_posMeshField2;
/*�|���S���̌���*/
D3DXVECTOR3 g_rotMeshField2;
/*�|���S���̃��[���h�}�g���b�N�X*/
D3DXMATRIX g_mtxWorldMeshField2;

void InitMeshField2(void)
{
	
	g_posMeshField2 = D3DXVECTOR3(0,30, 0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIEL2_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField2,
		NULL);
	VERTEX_3D*pVtx = NULL;
	/*���_�o�b�t�@�̐����i���O�p�`�͈ӎ����Ȃ��j*/
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffMeshField2->Lock(0, 0, (void**)&pVtx, 0);
	/*���_���W�̐ݒ�*/
	float fTexpos=0;
	int nIndex = 0;

	for (int vIndex = 0; vIndex < MESHFIEL2_Y_BLOCK +1; vIndex++)
	{
		fTexpos = 0;
		for (int hlndex = 0; hlndex < MESHFIE2L_X_BLOCK + 1; hlndex++)
		{
			
			/*���W*/
			float angle = (float)hlndex * 45;
			pVtx[nIndex].pos= D3DXVECTOR3(sinf(D3DXToRadian(-angle))*(MAX_SIZE/2)+ g_posMeshField2.x,
										-vIndex*(MAX_SIZE / 2)+ g_posMeshField2.y,
										cosf(D3DXToRadian(-angle))*(MAX_SIZE / 2)+ g_posMeshField2.z);
			/*�e���_�̖@���̐ݒ�i�x�N�g���̑傫���͂P�ɂ���K�v������j*/
			pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			D3DXVECTOR3 g_rotMeshField2;
			D3DXVec3Normalize(&g_rotMeshField2, &g_rotMeshField2);
			/*���_�J���[�̐ݒ�*/
			pVtx[nIndex].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			/*�e�N�X�`��*/
			pVtx[nIndex].tex = D3DXVECTOR2(fTexpos*0.125f, (float)vIndex);
			nIndex += 1;
			fTexpos += 1;
		}
	}
	

	


	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffMeshField2->Unlock();
	/*�e�N�X�`���̐ݒ�*/
	D3DXCreateTextureFromFile(pDevice, "data/image/NRR2016150966_1[1].jpg", &g_pTextureMeshField2);
	/*�C���f�b�N�X�o�b�t�@�i�|���S���o�b�t�@�j�̐���*/
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIEL2_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField2,
		NULL);
	/*�C���f�b�N�X�o�b�t�@�����b�N*/
	WORD*pldx;
	g_pIdxBuffMeshField2->Lock(0, 0, (void**)&pldx, 0);
	int ncunt=9;
	for(int npldx=0;npldx<17; npldx++)
	{
	
			/*�C���f�b�N�X�w��*/
			pldx[npldx] = ncunt;
			if (ncunt >= 9)
			{
				ncunt -=9;
			}
			else if(ncunt<9)
			{
				ncunt += 10;
			}
		
	}

	g_pIdxBuffMeshField2->Unlock();
}
void UninitMeshField2(void)
{
	/*���_�o�b�t�@�̉��*/
	if (g_pVtxBuffMeshField2 != NULL)
	{
		g_pVtxBuffMeshField2->Release();
		g_pVtxBuffMeshField2 = NULL;
	}
	if (g_pTextureMeshField2 != NULL)
	{
		g_pTextureMeshField2->Release();
		g_pTextureMeshField2 = NULL;
	}
	if (g_pIdxBuffMeshField2 != NULL)
	{
		g_pIdxBuffMeshField2->Release();
		g_pIdxBuffMeshField2 = NULL;
	}
}
void UpdateMeshField2(void)
{

}
void DrawMeshField2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*���[���h�}�g���N�X�̏���������*/
	D3DXMatrixIdentity(&g_mtxWorldMeshField2);
	/*�����𔽉f*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField2.y, g_rotMeshField2.x, g_rotMeshField2.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField2, &g_mtxWorldMeshField2, &mtxRot);
	/*�ʒu�𔽉f*/
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField2.x, g_posMeshField2.y, g_posMeshField2.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField2, &g_mtxWorldMeshField2, &mtxTrans);
	/*���[���h�}�g���N�X�̐ݒ�*/
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField2);
	/*�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�*/
	pDevice->SetIndices(g_pIdxBuffMeshField2);
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�*/
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField2, 0, sizeof(VERTEX_3D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_3D);
	/*�e�N�X�`���̕`��*/
	pDevice->SetTexture(0, g_pTextureMeshField2);
	/*�|���S���`��*/
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIEL2_VERTEX_NUM, 0, MESHFIEL2_PRIMITIVE_NUM);


	pDevice->SetTexture(0, NULL);
}

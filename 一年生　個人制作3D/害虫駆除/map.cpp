#include"map.h"
#include"model.h"
/*--�O���[�o���ϐ�--*/
/*���f�����*/
D3DXMATERIAL *pMat;
/*�p�[�c�Q�̍\����*/
MAP g_Map;

/*----------------*/


void InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	
		/*X�t�@�C���̓ǂݍ���*/
		D3DXLoadMeshFromX(
			"deta/Xfile/Stage.x",
			D3DXMESH_MANAGED,
			pDevice,
			NULL,
			&g_Map.BuffMat,
			NULL,
			&g_Map.NumMat,
			&g_Map.Mesh);

		/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
		pMat = (D3DXMATERIAL*)g_Map.BuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Map.NumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_Map.pTexture[nCntMat]);
			}
		}

	/*��������*/
	g_Map.rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	/*�����ʒu*/
	g_Map.pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}
void UninitMap(void)
{
	
		/*���b�V���̔j��*/
		if (g_Map.Mesh != NULL)
		{
			g_Map.Mesh->Release();
			g_Map.Mesh = NULL;
		}

		/*�}�e���A���̔j��*/
		if (g_Map.BuffMat != NULL)
		{	
			g_Map.BuffMat->Release();
			g_Map.BuffMat = NULL;
		}
		/*�e�N�X�`��*/
		for (int nCntMat = 0; nCntMat < (int)g_Map.NumMat; nCntMat++)
		{
			if (g_Map.pTexture[nCntMat] != NULL)
			{
				g_Map.pTexture[nCntMat]->Release();
				g_Map.pTexture[nCntMat] = NULL;
			}
		}
	


}
void UpdateMap(void)
{
	
	
}
void DrawMap(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	int nCntMat;
	/*���[���h�}�g���N�X�̏���������*/
	D3DXMatrixIdentity(&g_Map.mtxWorld);
	/*�����𔽉f*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Map.rot.y, g_Map.rot.x, g_Map.rot.z);
	D3DXMatrixMultiply(&g_Map.mtxWorld, &g_Map.mtxWorld, &mtxRot);
	/*�ʒu�𔽉f*/
	D3DXMatrixTranslation(&mtxTrans, g_Map.pos.x, g_Map.pos.y, g_Map.pos.z);
	D3DXMatrixMultiply(&g_Map.mtxWorld, &g_Map.mtxWorld, &mtxTrans);
	/*���[���h�}�g���b�N�X�̐ݒ�*/
	pDevice->SetTransform(D3DTS_WORLD, &g_Map.mtxWorld);
	/*���݂̃}�e���A�����擾����*/
	pDevice->GetMaterial(&matDef);
	for (nCntMat = 0; nCntMat < (int)g_Map.NumMat; nCntMat++)
	{
		/*�}�e���A���̐ݒ�*/
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, g_Map.pTexture[nCntMat]);
		/*���f���̕`��*/
		g_Map.Mesh->DrawSubset(nCntMat);
	}
	/*�ێ����Ă����}�e���A����߂�*/
	pDevice->SetMaterial(&matDef);
	
}
MAP*GetMap()
{
	return &g_Map;
}
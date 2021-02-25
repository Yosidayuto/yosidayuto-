#include "main.h"
#include "background.h"
/*--�O���[�o���ϐ�--*/
/*�|���S���̃e�N�X�`��*/
LPDIRECT3DTEXTURE9 g_textureBackground;
/*�|���S���̃��[���h�}�g���b�N�X*/
D3DXMATRIX g_mtxWorldBackground;
/*�}�e���A���f�[�^�ւ̃|�C���^*/
D3DXMATERIAL *pMatBackground;/*���f�����*/
BACKGROUND g_Background;

void InitBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
		/*X�t�@�C���̓ǂݍ���*/
		D3DXLoadMeshFromX(
			"data/Xfile/blue sky.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Background.pBuffMatBlock,
			NULL,
			&g_Background.nNumMatBlock,
			&g_Background.pMeshBlock);
		/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
		pMatBackground = (D3DXMATERIAL*)g_Background.pBuffMatBlock->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Background.nNumMatBlock; nCntMat++)
		{
			if (pMatBackground[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMatBackground[nCntMat].pTextureFilename, &g_textureBackground);
			}
		}		
		/*�����ʒu*/
		g_Background.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
void UninitBackground(void)
{
		/*���b�V���̔j��*/
		if (g_Background.pMeshBlock != NULL)
		{
			g_Background.pMeshBlock->Release();
			g_Background.pMeshBlock = NULL;
		}

		/*�}�e���A���̔j��*/
		if (g_Background.pBuffMatBlock != NULL)
		{
			g_Background.pBuffMatBlock->Release();
			g_Background.pBuffMatBlock = NULL;
		}
		/*�e�N�X�`��*/
		for (int nCnt = 0; nCnt < (int)g_Background.nNumMatBlock; nCnt++)
		{
			if (g_textureBackground != NULL)
			{
				g_textureBackground->Release();
				g_textureBackground = NULL;
			}
		}
}
void UpdateBackground(void)
{

}
void DrawBackground(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	
		/*���[���h�}�g���N�X�̏���������*/
		D3DXMatrixIdentity(&g_Background.mtxWorld);
		/*�����𔽉f*/
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Background.rot.y, g_Background.rot.x, g_Background.rot.z);
		D3DXMatrixMultiply(&g_Background.mtxWorld, &g_Background.mtxWorld, &mtxRot);
		/*�ʒu�𔽉f*/
		D3DXMatrixTranslation(&mtxTrans, g_Background.pos.x, g_Background.pos.y, g_Background.pos.z);
		D3DXMatrixMultiply(&g_Background.mtxWorld, &g_Background.mtxWorld, &mtxTrans);
		/*���[���h�}�g���b�N�X�̐ݒ�*/
		pDevice->SetTransform(D3DTS_WORLD, &g_Background.mtxWorld);
		/*���݂̃}�e���A�����擾����*/
		pDevice->GetMaterial(&matDef);


		for (int nCntMat = 0; nCntMat < (int)g_Background.nNumMatBlock; nCntMat++)
		{
			/*�}�e���A���̐ݒ�*/
			pDevice->SetMaterial(&pMatBackground[nCntMat].MatD3D);

			pDevice->SetTexture(0, g_textureBackground);

			/*���f���p�[�c�̕`��*/
			g_Background.pMeshBlock->DrawSubset(nCntMat);

		}
		/*�ێ����Ă����}�e���A����߂�*/
		pDevice->SetMaterial(&matDef);
}
void SetBackground(D3DXVECTOR3 pos)
{
	
		if (g_Background.bsed == false)
		{
			g_Background.pos = pos;
			g_Background.bsed = true;
		}
	
}
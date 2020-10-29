
#include "goal.h"
#include "model.h"
#include "fade.h"
#include "score.h"
#include"meshfield2.h"
#define MAX_GOAL (10)
/*--�O���[�o���ϐ�--*/
/*�|���S���̃e�N�X�`��*/
LPDIRECT3DTEXTURE9 g_pTextureGoal[256];
/*�|���S���̃��[���h�}�g���b�N�X*/
D3DXMATRIX g_mtxWorldGoal;
/*�}�e���A���f�[�^�ւ̃|�C���^*/
D3DXMATERIAL *pMatGoal;/*���f�����*/
GOAl g_Goal[MAX_GOAL];
bool g_score;
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nGoal = 0; nGoal < MAX_GOAL; nGoal++)
	{
		/*X�t�@�C���̓ǂݍ���*/
		D3DXLoadMeshFromX(
			"X�t�@�C��/�u���b�N.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Goal[nGoal].pBuffMatBlock,
			NULL,
			&g_Goal[nGoal].nNumMatBlock,
			&g_Goal[nGoal].pMeshBlock);
		/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
		pMatGoal = (D3DXMATERIAL*)g_Goal[nGoal].pBuffMatBlock->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Goal[nGoal].nNumMatBlock; nCntMat++)
		{
			if (pMatGoal[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMatGoal[nCntMat].pTextureFilename, &g_pTextureGoal[nCntMat]);
			}
		}

		/*�����ʒu*/
		g_Goal[nGoal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Goal[nGoal].buse = false;
		/*�����T�C�Y*/
		g_Goal[nGoal].size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		g_score = false;
	}
}
void UninitGoal(void)
{
	for (int nGoal = 0; nGoal < MAX_GOAL; nGoal++)
	{
		/*���b�V���̔j��*/
		if (g_Goal[nGoal].pMeshBlock != NULL)
		{
			g_Goal[nGoal].pMeshBlock->Release();
			g_Goal[nGoal].pMeshBlock = NULL;
		}

		/*�}�e���A���̔j��*/
		if (g_Goal[nGoal].pBuffMatBlock != NULL)
		{
			g_Goal[nGoal].pBuffMatBlock->Release();
			g_Goal[nGoal].pBuffMatBlock = NULL;
		}
		/*�e�N�X�`��*/
		for (int nCnt = 0; nCnt < (int)g_Goal[nGoal].nNumMatBlock; nCnt++)
		{
			if (g_pTextureGoal[nCnt] != NULL)
			{
				g_pTextureGoal[nCnt]->Release();
				g_pTextureGoal[nCnt] = NULL;
			}
		}

	}

}
void UpdateGoal(void)
{
	PLAYER *pPlayer = GetPlayer();
	ITEM *pItem = GetItem();
	for (int nGoal = 0; nGoal < MAX_GOAL; nGoal++)
	{
		if (g_Goal[nGoal].buse)//�S�[�������邩
		{
			/*�S�[���̓����蔻��*/
			if (g_Goal[nGoal].pos.x + 30 >= pPlayer->pos.x
				&&g_Goal[nGoal].pos.x - 30 <= pPlayer->pos.x
				&&g_Goal[nGoal].pos.y + 30 >= pPlayer->pos.y
				&&g_Goal[nGoal].pos.y - 30 <= pPlayer->pos.y
				&&g_Goal[nGoal].pos.z + 30 >= pPlayer->pos.z
				&&g_Goal[nGoal].pos.z - 30 <= pPlayer->pos.z)
			{
				if (!g_score)//��������x���o���Ȃ�����
				{
					if (pPlayer->bGoal == true)//�ړI�̃A�C�e���������Ă��邩
					{
						for (int nItem = 0; nItem < MAX_ITEM; nItem++)
						{
							for (int nItemTtpe = 0; nItemTtpe < TITLE_TYPE_MAX; nItemTtpe++)
							{//�A�C�e���̃X�R�A�𑗂�
								if (pPlayer->bItem[nItem][nItemTtpe])
								{
									AddScore(1, nItemTtpe+1);
									AddScore(pPlayer->nLife[nItem][nItemTtpe], nItemTtpe + 5);
								}
									
								
							}

						}
						
						SetFade(MODE_RESULE);//�t�F�[�h�A�E�g
						g_score = true;
					}
				}
				
			}
		}
	}
	
}
void DrawGoal(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	for (int nGoal = 0; nGoal < MAX_GOAL; nGoal++)
	{
		if (g_Goal[nGoal].buse)
		{
			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_Goal[nGoal].mtxWorld);
			/*�����𔽉f*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Goal[nGoal].rot.y, g_Goal[nGoal].rot.x, g_Goal[nGoal].rot.z);
			D3DXMatrixMultiply(&g_Goal[nGoal].mtxWorld, &g_Goal[nGoal].mtxWorld, &mtxRot);
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_Goal[nGoal].pos.x, g_Goal[nGoal].pos.y, g_Goal[nGoal].pos.z);
			D3DXMatrixMultiply(&g_Goal[nGoal].mtxWorld, &g_Goal[nGoal].mtxWorld, &mtxTrans);
			/*���[���h�}�g���b�N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Goal[nGoal].mtxWorld);
			/*���݂̃}�e���A�����擾����*/
			pDevice->GetMaterial(&matDef);


			for (int nCntMat = 0; nCntMat < (int)g_Goal[nGoal].nNumMatBlock; nCntMat++)
			{
				/*�}�e���A���̐ݒ�*/
				pDevice->SetMaterial(&pMatGoal[nCntMat].MatD3D);

				pDevice->SetTexture(0, g_pTextureGoal[nCntMat]);

				/*���f���p�[�c�̕`��*/
				g_Goal[nGoal].pMeshBlock->DrawSubset(nCntMat);

			}
			/*�ێ����Ă����}�e���A����߂�*/
			pDevice->SetMaterial(&matDef);
		}

	}



}
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nGoal = 0; nGoal < MAX_GOAL; nGoal++)
	{
		if (!g_Goal[nGoal].buse)
		{
			g_Goal[nGoal].pos = pos;	//�ʒu�ݒ�
			g_Goal[nGoal].size = size;	//�T�C�Y�ݒ�
			g_Goal[nGoal].buse = true;	//�g�p����
			SetMeshField2(D3DXVECTOR3(g_Goal[nGoal].pos.x, g_Goal[nGoal].pos.y, g_Goal[nGoal].pos.z));
			break;
		}
	}
}


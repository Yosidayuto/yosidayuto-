#include"main.h"
#include"item.h"
#include"model.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
/*���f�����*/
D3DXMATERIAL *pMatItem[TITLE_TYPE_MAX];
/*�A�C�e��*/
ITEM g_Item[MAX_ITEM];
/*�t�@�C���̓ǂݍ��ݏ���*/
typedef struct
{
	char *pFilename;	// �t�@�C����
}FILE_ITEM;
/*X�t�@�C���̎��*/
FILE_ITEM g_FileItem[TITLE_TYPE_MAX] =
{
	{ "X�t�@�C��/�i�{�[��.x" },	//���C���A�C�e��
	{ "X�t�@�C��/danbo-ru2.x" },	//�A�C�e����
	{ "X�t�@�C��/danbo-ru3.x" },	//�A�C�e����
	{ "X�t�@�C��/danbo-ru4.x" },	//�A�C�e����
};
void InitItem(void)
{
	VERTEX_3D*pVtx = NULL;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nItem = 0; nItem< MAX_ITEM; nItem++)
	{
		g_Item[nItem].pos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nItem].dir= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nItem].nType = 0;
		g_Item[nItem].buse = false;
		for (int nItemTtpe = 0; nItemTtpe < TITLE_TYPE_MAX; nItemTtpe++)
		{
		


			/*���_�o�b�t�@�̐���*/
			/*X�t�@�C���̓ǂݍ���*/
			D3DXLoadMeshFromX(
				g_FileItem[nItemTtpe].pFilename,
				D3DXMESH_MANAGED,
				pDevice,
				NULL,
				&g_Item[nItem].ItemParts[nItemTtpe].pBuffMat,
				NULL,
				&g_Item[nItem].ItemParts[nItemTtpe].nNumMat,
				&g_Item[nItem].ItemParts[nItemTtpe].pMesh);
			/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
			pMatItem[nItemTtpe] = (D3DXMATERIAL*)g_Item[nItem].ItemParts[nItemTtpe].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Item[nItem].ItemParts[nItemTtpe].nNumMat; nCntMat++)
			{
				if (pMatItem[nItemTtpe][nCntMat].pTextureFilename != NULL)
				{
					D3DXCreateTextureFromFile(pDevice, pMatItem[nItemTtpe][nCntMat].pTextureFilename, &g_Item[nItem].ItemParts[nItemTtpe].pTextureModel[nCntMat]);
				}
			}

			
		}

	}
}
void UninitItem(void)
{
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		for (int nItemTtpe = 0; nItemTtpe < TITLE_TYPE_MAX; nItemTtpe++)
		{
			/*���b�V���̔j��*/
			if (g_Item[nItem].ItemParts[nItemTtpe].pMesh != NULL)
			{
				g_Item[nItem].ItemParts[nItemTtpe].pMesh->Release();
				g_Item[nItem].ItemParts[nItemTtpe].pMesh = NULL;
			}

			/*�}�e���A���̔j��*/
			if (g_Item[nItem].ItemParts[nItemTtpe].pBuffMat != NULL)
			{
				g_Item[nItem].ItemParts[nItemTtpe].pBuffMat->Release();
				g_Item[nItem].ItemParts[nItemTtpe].pBuffMat = NULL;
			}
			/*�e�N�X�`��*/
			for (int nCnt = 0; nCnt < (int)g_Item[nItem].ItemParts[nItemTtpe].nNumMat; nCnt++)
			{
				if (g_Item[nItem].ItemParts[nItemTtpe].pTextureModel[nCnt] != NULL)
				{
					g_Item[nItem].ItemParts[nItemTtpe].pTextureModel[nCnt]->Release();
					g_Item[nItem].ItemParts[nItemTtpe].pTextureModel[nCnt] = NULL;
				}
			}

		}
	}
}
void UpdateItem(void)
{
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_Item[nItem].buse)
		{
			if (g_Item[nItem].pos.y<=3)//�n�ʔ���
			{
				g_Item[nItem].vy = 0;
				g_Item[nItem].movePos.y = 0;
			}
			else
			{
				/*�A�C�e���̈ړ��X�V*/
				g_Item[nItem].pos += g_Item[nItem].dir * 1;
				g_Item[nItem].vy = 0.01;
				/*�d�͉����x�X�V*/
				g_Item[nItem].movePos.y -= g_Item[nItem].vy;
				/*�ʒu�X�V*/
				g_Item[nItem].pos += g_Item[nItem].movePos;
			}
		
		}
	}
}
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int nType)
{
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (!g_Item[nItem].buse)
		{
			g_Item[nItem].pos = pos;
			g_Item[nItem].dir = dir;
			g_Item[nItem].nType = nType;
		
			if (g_Item[nItem].nType == 0)
			{
				g_Item[nItem].pos.y += 3;
			}
			g_Item[nItem].buse = true;
			break;
		}
	}
}
void DrawItem(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	D3DXMATRIX mtxRot, mtxTrans;
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_Item[nItem].buse)
		{
			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_Item[nItem].mtxWorld);
			/*�����𔽉f*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nItem].dir.y, g_Item[nItem].dir.x, g_Item[nItem].dir.z);
			D3DXMatrixMultiply(&g_Item[nItem].mtxWorld, &g_Item[nItem].mtxWorld, &mtxRot);
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_Item[nItem].pos.x, g_Item[nItem].pos.y, g_Item[nItem].pos.z);
			D3DXMatrixMultiply(&g_Item[nItem].mtxWorld, &g_Item[nItem].mtxWorld, &mtxTrans);
			/*���[���h�}�g���b�N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nItem].mtxWorld);
			/*���݂̃}�e���A�����擾����*/
			pDevice->GetMaterial(&matDef);

			for (int nCntMat = 0; nCntMat < (int)g_Item[nItem].ItemParts[g_Item[nItem].nType].nNumMat; nCntMat++)
			{
				/*�}�e���A���̐ݒ�*/
				pDevice->SetMaterial(&pMatItem[g_Item[nItem].nType][nCntMat].MatD3D);
				pDevice->SetTexture(0, g_Item[nItem].ItemParts[g_Item[nItem].nType].pTextureModel[nCntMat]);
				/*��ޕʂ̕`��*/
				g_Item[nItem].ItemParts[g_Item[nItem].nType].pMesh->DrawSubset(nCntMat);
			}
			/*�ێ����Ă����}�e���A����߂�*/
			pDevice->SetMaterial(&matDef);
		}
	}
}
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	PLAYER*pPlayer = GetPlayer();
	bool isGround = false;
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_Item[nItem].buse==true)
		{
			D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / 2, size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / 2, -size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 box2Max = D3DXVECTOR3(ITEM_SIZE / 2, ITEM_SIZE / 2, ITEM_SIZE / 2) + g_Item[nItem].pos;
			D3DXVECTOR3 box2Min = D3DXVECTOR3(-ITEM_SIZE / 2, -ITEM_SIZE / 2, -ITEM_SIZE / 2) + g_Item[nItem].pos;
			if (box2Min.y <= box1Max.y&&box2Max.y >= box1Max.y
				|| box2Max.y >= box1Min.y&&box2Min.y <= box1Min.y)
			{
				if (box2Min.x <= box1Max.x&&box2Max.x >= box1Max.x
					|| box2Max.x >= box1Min.x&&box2Min.x <= box1Min.x)
				{
					if (box2Min.z <= box1Max.z&&box2Max.z >= box1Max.z
						|| box2Max.z >= box1Min.z&&box2Min.z <= box1Min.z)
					{
						pPlayer->bItem[nItem][g_Item[nItem].nType] = true;
						if (g_Item[nItem].nType == 0)
						{
							pPlayer->bGoal = true;
						}
						for (int nItemTtpe = 0; nItemTtpe < TITLE_TYPE_MAX; nItemTtpe++)
						{
							
							/*if (g_Item[nItem].nLife > 0)
							{
								g_Item[nItem].nLife[TITLE_TYPE_MAX] -= 1;
							}*/
						}
						
						g_Item[nItem].buse = false;
						isGround = true;
					}
				}
			}
		}
	}
	return isGround;
}
ITEM*GetItem()
{
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		return &g_Item[nItem];
	}
}
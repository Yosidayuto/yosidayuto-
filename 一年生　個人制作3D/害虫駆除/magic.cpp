#include "main.h"
#include "block.h"
#include "polygon.h"
#include "enemy.h"
#include "model.h"
#include "item.h"
#include "magic.h"
#include "boss.h"
#include "sound.h"
#define MAX_SEARCH 50

typedef struct
{
	char *pFilMagic;	// �t�@�C����
}FILE;

/*--�O���[�o���ϐ�--*/
/*���f�����*/
D3DXMATERIAL *pMatMagic[MAGIC_PARTS_MAX];

MAGIC g_Magic[MAX_MAGIC];

/*�t�@�C��*/
FILE g_FileMagic[MAGIC_PARTS_MAX] =
{
	{ "data/Xfile/IceMagic.x" },
	{ "data/Xfile/FireMagic.x" },
	{ "data/Xfile/GrassMagic.x" },
	{ "data/Xfile/StarMagic.x" },
};
/*------------------*/

void InitMagic(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{

		if (!g_Magic[nMagic].bUse)
		{
			/*�����ʒu*/
			g_Magic[nMagic].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			/*��������*/
			g_Magic[nMagic].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			/*�����̑傫��*/
			g_Magic[nMagic].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			/*��ނ̏���*/
			g_Magic[nMagic].nType = NULL;
			/*�����g�p����*/
			g_Magic[nMagic].bUse = false;
		}

	}
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{
		for (int i = 0; i < MAGIC_PARTS_MAX; i++)
		{
			/*X�t�@�C���̓ǂݍ���*/
			D3DXLoadMeshFromX(
				g_FileMagic[i].pFilMagic,
				D3DXMESH_MANAGED,
				pDevice,
				NULL,
				&g_Magic[nMagic].enemyParts[i].pBuffMat,
				NULL,
				&g_Magic[nMagic].enemyParts[i].nNumMat,
				&g_Magic[nMagic].enemyParts[i].pMesh);
			/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
			pMatMagic[i] = (D3DXMATERIAL*)g_Magic[nMagic].enemyParts[i].pBuffMat->GetBufferPointer();
			/*�t�@�C���̓ǂݍ���*/
			for (int nCntMat = 0; nCntMat < (int)g_Magic[nMagic].enemyParts[i].nNumMat; nCntMat++)
			{
				if (pMatMagic[i][nCntMat].pTextureFilename != NULL)
				{
					D3DXCreateTextureFromFile(pDevice, pMatMagic[i][nCntMat].pTextureFilename, &g_Magic[nMagic].enemyParts[i].pTextureModel[nCntMat]);
				}
			}
		}
	}
}
void UninitMagic(void)
{
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{
		for (int i = 0; i < MAGIC_PARTS_MAX; i++)
		{
			/*���b�V���̔j��*/
			if (g_Magic[nMagic].enemyParts[i].pMesh != NULL)
			{
				g_Magic[nMagic].enemyParts[i].pMesh->Release();
				g_Magic[nMagic].enemyParts[i].pMesh = NULL;
			}

			/*�}�e���A���̔j��*/
			if (g_Magic[nMagic].enemyParts[i].pBuffMat != NULL)
			{
				g_Magic[nMagic].enemyParts[i].pBuffMat->Release();
				g_Magic[nMagic].enemyParts[i].pBuffMat = NULL;
			}
			/*�e�N�X�`��*/
			for (int nCnt = 0; nCnt < (int)g_Magic[nMagic].enemyParts[i].nNumMat; nCnt++)
			{
				if (g_Magic[nMagic].enemyParts[i].pTextureModel[nCnt] != NULL)
				{
					g_Magic[nMagic].enemyParts[i].pTextureModel[nCnt]->Release();
					g_Magic[nMagic].enemyParts[i].pTextureModel[nCnt] = NULL;
				}
			}
		}

	}
}
void UpdateMagic(void)
{
	VERTEX_3D*pVtx = NULL;
	PLAYER *pPlayer = GetPlayer();
	ENEMY *pEnemy = GetEnemy();
	BOOS *pBoos = GetBoos();
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{
		if (g_Magic[nMagic].bUse)
		{
			/*PlaySound(SOUND_LABEL_SE_MAGIC2);*/
			g_Magic[nMagic].pos += (g_Magic[nMagic].dir) * 1.0f;
			for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
			{
				if (pEnemy[nEnemy].use)
				{
					/*�����蔻��*/
					if (pEnemy[nEnemy].pos.x + 20 >= g_Magic[nMagic].pos.x
						&&pEnemy[nEnemy].pos.x - 20 <= g_Magic[nMagic].pos.x
						&&pEnemy[nEnemy].pos.y + 20 >= g_Magic[nMagic].pos.y
						&&pEnemy[nEnemy].pos.y - 20 <= g_Magic[nMagic].pos.y
						&&pEnemy[nEnemy].pos.z + 20 >= g_Magic[nMagic].pos.z
						&&pEnemy[nEnemy].pos.z - 20 <= g_Magic[nMagic].pos.z)
					{
						PlaySound(SOUND_LABEL_SE_HIT);
						HitEnemy(5, nEnemy);
						g_Magic[nMagic].bUse = false;
					}
					
				}
			}
			if (pBoos->pos.x + 150 >= g_Magic[nMagic].pos.x
				&&pBoos->pos.x - 150 <= g_Magic[nMagic].pos.x
				&&pBoos->pos.y + 700 >= g_Magic[nMagic].pos.y
				&&pBoos->pos.y - 700 <= g_Magic[nMagic].pos.y
				&&pBoos->pos.z + 50 >= g_Magic[nMagic].pos.z
				&&pBoos->pos.z - 50 <= g_Magic[nMagic].pos.z)
			{
				PlaySound(SOUND_LABEL_SE_HIT);
				g_Magic[nMagic].bUse = false;
				HitBoos(1, g_Magic[nMagic].nType);

			}
		}
	}
}
void DrawMagic(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	int nCntMat;
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{
		if (g_Magic[nMagic].bUse)
		{

			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_Magic[nMagic].mtxWorld);
			/*�����𔽉f*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Magic[nMagic].rot.y, g_Magic[nMagic].rot.x, g_Magic[nMagic].rot.z);
			D3DXMatrixMultiply(&g_Magic[nMagic].mtxWorld, &g_Magic[nMagic].mtxWorld, &mtxRot);
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_Magic[nMagic].pos.x, g_Magic[nMagic].pos.y, g_Magic[nMagic].pos.z);
			D3DXMatrixMultiply(&g_Magic[nMagic].mtxWorld, &g_Magic[nMagic].mtxWorld, &mtxTrans);
			/*���[���h�}�g���b�N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Magic[nMagic].mtxWorld);
			/*���݂̃}�e���A�����擾����*/
			pDevice->GetMaterial(&matDef);

			for (nCntMat = 0; nCntMat < (int)g_Magic[nMagic].enemyParts[g_Magic[nMagic].nType].nNumMat; nCntMat++)
			{
				/*�}�e���A���̐ݒ�*/
				pDevice->SetMaterial(&pMatMagic[g_Magic[nMagic].nType][nCntMat].MatD3D);
				pDevice->SetTexture(0, g_Magic[nMagic].enemyParts[g_Magic[nMagic].nType].pTextureModel[nCntMat]);
				/*��ޕʂ̕`��*/
				g_Magic[nMagic].enemyParts[g_Magic[nMagic].nType].pMesh->DrawSubset(nCntMat);
			}
			/*�ێ����Ă����}�e���A����߂�*/
			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetMagic(int Type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 dir)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *pPlayer = GetPlayer();
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{	/*�G�̎�ސݒ�*/
		if (!g_Magic[nMagic].bUse)
		{
			/*�ʒu�̏���*/
			g_Magic[nMagic].pos = pos;
			/*��ޏ���*/
			g_Magic[nMagic].nType = Type;

			D3DXVec3Normalize(&dir, &dir);
			/*��������*/
			g_Magic[nMagic].rot= rot;
			/*��������*/
			g_Magic[nMagic].dir = dir;
			/*�g�p����*/
			g_Magic[nMagic].bUse = true;
			break;
		}
	}
}
MAGIC*GetMagic()
{
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{
		return &g_Magic[nMagic];
	}

}
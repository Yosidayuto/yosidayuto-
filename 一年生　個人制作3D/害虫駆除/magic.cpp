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
	char *pFilMagic;	// ファイル名
}FILE;

/*--グローバル変数--*/
/*モデル情報*/
D3DXMATERIAL *pMatMagic[MAGIC_PARTS_MAX];

MAGIC g_Magic[MAX_MAGIC];

/*ファイル*/
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
			/*初期位置*/
			g_Magic[nMagic].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			/*初期向き*/
			g_Magic[nMagic].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			/*初期の大きさ*/
			g_Magic[nMagic].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			/*種類の初期*/
			g_Magic[nMagic].nType = NULL;
			/*初期使用処理*/
			g_Magic[nMagic].bUse = false;
		}

	}
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{
		for (int i = 0; i < MAGIC_PARTS_MAX; i++)
		{
			/*Xファイルの読み込み*/
			D3DXLoadMeshFromX(
				g_FileMagic[i].pFilMagic,
				D3DXMESH_MANAGED,
				pDevice,
				NULL,
				&g_Magic[nMagic].enemyParts[i].pBuffMat,
				NULL,
				&g_Magic[nMagic].enemyParts[i].nNumMat,
				&g_Magic[nMagic].enemyParts[i].pMesh);
			/*マテリアルデータへのポインタを取得*/
			pMatMagic[i] = (D3DXMATERIAL*)g_Magic[nMagic].enemyParts[i].pBuffMat->GetBufferPointer();
			/*ファイルの読み込み*/
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
			/*メッシュの破棄*/
			if (g_Magic[nMagic].enemyParts[i].pMesh != NULL)
			{
				g_Magic[nMagic].enemyParts[i].pMesh->Release();
				g_Magic[nMagic].enemyParts[i].pMesh = NULL;
			}

			/*マテリアルの破棄*/
			if (g_Magic[nMagic].enemyParts[i].pBuffMat != NULL)
			{
				g_Magic[nMagic].enemyParts[i].pBuffMat->Release();
				g_Magic[nMagic].enemyParts[i].pBuffMat = NULL;
			}
			/*テクスチャ*/
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
					/*当たり判定*/
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
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	int nCntMat;
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{
		if (g_Magic[nMagic].bUse)
		{

			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Magic[nMagic].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Magic[nMagic].rot.y, g_Magic[nMagic].rot.x, g_Magic[nMagic].rot.z);
			D3DXMatrixMultiply(&g_Magic[nMagic].mtxWorld, &g_Magic[nMagic].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Magic[nMagic].pos.x, g_Magic[nMagic].pos.y, g_Magic[nMagic].pos.z);
			D3DXMatrixMultiply(&g_Magic[nMagic].mtxWorld, &g_Magic[nMagic].mtxWorld, &mtxTrans);
			/*ワールドマトリックスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Magic[nMagic].mtxWorld);
			/*現在のマテリアルを取得する*/
			pDevice->GetMaterial(&matDef);

			for (nCntMat = 0; nCntMat < (int)g_Magic[nMagic].enemyParts[g_Magic[nMagic].nType].nNumMat; nCntMat++)
			{
				/*マテリアルの設定*/
				pDevice->SetMaterial(&pMatMagic[g_Magic[nMagic].nType][nCntMat].MatD3D);
				pDevice->SetTexture(0, g_Magic[nMagic].enemyParts[g_Magic[nMagic].nType].pTextureModel[nCntMat]);
				/*種類別の描画*/
				g_Magic[nMagic].enemyParts[g_Magic[nMagic].nType].pMesh->DrawSubset(nCntMat);
			}
			/*保持していたマテリアルを戻す*/
			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetMagic(int Type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 dir)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *pPlayer = GetPlayer();
	for (int nMagic = 0; nMagic < MAX_MAGIC; nMagic++)
	{	/*敵の種類設定*/
		if (!g_Magic[nMagic].bUse)
		{
			/*位置の処理*/
			g_Magic[nMagic].pos = pos;
			/*種類処理*/
			g_Magic[nMagic].nType = Type;

			D3DXVec3Normalize(&dir, &dir);
			/*向き処理*/
			g_Magic[nMagic].rot= rot;
			/*方向処理*/
			g_Magic[nMagic].dir = dir;
			/*使用処理*/
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
#include"main.h"
#include"item.h"
#include"model.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
/*モデル情報*/
D3DXMATERIAL *pMatItem[TITLE_TYPE_MAX];
/*アイテム*/
ITEM g_Item[MAX_ITEM];
/*ファイルの読み込み準備*/
typedef struct
{
	char *pFilename;	// ファイル名
}FILE_ITEM;
/*Xファイルの種類*/
FILE_ITEM g_FileItem[TITLE_TYPE_MAX] =
{
	{ "Xファイル/段ボール.x" },	//メインアイテム
	{ "Xファイル/danbo-ru2.x" },	//アイテム大
	{ "Xファイル/danbo-ru3.x" },	//アイテム中
	{ "Xファイル/danbo-ru4.x" },	//アイテム小
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
		


			/*頂点バッファの生成*/
			/*Xファイルの読み込み*/
			D3DXLoadMeshFromX(
				g_FileItem[nItemTtpe].pFilename,
				D3DXMESH_MANAGED,
				pDevice,
				NULL,
				&g_Item[nItem].ItemParts[nItemTtpe].pBuffMat,
				NULL,
				&g_Item[nItem].ItemParts[nItemTtpe].nNumMat,
				&g_Item[nItem].ItemParts[nItemTtpe].pMesh);
			/*マテリアルデータへのポインタを取得*/
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
			/*メッシュの破棄*/
			if (g_Item[nItem].ItemParts[nItemTtpe].pMesh != NULL)
			{
				g_Item[nItem].ItemParts[nItemTtpe].pMesh->Release();
				g_Item[nItem].ItemParts[nItemTtpe].pMesh = NULL;
			}

			/*マテリアルの破棄*/
			if (g_Item[nItem].ItemParts[nItemTtpe].pBuffMat != NULL)
			{
				g_Item[nItem].ItemParts[nItemTtpe].pBuffMat->Release();
				g_Item[nItem].ItemParts[nItemTtpe].pBuffMat = NULL;
			}
			/*テクスチャ*/
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
			if (g_Item[nItem].pos.y<=3)//地面判定
			{
				g_Item[nItem].vy = 0;
				g_Item[nItem].movePos.y = 0;
			}
			else
			{
				/*アイテムの移動更新*/
				g_Item[nItem].pos += g_Item[nItem].dir * 1;
				g_Item[nItem].vy = 0.01;
				/*重力加速度更新*/
				g_Item[nItem].movePos.y -= g_Item[nItem].vy;
				/*位置更新*/
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
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	D3DXMATRIX mtxRot, mtxTrans;
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_Item[nItem].buse)
		{
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Item[nItem].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nItem].dir.y, g_Item[nItem].dir.x, g_Item[nItem].dir.z);
			D3DXMatrixMultiply(&g_Item[nItem].mtxWorld, &g_Item[nItem].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Item[nItem].pos.x, g_Item[nItem].pos.y, g_Item[nItem].pos.z);
			D3DXMatrixMultiply(&g_Item[nItem].mtxWorld, &g_Item[nItem].mtxWorld, &mtxTrans);
			/*ワールドマトリックスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nItem].mtxWorld);
			/*現在のマテリアルを取得する*/
			pDevice->GetMaterial(&matDef);

			for (int nCntMat = 0; nCntMat < (int)g_Item[nItem].ItemParts[g_Item[nItem].nType].nNumMat; nCntMat++)
			{
				/*マテリアルの設定*/
				pDevice->SetMaterial(&pMatItem[g_Item[nItem].nType][nCntMat].MatD3D);
				pDevice->SetTexture(0, g_Item[nItem].ItemParts[g_Item[nItem].nType].pTextureModel[nCntMat]);
				/*種類別の描画*/
				g_Item[nItem].ItemParts[g_Item[nItem].nType].pMesh->DrawSubset(nCntMat);
			}
			/*保持していたマテリアルを戻す*/
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
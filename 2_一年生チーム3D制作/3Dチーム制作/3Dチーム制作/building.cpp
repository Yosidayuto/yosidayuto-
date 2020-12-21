#include"building.h"
#include "main.h"
#include "model.h"
#define MAX_BUILDING (100)
/*--グローバル変数--*/
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureBuilding[256];
/*ポリゴンのワールドマトリックス*/
D3DXMATRIX g_mtxWorldBuilding;
/*マテリアルデータへのポインタ*/
D3DXMATERIAL *pMat3;/*モデル情報*/
BUILDING g_Building[MAX_BUILDING];

void InitBuilding(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int n = 0; n < MAX_BUILDING; n++)
	{
		/*Xファイルの読み込み*/
		D3DXLoadMeshFromX(
			"Xファイル/ビル.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Building[n].pBuffMatBuilding,
			NULL,
			&g_Building[n].nNumMatBuilding,
			&g_Building[n].pMeshBuilding);
		/*マテリアルデータへのポインタを取得*/
		pMat3 = (D3DXMATERIAL*)g_Building[n].pBuffMatBuilding->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Building[n].nNumMatBuilding; nCntMat++)
		{
			if (pMat3[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat3[nCntMat].pTextureFilename, &g_pTextureBuilding[nCntMat]);
			}
		}

		/*初期位置*/
		g_Building[n].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Building[n].used = false;
		/*初期サイズ*/
		g_Building[n].size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	}
}
void UninitBuilding(void)
{
	for (int n = 0; n < MAX_BUILDING; n++)
	{
		/*メッシュの破棄*/
		if (g_Building[n].pMeshBuilding != NULL)
		{
			g_Building[n].pMeshBuilding->Release();
			g_Building[n].pMeshBuilding = NULL;
		}

		/*マテリアルの破棄*/
		if (g_Building[n].pBuffMatBuilding != NULL)
		{
			g_Building[n].pBuffMatBuilding->Release();
			g_Building[n].pBuffMatBuilding = NULL;
		}
		/*テクスチャ*/
		for (int nCnt = 0; nCnt < (int)g_Building[n].nNumMatBuilding; nCnt++)
		{
			if (g_pTextureBuilding[nCnt] != NULL)
			{
				g_pTextureBuilding[nCnt]->Release();
				g_pTextureBuilding[nCnt] = NULL;
			}
		}

	}

}
void UpdateBuilding(void)
{

}
void DrawBuilding(void)
{
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	for (int n = 0; n < MAX_BUILDING; n++)
	{
		if (g_Building[n].used == true)
		{
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Building[n].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Building[n].rot.y, g_Building[n].rot.x, g_Building[n].rot.z);
			D3DXMatrixMultiply(&g_Building[n].mtxWorld, &g_Building[n].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Building[n].pos.x, g_Building[n].pos.y, g_Building[n].pos.z);
			D3DXMatrixMultiply(&g_Building[n].mtxWorld, &g_Building[n].mtxWorld, &mtxTrans);
			/*ワールドマトリックスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Building[n].mtxWorld);
			/*現在のマテリアルを取得する*/
			pDevice->GetMaterial(&matDef);


			for (int nCntMat = 0; nCntMat < (int)g_Building[n].nNumMatBuilding; nCntMat++)
			{
				/*マテリアルの設定*/
				pDevice->SetMaterial(&pMat3[nCntMat].MatD3D);

				pDevice->SetTexture(0, g_pTextureBuilding[nCntMat]);

				/*モデルパーツの描画*/
				g_Building[n].pMeshBuilding->DrawSubset(nCntMat);

			}
			/*保持していたマテリアルを戻す*/
			pDevice->SetMaterial(&matDef);
		}

	}



}
void SetBuilding(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_BUILDING; i++)
	{
		if (g_Building[i].used == false)
		{
			g_Building[i].pos = pos;
			g_Building[i].size = size;
			g_Building[i].used = true;
			break;
		}

	}
}
bool CollisionBuilding(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	PLAYER *pPlayer = GetPlayer();
	bool isGround = false;
	for (int n = 0; n < MAX_BUILDING; n++)
	{
		if (g_Building[n].used == true)
		{
			D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / 2, size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / 2, -size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 box2Max = D3DXVECTOR3(g_Building[n].size.x / 2, g_Building[n].size.y / 2, g_Building[n].size.z / 2) + g_Building[n].pos;
			D3DXVECTOR3 box2Min = D3DXVECTOR3(-g_Building[n].size.x / 2, -g_Building[n].size.y / 2, -g_Building[n].size.z / 2) + g_Building[n].pos;

			if (box2Min.y <= box1Max.y&&box2Max.y >= box1Max.y
				|| box2Max.y >= box1Min.y&&box2Min.y <= box1Min.y)
			{
				if (box2Min.x <= box1Max.x&&box2Max.x >= box1Max.x
					|| box2Max.x >= box1Min.x&&box2Min.x <= box1Min.x)
				{
					if (box2Min.z <= box1Max.z&&box2Max.z >= box1Max.z
						|| box2Max.z >= box1Min.z&&box2Min.z <= box1Min.z)
					{
						if (box2Min.y <= box1Max.y&&box2Min.y + 3 >= box1Max.y)//下からの干渉
						{
							pPlayer->pos.y = box2Min.y + (-size.y / 2);
						}
						else if (box2Max.y >= box1Min.y&&box2Max.y - 3 <= box1Min.y)//上からの干渉
						{
							pPos = pPosOld;
							isGround = true;
						}
						else if (box2Min.x <= box1Max.x&&box2Min.x + 3 >= box1Max.x)//左からの干渉
						{
							pPlayer->pos.x = box2Min.x + (-size.x / 2);
						}
						else if (box2Max.x >= box1Min.x&&box2Max.x - 3 <= box1Min.x)//右からの干渉
						{
							pPlayer->pos.x = box2Max.x + (+size.x / 2);
						}
						else if (box2Min.z <= box1Max.z&&box2Min.z + 3 >= box1Max.z)//手前からの干渉
						{
							pPlayer->pos.z = box2Min.z + (-size.z / 2);
						}
						else if (box2Max.z >= box1Min.z&&box2Max.z - 3 <= box1Min.z)//奥から干渉
						{
							pPlayer->pos.z = box2Max.z + (+size.z / 2);
						}
					}
				}
			}
		}
	}
	return isGround;

}

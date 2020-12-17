#include "main.h"
#include "block.h"
#include "model.h"
#include "enemy.h"

/*--グローバル変数--*/
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureBlock[256];
/*ポリゴンのワールドマトリックス*/
D3DXMATRIX g_mtxWorldBlock;
/*マテリアルデータへのポインタ*/
D3DXMATERIAL *pMat2;/*モデル情報*/
BLOCK g_Block[MAX_BLOCK];

void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int n = 0; n < MAX_BLOCK; n++)
	{
		/*Xファイルの読み込み*/
		D3DXLoadMeshFromX(
			"Xファイル/ブロック.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			& g_Block[n].pBuffMatBlock ,
			NULL,
			&g_Block[n].nNumMatBlock ,
			&g_Block[n].pMeshBlock);
		/*マテリアルデータへのポインタを取得*/
		pMat2 = (D3DXMATERIAL*)g_Block[n].pBuffMatBlock->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Block[n].nNumMatBlock; nCntMat++)
		{
			if (pMat2[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat2[nCntMat].pTextureFilename, &g_pTextureBlock[nCntMat]);
			}
		}
		
		/*初期位置*/
		g_Block[n].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[n].used = false;
		/*初期サイズ*/
		g_Block[n].size= D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		
	}
}
void UninitBlock(void)
{
	for (int n = 0; n < MAX_BLOCK; n++)
	{
		/*メッシュの破棄*/
		if (g_Block[n].pMeshBlock != NULL)
		{
			g_Block[n].pMeshBlock->Release();
			g_Block[n].pMeshBlock = NULL;
		}

		/*マテリアルの破棄*/
		if (g_Block[n].pBuffMatBlock != NULL)
		{
			g_Block[n].pBuffMatBlock->Release();
			g_Block[n].pBuffMatBlock = NULL;
		}
		/*テクスチャ*/
		for (int nCnt = 0; nCnt < (int)g_Block[n].nNumMatBlock; nCnt++)
		{
			if (g_pTextureBlock[nCnt] != NULL)
			{
				g_pTextureBlock[nCnt]->Release();
				g_pTextureBlock[nCnt] = NULL;
			}
		}

	}
	
}
void UpdateBlock(void)
{
	
}
void DrawBlock(void)
{
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	for (int n = 0; n < MAX_BLOCK; n++)
	{
		if (g_Block[n].used == true)
		{
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Block[n].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[n].rot.y, g_Block[n].rot.x, g_Block[n].rot.z);
			D3DXMatrixMultiply(&g_Block[n].mtxWorld, &g_Block[n].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Block[n].pos.x, g_Block[n].pos.y, g_Block[n].pos.z);
			D3DXMatrixMultiply(&g_Block[n].mtxWorld, &g_Block[n].mtxWorld, &mtxTrans);
			/*ワールドマトリックスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[n].mtxWorld);
			/*現在のマテリアルを取得する*/
			pDevice->GetMaterial(&matDef);


			for (int nCntMat = 0; nCntMat < (int)g_Block[n].nNumMatBlock; nCntMat++)
			{
				/*マテリアルの設定*/
				pDevice->SetMaterial(&pMat2[nCntMat].MatD3D);

				pDevice->SetTexture(0, g_pTextureBlock[nCntMat]);

				/*モデルパーツの描画*/
				g_Block[n].pMeshBlock->DrawSubset(nCntMat);

			}
			/*保持していたマテリアルを戻す*/
			pDevice->SetMaterial(&matDef);
		}
		
	}
	
	

}
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (g_Block[i].used==false) 
		{
			g_Block[i].pos = pos;
			g_Block[i].size = size;
			g_Block[i].used = true;
			break;
		}
	
	}
}
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	PLAYER *pPlayer = GetPlayer();
	bool isGround = false;
	for (int n = 0; n < MAX_BLOCK; n++)
	{
		if (g_Block[n].used == true)
		{
			D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / 2, size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / 2, -size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 box2Max = D3DXVECTOR3(g_Block[n].size.x / 2, g_Block[n].size.y / 2, g_Block[n].size.z / 2)+g_Block[n].pos;
			D3DXVECTOR3 box2Min = D3DXVECTOR3(-g_Block[n].size.x / 2, -g_Block[n].size.y / 2, -g_Block[n].size.z / 2)+ g_Block[n].pos;
			
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
bool CollisionBlockEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	ENEMY*pEnemy = GetEnemy();
	bool isGround = false;
	for (int n = 0; n < MAX_BLOCK; n++)
	{
		if (g_Block[n].used)
		{
			D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / 2, size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / 2, -size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 box2Max = D3DXVECTOR3(g_Block[n].size.x / 2, g_Block[n].size.y / 2, g_Block[n].size.z / 2) + g_Block[n].pos;
			D3DXVECTOR3 box2Min = D3DXVECTOR3(-g_Block[n].size.x / 2, -g_Block[n].size.y / 2, -g_Block[n].size.z / 2) + g_Block[n].pos;
			for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
			{
				if (pEnemy[nEnemy].buse)
				{
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
									pEnemy[nEnemy].pos.y = box2Min.y + (-size.y / 2);
								}
								if (box2Max.y >= box1Min.y&&box2Max.y - 3 <= box1Min.y)//上からの干渉
								{
									pPos = pPosOld;
									isGround = true;
								}
								if (box2Min.x <= box1Max.x&&box2Min.x + 3 >= box1Max.x)//左からの干渉
								{
									pEnemy[nEnemy].pos.x = box2Min.x + (-size.x / 2);
								}
								if (box2Max.x >= box1Min.x&&box2Max.x - 3 <= box1Min.x)//右からの干渉
								{
									pEnemy[nEnemy].pos.x = box2Max.x + (+size.x / 2);
								}
								if (box2Min.z <= box1Max.z&&box2Min.z + 3 >= box1Max.z)//手前からの干渉
								{
									pEnemy[nEnemy].pos.z = box2Min.z + (-size.z / 2);
								}
								if (box2Max.z >= box1Min.z&&box2Max.z - 3 <= box1Min.z)//奥から干渉
								{
									pEnemy[nEnemy].pos.z = box2Max.z + (+size.z / 2);
								}
							}
						}
					}
				}

			}

		}
	}
	return isGround;
}
bool ColRayBox(D3DXVECTOR3* pos, D3DXVECTOR3* dir, SEARCH_BOX* border, D3DXMATRIX* mat, float& output, D3DXVECTOR3* colPos)
{
	// 光線を境界ボックスの空間へ移動
	D3DXMATRIX invMat;
	D3DXMatrixInverse(&invMat, 0, mat);

	D3DXVECTOR3 pos_l, dir_l;//ローカルpos,ローカルdir
	D3DXVec3TransformCoord(&pos_l, pos, &invMat);
	invMat._41 = 0.0f;
	invMat._42 = 0.0f;
	invMat._43 = 0.0f;
	D3DXVec3TransformCoord(&dir_l, dir, &invMat);

	// 交差判定
	float p[3], d[3], min[3], max[3];
	memcpy(p, &pos_l, sizeof(D3DXVECTOR3));
	memcpy(d, &dir_l, sizeof(D3DXVECTOR3));
	memcpy(min, &border->min, sizeof(D3DXVECTOR3));
	memcpy(max, &border->max, sizeof(D3DXVECTOR3));

	output = -FLT_MAX;//float型の最小値
	float output_max = FLT_MAX;//float型の最大値

	for (int i = 0; i < 3; ++i)
	{
		if (fabsf(d[i]) < FLT_EPSILON)
		{
			if (p[i] < min[i] || p[i] > max[i])
			{
				return false; // 交差していない
			}
		}
		else
		{
			// スラブとの距離を算出
			// t1が近スラブ、t2が遠スラブとの距離
			float odd = 1.0f / d[i];
			float t1 = (min[i] - p[i]) * odd;
			float t2 = (max[i] - p[i]) * odd;
			if (t1 > t2)
			{
				float tmp = t1; t1 = t2; t2 = tmp;
			}

			if (t1 > output) output = t1;

			if (t2 < output_max) output_max = t2;

			// スラブ交差チェック
			if (output >= output_max)
			{
				return false;
			}
		}
	}

	// 交差している
	if (colPos)
	{
		*colPos = *pos + output * (*dir);
	}
	return true;
}
BLOCK*GetBlock()
{
	for (int n = 0; n < MAX_BLOCK; n++)
	{
		return &g_Block[n];
	}
}
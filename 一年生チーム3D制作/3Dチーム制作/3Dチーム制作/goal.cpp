
#include "goal.h"
#include "model.h"
#include "fade.h"
#include "score.h"
#include"meshfield2.h"
#define MAX_GOAL (10)
/*--グローバル変数--*/
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureGoal[256];
/*ポリゴンのワールドマトリックス*/
D3DXMATRIX g_mtxWorldGoal;
/*マテリアルデータへのポインタ*/
D3DXMATERIAL *pMatGoal;/*モデル情報*/
GOAl g_Goal[MAX_GOAL];
bool g_score;
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nGoal = 0; nGoal < MAX_GOAL; nGoal++)
	{
		/*Xファイルの読み込み*/
		D3DXLoadMeshFromX(
			"Xファイル/ブロック.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Goal[nGoal].pBuffMatBlock,
			NULL,
			&g_Goal[nGoal].nNumMatBlock,
			&g_Goal[nGoal].pMeshBlock);
		/*マテリアルデータへのポインタを取得*/
		pMatGoal = (D3DXMATERIAL*)g_Goal[nGoal].pBuffMatBlock->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Goal[nGoal].nNumMatBlock; nCntMat++)
		{
			if (pMatGoal[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMatGoal[nCntMat].pTextureFilename, &g_pTextureGoal[nCntMat]);
			}
		}

		/*初期位置*/
		g_Goal[nGoal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Goal[nGoal].buse = false;
		/*初期サイズ*/
		g_Goal[nGoal].size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		g_score = false;
	}
}
void UninitGoal(void)
{
	for (int nGoal = 0; nGoal < MAX_GOAL; nGoal++)
	{
		/*メッシュの破棄*/
		if (g_Goal[nGoal].pMeshBlock != NULL)
		{
			g_Goal[nGoal].pMeshBlock->Release();
			g_Goal[nGoal].pMeshBlock = NULL;
		}

		/*マテリアルの破棄*/
		if (g_Goal[nGoal].pBuffMatBlock != NULL)
		{
			g_Goal[nGoal].pBuffMatBlock->Release();
			g_Goal[nGoal].pBuffMatBlock = NULL;
		}
		/*テクスチャ*/
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
		if (g_Goal[nGoal].buse)//ゴールがあるか
		{
			/*ゴールの当たり判定*/
			if (g_Goal[nGoal].pos.x + 30 >= pPlayer->pos.x
				&&g_Goal[nGoal].pos.x - 30 <= pPlayer->pos.x
				&&g_Goal[nGoal].pos.y + 30 >= pPlayer->pos.y
				&&g_Goal[nGoal].pos.y - 30 <= pPlayer->pos.y
				&&g_Goal[nGoal].pos.z + 30 >= pPlayer->pos.z
				&&g_Goal[nGoal].pos.z - 30 <= pPlayer->pos.z)
			{
				if (!g_score)//判定を何度も出さないため
				{
					if (pPlayer->bGoal == true)//目的のアイテムを持っているか
					{
						for (int nItem = 0; nItem < MAX_ITEM; nItem++)
						{
							for (int nItemTtpe = 0; nItemTtpe < TITLE_TYPE_MAX; nItemTtpe++)
							{//アイテムのスコアを送る
								if (pPlayer->bItem[nItem][nItemTtpe])
								{
									AddScore(1, nItemTtpe+1);
									AddScore(pPlayer->nLife[nItem][nItemTtpe], nItemTtpe + 5);
								}
									
								
							}

						}
						
						SetFade(MODE_RESULE);//フェードアウト
						g_score = true;
					}
				}
				
			}
		}
	}
	
}
void DrawGoal(void)
{
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	for (int nGoal = 0; nGoal < MAX_GOAL; nGoal++)
	{
		if (g_Goal[nGoal].buse)
		{
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Goal[nGoal].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Goal[nGoal].rot.y, g_Goal[nGoal].rot.x, g_Goal[nGoal].rot.z);
			D3DXMatrixMultiply(&g_Goal[nGoal].mtxWorld, &g_Goal[nGoal].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Goal[nGoal].pos.x, g_Goal[nGoal].pos.y, g_Goal[nGoal].pos.z);
			D3DXMatrixMultiply(&g_Goal[nGoal].mtxWorld, &g_Goal[nGoal].mtxWorld, &mtxTrans);
			/*ワールドマトリックスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Goal[nGoal].mtxWorld);
			/*現在のマテリアルを取得する*/
			pDevice->GetMaterial(&matDef);


			for (int nCntMat = 0; nCntMat < (int)g_Goal[nGoal].nNumMatBlock; nCntMat++)
			{
				/*マテリアルの設定*/
				pDevice->SetMaterial(&pMatGoal[nCntMat].MatD3D);

				pDevice->SetTexture(0, g_pTextureGoal[nCntMat]);

				/*モデルパーツの描画*/
				g_Goal[nGoal].pMeshBlock->DrawSubset(nCntMat);

			}
			/*保持していたマテリアルを戻す*/
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
			g_Goal[nGoal].pos = pos;	//位置設定
			g_Goal[nGoal].size = size;	//サイズ設定
			g_Goal[nGoal].buse = true;	//使用処理
			SetMeshField2(D3DXVECTOR3(g_Goal[nGoal].pos.x, g_Goal[nGoal].pos.y, g_Goal[nGoal].pos.z));
			break;
		}
	}
}


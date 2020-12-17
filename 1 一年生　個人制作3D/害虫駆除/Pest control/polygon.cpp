#include "main.h"
#include "polygon.h"
#include "model.h"
//グローバル変数
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;

POLGON g_Polgon[POLYGON_MAX];

void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntPolgon = 0; nCntPolgon < POLYGON_MAX; nCntPolgon++)
	{
		/*初期処理*/
		g_Polgon[nCntPolgon].pos = D3DXVECTOR3(0, 0.0f, 0);
		g_Polgon[nCntPolgon].rot = D3DXVECTOR3(0, 0, 0);
		g_Polgon[nCntPolgon].used = true;
		g_Polgon[nCntPolgon].size = D3DXVECTOR3(POLYGON_SAZE, 10.0f, POLYGON_SAZE);
	}
	D3DXCreateTextureFromFile(pDevice, "画像/草原　テクスチャ.jpg", &g_pTexturePolygon);
	/*頂点バッファの生成*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D*pVtx = NULL;
	/*頂点バッファをロック*/
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	/*頂点座標の設定*/
	pVtx[0].pos = D3DXVECTOR3(-POLYGON_SAZE /2, 0.0f, POLYGON_SAZE /2);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_SAZE /2, 0.0f, POLYGON_SAZE /2);
	pVtx[2].pos = D3DXVECTOR3(-POLYGON_SAZE /2, 0.0f, -POLYGON_SAZE /2);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_SAZE /2, 0.0f, -POLYGON_SAZE /2);
	/*各頂点の法線の設定（ベクトルの大きさは１にする必要がある）*/
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	/*頂点カラーの設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);
	/*頂点バッファのアンロック*/
	g_pVtxBuffPolygon->Unlock();
}
void UninitPolygon(void)
{
	
	/*頂点バッファの解放*/
	if(g_pVtxBuffPolygon!=NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
	/*テクスチャの開放*/
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
}
void UpdatePolygon(void)
{
	
	
}
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//行列計算用のマトリクス
	for (int nCntPolgon = 0; nCntPolgon < POLYGON_MAX; nCntPolgon++)
	{
		if (g_Polgon[nCntPolgon].used)
		{
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Polgon[nCntPolgon].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot,g_Polgon[nCntPolgon].rot.y, g_Polgon[nCntPolgon].rot.x, g_Polgon[nCntPolgon].rot.z);
			D3DXMatrixMultiply(&g_Polgon[nCntPolgon].mtxWorld, &g_Polgon[nCntPolgon].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Polgon[nCntPolgon].pos.x, g_Polgon[nCntPolgon].pos.y, g_Polgon[nCntPolgon].pos.z);
			D3DXMatrixMultiply(&g_Polgon[nCntPolgon].mtxWorld, &g_Polgon[nCntPolgon].mtxWorld, &mtxTrans);
			/*ワールドマトリクスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Polgon[nCntPolgon].mtxWorld);
			/*頂点バッファをデバイスのデータストリームに設定*/
			pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));
			/*頂点フォーマットの設定*/
			pDevice->SetFVF(FVF_VERTEX_3D);
			/*テクスチャの設定*/
			pDevice->SetTexture(0, g_pTexturePolygon);
			/*ポリゴンの描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	
	}
	pDevice->SetTexture(0, NULL);
}
bool CollisionPolygon(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	PLAYER *pPlayer = GetPlayer();
	bool isGround = false;
	for (int nCntPolgon = 0; nCntPolgon < POLYGON_MAX; nCntPolgon++)
	{
		D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / 2, size.y / 2, size.z / 2) + *pPos;
		D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / 2, -size.y / 2, -size.z / 2) + *pPos;
		D3DXVECTOR3 box2Max = D3DXVECTOR3(g_Polgon[nCntPolgon].size.x / 2, g_Polgon[nCntPolgon].size.y / 2, g_Polgon[nCntPolgon].size.z / 2) + g_Polgon[nCntPolgon].pos;
		D3DXVECTOR3 box2Min = D3DXVECTOR3(-g_Polgon[nCntPolgon].size.x / 2, -g_Polgon[nCntPolgon].size.y / 2, -g_Polgon[nCntPolgon].size.z / 2) + g_Polgon[nCntPolgon].pos;

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
					else if (box2Max.y >= box1Min.y&&box2Max.y - 5 <= box1Min.y)//上からの干渉
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
	return isGround;
}
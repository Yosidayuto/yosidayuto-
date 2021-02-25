#include"main.h"
#include"billboard.h"
#include"enemy.h"
#include"camera.h"
#include"sound.h"
//グローバル変数
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;
/*ビルボード*/
BILLBOARD g_billboard[MAX_BILLBOARD];

void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nBillboard = 0; nBillboard < MAX_BILLBOARD; nBillboard++)
	{
		g_billboard[nBillboard].pos = D3DXVECTOR3(0, 0, 0);
		g_billboard[nBillboard].dir = D3DXVECTOR3(0, 0, 0);
		g_billboard[nBillboard].buse = false;
	}
	/*頂点バッファの生成*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);
	D3DXCreateTextureFromFile(pDevice, "data/image/bullet.png", &g_pTextureBillboard);
	VERTEX_3D*pVtx = NULL;
	/*頂点バッファをロック*/
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	//for (int nBillboard = 0; nBillboard < MAX_BILLBOARD; nBillboard++)
	/*頂点座標の設定*/
	pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE / 2, BILLBOARD_SIZE / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE / 2, BILLBOARD_SIZE / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE / 2, -BILLBOARD_SIZE / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE / 2, -BILLBOARD_SIZE / 2, 0.0f);
	/*各頂点の法線の設定（ベクトルの大きさは１にする必要がある）*/
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	/*頂点カラーの設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	/*テクスチャの設定*/
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);	
	/*頂点バッファのアンロック*/
	g_pVtxBuffBillboard->Unlock();
}
void UninitBillboard(void)
{
	/*頂点バッファの解放*/
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}
void UpdateBillboard(void)
{
	ENEMY *pEnemy = GetEnemy();
	for (int i = 0;i < MAX_BILLBOARD; i++)
	{
		if (g_billboard[i].buse)
		{
			/*ビルボードの位置の更新*/
			g_billboard[i].pos += g_billboard[i].dir * 1;
			for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
			{
				if (pEnemy[nEnemy].use)
				{
				
					if (pEnemy[nEnemy].pos.x + 30 >= g_billboard[i].pos.x
						&&pEnemy[nEnemy].pos.x - 30 <= g_billboard[i].pos.x
						&&pEnemy[nEnemy].pos.y + 30 >= g_billboard[i].pos.y
						&&pEnemy[nEnemy].pos.y - 30 <= g_billboard[i].pos.y
						&&pEnemy[nEnemy].pos.z + 30 >= g_billboard[i].pos.z
						&&pEnemy[nEnemy].pos.z - 30 <= g_billboard[i].pos.z)
					{
						PlaySound(SOUND_LABEL_SE_HIT);
						HitEnemy(1, nEnemy);
						g_billboard[i].buse = false;
					}
				}
			}
			
		}
	}
}
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	CAMERA* pCamera = GetCamera();
	VERTEX_3D*pVtx = NULL;
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		if (!g_billboard[nCntShadow].buse)
		{
			/*位置設定*/
			g_billboard[nCntShadow].pos = pos;
			D3DXVec3Normalize(&dir, &dir);//正規化する（大きさ1のベクトルにする必要がある)
			/*向き設定*/
			g_billboard[nCntShadow].dir = dir;
			/*使用しているか*/
			g_billboard[nCntShadow].buse = true;
			break;
		}
	}
}
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		if (g_billboard[i].buse)
		{
			/*アルファテストを有効化*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			/*アルファテスト基準値の設定*/
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			/*アルファテストの比較方法の設定*/
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_billboard[i].mtxWorld);
			//回転の逆行列を生成
			pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
			D3DXMatrixInverse(&g_billboard[i].mtxWorld, NULL, &mtxRot);
			g_billboard[i].mtxWorld._41 = 0;
			g_billboard[i].mtxWorld._42 = 0;
			g_billboard[i].mtxWorld._43 = 0;		
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_billboard[i].pos.x, g_billboard[i].pos.y, g_billboard[i].pos.z);
			D3DXMatrixMultiply(&g_billboard[i].mtxWorld, &g_billboard[i].mtxWorld, &mtxTrans);
			/*ワールドマトリクスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_billboard[i].mtxWorld);
			/*頂点バッファをデバイスのデータストリームに設定*/
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
			/*頂点フォーマットの設定*/
			pDevice->SetFVF(FVF_VERTEX_3D);
			/*テクスチャの設定*/
			pDevice->SetTexture(0, g_pTextureBillboard);
			/*ポリゴン描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			/*アルファテストを無効化*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}
	pDevice->SetTexture(0, NULL);
}
BILLBOARD*GetBillboard()
{
	
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		return &g_billboard[nCntShadow];
	}
	return NULL;
}

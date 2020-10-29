#include"main.h"
#include"billboard.h"
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
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		g_billboard[nCntShadow].use = false;
	}
	/*頂点バッファの生成*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4* MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);
	D3DXCreateTextureFromFile(pDevice, "画像/3D画像_新_改.png", &g_pTextureBillboard);
	VERTEX_3D*pVtx = NULL;
	/*頂点バッファをロック*/
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		/*頂点座標の設定*/
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE / 2, BILLBOARD_SIZE/2,0.0f);
		pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE / 2, BILLBOARD_SIZE/2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE / 2,-BILLBOARD_SIZE/2,0.0f);
		pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE / 2, -BILLBOARD_SIZE/2,0.0f);
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
	}
	

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
	for (int i = 0;i < MAX_BILLBOARD; i++)
	{
		if (g_billboard[i].use)
		{
			/*ビルボードの位置の更新（※位置を更新したい場合）*/
			g_billboard[i].pos += g_billboard[i].dir * 1/*移動量*/;
		
		}
	}
}
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	VERTEX_3D*pVtx = NULL;
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		D3DXVec3Normalize(&dir, &dir);//正規化する（大きさ1のベクトルにする必要がある）
		/*位置設定*/
		g_billboard[nCntShadow].pos = pos;
		/*向き設定*/
		g_billboard[nCntShadow].dir = dir;

		
		/*使用しているか*/
		g_billboard[nCntShadow].use = true;
		break;
	}
}
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		if (g_billboard[i].use)
		{
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_billboard[i].mtxWorld);

			//回転の逆行列を生成
			pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
			D3DXMatrixInverse(&g_billboard[i].mtxWorld, NULL, &mtxRot);
			g_billboard[i].mtxWorld._41 = 0;
			g_billboard[i].mtxWorld._42 = 0;
			g_billboard[i].mtxWorld._43 = 0;
			/*位置を反映、ワールドマトリックス設定、ポリゴン描画*/
			
			
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_billboard[i].pos.x, g_billboard[i].pos.y, g_billboard[i].pos.z);
			D3DXMatrixMultiply(&g_billboard[i].mtxWorld, &g_billboard[i].mtxWorld, &mtxTrans);
			/*ワールドマトリクスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_billboard[i].mtxWorld);
			/*頂点バッファをデバイスのデータストリームに設定*/
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
			/*頂点フォーマットの設定*/
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, g_pTextureBillboard);
			/*ポリゴン描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
		
	}
	pDevice->SetTexture(0, NULL);
}

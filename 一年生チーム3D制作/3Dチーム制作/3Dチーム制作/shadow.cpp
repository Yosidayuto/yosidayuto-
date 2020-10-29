#include"main.h"
#include"shadow.h"
//グローバル変数
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;
/*影*/
SHADOW g_shadow[MAX_SHADOW];


/*初期化処理*/
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].use = false;
	}
	/*頂点バッファの生成*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);
	D3DXCreateTextureFromFile(pDevice, "画像/shadow.png", &g_pTextureShadow);
	VERTEX_3D*pVtx = NULL;
	/*頂点バッファをロック*/
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	/*頂点座標の設定*/
	pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE / 2, 0, SHADOW_SIZE / 2);
	pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE / 2, 0, SHADOW_SIZE / 2);
	pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE / 2, 0, -SHADOW_SIZE / 2);
	pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE / 2, 0, -SHADOW_SIZE / 2);
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
	g_pVtxBuffShadow->Unlock();
}
void UninitShadow(void)
{
	/*頂点バッファの解放*/
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

}
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow = 0;
	for (; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (!g_shadow[nCntShadow].use)
		{
			//g_shadow[nCntShadow]を初期化、useをtrueにする
			g_shadow[nCntShadow].use = true;
			break;
		}
	}
	return nCntShadow;	//影生成に使用した配列のインデックスを返す
}
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos)
{
	g_shadow[nldxShadow].pos = pos;
}
void DrawShadow(void)
{
	/*減算合成に設定（影は黒いから減算して黒に近づける*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetTexture(0, g_pTextureShadow);
	for (int i = 0; i < MAX_SHADOW; i++)
	{
		if (g_shadow[i].use)
		{
			/*ワールドマトリックスの設定　初期化、向き、位置*/
			
			
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_shadow[i].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[i].rot.y, g_shadow[i].rot.x, g_shadow[i].rot.z);
			D3DXMatrixMultiply(&g_shadow[i].mtxWorld, &g_shadow[i].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_shadow[i].pos.x, g_shadow[i].pos.y, g_shadow[i].pos.z);
			D3DXMatrixMultiply(&g_shadow[i].mtxWorld, &g_shadow[i].mtxWorld, &mtxTrans);
			/*ワールドマトリクスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[i].mtxWorld);
			/*頂点バッファをデバイスのデータストリームに設定*/
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
			/*頂点フォーマットの設定*/
			pDevice->SetFVF(FVF_VERTEX_3D);

			/*ポリゴン描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	/*レンダーステート設定を元に戻す*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetTexture(0, NULL);

}
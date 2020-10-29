#include "main.h"
#include "polygon.h"
//グローバル変数
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
/*ポリゴンの位置*/
D3DXVECTOR3 g_posPolygon;
/*ポリゴンの向き*/
D3DXVECTOR3 g_rotPolygon;
/*ポリゴンのワールドマトリックス*/
D3DXMATRIX g_mtxWorldPolygon;
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
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
	pVtx[0].pos = D3DXVECTOR3(-POLYGONX /2, 0, POLYGONZ /2);
	pVtx[1].pos = D3DXVECTOR3(POLYGONX /2, 0, POLYGONZ /2);
	pVtx[2].pos = D3DXVECTOR3(-POLYGONX /2, 0, -POLYGONZ /2);
	pVtx[3].pos = D3DXVECTOR3(POLYGONX /2, 0, -POLYGONZ /2);
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
}
void UpdatePolygon(void)
{
	
	g_posPolygon = D3DXVECTOR3(0, 0, 0);
}
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//行列計算用のマトリクス
	/*ワールドマトリクスの初期化処理*/
	D3DXMatrixIdentity(&g_mtxWorldPolygon);
	/*向きを反映*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);
	/*位置を反映*/
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);
	/*ワールドマトリクスの設定*/
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);
	/*頂点バッファをデバイスのデータストリームに設定*/
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_3D);
	/*ポリゴンの描画*/
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
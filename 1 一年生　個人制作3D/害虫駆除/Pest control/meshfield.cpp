#include "main.h"
#include "meshfield.h"

#define MAX_SIZE 100
//グローバル変数
/*メッシュフィールドのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;
/*インデックスバッファへのポイント*/
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
/*ポリゴンの位置*/
D3DXVECTOR3 g_posMeshField;
/*ポリゴンの向き*/
D3DXVECTOR3 g_rotMeshField;
/*ポリゴンのワールドマトリックス*/
D3DXMATRIX g_mtxWorldMeshField;

void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIEL_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);
	VERTEX_3D*pVtx = NULL;
	/*頂点バッファの生成（※三角形は意識しない）*/
	/*頂点バッファをロック*/
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	/*頂点座標の設定*/
	pVtx[0].pos = D3DXVECTOR3(-MAX_SIZE / 2	, 2, MAX_SIZE / 2);
	pVtx[1].pos = D3DXVECTOR3(0				, 2, MAX_SIZE / 2);
	pVtx[2].pos = D3DXVECTOR3(MAX_SIZE / 2	, 2, MAX_SIZE / 2);
	pVtx[3].pos = D3DXVECTOR3(-MAX_SIZE / 2	, 2, 0 / 2);
	pVtx[4].pos = D3DXVECTOR3(0				, 2, 0 / 2);
	pVtx[5].pos = D3DXVECTOR3(MAX_SIZE / 2	, 2, 0 / 2);
	pVtx[6].pos = D3DXVECTOR3(-MAX_SIZE / 2	, 2, -MAX_SIZE / 2);
	pVtx[7].pos = D3DXVECTOR3(0				, 2, -MAX_SIZE / 2);
	pVtx[8].pos = D3DXVECTOR3(MAX_SIZE / 2	, 2, -MAX_SIZE / 2);
	/*各頂点の法線の設定（ベクトルの大きさは１にする必要がある）*/
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	/*頂点カラーの設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	/*テクスチャ*/
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0);
	pVtx[2].tex = D3DXVECTOR2(1, 0);
	pVtx[3].tex = D3DXVECTOR2(0, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0, 1);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1);
	pVtx[8].tex = D3DXVECTOR2(1, 1);
	/*頂点バッファのアンロック*/
	g_pVtxBuffMeshField->Unlock();
	/*テクスチャの設定*/
	D3DXCreateTextureFromFile(pDevice, "data/image/NRR2016150966_1[1].jpg", &g_pTextureMeshField);
	/*インデックスバッファ（ポリゴンバッファ）の生成*/
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIEL_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);
	/*インデックスバッファをロック*/
	WORD*pldx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pldx, 0);
	/*インデックス指定*/
	pldx[0] = 3;
	pldx[1] = 0;
	pldx[2] = 4;
	/*--------*/
	pldx[3] = 1;
	pldx[4] = 5;
	pldx[5] = 2;
	/*--------*/
	pldx[6] = 2;
	pldx[7] = 6;
	/*--------*/
	pldx[8] = 6;
	pldx[9] = 3;
	pldx[10] = 7;
	/*--------*/
	pldx[11] = 4;
	pldx[12] = 8;
	pldx[13] = 5;
	/*--------*/
	
	g_pIdxBuffMeshField->Unlock();
}
void UninitMeshField(void)
{
	/*頂点バッファの解放*/
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}
void UpdateMeshField(void)
{

}
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*ワールドマトリクスの初期化処理*/
	D3DXMatrixIdentity(&g_mtxWorldMeshField);
	/*向きを反映*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);
	/*位置を反映*/
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);
	/*ワールドマトリクスの設定*/
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);
	/*インデックスバッファをデータストリームに設定*/
	pDevice->SetIndices(g_pIdxBuffMeshField);
	/*頂点バッファをデバイスのデータストリームに設定*/
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_3D);
	/*テクスチャの描画*/
	pDevice->SetTexture(0, g_pTextureMeshField);
	/*ポリゴン描画*/
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIEL_VERTEX_NUM,0, MESHFIEL_PRIMITIVE_NUM);


	pDevice->SetTexture(0, NULL);
}

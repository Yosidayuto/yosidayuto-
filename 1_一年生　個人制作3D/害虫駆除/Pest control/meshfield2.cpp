#include "main.h"
#include "meshfield2.h"

#define MAX_SIZE 100
//グローバル変数
/*メッシュフィールドのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureMeshField2 = NULL;
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField2 = NULL;
/*インデックスバッファへのポイント*/
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField2 = NULL;
/*ポリゴンの位置*/
D3DXVECTOR3 g_posMeshField2;
/*ポリゴンの向き*/
D3DXVECTOR3 g_rotMeshField2;
/*ポリゴンのワールドマトリックス*/
D3DXMATRIX g_mtxWorldMeshField2;

void InitMeshField2(void)
{
	
	g_posMeshField2 = D3DXVECTOR3(0,30, 0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIEL2_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField2,
		NULL);
	VERTEX_3D*pVtx = NULL;
	/*頂点バッファの生成（※三角形は意識しない）*/
	/*頂点バッファをロック*/
	g_pVtxBuffMeshField2->Lock(0, 0, (void**)&pVtx, 0);
	/*頂点座標の設定*/
	float fTexpos=0;
	int nIndex = 0;

	for (int vIndex = 0; vIndex < MESHFIEL2_Y_BLOCK +1; vIndex++)
	{
		fTexpos = 0;
		for (int hlndex = 0; hlndex < MESHFIE2L_X_BLOCK + 1; hlndex++)
		{
			
			/*座標*/
			float angle = (float)hlndex * 45;
			pVtx[nIndex].pos= D3DXVECTOR3(sinf(D3DXToRadian(-angle))*(MAX_SIZE/2)+ g_posMeshField2.x,
										-vIndex*(MAX_SIZE / 2)+ g_posMeshField2.y,
										cosf(D3DXToRadian(-angle))*(MAX_SIZE / 2)+ g_posMeshField2.z);
			/*各頂点の法線の設定（ベクトルの大きさは１にする必要がある）*/
			pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			D3DXVECTOR3 g_rotMeshField2;
			D3DXVec3Normalize(&g_rotMeshField2, &g_rotMeshField2);
			/*頂点カラーの設定*/
			pVtx[nIndex].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			/*テクスチャ*/
			pVtx[nIndex].tex = D3DXVECTOR2(fTexpos*0.125f, (float)vIndex);
			nIndex += 1;
			fTexpos += 1;
		}
	}
	

	


	/*頂点バッファのアンロック*/
	g_pVtxBuffMeshField2->Unlock();
	/*テクスチャの設定*/
	D3DXCreateTextureFromFile(pDevice, "data/image/NRR2016150966_1[1].jpg", &g_pTextureMeshField2);
	/*インデックスバッファ（ポリゴンバッファ）の生成*/
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIEL2_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField2,
		NULL);
	/*インデックスバッファをロック*/
	WORD*pldx;
	g_pIdxBuffMeshField2->Lock(0, 0, (void**)&pldx, 0);
	int ncunt=9;
	for(int npldx=0;npldx<17; npldx++)
	{
	
			/*インデックス指定*/
			pldx[npldx] = ncunt;
			if (ncunt >= 9)
			{
				ncunt -=9;
			}
			else if(ncunt<9)
			{
				ncunt += 10;
			}
		
	}

	g_pIdxBuffMeshField2->Unlock();
}
void UninitMeshField2(void)
{
	/*頂点バッファの解放*/
	if (g_pVtxBuffMeshField2 != NULL)
	{
		g_pVtxBuffMeshField2->Release();
		g_pVtxBuffMeshField2 = NULL;
	}
	if (g_pTextureMeshField2 != NULL)
	{
		g_pTextureMeshField2->Release();
		g_pTextureMeshField2 = NULL;
	}
	if (g_pIdxBuffMeshField2 != NULL)
	{
		g_pIdxBuffMeshField2->Release();
		g_pIdxBuffMeshField2 = NULL;
	}
}
void UpdateMeshField2(void)
{

}
void DrawMeshField2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*ワールドマトリクスの初期化処理*/
	D3DXMatrixIdentity(&g_mtxWorldMeshField2);
	/*向きを反映*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField2.y, g_rotMeshField2.x, g_rotMeshField2.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField2, &g_mtxWorldMeshField2, &mtxRot);
	/*位置を反映*/
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField2.x, g_posMeshField2.y, g_posMeshField2.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField2, &g_mtxWorldMeshField2, &mtxTrans);
	/*ワールドマトリクスの設定*/
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField2);
	/*インデックスバッファをデータストリームに設定*/
	pDevice->SetIndices(g_pIdxBuffMeshField2);
	/*頂点バッファをデバイスのデータストリームに設定*/
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField2, 0, sizeof(VERTEX_3D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_3D);
	/*テクスチャの描画*/
	pDevice->SetTexture(0, g_pTextureMeshField2);
	/*ポリゴン描画*/
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIEL2_VERTEX_NUM, 0, MESHFIEL2_PRIMITIVE_NUM);


	pDevice->SetTexture(0, NULL);
}

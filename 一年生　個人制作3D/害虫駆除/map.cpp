#include"map.h"
#include"model.h"
/*--グローバル変数--*/
/*モデル情報*/
D3DXMATERIAL *pMat;
/*パーツ群の構造体*/
MAP g_Map;

/*----------------*/


void InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	
		/*Xファイルの読み込み*/
		D3DXLoadMeshFromX(
			"deta/Xfile/Stage.x",
			D3DXMESH_MANAGED,
			pDevice,
			NULL,
			&g_Map.BuffMat,
			NULL,
			&g_Map.NumMat,
			&g_Map.Mesh);

		/*マテリアルデータへのポインタを取得*/
		pMat = (D3DXMATERIAL*)g_Map.BuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Map.NumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_Map.pTexture[nCntMat]);
			}
		}

	/*初期向き*/
	g_Map.rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	/*初期位置*/
	g_Map.pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}
void UninitMap(void)
{
	
		/*メッシュの破棄*/
		if (g_Map.Mesh != NULL)
		{
			g_Map.Mesh->Release();
			g_Map.Mesh = NULL;
		}

		/*マテリアルの破棄*/
		if (g_Map.BuffMat != NULL)
		{	
			g_Map.BuffMat->Release();
			g_Map.BuffMat = NULL;
		}
		/*テクスチャ*/
		for (int nCntMat = 0; nCntMat < (int)g_Map.NumMat; nCntMat++)
		{
			if (g_Map.pTexture[nCntMat] != NULL)
			{
				g_Map.pTexture[nCntMat]->Release();
				g_Map.pTexture[nCntMat] = NULL;
			}
		}
	


}
void UpdateMap(void)
{
	
	
}
void DrawMap(void)
{
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	int nCntMat;
	/*ワールドマトリクスの初期化処理*/
	D3DXMatrixIdentity(&g_Map.mtxWorld);
	/*向きを反映*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Map.rot.y, g_Map.rot.x, g_Map.rot.z);
	D3DXMatrixMultiply(&g_Map.mtxWorld, &g_Map.mtxWorld, &mtxRot);
	/*位置を反映*/
	D3DXMatrixTranslation(&mtxTrans, g_Map.pos.x, g_Map.pos.y, g_Map.pos.z);
	D3DXMatrixMultiply(&g_Map.mtxWorld, &g_Map.mtxWorld, &mtxTrans);
	/*ワールドマトリックスの設定*/
	pDevice->SetTransform(D3DTS_WORLD, &g_Map.mtxWorld);
	/*現在のマテリアルを取得する*/
	pDevice->GetMaterial(&matDef);
	for (nCntMat = 0; nCntMat < (int)g_Map.NumMat; nCntMat++)
	{
		/*マテリアルの設定*/
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, g_Map.pTexture[nCntMat]);
		/*モデルの描画*/
		g_Map.Mesh->DrawSubset(nCntMat);
	}
	/*保持していたマテリアルを戻す*/
	pDevice->SetMaterial(&matDef);
	
}
MAP*GetMap()
{
	return &g_Map;
}
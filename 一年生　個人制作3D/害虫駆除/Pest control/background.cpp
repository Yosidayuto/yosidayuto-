#include "main.h"
#include "background.h"
/*--グローバル変数--*/
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_textureBackground;
/*ポリゴンのワールドマトリックス*/
D3DXMATRIX g_mtxWorldBackground;
/*マテリアルデータへのポインタ*/
D3DXMATERIAL *pMatBackground;/*モデル情報*/
BACKGROUND g_Background;

void InitBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
		/*Xファイルの読み込み*/
		D3DXLoadMeshFromX(
			"data/Xfile/blue sky.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Background.pBuffMatBlock,
			NULL,
			&g_Background.nNumMatBlock,
			&g_Background.pMeshBlock);
		/*マテリアルデータへのポインタを取得*/
		pMatBackground = (D3DXMATERIAL*)g_Background.pBuffMatBlock->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Background.nNumMatBlock; nCntMat++)
		{
			if (pMatBackground[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMatBackground[nCntMat].pTextureFilename, &g_textureBackground);
			}
		}		
		/*初期位置*/
		g_Background.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
void UninitBackground(void)
{
		/*メッシュの破棄*/
		if (g_Background.pMeshBlock != NULL)
		{
			g_Background.pMeshBlock->Release();
			g_Background.pMeshBlock = NULL;
		}

		/*マテリアルの破棄*/
		if (g_Background.pBuffMatBlock != NULL)
		{
			g_Background.pBuffMatBlock->Release();
			g_Background.pBuffMatBlock = NULL;
		}
		/*テクスチャ*/
		for (int nCnt = 0; nCnt < (int)g_Background.nNumMatBlock; nCnt++)
		{
			if (g_textureBackground != NULL)
			{
				g_textureBackground->Release();
				g_textureBackground = NULL;
			}
		}
}
void UpdateBackground(void)
{

}
void DrawBackground(void)
{
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	
		/*ワールドマトリクスの初期化処理*/
		D3DXMatrixIdentity(&g_Background.mtxWorld);
		/*向きを反映*/
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Background.rot.y, g_Background.rot.x, g_Background.rot.z);
		D3DXMatrixMultiply(&g_Background.mtxWorld, &g_Background.mtxWorld, &mtxRot);
		/*位置を反映*/
		D3DXMatrixTranslation(&mtxTrans, g_Background.pos.x, g_Background.pos.y, g_Background.pos.z);
		D3DXMatrixMultiply(&g_Background.mtxWorld, &g_Background.mtxWorld, &mtxTrans);
		/*ワールドマトリックスの設定*/
		pDevice->SetTransform(D3DTS_WORLD, &g_Background.mtxWorld);
		/*現在のマテリアルを取得する*/
		pDevice->GetMaterial(&matDef);


		for (int nCntMat = 0; nCntMat < (int)g_Background.nNumMatBlock; nCntMat++)
		{
			/*マテリアルの設定*/
			pDevice->SetMaterial(&pMatBackground[nCntMat].MatD3D);

			pDevice->SetTexture(0, g_textureBackground);

			/*モデルパーツの描画*/
			g_Background.pMeshBlock->DrawSubset(nCntMat);

		}
		/*保持していたマテリアルを戻す*/
		pDevice->SetMaterial(&matDef);
}
void SetBackground(D3DXVECTOR3 pos)
{
	
		if (g_Background.bsed == false)
		{
			g_Background.pos = pos;
			g_Background.bsed = true;
		}
	
}
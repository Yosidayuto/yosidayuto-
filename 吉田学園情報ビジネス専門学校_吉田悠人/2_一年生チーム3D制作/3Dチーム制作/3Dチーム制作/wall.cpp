#include"wall.h"
#include"main.h"
//グローバル変数
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
/*壁*/
WALL g_Wall[MAX_WALL];


void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].dir = D3DXVECTOR3(0, 0, 0);
		g_Wall[nCntWall].pos = D3DXVECTOR3(0, 0, 0);
		g_Wall[nCntWall].buse = false;
	}
	/*頂点バッファの生成*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);
	D3DXCreateTextureFromFile(pDevice, "画像/baria.jpg", &g_pTextureWall);
	VERTEX_3D*pVtx = NULL;
	/*頂点バッファをロック*/
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
	/*頂点座標の設定*/
	pVtx[0].pos = D3DXVECTOR3(-WALL_X / 2, WALL_Y / 2, 0);
	pVtx[1].pos = D3DXVECTOR3(WALL_X / 2, WALL_Y / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(-WALL_X / 2, -WALL_Y / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(WALL_X / 2, -WALL_Y / 2, 0);
	/*各頂点の法線の設定（ベクトルの大きさは１にする必要がある）*/
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	/*頂点カラーの設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);
	
	}
	pVtx += 4;
	/*頂点バッファのアンロック*/
	g_pVtxBuffWall->Unlock();
}
void UninitWall(void)
{
	/*頂点バッファの解放*/
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}
void UpdateWall(void)
{

}
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos)
{
	VERTEX_3D*pVtx = NULL;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (!g_Wall[nCntWall].buse)
		{
			/*位置設定*/
			g_Wall[nCntWall].pos = pos;
			/*向き設定*/
			g_Wall[nCntWall].dir = dir;

			/*頂点バッファをロック*/
			g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
			/*位置処理*/
			pVtx[0].pos = D3DXVECTOR3((endPos.x ),(WALL_Y / 2), 0);
			pVtx[1].pos = D3DXVECTOR3((startPos.x ),(WALL_Y / 2), 0);
			pVtx[2].pos = D3DXVECTOR3((endPos.x ),(-WALL_Y / 2), 0);
			pVtx[3].pos = D3DXVECTOR3((startPos.x ),(-WALL_Y / 2), 0);
			/*頂点バッファのアンロック*/
			g_pVtxBuffWall->Unlock();
			/*使用しているか*/
			g_Wall[nCntWall].buse = true;
			break;
		}
		pVtx += 4;
	}
	
}
void DrawWall(void)
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	
	
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].buse)
		{
			/*アルファテストを有効化*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			/*アルファテスト基準値の設定*/
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			/*アルファテストの比較方法の設定*/
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].dir.y, g_Wall[nCntWall].dir.x, g_Wall[nCntWall].dir.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);
			/*ワールドマトリクスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);
			/*頂点バッファをデバイスのデータストリームに設定*/
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));
			/*頂点フォーマットの設定*/
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureWall);
			///*レンダリングステート(加算合成処理)*/
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			/*ポリゴン描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			///*レンダーステート*/
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			/*アルファテストを無効化*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}
	
	pDevice->SetTexture(0, NULL);
}
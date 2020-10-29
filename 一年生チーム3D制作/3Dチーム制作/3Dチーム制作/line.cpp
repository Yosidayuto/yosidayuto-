#include"line.h"
#include"main.h"
#include"wall.h"
//グローバル変数
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;
/*線*/
LINE  g_Line[MAX_LINE];


void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nLine = 0; nLine < MAX_LINE; nLine++)
	{
		g_Line[nLine].pos = D3DXVECTOR3(0, 0, 0);
		g_Line[nLine].rot = D3DXVECTOR3(0, 0, 0);
		g_Line[nLine].buse = false;
	}
	/*頂点バッファの生成*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_POINT) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_POINT,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);
	VERTEX_POINT*pVtx = NULL;
	/*頂点バッファをロック*/
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);
	/*頂点座標の設定*/
	pVtx[0].pos = D3DXVECTOR3(0,0,0);
	pVtx[1].pos = D3DXVECTOR3(0,0,0);
	
	/*頂点カラーの設定*/
	pVtx[0].col = D3DXCOLOR(1, 1, 1, 1);
	pVtx[1].col = D3DXCOLOR(1, 1, 1, 1);

	/*頂点バッファのアンロック*/
	g_pVtxBuffLine->Unlock();
}
void UninitLine(void)
{
	/*頂点バッファの解放*/
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
	
}
void UpdateLine(void)
{
	VERTEX_POINT*pVtx = NULL;
	/*頂点バッファをロック*/
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);
	
	/*頂点バッファのアンロック*/
	g_pVtxBuffLine->Unlock();
}
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos, D3DXCOLOR color)
{
	VERTEX_POINT*pVtx = NULL;
	/*頂点バッファをロック*/
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);
	for (int nLine = 0; nLine < MAX_LINE; nLine++)
	{
		if (!g_Line[nLine].buse)
		{
			
			/*位置設定*/
			g_Line[nLine].pos = pos;
			/*向き設定*/
			g_Line[nLine].rot = rot;
			
			/*位置処理*/
			pVtx[0].pos = startPos;
			pVtx[1].pos = endPos;

			pVtx[0].col = color;
			pVtx[1].col = color;
			SetWall(pos, rot, startPos, endPos);
			/*使用しているか*/
			g_Line[nLine].buse = true;
			break;
		}
		pVtx += 2;
	}
	/*頂点バッファのアンロック*/
	g_pVtxBuffLine->Unlock();
}
void DrawLine(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;


	for (int nLine = 0; nLine < MAX_LINE; nLine++)
	{
		if (g_Line[nLine].buse)
		{
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Line[nLine].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Line[nLine].rot.y, g_Line[nLine].rot.x, g_Line[nLine].rot.z);
			D3DXMatrixMultiply(&g_Line[nLine].mtxWorld, &g_Line[nLine].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Line[nLine].pos.x, g_Line[nLine].pos.y, g_Line[nLine].pos.z);
			D3DXMatrixMultiply(&g_Line[nLine].mtxWorld, &g_Line[nLine].mtxWorld, &mtxTrans);
			/*ワールドマトリクスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Line[nLine].mtxWorld);
			/*頂点バッファをデバイスのデータストリームに設定*/
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_POINT));
			/*頂点フォーマットの設定*/
			pDevice->SetFVF(FVF_VERTEX_POINT);
			/*ポリゴン描画*/
			pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 2);
		}
	}
}
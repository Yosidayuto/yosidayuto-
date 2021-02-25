#include "main.h"
#include "bg.h"

/*マクロ定義*/
#define MAX_BG (128)
/*構造体*/
typedef struct
{
	int nCounterAnim;//カウンター
	int nPtternAnim;//パターンNo
}BG;
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePolygonBg = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonbg = NULL;//バッファへのポインター

BG g_aBg[MAX_BG];
/*初期化処理*/
void InintPolygonbg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//頂点情報へのポインター
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/bg100.png", &g_pTexturePolygonBg);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffPolygonbg,//変数名が変わると変更が必要
		NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得

	g_pVtxBuffPolygonbg->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない

													  //頂点座標の設定（右回りで設定する）

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	//rhwの設定（値は１，０で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャの座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);
	//頂点データをアンロックする
	g_pVtxBuffPolygonbg->Unlock();

}

void UninitPolygonbg(void)
{



	//テクスチャの設定
	if (g_pTexturePolygonBg != NULL)
	{
		g_pTexturePolygonBg->Release();
		g_pTexturePolygonBg = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffPolygonbg != NULL)
	{
		g_pVtxBuffPolygonbg->Release();
		g_pVtxBuffPolygonbg = NULL;
	}
}
void UpdatePolygonbg(void)
{
	VERTEX_2D*pVtx;
	int  nCntBg;
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffPolygonbg->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		g_aBg[nCntBg].nCounterAnim++;
		if (g_aBg[nCntBg].nCounterAnim == 5)
		{
			g_aBg[nCntBg].nCounterAnim = 0;//カウンターを初期値に戻す
			g_aBg[nCntBg].nPtternAnim++;
			if (g_aBg[nCntBg].nPtternAnim == 1000)
			{
				g_aBg[nCntBg].nPtternAnim = 0;

			}

		}
		pVtx[0].tex = D3DXVECTOR2(0.0f, g_aBg[nCntBg].nPtternAnim*0.99f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, g_aBg[nCntBg].nPtternAnim*0.99f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, g_aBg[nCntBg].nPtternAnim*0.99f + 0.99f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, g_aBg[nCntBg].nPtternAnim*0.99f + 0.99f);


	}
	/*頂点データをアンロック*/
	g_pVtxBuffPolygonbg->Unlock();
}
//描画処理
void DrawPolygonbg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonbg, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygonBg);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

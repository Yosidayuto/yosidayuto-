#include "main.h"
#include "result.h"
#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//バッファへのポインター

LPDIRECT3DTEXTURE9 g_pTextureResultRogo = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultRogo = NULL;//バッファへのポインター


int nCutScore01 = 0;
int nCutScore02 = 0;
/*---------------------------------------------------*/
/*初期化処理										*/
/*-------------------------------------------------*/
void InintResult(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/bg000.png", &g_pTextureResult);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*2,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffResult,//変数名が変わると変更が必要
		NULL);
	
	/*-----------------------------------------------------------------------------------------------------------------------*/

	D3DXCreateTextureFromFile(pDevice, "TEXTURE/gameover_logo.png", &g_pTextureResultRogo);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*2,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffResultRogo,//変数名が変わると変更が必要
		NULL);

	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得

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
	g_pVtxBuffResult->Unlock();

	/*------------------------------------------------------------------------------------------------------------------------------------*/

	g_pVtxBuffResultRogo->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得

	pVtx[4].pos = D3DXVECTOR3(-SCREEN_WIDTH/3, -SCREEN_HEIGHT/5, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH/3, -SCREEN_HEIGHT/5, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-SCREEN_WIDTH/3, SCREEN_HEIGHT/5, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH/3, SCREEN_HEIGHT/5, 0.0f);
	//rhwの設定（値は１，０で固定）
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;
	//頂点カラーの設定（0～255の数値で設定）
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャの座標の設定
	pVtx[4].tex = D3DXVECTOR2(0, 0);
	pVtx[5].tex = D3DXVECTOR2(1, 0);
	pVtx[6].tex = D3DXVECTOR2(0, 1);
	pVtx[7].tex = D3DXVECTOR2(1, 1);
	//頂点データをアンロックする
	g_pVtxBuffResultRogo->Unlock();
	
}
void UpdateResult(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	g_pVtxBuffResultRogo->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得

	pVtx[4].pos = D3DXVECTOR3(650+(-SCREEN_WIDTH / 3), 300+(-SCREEN_HEIGHT / 5), 0.0f);
	pVtx[5].pos = D3DXVECTOR3(650+( SCREEN_WIDTH / 3), 300+(-SCREEN_HEIGHT / 5), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(650+(-SCREEN_WIDTH / 3), 300+( SCREEN_HEIGHT / 5), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(650+( SCREEN_WIDTH / 3), 300+( SCREEN_HEIGHT / 5), 0.0f);
	
	for (int nCnt = 0; nCnt < 255; nCnt++)
	{
		nCutScore01++;
		if (nCutScore01 == 500)
		{
			nCutScore01 = 0;//カウンターを初期値に戻す
			nCutScore02++;
			if (nCutScore02 >= 255)
			{
				nCutScore02 = 255;
			}
		}
	}
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, nCutScore02);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, nCutScore02);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, nCutScore02);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, nCutScore02);

	g_pVtxBuffResultRogo->Unlock();//頂点データをアンロックする

}
void UninitResult(void)
{
//テクスチャの設定
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
void DrawResult(void) 
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	/*----------------------------------------------------------------------*/
	
	
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffResultRogo, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultRogo);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, NUM_POLYGON);
}
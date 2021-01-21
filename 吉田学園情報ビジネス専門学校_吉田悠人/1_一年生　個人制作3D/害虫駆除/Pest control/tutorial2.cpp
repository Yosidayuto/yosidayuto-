#include "main.h"
#include "input.h"
#include "fade.h"
#include "tutorial2.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTutorial2 = {};//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial2 = {};//バッファへのポインター
TUTORIAL2 g_Tutorial2;
/*---------------------------------------------------*/
/*初期化処理										*/
/*-------------------------------------------------*/
void InintTutorial2(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*位置の初期化*/
	g_Tutorial2.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	/*使用処理の初期化*/
	g_Tutorial2.buse = false;
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "data/image//tutorial_2.png", &g_pTextureTutorial2);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffTutorial2,//変数名が変わると変更が必要
		NULL);

	g_pVtxBuffTutorial2->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
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
	g_pVtxBuffTutorial2->Unlock();


}
void UninitTutorial2(void)
{
	//テクスチャの設定
	if (g_pTextureTutorial2 != NULL)
	{
		g_pTextureTutorial2->Release();
		g_pTextureTutorial2= NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffTutorial2 != NULL)
	{
		g_pVtxBuffTutorial2->Release();
		g_pVtxBuffTutorial2 = NULL;
	}	
}
void UpdateTutorial2(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_pVtxBuffTutorial2->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_Tutorial2.pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Tutorial2.pos.x + -SCREEN_WIDTH / 2, g_Tutorial2.pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Tutorial2.pos.x + SCREEN_WIDTH / 2, g_Tutorial2.pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Tutorial2.pos.x + -SCREEN_WIDTH / 2, g_Tutorial2.pos.y + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Tutorial2.pos.x + SCREEN_WIDTH / 2, g_Tutorial2.pos.y + SCREEN_HEIGHT / 2, 0.0f);
	g_pVtxBuffTutorial2->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(MODE_GAME);
	}
}
void DrawTutorial2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial2, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial2);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}
#include"main.h"
#include"fade.h"

#define FADE_RATE (0.01f)
/*グローバル変数*/
LPDIRECT3DTEXTURE9 g_apTextureFade= NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade= NULL;		//頂点バッファへのポインタ

MODE g_modeNext = MODE_TITLE;	//次の画面（モード）
FADE g_fade;										//フェード状態
D3DXCOLOR g_colorFade;								//フェード色

/*初期化処理*/
void InitFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒い画面（透明）

	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//バッファサイズ
		D3DUSAGE_WRITEONLY,											//(固定)
		FVF_VERTEX_2D,												//頂点フォーマット
		D3DPOOL_MANAGED,											//（固定）
		&g_pVtxBuffFade,												//変数名が変わると変更が必要
		NULL);
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	//rhwの設定（値は１，０で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	g_pVtxBuffFade->Unlock();

}
void UninitFade(void)
{
	////テクスチャの設定
	//if (g_apTextureFade != NULL)
	//{
	//	g_apTextureFade->Release();
	//	g_apTextureFade = NULL;
	//}

	//頂点バッファの開放
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
void UpdaFade(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得

	
		if (g_fade != FADE_NONE)
		{//フェード処理中
			if (g_fade == FADE_IN)
			{//フェードイン処理
				g_colorFade.a -= FADE_RATE;			//a値を減算して後ろの画面を浮き上がらせる
				if (g_colorFade.a <= 0.0f)
				{
					/*フェード処理終了*/
					g_colorFade.a = 0.0f;
					g_fade = FADE_NONE;
				}
			}
			else if (g_fade == FADE_OUT)
			{//フェードアウト処理
				g_colorFade.a += FADE_RATE;			//a値を加算して後ろの画面を消していく
				if (g_colorFade.a >= 1.0f)
				{
					/*フェードイン処理に切り替え*/
					g_colorFade.a = 1.0f;
					g_fade = FADE_IN;

					/*モードを設定*/
					SetMode(g_modeNext);

				}
			}
		}
		
	
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;
	
	pVtx += 4;
	g_pVtxBuffFade->Unlock();
}

void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureFade);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

/*フェードの状態設定*/
void SetFade(MODE modeNext)
{
	
	g_fade = FADE_OUT;
	g_modeNext = modeNext;


}

FADE GetFade(void)
{
	return g_fade;
}
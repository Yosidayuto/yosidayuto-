#include "main.h"
#include "title.h"
#include"fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//バッファへのポインター

LPDIRECT3DTEXTURE9 g_pTextureTitlerogo = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlerogo = NULL;//バッファへのポインター

LPDIRECT3DTEXTURE9 g_pTextureTitlePusy = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlePusy = NULL;//バッファへのポインター


TITLE g_Title;
float nCountercol2 = 0.0f;
int nCountercol = 0;
int nSwitch=0;
int siltuti = 0;
/*---------------------------------------------------*/
/*初期化処理										*/
/*-------------------------------------------------*/
void InintTitle(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntTitle = 4; nCntTitle < 7; nCntTitle++)
	{
		g_Title.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Title.move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_Title.bUse = false;
	}
	
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/bg000.png", &g_pTextureTitle);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX *3,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffTitle,//変数名が変わると変更が必要
		NULL);
	
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/title_logo.png", &g_pTextureTitlerogo);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX *3,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffTitlerogo,//変数名が変わると変更が必要
		NULL);

	D3DXCreateTextureFromFile(pDevice, "TEXTURE/press_enter.png", &g_pTextureTitlePusy);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * 3,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffTitlePusy,//変数名が変わると変更が必要
		NULL);

	
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得

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
	g_pVtxBuffTitle->Unlock();

	
	g_pVtxBuffTitlerogo->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtx[4].pos = D3DXVECTOR3(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 4, 0.0f);
	pVtx[5].pos = D3DXVECTOR3( SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 4, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 4, 0.0f);
	pVtx[7].pos = D3DXVECTOR3( SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 4, 0.0f);

	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[4].tex = D3DXVECTOR2(0, 0);
	pVtx[5].tex = D3DXVECTOR2(1, 0);
	pVtx[6].tex = D3DXVECTOR2(0, 1);
	pVtx[7].tex = D3DXVECTOR2(1, 1);
	g_pVtxBuffTitlerogo->Unlock();


	g_pVtxBuffTitlePusy->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtx[8].pos = D3DXVECTOR3(-SCREEN_WIDTH / 3, -SCREEN_HEIGHT / 10, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, -SCREEN_HEIGHT / 10, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(-SCREEN_WIDTH / 3, SCREEN_HEIGHT / 10, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 10, 0.0f);

	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[8].tex = D3DXVECTOR2(0, 0);
	pVtx[9].tex = D3DXVECTOR2(1, 0);
	pVtx[10].tex = D3DXVECTOR2(0, 1);
	pVtx[11].tex = D3DXVECTOR2(1, 1);
	g_pVtxBuffTitlePusy->Unlock();
}
void UpdateTitle(void)
{

	VERTEX_2D *pVtx;//頂点情報へのポインター
	g_pVtxBuffTitlerogo->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	if (g_Title.bUse == true)
	{
		g_Title.pos += g_Title.move*0.5f;
		pVtx[4].pos = D3DXVECTOR3(g_Title.pos.x + (-SCREEN_WIDTH / 3), g_Title.pos.y + (-SCREEN_HEIGHT / 5), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Title.pos.x + (SCREEN_WIDTH / 3), g_Title.pos.y + (-SCREEN_HEIGHT / 5), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Title.pos.x + (-SCREEN_WIDTH / 3), g_Title.pos.y + (SCREEN_HEIGHT / 5), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Title.pos.x + (SCREEN_WIDTH / 3), g_Title.pos.y + (SCREEN_HEIGHT / 5), 0.0f);
		/*敵が画面外に行ったら*/
		if (g_Title.pos.y >=300 )
		{
			/*使わなくする*/
			g_Title.pos -= g_Title.move;
		}
	}
	g_pVtxBuffTitlerogo->Unlock();
	g_pVtxBuffTitlePusy->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtx[8].pos = D3DXVECTOR3(650+(-SCREEN_WIDTH / 5), 500 + ( -SCREEN_HEIGHT / 12), 0.0f);
	pVtx[9].pos = D3DXVECTOR3(650+(SCREEN_WIDTH / 5), 500 + (-SCREEN_HEIGHT / 12), 0.0f);
	pVtx[10].pos = D3DXVECTOR3(650+ (-SCREEN_WIDTH /5), 500 + (SCREEN_HEIGHT / 12), 0.0f);
	pVtx[11].pos = D3DXVECTOR3(650+(SCREEN_WIDTH / 5), 500 + (SCREEN_HEIGHT / 12), 0.0f);
	for (int nCnt = 0; nCnt < 1000; nCnt++)
	{
		
		nCountercol++;
		if (nCountercol >= 1000)
		{
			nCountercol = 0;//カウンターを初期値に戻す

			
			switch (nSwitch)
			{
			case 0:
				nCountercol2+=0.01f;
				if (nCountercol2 >= 1.0f)
				{
					nSwitch = 1;
				}
				break;
			case 1:
				nCountercol2-=0.01f;
				if (nCountercol2 <= 0.0f)
				{
					nSwitch = 0;
				}
				break;
				
			}
		
		}
	}
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, nCountercol2);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, nCountercol2);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, nCountercol2);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, nCountercol2);

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		siltuti++;
	}
	if (siltuti >= 1)
	{
		for (int nCnt = 0; nCnt < 255; nCnt++)
		{

			nCountercol += 1;
			if (nCountercol >= 0)
			{
				nCountercol = 0;//カウンターを初期値に戻す


				switch (nSwitch)
				{
				case 0:
					nCountercol2 += 0.5f;
					if (nCountercol2 >= 1.0f)
					{
						nSwitch = 1;
					}
					break;
				case 1:
					nCountercol2 -= 0.1f;
					if (nCountercol2 <= 0.0f)
					{
						nSwitch = 0;
					}
					break;

				}

			}
		}
	}
	if (GetKeyboarRelease(DIK_RETURN))	//エンターキーを押すと進む
	{
		SetFade(MODE_GAME);
	}
	g_pVtxBuffTitlePusy->Unlock();
}
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTitlerogo, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitlerogo);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, NUM_POLYGON);



	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTitlePusy, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitlePusy);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, NUM_POLYGON);

}
void UninitTitle(void)
{
	//テクスチャの設定
	if (g_pTextureTitle!= NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle= NULL;
	}
	
	//頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle= NULL;
	}
	
	
}

void SetTitle(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	g_pVtxBuffTitlerogo->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得

	g_Title.pos = pos;
	

	if (g_Title.bUse == false)
	{
		pVtx[4].pos = D3DXVECTOR3(g_Title.pos.x + (-SCREEN_WIDTH / 2), g_Title.pos.y + (-SCREEN_HEIGHT / 4), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Title.pos.x + (SCREEN_WIDTH / 2), g_Title.pos.y + (-SCREEN_HEIGHT / 4), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Title.pos.x + (-SCREEN_WIDTH / 2), g_Title.pos.y + (SCREEN_HEIGHT / 4), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Title.pos.x + (SCREEN_WIDTH / 2), g_Title.pos.y + (SCREEN_HEIGHT / 4), 0.0f);

		g_Title.bUse = true;
	}
	g_pVtxBuffTitlerogo->Unlock();
}

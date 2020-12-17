#include "main.h"
#include "gameover.h"
#include "input.h"
#include "fade.h"
#include "Game.h"
#include "sound.h"
/*グローバル変数*/
LPDIRECT3DTEXTURE9 g_pTextureGameover[GAMEOVER_TEXTURE_MAX] = {};//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxGameover[GAMEOVER_TEXTURE_MAX] = {};//バッファへのポインター
GAMEOVER g_Gameover[GAMEOVER_TEXTURE_MAX];
int g_nSelectGameover;	//選択
typedef struct
{
	char *pFilename;	// ファイル名
}FILE_GAMEOVER;
/*ファイル*/
FILE_GAMEOVER g_File[GAMEOVER_TEXTURE_MAX] =
{
	{ "data/image/GameOver.png" },
	{ "data/image/RestartButton.png" },
	{ "data/image/ShutDownButton.png" },

};

/*---------------------------------------------------*/
/*初期化処理										*/
/*-------------------------------------------------*/
void InintGameover(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nGameover = 0; nGameover < GAMEOVER_TEXTURE_MAX; nGameover++)
	{
		/*位置の初期化*/
		g_Gameover[nGameover].pos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*選択処理の初期化*/
		g_nSelectGameover = 0;
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(pDevice, g_File[nGameover].pFilename, &g_pTextureGameover[nGameover]);
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * 3,//バッファサイズ
			D3DUSAGE_WRITEONLY,//(固定)
			FVF_VERTEX_2D,//頂点フォーマット
			D3DPOOL_MANAGED,//（固定）
			&g_pVtxGameover[nGameover],//変数名が変わると変更が必要
			NULL);
		g_pVtxGameover[nGameover]->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
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
		g_pVtxGameover[nGameover]->Unlock();
	}
	
}
void UpdateGameover(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	/*背景*/
	g_pVtxGameover[0]->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_Gameover[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Gameover[0].pos.x + -SCREEN_WIDTH / 2, g_Gameover[0].pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Gameover[0].pos.x + SCREEN_WIDTH / 2, g_Gameover[0].pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Gameover[0].pos.x + -SCREEN_WIDTH / 2, g_Gameover[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Gameover[0].pos.x + SCREEN_WIDTH / 2, g_Gameover[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	g_pVtxGameover[0]->Unlock();
	/*リスタートコマンド*/
	g_pVtxGameover[1]->Lock(0, 0, (void**)&pVtx, 0);
	/*位置設定*/
	g_Gameover[1].pos = D3DXVECTOR3(425.0f, 540.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Gameover[1].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[1].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Gameover[1].pos.x + GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[1].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Gameover[1].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[1].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Gameover[1].pos.x + GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[1].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	/*カラー設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_pVtxGameover[1]->Unlock();
	/*終了コマンド*/
	g_pVtxGameover[2]->Lock(0, 0, (void**)&pVtx, 0);
	/*位置設定*/
	g_Gameover[2].pos = D3DXVECTOR3(850.0f, 540.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Gameover[2].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[2].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Gameover[2].pos.x + GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[2].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Gameover[2].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[2].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Gameover[2].pos.x + GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[2].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	/*カラー設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pVtxGameover[2]->Unlock();
	/*選択処理*/
	if (GetKeyboardTrigger(DIK_RIGHT))
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectGameover = 1;
	}
	else if (GetKeyboardTrigger(DIK_LEFT))
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectGameover = 0;
	}
	/*選択状態のUI*/
	if (g_nSelectGameover == 0)
	{
		g_pVtxGameover[1]->Lock(0, 0, (void**)&pVtx, 0);
		/*位置設定*/
		pVtx[0].pos = D3DXVECTOR3((g_Gameover[1].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2) + 10, (g_Gameover[1].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Gameover[1].pos.x + GAMEOVER_COMMAND_SIZE_X / 2) - 10, (g_Gameover[1].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Gameover[1].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2) + 10, (g_Gameover[1].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Gameover[1].pos.x + GAMEOVER_COMMAND_SIZE_X / 2) - 10, (g_Gameover[1].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		/*カラー設定*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxGameover[1]->Unlock();
	}
	else
	{
		g_pVtxGameover[2]->Lock(0, 0, (void**)&pVtx, 0);
		/*位置設定*/
		pVtx[0].pos = D3DXVECTOR3((g_Gameover[2].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2) + 10, (g_Gameover[2].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Gameover[2].pos.x + GAMEOVER_COMMAND_SIZE_X / 2) - 10, (g_Gameover[2].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Gameover[2].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2) + 10, (g_Gameover[2].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Gameover[2].pos.x + GAMEOVER_COMMAND_SIZE_X / 2) - 10, (g_Gameover[2].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		/*カラー設定*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxGameover[2]->Unlock();
	}
	if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectGameover == 0)
	{
		PlaySound(SOUND_LABEL_SE_DECIDED);
	
		SetFade(MODE_TITLE);
	}
	else if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectGameover == 1)
	{
		PlaySound(SOUND_LABEL_SE_DECIDED);
		exit(1);
	}

}
void UninitGameover(void)
{
	for (int nGameover = 0; nGameover < GAMEOVER_TEXTURE_MAX; nGameover++)
	{
		//テクスチャの設定
		if (g_pTextureGameover != NULL)
		{
			g_pTextureGameover[nGameover]->Release();
			g_pTextureGameover[nGameover] = NULL;
		}

		//頂点バッファの開放
		if (g_pVtxGameover[nGameover] != NULL)
		{
			g_pVtxGameover[nGameover]->Release();
			g_pVtxGameover[nGameover] = NULL;
		}
	}
}
void DrawGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nGameover = 0; nGameover < GAMEOVER_TEXTURE_MAX; nGameover++)
	{
		//頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxGameover[nGameover], 0, sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureGameover[nGameover]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
typedef struct
{
	char *pFilename;	// ファイル名
}FILE_TITLE;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_TEXTURE_MAX] = {};//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle[TITLE_TEXTURE_MAX] = {};//バッファへのポインター
TITLE g_Title[TITLE_TEXTURE_MAX];
int g_nSelectTitle;
FILE_TITLE g_File[TITLE_TEXTURE_MAX] =
{
	{ "画像/たいとる画面.png" },
	{ "画像/title.png" },
	{ "画像/titleback.png" },
	{ "画像/" },
};

/*---------------------------------------------------*/
/*初期化処理										*/
/*-------------------------------------------------*/
void InintTitle(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nTitle = 0; nTitle < TITLE_TEXTURE_MAX; nTitle++)
	{
		/*位置の初期化*/
		g_Title[nTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_nSelectTitle = 0;
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(pDevice, g_File[nTitle].pFilename, &g_pTextureTitle[nTitle]);
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//バッファサイズ
			D3DUSAGE_WRITEONLY,//(固定)
			FVF_VERTEX_2D,//頂点フォーマット
			D3DPOOL_MANAGED,//（固定）
			&g_pVtxBuffTitle[nTitle],//変数名が変わると変更が必要
			NULL);

		g_pVtxBuffTitle[nTitle]->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
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
		g_pVtxBuffTitle[nTitle]->Unlock();
	}

}
void UninitTitle(void)
{
	for (int nTitle = 0; nTitle < TITLE_TEXTURE_MAX; nTitle++)
	{
		//テクスチャの設定
		if (g_pTextureTitle[nTitle] != NULL)
		{
			g_pTextureTitle[nTitle]->Release();
			g_pTextureTitle[nTitle] = NULL;
		}
		//頂点バッファの開放
		if (g_pVtxBuffTitle[nTitle] != NULL)
		{
			g_pVtxBuffTitle[nTitle]->Release();
			g_pVtxBuffTitle[nTitle] = NULL;
		}
	}
	


}
void UpdateTitle(void)
{
	/*頂点情報へのポインター*/
	VERTEX_2D *pVtx;
	/*コントローラーの処理*/
	JOYINFOEX JOYPAD;
	/*ジョイパットの入力*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // 全ての情報を取得

	/*背景*/
	g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_Title[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Title[0].pos.x + -SCREEN_WIDTH / 2, g_Title[0].pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Title[0].pos.x + SCREEN_WIDTH / 2, g_Title[0].pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Title[0].pos.x + -SCREEN_WIDTH / 2, g_Title[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Title[0].pos.x + SCREEN_WIDTH / 2, g_Title[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	g_pVtxBuffTitle[0]->Unlock();
	/*スタートコマンド*/
	g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);
	/*位置設定*/
	g_Title[1].pos = D3DXVECTOR3(920.0f, 400.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Title[1].pos.x + -TITLE_COMMAND_SIZE_X / 2, g_Title[1].pos.y + -TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Title[1].pos.x + TITLE_COMMAND_SIZE_X / 2, g_Title[1].pos.y + -TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Title[1].pos.x + -TITLE_COMMAND_SIZE_X / 2, g_Title[1].pos.y + TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Title[1].pos.x + TITLE_COMMAND_SIZE_X / 2, g_Title[1].pos.y + TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	/*カラー設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pVtxBuffTitle[1]->Unlock();
	/*終了コマンド*/
	g_pVtxBuffTitle[2]->Lock(0, 0, (void**)&pVtx, 0);
	/*位置設定*/
	g_Title[2].pos = D3DXVECTOR3(920.0f, 500.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Title[2].pos.x + -TITLE_COMMAND_SIZE_X / 2, g_Title[2].pos.y + -TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Title[2].pos.x + TITLE_COMMAND_SIZE_X / 2, g_Title[2].pos.y + -TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Title[2].pos.x + -TITLE_COMMAND_SIZE_X / 2, g_Title[2].pos.y + TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Title[2].pos.x + TITLE_COMMAND_SIZE_X / 2, g_Title[2].pos.y + TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	/*カラー設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pVtxBuffTitle[2]->Unlock();
	/*タイトルロゴ*/
	//g_pVtxBuffTitle[3]->Lock(0, 0, (void**)&pVtx, 0);
	///*位置設定*/
	//g_Title[3].pos = D3DXVECTOR3(640.0f, 260.0f, 0.0f);
	//pVtx[0].pos = D3DXVECTOR3(g_Title[3].pos.x + -TITLE_LOGO_SIZE_X / 2, g_Title[3].pos.y + -TITLE_LOGO_SIZE_Y / 2, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_Title[3].pos.x + TITLE_LOGO_SIZE_X / 2, g_Title[3].pos.y + -TITLE_LOGO_SIZE_Y / 2, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_Title[3].pos.x + -TITLE_LOGO_SIZE_X / 2, g_Title[3].pos.y + TITLE_LOGO_SIZE_Y / 2, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_Title[3].pos.x + TITLE_LOGO_SIZE_X / 2, g_Title[3].pos.y + TITLE_LOGO_SIZE_Y / 2, 0.0f);
	///*カラー設定*/
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_pVtxBuffTitle[3]->Unlock();
	/*選択処理*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD) == JOYERR_NOERROR)
	{
	
		if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//後ろに倒すスティック
		{
			g_nSelectTitle = 1;
		}
		if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//前に倒すスティック
		{
			g_nSelectTitle = 0;
		}
	
		if (JOYPAD.dwButtons & JOY_BUTTON1&&g_nSelectTitle == 0)
		{
			SetFade(MODE_TUTORIAL);
		}
		else if (JOYPAD.dwButtons& JOY_BUTTON1&&g_nSelectTitle == 1)
		{
			exit(1);
		}

	}
	/*if (GetKeyboardTrigger(DIK_UP))
	{
		
		g_nSelectTitle = 0;
	}
	else if (GetKeyboardTrigger(DIK_DOWN))
	{
		
		g_nSelectTitle = 1;
	}*/

	/*選択状態のUI*/
	if (g_nSelectTitle == 0)
	{
		g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);
		/*位置設定*/
	/*	pVtx[0].pos = D3DXVECTOR3((g_Title[1].pos.x + -TITLE_COMMAND_SIZE_X / 2) + 10, (g_Title[1].pos.y + -TITLE_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Title[1].pos.x + TITLE_COMMAND_SIZE_X / 2) - 10, (g_Title[1].pos.y + -TITLE_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Title[1].pos.x + -TITLE_COMMAND_SIZE_X / 2) + 10, (g_Title[1].pos.y + TITLE_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Title[1].pos.x + TITLE_COMMAND_SIZE_X / 2) - 10, (g_Title[1].pos.y + TITLE_COMMAND_SIZE_Y / 2) - 10, 0.0f);*/
		/*カラー設定*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxBuffTitle[1]->Unlock();
	}
	else
	{
		g_pVtxBuffTitle[2]->Lock(0, 0, (void**)&pVtx, 0);
		/*位置設定*/
	/*	pVtx[0].pos = D3DXVECTOR3((g_Title[2].pos.x + -TITLE_COMMAND_SIZE_X / 2) + 10, (g_Title[2].pos.y + -TITLE_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Title[2].pos.x + TITLE_COMMAND_SIZE_X / 2) - 10, (g_Title[2].pos.y + -TITLE_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Title[2].pos.x + -TITLE_COMMAND_SIZE_X / 2) + 10, (g_Title[2].pos.y + TITLE_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Title[2].pos.x + TITLE_COMMAND_SIZE_X / 2) - 10, (g_Title[2].pos.y + TITLE_COMMAND_SIZE_Y / 2) - 10, 0.0f);*/
		/*カラー設定*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxBuffTitle[2]->Unlock();
	}

	if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectTitle == 0)
	{
		SetFade(MODE_TUTORIAL);
	}
	else if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectTitle == 1)
	{
		exit(1);
	}
}
void DrawTitle(void)
{
	for (int nTitle = 0; nTitle < TITLE_TEXTURE_MAX; nTitle++)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		//頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[nTitle], 0, sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nTitle]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

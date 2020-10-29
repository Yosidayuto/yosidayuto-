#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "time.h"

typedef struct
{
	char *pFilename;	// ファイル名

}FILE_RESULT;

/*グローバル変数*/

LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_TEXTURE_MAX] = {};//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxResult[RESULT_TEXTURE_MAX] = {};//バッファへのポインター
RESULT g_Result[RESULT_TEXTURE_MAX];
int g_nSelectResult;	//選択
/*ファイル*/
FILE_RESULT g_File[RESULT_TEXTURE_MAX] =
{
	{ "画像/リザルト画面.png" },
	{ "画像/リザルト.png" },
	{ "画像/back.png" },
};

/*---------------------------------------------------*/
/*初期化処理										*/
/*-------------------------------------------------*/
void InintResult(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nResult = 0; nResult < RESULT_TEXTURE_MAX; nResult++)
	{
		/*位置の初期化*/
		g_Result[nResult].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*選択処理の初期化*/
		g_nSelectResult = 0;											//0が選択リスタート
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(pDevice, g_File[nResult].pFilename, &g_pTextureResult[nResult]);
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//バッファサイズ
			D3DUSAGE_WRITEONLY,//(固定)
			FVF_VERTEX_2D,//頂点フォーマット
			D3DPOOL_MANAGED,//（固定）
			&g_pVtxResult[nResult],//変数名が変わると変更が必要
			NULL);

		g_pVtxResult[nResult]->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
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
		g_pVtxResult[nResult]->Unlock();
	}
}
void UpdateResult(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	/*コントローラーの処理*/
	JOYINFOEX JOYPAD;

	/*ジョイパットの入力*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // 全ての情報を取得

	/*背景*/
	g_pVtxResult[0]->Lock(0, 0, (void**)&pVtx, 0);//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_Result[0].pos= D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Result[0].pos.x + - SCREEN_WIDTH/2, g_Result[0].pos.y + -SCREEN_HEIGHT/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Result[0].pos.x + SCREEN_WIDTH/2, g_Result[0].pos.y + -SCREEN_HEIGHT/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Result[0].pos.x +  -SCREEN_WIDTH/2, g_Result[0].pos.y + SCREEN_HEIGHT/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Result[0].pos.x + SCREEN_WIDTH/2, g_Result[0].pos.y + SCREEN_HEIGHT/2, 0.0f);
	g_pVtxResult[0]->Unlock();
	/*リスタートコマンド*/
	g_pVtxResult[1]->Lock(0, 0, (void**)&pVtx, 0);
	/*位置設定*/
	g_Result[1].pos = D3DXVECTOR3(425.0f, 640.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Result[1].pos.x + -RESULT_COMMAND_SIZE_X /2, g_Result[1].pos.y + -RESULT_COMMAND_SIZE_Y /2,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Result[1].pos.x + RESULT_COMMAND_SIZE_X /2, g_Result[1].pos.y + -RESULT_COMMAND_SIZE_Y /2,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Result[1].pos.x + -RESULT_COMMAND_SIZE_X /2, g_Result[1].pos.y + RESULT_COMMAND_SIZE_Y /2,0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Result[1].pos.x + RESULT_COMMAND_SIZE_X /2, g_Result[1].pos.y + RESULT_COMMAND_SIZE_Y /2,0.0f);
	/*カラー設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_pVtxResult[1]->Unlock();
	/*終了コマンド*/
	g_pVtxResult[2]->Lock(0, 0, (void**)&pVtx, 0);
	/*位置設定*/
	g_Result[2].pos = D3DXVECTOR3(850.0f, 640.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Result[2].pos.x + -RESULT_COMMAND_SIZE_X / 2, g_Result[2].pos.y + -RESULT_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Result[2].pos.x + RESULT_COMMAND_SIZE_X / 2, g_Result[2].pos.y + -RESULT_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Result[2].pos.x + -RESULT_COMMAND_SIZE_X / 2, g_Result[2].pos.y + RESULT_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Result[2].pos.x + RESULT_COMMAND_SIZE_X / 2, g_Result[2].pos.y + RESULT_COMMAND_SIZE_Y / 2, 0.0f);
	/*カラー設定*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_pVtxResult[2]->Unlock();

	/*選択処理*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD) == JOYERR_NOERROR)
	{
		if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//左に倒すスティック
		{
			g_nSelectResult = 1;
		}
		if(JOYPAD.dwXpos < 0x7FFF - 0x4000)//右に倒すスティック
		{
			g_nSelectResult = 0;
		}

		if (JOYPAD.dwButtons & JOY_BUTTON1&&g_nSelectResult == 0)
		{
			SetFade(MODE_TITLE);
		}
		else if (JOYPAD.dwButtons& JOY_BUTTON1&&g_nSelectResult == 1)
		{
			exit(1);
		}

	}
	/*if (GetKeyboardTrigger(DIK_RIGHT))
	{
		
		g_nSelectResult = 1;
	}
	else if (GetKeyboardTrigger(DIK_LEFT))
	{

		g_nSelectResult = 0;
	}*/
	/*選択状態のUI*/
	if (g_nSelectResult ==0)
	{
		g_pVtxResult[1]->Lock(0, 0, (void**)&pVtx, 0);
		/*位置設定*/
		/*pVtx[0].pos = D3DXVECTOR3((g_Result[1].pos.x + -RESULT_COMMAND_SIZE_X / 2) + 10, (g_Result[1].pos.y + -RESULT_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Result[1].pos.x + RESULT_COMMAND_SIZE_X / 2) - 10, (g_Result[1].pos.y + -RESULT_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Result[1].pos.x + -RESULT_COMMAND_SIZE_X / 2) + 10, (g_Result[1].pos.y + RESULT_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Result[1].pos.x + RESULT_COMMAND_SIZE_X / 2) - 10, (g_Result[1].pos.y + RESULT_COMMAND_SIZE_Y / 2) - 10, 0.0f);*/
		/*カラー設定*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxResult[1]->Unlock();
	}
	else
	{
		g_pVtxResult[2]->Lock(0, 0, (void**)&pVtx, 0);
		/*位置設定*/
		/*pVtx[0].pos = D3DXVECTOR3((g_Result[2].pos.x + -RESULT_COMMAND_SIZE_X / 2)+10, (g_Result[2].pos.y + -RESULT_COMMAND_SIZE_Y / 2)+10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Result[2].pos.x + RESULT_COMMAND_SIZE_X / 2)-10, (g_Result[2].pos.y + -RESULT_COMMAND_SIZE_Y / 2)+10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Result[2].pos.x + -RESULT_COMMAND_SIZE_X / 2)+10, (g_Result[2].pos.y + RESULT_COMMAND_SIZE_Y / 2)-10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Result[2].pos.x + RESULT_COMMAND_SIZE_X / 2)-10, (g_Result[2].pos.y + RESULT_COMMAND_SIZE_Y / 2)-10, 0.0f);*/
		/*カラー設定*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxResult[2]->Unlock();										  
	}
	if (GetKeyboardTrigger(DIK_RETURN)&& g_nSelectResult == 0)
	{
		SetFade(MODE_TITLE);
	}
	else if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectResult == 1)
	{
		exit(1);
	}

}
void UninitResult(void)
{
	for (int nResult = 0; nResult < RESULT_TEXTURE_MAX; nResult++)
	{
		//テクスチャの設定
		if (g_pTextureResult[nResult] != NULL)
		{
			g_pTextureResult[nResult]->Release();
			g_pTextureResult[nResult] = NULL;
		}
		//頂点バッファの開放
		if (g_pVtxResult[nResult] != NULL)
		{
			g_pVtxResult[nResult]->Release();
			g_pVtxResult[nResult] = NULL;
		}
	}
}
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nResult = 0; nResult < RESULT_TEXTURE_MAX; nResult++)
	{
		//頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxResult[nResult], 0, sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[nResult]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
	DrawTime();
}
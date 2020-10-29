#include"spawn.h"
#include"enemy.h"
#include <time.h>
LPDIRECT3DTEXTURE9 g_pTextureSpawn= NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxSpawn= NULL;		//頂点バッファへのポインタ
SPAWN g_aSpawn[MAX_SPAWN];
void InitSpawn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntSpawn;
	for (nCntSpawn = 0; nCntSpawn < MAX_SPAWN; nCntSpawn++)
	{
		g_aSpawn[nCntSpawn].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSpawn[nCntSpawn].move= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_aSpawn[nCntSpawn].bUse= false;
		srand(time(NULL));
	}
	
	D3DXCreateTextureFromFile(pDevice, "thWEFU39RJ.png", &g_pTextureSpawn);//テクスチャの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_SPAWN,		//バッファサイズ
		D3DUSAGE_WRITEONLY,											//(固定)
		FVF_VERTEX_2D,												//頂点フォーマット
		D3DPOOL_MANAGED,											//（固定）
		&g_pVtxSpawn,												//変数名が変わると変更が必要
		NULL);
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxSpawn->Lock(0, 0, (void**)&pVtx, 0);

	
		/*頂点座標の設定*/
		pVtx[0].pos = D3DXVECTOR3(-SPAWN_SIZE / 2, -SPAWN_SIZE / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( SPAWN_SIZE / 2, -SPAWN_SIZE / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAWN_SIZE / 2,  SPAWN_SIZE / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3 (SPAWN_SIZE / 2,  SPAWN_SIZE / 2, 0.0f);
		/*rhwの設定（値は１，０で固定）*/
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		/*頂点カラーの設定*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		/*テクスチャの座標の設定*/
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		/*頂点データのポインタを4つ*/
		pVtx += 4;
	
	/*頂点データをアンロックする*/
	g_pVtxSpawn->Unlock();
}
void UninitSpawn(void)
{
	//テクスチャの設定
	if (g_pTextureSpawn != NULL)
	{
		g_pTextureSpawn->Release();
		g_pTextureSpawn = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxSpawn != NULL)
	{
		g_pVtxSpawn->Release();
		g_pVtxSpawn = NULL;
	}
}
void UpdateSpawn(void)
{
	VERTEX_2D*pVtx;
	int nCntSpawn;
	int g_nCntSpawn=30;
	
	
	g_pVtxSpawn->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntSpawn = 0; nCntSpawn < MAX_SPAWN; nCntSpawn++)
	{
		if (g_aSpawn[nCntSpawn].bUse == true)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x + (-SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y + (-SPAWN_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x + (SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y + (-SPAWN_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x + (-SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y + (SPAWN_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x + (SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y + (SPAWN_SIZE / 2), 0.0f);
			g_aSpawn[nCntSpawn].pos += g_aSpawn[nCntSpawn].move;
			
			if ((rand() % ((g_nCntSpawn) * 20)) <= 0)
			{
				SetEnemy(g_aSpawn[nCntSpawn].pos, 0);
			}
			if (g_aSpawn[nCntSpawn].pos.x<0 + (SPAWN_SIZE / 2) || g_aSpawn[nCntSpawn].pos.x>SCREEN_WIDTH - (SPAWN_SIZE / 2))
			{
				g_aSpawn[nCntSpawn].move *= -1;
				g_nCntSpawn--;
			}

		}
	}
	g_pVtxSpawn->Unlock();
}
void DrawWpawn(void)
{
	int  nCntSpawn;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*頂点バッファをデバイスのデータストリームにバインド*/
	pDevice->SetStreamSource(0, g_pVtxSpawn, 0, sizeof(VERTEX_2D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*テクスチャの設定*/
	pDevice->SetTexture(0, g_pTextureSpawn);
	/*ポリゴンの描画*/
	for (nCntSpawn = 0; nCntSpawn < MAX_SPAWN; nCntSpawn++)
	{
		if (g_aSpawn[nCntSpawn].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
		}
	}
}
void SetWpawn(D3DXVECTOR3 pos)
{

	int nCntSpawn;
	VERTEX_2D*pVtx;
	g_pVtxSpawn->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntSpawn = 0; nCntSpawn < MAX_SPAWN; nCntSpawn++)
	{

		if (g_aSpawn[nCntSpawn].bUse == false)					//敵が使用されていない場合
		{
			/*位置設定*/
			g_aSpawn[nCntSpawn].pos = pos;

			pVtx[0].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x+(-SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y+(-SPAWN_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x+( SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y+(-SPAWN_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x+(-SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y+( SPAWN_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x+( SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y+( SPAWN_SIZE / 2), 0.0f);

			/*使用している状態にする*/
			g_aSpawn[nCntSpawn].bUse = true;

			break;
		}
		pVtx += 4;
	}
	g_pVtxSpawn->Unlock();
}
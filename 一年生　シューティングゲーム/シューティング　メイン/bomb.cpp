#include"main.h"
#include"bomb.h"
#include"player.h"
#include"enemy.h"
LPDIRECT3DTEXTURE9 g_pTexturBomb = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBomb = NULL;//バッファへのポインター

BOMB g_aBomb[MAX_BOMB];

int nCntAnime = 0;
int nPatternAnimX = 0;
int nPatternAnimY = 0;
void InintBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//頂点情報へのポインター
	int nCntBomb;
	for (nCntBomb = 0; nCntBomb< MAX_BOMB; nCntBomb++)
	{
		g_aBomb[nCntBomb].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[nCntBomb].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBomb[nCntBomb].bUse = false;
	}


	D3DXCreateTextureFromFile(pDevice, "120b99a08cce763536914aee77045be5.png", &g_pTexturBomb);//テクスチャの読み込み	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BOMB,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffBomb,//変数名が変わると変更が必要
		NULL);



	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb ++)
	{
		/*頂点座標の設定（右回りで設定する*/
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		/*rhwの設定（値は１，０で固定）*/
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		/*頂点カラーの設定（0～255の数値で設定）*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標の設定
		pVtx[0 ].tex = D3DXVECTOR2(0, 0);
		pVtx[1 ].tex = D3DXVECTOR2(1, 0);
		pVtx[2 ].tex = D3DXVECTOR2(0, 1);
		pVtx[3 ].tex = D3DXVECTOR2(1, 1);

	}
	pVtx += 4;
	//頂点データをアンロックする
	g_pVtxBuffBomb->Unlock();
}
void UninitBomb(void)
{
	//テクスチャの設定
	if (g_pTexturBomb != NULL)
	{
		g_pTexturBomb->Release();
		g_pTexturBomb = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffBomb != NULL)
	{
		g_pVtxBuffBomb->Release();
		g_pVtxBuffBomb = NULL;
	}
}
void UpdateBomb(void)
{
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	ENEMY*pEnemy;

	int nCntBomb;
	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++)
	{ 
		if (g_aBomb[nCntBomb].bUse == true)//ボムが使用されている		
		{
		
				nCntAnime++;//カウンター計算
				if (nCntAnime == 15)
				{
					nCntAnime = 0;//カウンターを初期値に戻す
					nPatternAnimX++;
				
					if (nPatternAnimX == 5)
					{
						nPatternAnimY++;
						nPatternAnimX = 0;
					}
					if (nPatternAnimY == 3)
					{
						
						for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
						{
							pEnemy = GetEnemy();
							if (pEnemy[nCntEnemy].bUse == true)
							{
								HitEnemy(nCntEnemy, 10);
							}
						}
						g_aBomb[nCntBomb].bUse = false;
					}
				}
				pPlayer = GatPlayer();
				//テクスチャの座標の設定
				pVtx[0].tex = D3DXVECTOR2(nPatternAnimX*0.2f,		 nPatternAnimY*0.325f);
				pVtx[1].tex = D3DXVECTOR2(nPatternAnimX*0.2f+0.2f,	 nPatternAnimY*0.325f);
				pVtx[2].tex = D3DXVECTOR2(nPatternAnimX*0.2f,		 nPatternAnimY*0.325f+0.325f);
				pVtx[3].tex = D3DXVECTOR2(nPatternAnimX*0.2f+0.2f,	 nPatternAnimY*0.325f+0.325f);

				pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x + (-BOMB_SION / 2)*nPatternAnimX*2, pPlayer->pos.y + (-BOMB_SION / 2)*nPatternAnimX*2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + (BOMB_SION / 2)*nPatternAnimX*2, pPlayer->pos.y + (-BOMB_SION / 2)*nPatternAnimX*2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x + (-BOMB_SION / 2)*nPatternAnimX*2, pPlayer->pos.y + (BOMB_SION / 2)*nPatternAnimX*2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + (BOMB_SION / 2)*nPatternAnimX*2, pPlayer->pos.y + (BOMB_SION / 2)*nPatternAnimX*2, 0.0f);

		}
	}
	//頂点データをアンロックする
	g_pVtxBuffBomb->Unlock();
}
void DrawBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBomb;
	/*頂点バッファをデバイスのデータストリームにバインド*/
	pDevice->SetStreamSource(0, g_pVtxBuffBomb, 0, sizeof(VERTEX_2D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*テクスチャの設定*/
	pDevice->SetTexture(0, g_pTexturBomb);


	/*ポリゴンの描画*/
	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++)
	{
		if (g_aBomb[nCntBomb].bUse == true)
		{
			/*弾が使用中なら描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBomb * 4, NUM_POLYGON);
		}
	}
}
void SetBomb(D3DXVECTOR3 pos)
{
	int nCntBomb;
	VERTEX_2D*pVtx;
	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++)
	{

		if (g_aBomb[nCntBomb].bUse == false)					//弾が使用されていない場合
		{
			/*位置設定*/
			g_aBomb[nCntBomb].pos = pos;
			
			/*頂点座標の設定*/
			pVtx[0].pos = D3DXVECTOR3(g_aBomb[nCntBomb].pos.x + (-BOMB_SION / 2), g_aBomb[nCntBomb].pos.y + (-BOMB_SION / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBomb[nCntBomb].pos.x + (BOMB_SION / 2), g_aBomb[nCntBomb].pos.y + (-BOMB_SION / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBomb[nCntBomb].pos.x + (-BOMB_SION / 2), g_aBomb[nCntBomb].pos.y + (BOMB_SION / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBomb[nCntBomb].pos.x + (BOMB_SION / 2), g_aBomb[nCntBomb].pos.y + (BOMB_SION / 2), 0.0f);


			/*使用している状態にする*/
			g_aBomb[nCntBomb].bUse = true;
			break;
		}
		pVtx += 4;													//頂点データのポインタを四分進める
	}
	g_pVtxBuffBomb->Unlock();
}
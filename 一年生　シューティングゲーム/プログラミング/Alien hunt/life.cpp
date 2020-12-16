#include"life.h"
#include"main.h"
#include"player.h"
LPDIRECT3DTEXTURE9 g_pTexturLife= NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife= NULL;//バッファへのポインター

LIFE g_aLife[MAX_LIFE];

void InintLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//頂点情報へのポインター
	int nCntLife;
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLife[nCntLife].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLife[nCntLife].bUse = false;
	}


	D3DXCreateTextureFromFile(pDevice, "TEXTURE/heart.png", &g_pTexturLife);//テクスチャの読み込み	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_LIFE,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffLife,//変数名が変わると変更が必要
		NULL);



	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife = nCntLife + 4)
	{
		/*頂点座標の設定（右回りで設定する*/
		pVtx[0 + nCntLife].pos = D3DXVECTOR3((-LIFE_SION_X / 2), (-LIFE_SION_Y / 2), 0.0f);
		pVtx[1 + nCntLife].pos = D3DXVECTOR3((LIFE_SION_X / 2), (-LIFE_SION_Y / 2), 0.0f);
		pVtx[2 + nCntLife].pos = D3DXVECTOR3((-LIFE_SION_X / 2), (LIFE_SION_Y / 2), 0.0f);
		pVtx[3 + nCntLife].pos = D3DXVECTOR3((LIFE_SION_X / 2), (LIFE_SION_Y / 2), 0.0f);

		/*rhwの設定（値は１，０で固定）*/
		pVtx[0 + nCntLife].rhw = 1.0f;
		pVtx[1 + nCntLife].rhw = 1.0f;
		pVtx[2 + nCntLife].rhw = 1.0f;
		pVtx[3 + nCntLife].rhw = 1.0f;

		/*頂点カラーの設定（0～255の数値で設定）*/
		pVtx[0 + nCntLife].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1 + nCntLife].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2 + nCntLife].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3 + nCntLife].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標の設定
		pVtx[0 + nCntLife].tex = D3DXVECTOR2(0, 0);
		pVtx[1 + nCntLife].tex = D3DXVECTOR2(1, 0);
		pVtx[2 + nCntLife].tex = D3DXVECTOR2(0, 1);
		pVtx[3 + nCntLife].tex = D3DXVECTOR2(1, 1);
	
	}
	pVtx += 4;
	//頂点データをアンロックする
	g_pVtxBuffLife->Unlock();
}
void UninitLife(void)
{
	//テクスチャの設定
	if (g_pTexturLife != NULL)
	{
		g_pTexturLife->Release();
		g_pTexturLife = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}
void UpdateLife(void)
{
	int nCntLife;
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			pPlayer = GatPlayer();
			switch (pPlayer->nLife)
			{
			case 5:
				if (pVtx[1].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[0].tex = D3DXVECTOR2(0, 0);
					pVtx[1].tex = D3DXVECTOR2(1, 0);
					pVtx[2].tex = D3DXVECTOR2(0, 1);
					pVtx[3].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 4:
				
				pVtx[0].tex = D3DXVECTOR2(0, 0);
				pVtx[1].tex = D3DXVECTOR2(0, 0);
				pVtx[2].tex = D3DXVECTOR2(0, 0);
				pVtx[3].tex = D3DXVECTOR2(0, 0);
				if (pVtx[5].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[4].tex = D3DXVECTOR2(0, 0);
					pVtx[5].tex = D3DXVECTOR2(1, 0);
					pVtx[6].tex = D3DXVECTOR2(0, 1);
					pVtx[7].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 3:
				pVtx[4].tex = D3DXVECTOR2(0, 0);
				pVtx[5].tex = D3DXVECTOR2(0, 0);
				pVtx[6].tex = D3DXVECTOR2(0, 0);
				pVtx[7].tex = D3DXVECTOR2(0, 0);
				if (pVtx[9].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[8].tex = D3DXVECTOR2(0, 0);
					pVtx[9].tex = D3DXVECTOR2(1, 0);
					pVtx[10].tex = D3DXVECTOR2(0, 1);
					pVtx[11].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 2:
				pVtx[8].tex = D3DXVECTOR2(0, 0);
				pVtx[9].tex = D3DXVECTOR2(0, 0);
				pVtx[10].tex = D3DXVECTOR2(0, 0);
				pVtx[11].tex = D3DXVECTOR2(0, 0);
				if (pVtx[13].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[12].tex = D3DXVECTOR2(0, 0);
					pVtx[13].tex = D3DXVECTOR2(1, 0);
					pVtx[14].tex = D3DXVECTOR2(0, 1);
					pVtx[15].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 1:
				pVtx[12].tex = D3DXVECTOR2(0, 0);
				pVtx[13].tex = D3DXVECTOR2(0, 0);
				pVtx[14].tex = D3DXVECTOR2(0, 0);
				pVtx[15].tex = D3DXVECTOR2(0, 0);
				if (pVtx[17].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[16].tex = D3DXVECTOR2(0, 0);
					pVtx[17].tex = D3DXVECTOR2(1, 0);
					pVtx[18].tex = D3DXVECTOR2(0, 1);
					pVtx[19].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 0:
				pVtx[16].tex = D3DXVECTOR2(0, 0);
				pVtx[17].tex = D3DXVECTOR2(0, 0);
				pVtx[18].tex = D3DXVECTOR2(0, 0);
				pVtx[19].tex = D3DXVECTOR2(0, 0);
				break;
			}

			
		}
		
	}
	//頂点データをアンロックする
	g_pVtxBuffLife->Unlock();
}
void DrawLife(void)
{
	int nCntLife;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturLife);
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, NUM_POLYGON);
	}
}
void SetLife(D3DXVECTOR3 pos)
{
	int nCntLife;
	int nCntPos;
	int nCntzi = 0;
	VERTEX_2D*pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{
			g_aLife[nCntLife].pos = pos;
			for (nCntPos = 0; nCntPos < MAX_LIFE; nCntPos = nCntPos + 4)
			{
				/*頂点座標の設定（右回りで設定する*/
				pVtx[0 + nCntPos].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x +(nCntzi)+(-LIFE_SION_X / 2), g_aLife[nCntLife].pos.y + (-LIFE_SION_Y / 2), 0.0f);
				pVtx[1 + nCntPos].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x +(nCntzi)+(LIFE_SION_X / 2), g_aLife[nCntLife].pos.y + (-LIFE_SION_Y / 2), 0.0f);
				pVtx[2 + nCntPos].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x +(nCntzi)+(-LIFE_SION_X / 2), g_aLife[nCntLife].pos.y + (LIFE_SION_Y / 2), 0.0f);
				pVtx[3 + nCntPos].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x +(nCntzi)+(LIFE_SION_X / 2), g_aLife[nCntLife].pos.y + (LIFE_SION_Y / 2), 0.0f);
				nCntzi += 50;
				/*使用している状態にする*/
				g_aLife[nCntPos].bUse = true;
			}
			break;
		
		}
	
		pVtx += 4;
	}
	
	g_pVtxBuffLife->Unlock();	//頂点データをアンロックする
}


#include"bomuSaid.h"
#include"main.h"
#include"player.h"

LPDIRECT3DTEXTURE9 g_pTexturBomuSaid = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBomuSaid = NULL;//バッファへのポインター

BOMUSAID g_aBomuSaid[MAX_BOMUSAID];
void InintBomuSaid(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//頂点情報へのポインター
	int nCntBomuSaid;
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid++)
	{
		g_aBomuSaid[nCntBomuSaid].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomuSaid[nCntBomuSaid].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBomuSaid[nCntBomuSaid].bUse = false;
	}


	D3DXCreateTextureFromFile(pDevice, "TEXTURE/heart.png", &g_pTexturBomuSaid);//テクスチャの読み込み	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BOMUSAID,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBomuSaid,//変数名が変わると変更が必要
		NULL);



	g_pVtxBomuSaid->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid = nCntBomuSaid + 4)
	{
		/*頂点座標の設定（右回りで設定する*/
		pVtx[0 + nCntBomuSaid].pos = D3DXVECTOR3((-BOMUSAID_SION_X / 2), (-BOMUSAID_SION_Y / 2), 0.0f);
		pVtx[1 + nCntBomuSaid].pos = D3DXVECTOR3((BOMUSAID_SION_X / 2), (-BOMUSAID_SION_Y / 2), 0.0f);
		pVtx[2 + nCntBomuSaid].pos = D3DXVECTOR3((-BOMUSAID_SION_X / 2), (BOMUSAID_SION_Y / 2), 0.0f);
		pVtx[3 + nCntBomuSaid].pos = D3DXVECTOR3((BOMUSAID_SION_X / 2), (BOMUSAID_SION_Y / 2), 0.0f);

		/*rhwの設定（値は１，０で固定）*/
		pVtx[0 + nCntBomuSaid].rhw = 1.0f;
		pVtx[1 + nCntBomuSaid].rhw = 1.0f;
		pVtx[2 + nCntBomuSaid].rhw = 1.0f;
		pVtx[3 + nCntBomuSaid].rhw = 1.0f;

		/*頂点カラーの設定（0～255の数値で設定）*/
		pVtx[0 + nCntBomuSaid].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1 + nCntBomuSaid].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2 + nCntBomuSaid].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3 + nCntBomuSaid].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標の設定
		pVtx[0 + nCntBomuSaid].tex = D3DXVECTOR2(0, 0);
		pVtx[1 + nCntBomuSaid].tex = D3DXVECTOR2(1, 0);
		pVtx[2 + nCntBomuSaid].tex = D3DXVECTOR2(0, 1);
		pVtx[3 + nCntBomuSaid].tex = D3DXVECTOR2(1, 1);

	}
	pVtx += 4;
	//頂点データをアンロックする
	g_pVtxBomuSaid->Unlock();
}
void UninitBomuSaid(void)
{
	//テクスチャの設定
	if (g_pTexturBomuSaid != NULL)
	{
		g_pTexturBomuSaid->Release();
		g_pTexturBomuSaid = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBomuSaid != NULL)
	{
		g_pVtxBomuSaid->Release();
		g_pVtxBomuSaid = NULL;
	}
}
void UpdateBomuSaid(void)
{
	int nCntBomuSaid;
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	g_pVtxBomuSaid->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid++)
	{
		if (g_aBomuSaid[nCntBomuSaid].bUse == true)
		{
			pPlayer = GatPlayer();
			switch (pPlayer->nBomb)
			{
			case 2:
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
			case 1:
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
			case 0:
				pVtx[8].tex = D3DXVECTOR2(0, 0);
				pVtx[9].tex = D3DXVECTOR2(0, 0);
				pVtx[10].tex = D3DXVECTOR2(0, 0);
				pVtx[11].tex = D3DXVECTOR2(0, 0);
				break;
			}


		}

	}
	//頂点データをアンロックする
	g_pVtxBomuSaid->Unlock();
}
void DrawBomuSaid(void)
{
	int nCntBomuSaid;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBomuSaid, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturBomuSaid);
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBomuSaid * 4, NUM_POLYGON);
	}
}
void SetBomuSaid(D3DXVECTOR3 pos)
{
	int nCntBomuSaid;
	int nCntPos;
	int nCntzi = 0;
	VERTEX_2D*pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBomuSaid->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid++)
	{
		if (g_aBomuSaid[nCntBomuSaid].bUse == false)
		{
			g_aBomuSaid[nCntBomuSaid].pos = pos;
			for (nCntPos = 0; nCntPos < MAX_BOMUSAID; nCntPos = nCntPos + 4)
			{
				/*頂点座標の設定（右回りで設定する*/
				pVtx[0 + nCntPos].pos = D3DXVECTOR3(g_aBomuSaid[nCntBomuSaid].pos.x + (nCntzi)+(-BOMUSAID_SION_X / 2), g_aBomuSaid[nCntBomuSaid].pos.y + (-BOMUSAID_SION_Y / 2), 0.0f);
				pVtx[1 + nCntPos].pos = D3DXVECTOR3(g_aBomuSaid[nCntBomuSaid].pos.x + (nCntzi)+(BOMUSAID_SION_X / 2), g_aBomuSaid[nCntBomuSaid].pos.y + (-BOMUSAID_SION_Y / 2), 0.0f);
				pVtx[2 + nCntPos].pos = D3DXVECTOR3(g_aBomuSaid[nCntBomuSaid].pos.x + (nCntzi)+(-BOMUSAID_SION_X / 2), g_aBomuSaid[nCntBomuSaid].pos.y + (BOMUSAID_SION_Y / 2), 0.0f);
				pVtx[3 + nCntPos].pos = D3DXVECTOR3(g_aBomuSaid[nCntBomuSaid].pos.x + (nCntzi)+(BOMUSAID_SION_X / 2), g_aBomuSaid[nCntBomuSaid].pos.y + (BOMUSAID_SION_Y / 2), 0.0f);
				nCntzi += 50;
				/*使用している状態にする*/
				g_aBomuSaid[nCntPos].bUse = true;
			}
			break;

		}

		pVtx += 4;
	}

	g_pVtxBomuSaid->Unlock();	//頂点データをアンロックする
}


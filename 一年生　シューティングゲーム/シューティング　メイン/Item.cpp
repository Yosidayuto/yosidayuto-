
#include"main.h"
#include"Item.h"
#include"player.h"
#include"enemy.h"
/*マクロ定義*/
#define MAX_ITEM (128)							//アイテムの最大数

/*グローバル変数*/
LPDIRECT3DTEXTURE9 g_apTextureItem = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem= NULL;		//頂点バッファへのポインタ
ITEM g_aItem[MAX_ITEM];
int nCntType;
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntItem;
	/*敵の情報を初期化*/
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].bUse = false;
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	/*テクスチャの読み込み*/
	D3DXCreateTextureFromFile(pDevice, "yajirusi0101.png", &g_apTextureItem);//テクスチャの読み込み

	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_ITEM,		//バッファサイズ
		D3DUSAGE_WRITEONLY,											//(固定)
		FVF_VERTEX_2D,												//頂点フォーマット
		D3DPOOL_MANAGED,											//（固定）
		&g_pVtxBuffItem,											//変数名が変わると変更が必要
		NULL);
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		/*頂点座標の設定*/
		pVtx[0].pos = D3DXVECTOR3(-MAX_ITEM_SIZ / 2, -MAX_ITEM_SIZ / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_ITEM_SIZ / 2, -MAX_ITEM_SIZ / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_ITEM_SIZ / 2, MAX_ITEM_SIZ / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_ITEM_SIZ / 2, MAX_ITEM_SIZ / 2, 0.0f);
		/*rhwの設定（値は１，０で固定）*/
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		/*頂点カラーの設定*/
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		/*テクスチャの座標の設定*/
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		///*頂点データのポインタを4つ*/
		pVtx += 4;
	}
	/*頂点データをアンロック*/
	g_pVtxBuffItem->Unlock();

}



void UninitItem(void)
{
	
	if (g_apTextureItem!= NULL)
	{
		g_apTextureItem->Release();
		g_apTextureItem = NULL;
	}

	/*頂点バッファの開放*/
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

void UpdaItem(void)
{

	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	int nCntPlayer;

	int nCntItem;
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)//アイテムが使用されている					//弾が使用されている
		{
			pPlayer = GatPlayer();
		
			if (pPlayer->pos.x + 30 >= g_aItem[nCntItem].pos.x
				&&pPlayer->pos.x - 30 <= g_aItem[nCntItem].pos.x
				&&pPlayer->pos.y + 30 >= g_aItem[nCntItem].pos.y
				&&pPlayer->pos.y - 30 <= g_aItem[nCntItem].pos.y)
			{
				switch (g_aItem[nCntItem].nType)
				{
				case 0:
					if (pPlayer->nBulletType<6)
					{
						pPlayer->nBulletType = 1 + pPlayer->nBulletType;
					}
				
					break;
				case 1:
					if (pPlayer->nLife < 5)
					{
						pPlayer->nLife = 1 + pPlayer->nLife;
					}
					break;
				case 2:
					if (pPlayer->nBomb < 3)
					{
						pPlayer->nBomb = 1 + pPlayer->nBomb;
					}
					break;
				case 3:
					break;
				case 4:
					break;
				}
				g_aItem[nCntItem].bUse = false;//使用しない状態にする
			}
			
			/*位置更新*/
			g_aItem[nCntItem].pos += g_aItem[nCntItem].move*0.3;

		

			/*頂点座標の設定*/
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (-MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (-MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (-MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (-MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (MAX_ITEM_SIZ / 2), 0.0f);

			

			if (g_aItem[nCntItem].pos.y>SCREEN_HEIGHT ||
				g_aItem[nCntItem].pos.y<0 ||
				g_aItem[nCntItem].pos.x> SCREEN_WIDTH ||
				g_aItem[nCntItem].pos.x<0)
			{
				g_aItem[nCntItem].bUse = false;
			}
		}
		pVtx += 4;													//頂点データのポインタを四分進める
	}
	g_pVtxBuffItem->Unlock();
}
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntItem;
	/*頂点バッファをデバイスのデータストリームにバインド*/
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*ポリゴンの描画*/
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, NUM_POLYGON);

		}
	}
}

void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move/*移動量*/, D3DXCOLOR col)
{
	
	VERTEX_2D*pVtx;
  	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	int nCntItem;
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)					//弾が使用されていない場合
		{
			/*位置設定*/
			g_aItem[nCntItem].pos = pos;
			/*移動量を設定*/
			g_aItem[nCntItem].move = move;
			/*色*/
			g_aItem[nCntItem].col = col;
			/*頂点座標の設定*/
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (-MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (-MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (-MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (-MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (MAX_ITEM_SIZ / 2), 0.0f);
			nCntType = rand() % 2;
			switch (nCntType)
			{
			case 0://バレット強化
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				g_aItem[nCntItem].nType = 0;
				break;
			case 1://体力回復
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
				g_aItem[nCntItem].nType = 1;
				break;
			case 2://ボム追加
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				g_aItem[nCntItem].nType = 2;
				break;
				/*case 3:
				pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				g_aItem[nCntItem].nType = 3;
				break;
			case 4:
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				g_aItem[nCntItem].nType = 4;
				break;*/
			}

			/*使用している状態にする*/
			g_aItem[nCntItem].bUse = true;
			break;
		}
		pVtx += 4;													//頂点データのポインタを四分進める
	}
	g_pVtxBuffItem->Unlock();
}

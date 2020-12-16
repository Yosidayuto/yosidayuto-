#include"main.h"
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"player.h"
#include"effect.h"
/*マクロ定義*/
#define MAX_BULLET (128)							//弾の最大数
//構造体定義
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	BULLETTYPE type;								//種類
	int nLife;										//寿命
	D3DXCOLOR col;									//色
	bool bUse;										//使用されているか
}BULLET;
/*グローバル変数*/
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBullet = NULL;		//頂点バッファへのポインタ

BULLET g_aBullet[MAX_BULLET];//弾の情報

							 /*初期化処理*/
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntBullet;

	/*弾の情報の初期化*/
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aBullet[nCntBullet].nLife = 50;
		g_aBullet[nCntBullet].bUse = false;
	}
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/bullet.png", &g_pTextureBullet);//テクスチャの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BULLET,		//バッファサイズ
		D3DUSAGE_WRITEONLY,											//(固定)
		FVF_VERTEX_2D,												//頂点フォーマット
		D3DPOOL_MANAGED,											//（固定）
		&g_pVtxBullet,												//変数名が変わると変更が必要
		NULL);
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		/*頂点座標の設定*/
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 100, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100, 100, 0.0f);
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
	}
	/*頂点データをアンロックする*/
	g_pVtxBullet->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	//テクスチャの設定
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBullet != NULL)
	{
		g_pVtxBullet->Release();
		g_pVtxBullet = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_2D*pVtx;
	ENEMY*pEnemy;
	PLAYER *pPlayer;
	int nCntEnemy;
	int nCntBullet;
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)//弾が使用されている					
		{
			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYE)
			{/*プレイヤーの弾*/

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1.5f, 6);
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					/*敵を取得*/
					pEnemy = GetEnemy();
					if (pEnemy[nCntEnemy].bUse == true)
					{
						if (pEnemy[nCntEnemy].pos.x + 30 >= g_aBullet[nCntBullet].pos.x
							&&pEnemy[nCntEnemy].pos.x - 30 <= g_aBullet[nCntBullet].pos.x
							&&pEnemy[nCntEnemy].pos.y + 30 >= g_aBullet[nCntBullet].pos.y
							&&pEnemy[nCntEnemy].pos.y - 30 <= g_aBullet[nCntBullet].pos.y)
						{
							/*爆発生成*/
  							HitEnemy(nCntEnemy, 1);

							g_aBullet[nCntBullet].bUse = false;//使用しない状態にする
							g_aBullet[nCntBullet].nLife = 50;
						}
					}
				}
				/*位置更新*/
				g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{/*敵の弾*/
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 1.5f, 5);
				pPlayer = GatPlayer();
				if (pPlayer->pos.x + 30 >= g_aBullet[nCntBullet].pos.x
					&&pPlayer->pos.x - 30 <= g_aBullet[nCntBullet].pos.x
					&&pPlayer->pos.y + 30 >= g_aBullet[nCntBullet].pos.y
					&&pPlayer->pos.y - 30 <= g_aBullet[nCntBullet].pos.y)
				{
					HitPlayer(1);
					g_aBullet[nCntBullet].bUse = false;//使用しない状態にする
					g_aBullet[nCntBullet].nLife = 50;
				}
				/*位置更新*/
				g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move*0.4f;
			}


		

			/*頂点座標の設定*/
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (-BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (-BULLET_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (-BULLET_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (-BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE_Y / 2), 0.0f);

			if (g_aBullet[nCntBullet].pos.y>SCREEN_HEIGHT ||
				g_aBullet[nCntBullet].pos.y<0 ||
				g_aBullet[nCntBullet].pos.x> SCREEN_WIDTH ||
				g_aBullet[nCntBullet].pos.x<0)
			{
				g_aBullet[nCntBullet].bUse = false;
				g_aBullet[nCntBullet].nLife = 50;
			}
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				/*爆破発生*/
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
				g_aBullet[nCntBullet].nLife = 50;
			}
		}
		pVtx += 4;													//頂点データのポインタを四分進める
	}
	g_pVtxBullet->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBullet;
	/*頂点バッファをデバイスのデータストリームにバインド*/
	pDevice->SetStreamSource(0, g_pVtxBullet, 0, sizeof(VERTEX_2D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*テクスチャの設定*/
	pDevice->SetTexture(0, g_pTextureBullet);


	/*ポリゴンの描画*/
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			/*弾が使用中なら描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, NUM_POLYGON);
		}
	}
}

void SetBullet(D3DXVECTOR3 pos/*発射位置*/, D3DXVECTOR3 move/*移動量*/, BULLETTYPE type, int nLife, D3DXCOLOR col)
{

	int nCntBullet;
	VERTEX_2D*pVtx;
	g_pVtxBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{

		if (g_aBullet[nCntBullet].bUse == false)					//弾が使用されていない場合
		{
			/*位置設定*/
			g_aBullet[nCntBullet].pos = pos;
			/*種類*/
			g_aBullet[nCntBullet].type = type;
			/*移動量を設定*/
			g_aBullet[nCntBullet].move = move;
			/*寿命*/
			g_aBullet[nCntBullet].nLife = nLife;
			/*色*/
			g_aBullet[nCntBullet].col = col;
			/*頂点座標の設定*/
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (-BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (-BULLET_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (-BULLET_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (-BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE_Y / 2), 0.0f);

			pVtx[0].col = g_aBullet[nCntBullet].col;
			pVtx[1].col = g_aBullet[nCntBullet].col;
			pVtx[2].col = g_aBullet[nCntBullet].col;
			pVtx[3].col = g_aBullet[nCntBullet].col;

			/*使用している状態にする*/
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
		pVtx += 4;													//頂点データのポインタを四分進める
	}
	g_pVtxBullet->Unlock();
}
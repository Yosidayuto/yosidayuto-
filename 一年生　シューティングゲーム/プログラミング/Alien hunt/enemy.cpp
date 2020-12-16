#include "enemy.h"
#include "main.h"
#include"explosion.h"
#include"bullet.h"
#include"score.h"
#include"Item.h"
#include"player.h"
#include <time.h>
/*マクロ定義*/
#define MAX_TYPE_ENEMY (100)

/*グローバル変数*/
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_TYPE_ENEMY] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//頂点バッファへのポインタ
ENEMY g_aEnemy[MAX_ENEMY];

/*初期化処理*/
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntEnemy;
	/*敵の情報を初期化*/
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nLife = 5;
		g_aEnemy[nCntEnemy].move= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		srand(time(NULL));
	}
	/*テクスチャの読み込み*/
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/enemy000.png", &g_apTextureEnemy[0]);//テクスチャの読み込み

	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_ENEMY,		//バッファサイズ
		D3DUSAGE_WRITEONLY,											//(固定)
		FVF_VERTEX_2D,												//頂点フォーマット
		D3DPOOL_MANAGED,											//（固定）
		&g_pVtxBuffEnemy,											//変数名が変わると変更が必要
		NULL);
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		/*頂点座標の設定*/
		pVtx[0].pos = D3DXVECTOR3(-MAX_ENEMYSIZ / 2, -MAX_ENEMYSIZ / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_ENEMYSIZ / 2, -MAX_ENEMYSIZ / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_ENEMYSIZ / 2, MAX_ENEMYSIZ / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_ENEMYSIZ / 2, MAX_ENEMYSIZ / 2, 0.0f);
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
	g_pVtxBuffEnemy->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;
	/*テクスチャの開放*/
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}
	/*頂点バッファの開放*/
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	float fAngle;//角度
	int nCntEnemy;
	int g_nCountEnemy = 10;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//敵が使用されている
		{
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (-MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (-MAX_ENEMYSIZ / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (-MAX_ENEMYSIZ / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (-MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMYSIZ / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMYSIZ / 2), 0.0f);
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move*MOVE_ENEMY;
			/*敵が画面外に行ったら*/
			if (g_aEnemy[nCntEnemy].pos.y > SCREEN_HEIGHT)
			{
				/*使わなくする*/
				g_aEnemy[nCntEnemy].bUse = false;
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL://通常時
				
				if ((rand() % (g_nCountEnemy * 20)) == 0)
				{
					pPlayer = GatPlayer();
					/*角度を求める*/
					fAngle = atan2f(-(g_aEnemy[nCntEnemy].pos.x- pPlayer->pos.x), -(g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y));
					if (fAngle > D3DX_PI) { fAngle -= D3DX_PI*2.0f; }
					if (fAngle < D3DX_PI) { fAngle += D3DX_PI*2.0f; }

					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(fAngle)*8, cosf(fAngle)*8, 0.0f), BULLETTYPE_ENEMY, 100, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));//敵の攻撃
				}
				break;
			case ENEMYSTATE_DAMAGE://ダメージ状態
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					/*頂点カラーの設定*/
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				break;
			
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();

}
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEnemy;
	/*頂点バッファをデバイスのデータストリームにバインド*/
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*ポリゴンの描画*/
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			/*テクスチャの設定*/
			pDevice->SetTexture(0,g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy*4 , NUM_POLYGON);

		}
	}
}

void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;
	VERTEX_2D*pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
	
			if (g_aEnemy[nCntEnemy].bUse == false)					//敵が使用されていない場合
			{
				/*位置設定*/
				g_aEnemy[nCntEnemy].pos = pos;

				/*敵種類*/
				g_aEnemy[nCntEnemy].nType = nType;

				/*位置処理*/
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (-MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (-MAX_ENEMYSIZ / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (-MAX_ENEMYSIZ / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (-MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMYSIZ / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMYSIZ / 2), 0.0f);

			

				/*使用している状態にする*/
				g_aEnemy[nCntEnemy].bUse = true;
			
				break;
			}
			pVtx += 4;
	
	}
	g_pVtxBuffEnemy->Unlock();
}

ENEMY *GetEnemy(void)
{
	
		return &g_aEnemy[0];
	
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D*pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	int nCntItem = 1;
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		
		
		/*爆発発生*/
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		/*アイテム発生*/
		if ((rand() % ((nCntItem) * 1)) <= 0)
		{
			SetItem(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

   		g_aEnemy[nCntEnemy].bUse = false;
  		g_aEnemy[nCntEnemy].nLife = 5;
		ScoreUp(1);
	}
	else if (g_aEnemy[nCntEnemy].nLife >= 0)
	{
		/*ダメージ状態に移動*/
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;
		/*頂点カラーの設定*/
		pVtx[0 + (nCntEnemy * 4)].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[1 + (nCntEnemy * 4)].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[2 + (nCntEnemy * 4)].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[3 + (nCntEnemy * 4)].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}
	g_pVtxBuffEnemy->Unlock();
}
#include"main.h"
#include"effect.h"
#include"player.h"
#include"enemy.h"

#define MAX_EFFECT (4096)//エフェクト最大数

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	float fRadius;			//半径
	float fRadiusValue;		//半径変化量
	float fColAlphaValue;	//色変化量
	int nLife;				//ライフ

	bool bUse;				//使用しているかどうか
}EFFECT;
/*グローバル変数*/
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect= NULL;		//頂点バッファへのポインタ

EFFECT g_aEffect[MAX_EFFECT];

void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntEffect;

	/*弾の情報の初期化*/
	for (nCntEffect = 0; nCntEffect< MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(255, 255, 255,5);
		g_aEffect[nCntEffect].nLife = 50;
		g_aEffect[nCntEffect].bUse = false;
		g_aEffect[nCntEffect].fRadius = 0;
		g_aEffect[nCntEffect].fRadiusValue = 0;
	}
	D3DXCreateTextureFromFile(pDevice, "bullet000.png", &g_pTextureEffect);//テクスチャの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_EFFECT,		//バッファサイズ
		D3DUSAGE_WRITEONLY,											//(固定)
		FVF_VERTEX_2D,												//頂点フォーマット
		D3DPOOL_MANAGED,											//（固定）
		&g_pVtxBuffEffect,												//変数名が変わると変更が必要
		NULL);
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		/*頂点座標の設定*/
		pVtx[0].pos = D3DXVECTOR3(-EFFECT_SIZE/2,- EFFECT_SIZE/2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EFFECT_SIZE/2, -EFFECT_SIZE/2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EFFECT_SIZE/2, EFFECT_SIZE/2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EFFECT_SIZE/2, EFFECT_SIZE/2, 0.0f);
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
	g_pVtxBuffEffect->Unlock();
}
void UninitEffect(void)
{
	//テクスチャの設定
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	VERTEX_2D*pVtx;
	int nCntEffect;
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			g_aEffect[nCntEffect].fRadiusValue++;
			if (g_aEffect[nCntEffect].fRadiusValue>= 1)
			{
				g_aEffect[nCntEffect].fRadiusValue = 0;//カウンターを初期値に戻す
				g_aEffect[nCntEffect].nLife--;
				g_aEffect[nCntEffect].fRadius--;
				if (g_aEffect[nCntEffect].nLife == 0)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}
		
			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r +0, g_aEffect[nCntEffect].col.g+0, g_aEffect[nCntEffect].col.b+0, g_aEffect[nCntEffect].col.a+0);
			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r + 0, g_aEffect[nCntEffect].col.g + 0, g_aEffect[nCntEffect].col.b+0, g_aEffect[nCntEffect].col.a+0);
			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r + 0, g_aEffect[nCntEffect].col.g + 0, g_aEffect[nCntEffect].col.b+0, g_aEffect[nCntEffect].col.a+0);
			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r + 0, g_aEffect[nCntEffect].col.g + 0, g_aEffect[nCntEffect].col.b+0, g_aEffect[nCntEffect].col.a+0);
		}
		pVtx += 4;
	}
	/*頂点データをアンロックする*/
	g_pVtxBuffEffect->Unlock();
}
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;
	/*頂点バッファをデバイスのデータストリームにバインド*/
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*テクスチャの設定*/
	pDevice->SetTexture(0, g_pTextureEffect);
	/*レンダリングステート(加算合成処理)*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	/*ポリゴンの描画*/
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			/*弾が使用中なら描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, NUM_POLYGON);
		}
	}
	/*レンダーステート*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
void SetEffect(D3DXVECTOR3 pos/*発射位置*/, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_2D*pVtx;
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{

		if (g_aEffect[nCntEffect].bUse == false)					//弾が使用されていない場合
		{
			/*位置設定*/
			g_aEffect[nCntEffect].pos = pos;
			/*寿命*/
			g_aEffect[nCntEffect].nLife = nLife;
			/*色*/
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].col.r = col.r;
			g_aEffect[nCntEffect].col.a = col.a;
			g_aEffect[nCntEffect].col.b = col.b;
			g_aEffect[nCntEffect].col.g = col.g;

			g_aEffect[nCntEffect].fRadius = fRadius;
			/*頂点座標の設定*/
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (-EFFECT_SIZE / 2)* g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + (-EFFECT_SIZE / 2)* g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (EFFECT_SIZE / 2)*g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + (-EFFECT_SIZE / 2)* g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (-EFFECT_SIZE / 2)*g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + (EFFECT_SIZE / 2)*g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (EFFECT_SIZE / 2)* g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + (EFFECT_SIZE / 2)*g_aEffect[nCntEffect].fRadius, 0.0f);
				/*頂点カラーの設定*/
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			/*使用している状態にする*/
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;													//頂点データのポインタを四分進める
	}
	g_pVtxBuffEffect->Unlock();
}
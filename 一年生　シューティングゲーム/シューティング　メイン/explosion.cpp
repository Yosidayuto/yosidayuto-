#include "explosion.h"
#include"main.h"
/*マクロ定義*/
#define  MAX_EXPLOSLON (128)//爆発の最大数

/*構造体定義*/
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;//色
	int nCounterAnim;//カウンター
	int nPtternAnim;//パターンNo
	bool bUse;//使用しているかどうか
}EXPLOSION;
/*グローバル変数*/
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
EXPLOSION g_aExplosion[MAX_EXPLOSLON];//爆発の情報

									  /*初期化処理*/
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntExplosion;
	/*爆発情報の初期化*/
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPtternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}
	/*テクスチャの読み込み*/
	D3DXCreateTextureFromFile(pDevice, "explosion000.png", &g_pTextureExplosion);//テクスチャの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_EXPLOSLON,		//バッファサイズ
		D3DUSAGE_WRITEONLY,											//(固定)
		FVF_VERTEX_2D,												//頂点フォーマット
		D3DPOOL_MANAGED,											//（固定）
		&g_pVtxBuffExplosion,												//変数名が変わると変更が必要
		NULL);
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		/*頂点座標の設定*/
		pVtx[0].pos = D3DXVECTOR3(-MAX_EXPLOSION / 2, -MAX_EXPLOSION / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_EXPLOSION / 2, -MAX_EXPLOSION / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_EXPLOSION / 2, MAX_EXPLOSION / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_EXPLOSION / 2, MAX_EXPLOSION / 2, 0.0f);
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

		/*頂点データのポインタを4つ*/
		pVtx += 4;
	}
	/*頂点データをアンロック*/
	g_pVtxBuffExplosion->Unlock();

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	//テクスチャの設定
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdaExplosion(void)
{

	VERTEX_2D*pVtx;
	int  nCntExplosion;
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{

			g_aExplosion[nCntExplosion].nCounterAnim++;
			if (g_aExplosion[nCntExplosion].nCounterAnim == 10)
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0;//カウンターを初期値に戻す
				g_aExplosion[nCntExplosion].nPtternAnim++;

				if (g_aExplosion[nCntExplosion].nPtternAnim == 8)
				{
					g_aExplosion[nCntExplosion].nPtternAnim = 0;
					g_aExplosion[nCntExplosion].bUse = false;
				}

			}
			if (g_aExplosion[nCntExplosion].pos.y>SCREEN_HEIGHT ||
				g_aExplosion[nCntExplosion].pos.y<0 ||
				g_aExplosion[nCntExplosion].pos.x> SCREEN_WIDTH ||
				g_aExplosion[nCntExplosion].pos.x<0)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (-MAX_EXPLOSION / 2), g_aExplosion[nCntExplosion].pos.y + (-MAX_EXPLOSION / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (MAX_EXPLOSION / 2), g_aExplosion[nCntExplosion].pos.y + (-MAX_EXPLOSION / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (-MAX_EXPLOSION / 2), g_aExplosion[nCntExplosion].pos.y + (MAX_EXPLOSION / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (MAX_EXPLOSION / 2), g_aExplosion[nCntExplosion].pos.y + (MAX_EXPLOSION / 2), 0.0f);

			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPtternAnim*0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPtternAnim*0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPtternAnim*0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPtternAnim*0.125f + 0.125f, 1.0f);
			
		}
		pVtx += 4;
	}
	/*頂点データをアンロック*/
	g_pVtxBuffExplosion->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DraawExplosion(void)
{
	int  nCntExplosion;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*頂点バッファをデバイスのデータストリームにバインド*/
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	/*頂点フォーマットの設定*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*テクスチャの設定*/
	pDevice->SetTexture(0, g_pTextureExplosion);
	/*ポリゴンの描画*/
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//爆発が使用中なら描画
		{

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion*4, NUM_POLYGON);
		}
	}
}
void SetExplosion(D3DXVECTOR3 pos/*発射位置*/, D3DXCOLOR col/*色*/)
{
	VERTEX_2D*pVtx;
	int nCntExplosion;
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)//爆発が未使用の場合
		{
			g_aExplosion[nCntExplosion].pos = pos;//位置
			g_aExplosion[nCntExplosion].col = col;//色

													/*頂点座標の設定*/
			pVtx[0].pos = D3DXVECTOR3(-MAX_EXPLOSION / 2, -MAX_EXPLOSION / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(MAX_EXPLOSION / 2, -MAX_EXPLOSION / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-MAX_EXPLOSION / 2, MAX_EXPLOSION / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_EXPLOSION / 2, MAX_EXPLOSION / 2, 0.0f);
			g_aExplosion[nCntExplosion].bUse = true;//使用している状態にする
			break;
		}
		pVtx += 4;
	}
	/*頂点データをアンロック*/
	g_pVtxBuffExplosion->Unlock();
}
#include"life.h"
#include"main.h"
#include"model.h"
#include"camera.h"
typedef struct
{
	char *pFilename;	// ファイル名
}FILE_LIFE;
/*グローバル変数*/
//バッファへのポインター
LPDIRECT3DTEXTURE9 g_pTexturLife[LIFE_TEXTURE_MAX] = {};
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife[LIFE_TEXTURE_MAX] = {};//バッファへのポインター
LIFE g_aLife[LIFE_TEXTURE_MAX];
FILE_LIFE g_File[LIFE_TEXTURE_MAX] =
{
	{ "data/image/Physical.png" },
	{ "data/image/PhysicalLeft.png" },
	{ "data/image/PhysicalCentral.png" },
	{ "data/image/PhysicalRight.png" },
};

void InintLife(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nLife = 0; nLife < LIFE_TEXTURE_MAX; nLife++)
	{
		
		g_aLife[nLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLife[nLife].bUse = true;
		/*テクスチャの読み込み*/	
		D3DXCreateTextureFromFile(pDevice, g_File[nLife].pFilename, &g_pTexturLife[nLife]);
		/*頂点バッファの生成*/
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,//バッファサイズ
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffLife[nLife],
			NULL);
		g_pVtxBuffLife[nLife]->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
		/*頂点座標の設定（右回りで設定する*/
		pVtx[0].pos = D3DXVECTOR3((-LIFE1_SION_X / 2), (-LIFE1_SION_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3((LIFE1_SION_X / 2), (-LIFE1_SION_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3((-LIFE1_SION_X / 2), (LIFE1_SION_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3((LIFE1_SION_X / 2), (LIFE1_SION_Y / 2), 0.0f);
		//rhwの設定（値は１，０で固定）
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
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);
		//頂点データをアンロックする
		g_pVtxBuffLife[nLife]->Unlock();
	}
}
void UninitLife(void)
{
	for (int nLife = 0; nLife < LIFE_TEXTURE_MAX; nLife++)
	{
		//テクスチャの設定
		if (g_pTexturLife[nLife] != NULL)
		{
			g_pTexturLife[nLife]->Release();
			g_pTexturLife[nLife] = NULL;
		}
		//頂点バッファの開放
		if (g_pVtxBuffLife[nLife] != NULL)
		{
			g_pVtxBuffLife[nLife]->Release();
			g_pVtxBuffLife[nLife] = NULL;
		}
	}
	
}
void UpdateLife(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	PLAYER *pPlayer = GetPlayer();
	
	g_pVtxBuffLife[0]->Lock(0, 0, (void**)&pVtx, 0);
	g_aLife[0].pos = D3DXVECTOR3(300,40,0);
	pVtx[0].pos = D3DXVECTOR3(g_aLife[0].pos.x + (-LIFE1_SION_X / 2), g_aLife[0].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLife[0].pos.x + ( LIFE1_SION_X / 2), g_aLife[0].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLife[0].pos.x + (-LIFE1_SION_X / 2), g_aLife[0].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLife[0].pos.x + (LIFE1_SION_X / 2), g_aLife[0].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	/*頂点データをアンロックする*/
	g_pVtxBuffLife[0]->Unlock();

	g_pVtxBuffLife[1]->Lock(0, 0, (void**)&pVtx, 0);
	g_aLife[1].pos = D3DXVECTOR3(200, 40, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aLife[1].pos.x + (-LIFE1_SION_X / 2)/3, g_aLife[1].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLife[1].pos.x +  (LIFE1_SION_X / 2)/3, g_aLife[1].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLife[1].pos.x + (-LIFE1_SION_X / 2)/3, g_aLife[1].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLife[1].pos.x +  (LIFE1_SION_X / 2)/3, g_aLife[1].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	/*頂点データをアンロックする*/
	g_pVtxBuffLife[1]->Unlock();

	g_pVtxBuffLife[2]->Lock(0, 0, (void**)&pVtx, 0);
	g_aLife[2].pos = D3DXVECTOR3(300, 40, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aLife[2].pos.x + (-LIFE1_SION_X / 2) / 3, g_aLife[2].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLife[2].pos.x + (LIFE1_SION_X / 2) / 3, g_aLife[2].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLife[2].pos.x + (-LIFE1_SION_X / 2) / 3, g_aLife[2].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLife[2].pos.x + (LIFE1_SION_X / 2) / 3, g_aLife[2].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	/*頂点データをアンロックする*/
	g_pVtxBuffLife[2]->Unlock();

	g_pVtxBuffLife[3]->Lock(0, 0, (void**)&pVtx, 0);
	g_aLife[3].pos = D3DXVECTOR3(400, 40, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aLife[3].pos.x + (-LIFE1_SION_X / 2) / 3, g_aLife[3].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLife[3].pos.x + (LIFE1_SION_X / 2) / 3, g_aLife[3].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLife[3].pos.x + (-LIFE1_SION_X / 2) / 3, g_aLife[3].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLife[3].pos.x + (LIFE1_SION_X / 2) / 3, g_aLife[3].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	/*頂点データをアンロックする*/
	g_pVtxBuffLife[3]->Unlock();

	switch (pPlayer->nLife)
	{
	case 3:

		break;
	case 2:
		g_aLife[3].bUse = false;
		break;
	case 1:
		g_aLife[2].bUse = false;
		break;
	case 0:
		g_aLife[1].bUse = false;
		break;
	}
}
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nLife = 0; nLife < LIFE_TEXTURE_MAX; nLife++)
	{
		if (g_aLife[nLife].bUse)
		{
			/*アルファテストを有効化*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			/*アルファテスト基準値の設定*/
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			/*アルファテストの比較方法の設定*/
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			//頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffLife[nLife], 0, sizeof(VERTEX_2D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturLife[nLife]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			/*アルファテストを無効化*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}
}



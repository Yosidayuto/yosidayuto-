#include "score.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCORE (6)	//スコアの最大桁数
#define SCOREWIDTH (50.0f)
#define SCORE_SIZE (25.0f)
#define SCORE_NNMBER (9)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;					// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore[SCORE_NNMBER] = {};		// 頂点バッファへのポインタ
int						g_nScore[SCORE_NNMBER];					// スコア
D3DXVECTOR3				g_pos[SCORE_NNMBER];					//位置
D3DXVECTOR3				g_size[SCORE_NNMBER];					//サイズ
//=============================================================================
// 初期化処理
//=============================================================================

void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		// スコアの初期化
		g_nScore[nScore] = 0;
	}/*位置*/
	g_pos[0] = D3DXVECTOR3(1130, 530, 0);	//合計
	g_pos[1] = D3DXVECTOR3(860, 235, 0);	//アイテムメイン
	g_pos[2] = D3DXVECTOR3(860, 278, 0);	//アイテム大
	g_pos[3] = D3DXVECTOR3(860, 320, 0);	//アイテム中
	g_pos[4] = D3DXVECTOR3(860, 360, 0);	//アイテム小

	g_pos[5] = D3DXVECTOR3(1100, 235, 0);	//-アイテムメイン
	g_pos[6] = D3DXVECTOR3(1100, 278, 0);	//-アイテム大
	g_pos[7] = D3DXVECTOR3(1100, 320, 0);	//-アイテム中
	g_pos[8] = D3DXVECTOR3(1100, 360, 0);	//-アイテム小
	/*サイズ*/
	g_size[0]= D3DXVECTOR3(80, 80, 0);		//合計
	g_size[1] = D3DXVECTOR3(30, 30, 0);		//アイテムメイン
	g_size[2] = D3DXVECTOR3(30, 30, 0);		//アイテム大
	g_size[3] = D3DXVECTOR3(30, 30, 0);		//アイテム中
	g_size[4] = D3DXVECTOR3(30, 30, 0);		//アイテム小

	g_size[5] = D3DXVECTOR3(30, 30, 0);		//-アイテムメイン
	g_size[6] = D3DXVECTOR3(30, 30, 0);		//-アイテム大
	g_size[7] = D3DXVECTOR3(30, 30, 0);		//-アイテム中
	g_size[8] = D3DXVECTOR3(30, 30, 0);		//-アイテム小
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		"画像/スコア2.png",		// ファイルの名前
		&g_pTextureScore);				// テクスチャへのポインタ
	// 頂点情報の作成
	MakeVertexScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		//頂点バッファの破棄
		if (g_pVtxBuffScore != NULL)
		{
			g_pVtxBuffScore[nScore]->Release();
			g_pVtxBuffScore[nScore] = NULL;
		}
	}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffScore[nScore], 0, sizeof(VERTEX_2D));	
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScore);
		for (int nCntTex = 0; nCntTex < MAX_SCORE; nCntTex++)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTex, 2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;	//頂点情報へのポインタ
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffScore[nScore],
			NULL);

		//頂点をロックし、頂点データへのポインタ取得
		g_pVtxBuffScore[nScore]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPos = 0; nCntPos < MAX_SCORE; nCntPos++, pVtx += 4)
		{
			if (nScore == 0)
			{
				//頂点情報の設定
				pVtx[0].pos = D3DXVECTOR3(-g_size[nScore].x / 2 + g_pos[nScore].x, -g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * SCOREWIDTH, 0.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_size[nScore].x / 2 + g_pos[nScore].x, -g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * SCOREWIDTH, 0.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_size[nScore].x / 2 + g_pos[nScore].x, g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * SCOREWIDTH, 0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_size[nScore].x / 2 + g_pos[nScore].x, g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * SCOREWIDTH, 0.0f, 0.0f);

			}
			else
			{
				//頂点情報の設定
				pVtx[0].pos = D3DXVECTOR3(-g_size[nScore].x / 2 + g_pos[nScore].x, -g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * 30.0f, 0.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_size[nScore].x / 2 + g_pos[nScore].x, -g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * 30.0f, 0.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_size[nScore].x / 2 + g_pos[nScore].x, g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * 30.0f, 0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_size[nScore].x / 2 + g_pos[nScore].x, g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * 30.0f, 0.0f, 0.0f);

			}
		
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//色の設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}
		//頂点バッファをアンロックする
		g_pVtxBuffScore[nScore]->Unlock();
	}

}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue, int nType)
{
	
	float fTex[MAX_SCORE][SCORE_NNMBER];
	VERTEX_2D*pVtx;	//頂点情報へのポインタ
	/*スコア処理*/
	if (nType == 1)
	{//メインアイテム
		nValue *= 10000;
	}
	else if (nType == 2)
	{//アイテム大
		nValue *= 5000;
	}
	else if (nType == 3)
	{//アイテム中
		nValue *= 2500;
	}
	else if(nType == 4)
	{//アイテム小
		nValue *= 1000;
	}

	/*マイナススコア*/
	else if (nType == 5)
	{//メインアイテム
		nValue *= 3000;
	}
	else if (nType == 6)
	{//アイテム大
		nValue *= 1000;
	}
	else if (nType == 7)
	{//アイテム中
		nValue *= 800;
	}
	else if (nType == 8)
	{//アイテム小
		nValue *= 200;
	}

	g_nScore[nType] += nValue;
	g_nScore[0] = g_nScore[1] + g_nScore[2] + g_nScore[3] + g_nScore[4];
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		fTex[0][nScore] = g_nScore[nScore] % 10 * 0.1f;
		fTex[1][nScore] = g_nScore[nScore] / 10 % 10 * 0.1f;
		fTex[2][nScore] = g_nScore[nScore] / 100 % 10 * 0.1f;
		fTex[3][nScore] = g_nScore[nScore] / 1000 % 10 * 0.1f;
		fTex[4][nScore] = g_nScore[nScore] / 10000 % 10 * 0.1f;
		fTex[5][nScore] = g_nScore[nScore] / 100000 % 10 * 0.1f;
		/*fTex[6][nScore] = g_nScore[nScore] / 1000000 % 10 * 0.1f;
		fTex[7][nScore] = g_nScore[nScore] / 10000000 % 10 * 0.1f;*/
		//頂点をロックし、頂点データへのポインタ取得
		g_pVtxBuffScore[nScore]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntPos = 0; nCntPos < MAX_SCORE; nCntPos++, pVtx += 4)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((0.1f + fTex[nCntPos][nScore]) - 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((0.1f + fTex[nCntPos][nScore]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((0.1f + fTex[nCntPos][nScore]) - 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((0.1f + fTex[nCntPos][nScore]), 1.0f);
		}
		//頂点バッファをアンロックする
		g_pVtxBuffScore[nScore]->Unlock();
	}
	
}
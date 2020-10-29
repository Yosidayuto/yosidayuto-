#include"main.h"
#include"score.h"
#include"enemy.h"
LPDIRECT3DTEXTURE9 g_pTexturScore = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//バッファへのポインター
/*リザルト画面スコアカラー*/
int nCutScorecol01;
int nCutScorecol02;
/*スコアアップの計算*/
int Score1 = 0;
int Score2 = 0;
int Score3 = 0;


SCORE g_aScore[MAX_SCORE];
void InintScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//頂点情報へのポインター
	int nCntScore;
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		g_aScore[nCntScore].pos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[nCntScore].col= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aScore[nCntScore].bUse = false;
		g_aScore[nCntScore].nScoreCnt = 0;
	}

					
	D3DXCreateTextureFromFile(pDevice, "number000.png", &g_pTexturScore);//テクスチャの読み込み	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_SCORE,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffScore,//変数名が変わると変更が必要
		NULL);

	

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore= nCntScore+4)
	{
		/*頂点座標の設定（右回りで設定する*/
		pVtx[0+ nCntScore].pos = D3DXVECTOR3((-SCORE_SION_X / 2), (-SCORE_SION_Y / 2), 0.0f);
		pVtx[1+ nCntScore].pos = D3DXVECTOR3((SCORE_SION_X / 2), (-SCORE_SION_Y / 2), 0.0f);
		pVtx[2+ nCntScore].pos = D3DXVECTOR3((-SCORE_SION_X / 2), (SCORE_SION_Y / 2), 0.0f);
		pVtx[3+ nCntScore].pos = D3DXVECTOR3((SCORE_SION_X / 2), (SCORE_SION_Y / 2), 0.0f);

		/*rhwの設定（値は１，０で固定）*/
		pVtx[0+ nCntScore].rhw = 1.0f;
		pVtx[1+ nCntScore].rhw = 1.0f;
		pVtx[2+ nCntScore].rhw = 1.0f;
		pVtx[3+ nCntScore].rhw = 1.0f;

		/*頂点カラーの設定（0～255の数値で設定）*/
		pVtx[0+ nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1+ nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2+ nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3+ nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標の設定
		pVtx[0+ nCntScore].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1+ nCntScore].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2+ nCntScore].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+ nCntScore].tex = D3DXVECTOR2(0.1f, 1.0);
		
	}
	//頂点データをアンロックする
	g_pVtxBuffScore->Unlock();
	
}

void UninitScore(void)
{
	//テクスチャの設定
	if (g_pTexturScore != NULL)
	{
		g_pTexturScore->Release();
		g_pTexturScore = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
void UpdateScore(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	MODE mode;
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	/*リザルト画面スコア処理*/
		mode = GetMode();
		if (mode == MODE_RESULE)
		{
			pVtx[0].pos = D3DXVECTOR3(550 + (-SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(550 + ( SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(550 + (-SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(550 + ( SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);

			pVtx[4].pos = D3DXVECTOR3(650 + (-SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[5].pos = D3DXVECTOR3(650 + ( SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[6].pos = D3DXVECTOR3(650 + (-SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);
			pVtx[7].pos = D3DXVECTOR3(650 + ( SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);


			pVtx[8].pos = D3DXVECTOR3(750 + (-SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[9].pos = D3DXVECTOR3(750 + ( SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[10].pos= D3DXVECTOR3(750 + (-SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);
			pVtx[11].pos= D3DXVECTOR3(750 + ( SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);
		
			/*リザルト画面スコアカラー処理*/
			for (int nCnt = 0; nCnt < 255; nCnt++)
			{
				nCutScorecol01++;
				if (nCutScorecol01 == 500)
				{
					nCutScorecol01 = 0;//カウンターを初期値に戻す
					nCutScorecol02++;
					if (nCutScorecol02 >= 255)
					{
						nCutScorecol02 = 255;
					}
				}
			}
			for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore = nCntScore + 4)
			{
				pVtx[0 + nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, nCutScorecol02);
				pVtx[1 + nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, nCutScorecol02);
				pVtx[2 + nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, nCutScorecol02);
				pVtx[3 + nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, nCutScorecol02);
			}
		}

	g_pVtxBuffScore->Unlock();	//頂点データをアンロックする
}
void DrawScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturScore);
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore*4, NUM_POLYGON);
	}
}
void SetScore(D3DXVECTOR3 pos)
{
	int nCntScore;
	int nCntPos;
	int nCntzi=1;
	VERTEX_2D*pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない
	for (nCntScore = 0; nCntScore < 1; nCntScore++)
	{
		if (g_aScore[nCntScore].bUse == false)
		{
			g_aScore[nCntScore].pos = pos;
			for (nCntPos = 0; nCntPos < MAX_SCORE; nCntPos = nCntPos + 4)
			{
				/*頂点座標の設定（右回りで設定する*/
				pVtx[0 + nCntPos].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x *(nCntzi)+ (-SCORE_SION_X / 2), g_aScore[nCntScore].pos.y + (-SCORE_SION_Y / 2), 0.0f);
				pVtx[1 + nCntPos].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x *(nCntzi)+ (SCORE_SION_X / 2), g_aScore[nCntScore].pos.y + (-SCORE_SION_Y / 2), 0.0f);
				pVtx[2 + nCntPos].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x *(nCntzi)+ (-SCORE_SION_X / 2), g_aScore[nCntScore].pos.y + (SCORE_SION_Y / 2), 0.0f);
				pVtx[3 + nCntPos].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x *(nCntzi)+ (SCORE_SION_X / 2), g_aScore[nCntScore].pos.y + (SCORE_SION_Y / 2), 0.0f);
				nCntzi++;
			}
			/*使用している状態にする*/
			g_aScore[nCntScore].bUse = true;

			break;
		}
	}

	g_pVtxBuffScore->Unlock();	//頂点データをアンロックする
}
void ScoreUp(int Score)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	
  	Score1 += Score;
 	if (Score1 >= 10)
	{
		Score1 = 0;
		Score2++;
	}
	if (Score2 >= 10)
	{
		Score2 = 0;
		Score3++;
	}
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(Score3*0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Score3*0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(Score3*0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(Score3*0.1f + 0.1f, 1.0);

	pVtx[4].tex = D3DXVECTOR2(Score2*0.1f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(Score2*0.1f + 0.1f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(Score2*0.1f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(Score2*0.1f + 0.1f, 1.0);

	pVtx[8].tex = D3DXVECTOR2(Score1*0.1f	, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(Score1*0.1f+0.1f, 0.0f);
	pVtx[10].tex= D3DXVECTOR2(Score1*0.1f	, 1.0f);
	pVtx[11].tex= D3DXVECTOR2(Score1*0.1f+ 0.1f, 1.0);
	g_pVtxBuffScore->Unlock();
}
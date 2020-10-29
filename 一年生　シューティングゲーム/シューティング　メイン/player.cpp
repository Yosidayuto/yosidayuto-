#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include"fade.h"
#include"bomb.h"
						  /*グローバル変数*/
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;//テクスチャへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;//バッファへのポインター
PLAYER g_aPlayer;

int g_nCounterAnim;//アニメーションカウンター
int g_nPatternAnim;//アニメーションパターンNo
				   //**********//
				   //初期化処理//
				   //**********//
void InintPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//頂点情報へのポインター
	g_nCounterAnim = 0;
	g_nPatternAnim = 0;
	g_aPlayer.nLife = 5;
	g_aPlayer.dDisp = true;
	g_aPlayer.nBulletType = 0;
	g_aPlayer.nBomb = 0;
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "player000.png", &g_pTexturePolygon);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//バッファサイズ
		D3DUSAGE_WRITEONLY,											//(固定)
		FVF_VERTEX_2D,												//頂点フォーマット
		D3DPOOL_MANAGED,											//（固定）
		&g_pVtxBuffPolygon,											//変数名が変わると変更が必要
		NULL);

	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	/*頂点座標の設定（右回りで設定する）*/
	pVtx[0].pos = D3DXVECTOR3(-POLYGON_SIZE_X / 2, -POLYGON_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_SIZE_X / 2, -POLYGON_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-POLYGON_SIZE_X / 2, POLYGON_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_SIZE_X / 2, POLYGON_SIZE_Y / 2, 0.0f);
	/*rhwの設定（値は１，０で固定）*/
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	/*頂点カラーの設定（0～255の数値で設定）*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	/*テクスチャの座標の設定*/
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	/*頂点データをアンロックする*/
	g_pVtxBuffPolygon->Unlock();

	


}




void UninitPolygon(void)
{
	//テクスチャの設定
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}
void UpdatePolygon(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*頂点データの範囲をロックし、頂点バッファへのポインタを取得*/
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	switch (g_aPlayer.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_aPlayer.nCountState--;
		if (g_aPlayer.nCountState <= 0)
		{
			/*通常描画に戻す処理*/
			g_aPlayer.state = PLAYERSTATE_NORMAL;
			/*頂点カラーの設定*/
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_DEATH:
		g_aPlayer.nCountState--;
		if (g_aPlayer.nCountState <= 0)
		{
			SetFade(MODE_RESULE); 
		}
		return;
		break;
	}
	/*頂点データをアンロックする*/
	g_pVtxBuffPolygon->Unlock();
	/*-----------------------------------------------------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------------------------------------------------*/

	/*スペースキーが押された*/
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		switch (g_aPlayer.nBulletType)
		{
		case 0:
 			SetBullet(g_aPlayer.pos, D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 30, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 1:
			SetBullet(g_aPlayer.pos+D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos+D3DXVECTOR3(-10,- 30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 2:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos, D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 40, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 3:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(-5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos, D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 40, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 4:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(-5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos, D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 55, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 5:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(30, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-30, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 6:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(30, -30, 1.0f), D3DXVECTOR3(5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-30, -30, 1.0f), D3DXVECTOR3(-5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		}
 	
	}
	if (GetKeyboardTrigger(DIK_R)&&g_aPlayer.nBomb>0)
	{
		SetBomb(g_aPlayer.pos);
		g_aPlayer.nBomb--;
	}
	/*Wのキーが押されたかどうか*/
	if (Getkeyboardpress(DIK_W))
	{
		g_aPlayer.move.y -= VALUE_MOVE;
		g_aPlayer.move.y -= VALUE_MOVE;
	}
	/*Sのキーが押されたかどうか*/
	if (Getkeyboardpress(DIK_S))
	{
		g_aPlayer.move.y += VALUE_MOVE;
		g_aPlayer.move.y += VALUE_MOVE;
	}
	/*Aのキーが押されたかどうか*/
	if (Getkeyboardpress(DIK_A))
	{
		g_aPlayer.move.x -= VALUE_MOVE;
		g_aPlayer.move.x -= VALUE_MOVE;
	}
	/*Dのキーが押されたかどうか*/
	if (Getkeyboardpress(DIK_D))
	{
		g_aPlayer.move.x += VALUE_MOVE;
		g_aPlayer.move.x += VALUE_MOVE;
	}
	/*---------------------------------------------------------------*/
	/*画面外に行かない*/
	if (g_aPlayer.pos.y < 0 + (POLYGON_SIZE_Y / 2))
	{
		g_aPlayer.move.y += VALUE_MOVE;
		g_aPlayer.move.y += VALUE_MOVE;
	}
	if (g_aPlayer.pos.y > SCREEN_HEIGHT - (POLYGON_SIZE_Y / 2))
	{
		g_aPlayer.move.y -= VALUE_MOVE;
		g_aPlayer.move.y -= VALUE_MOVE;
	}
	if (g_aPlayer.pos.x<0 + (POLYGON_SIZE_X / 2) )
	{
		g_aPlayer.move.x += VALUE_MOVE;
		g_aPlayer.move.x += VALUE_MOVE;
	}
	if (g_aPlayer.pos.x > SCREEN_WIDTH - (POLYGON_SIZE_X / 2))
	{
		g_aPlayer.move.x -= VALUE_MOVE;
		g_aPlayer.move.x -= VALUE_MOVE;
	}
	/*-------------------------------------------------------------*/
	/*シフトをしながら*/
	if (Getkeyboardpress(DIK_LSHIFT))
	{
		if (Getkeyboardpress(DIK_D))
		{
			g_aPlayer.move.x -= VALUE_MOVE;
		}
		if (Getkeyboardpress(DIK_W))
		{
			g_aPlayer.move.y += VALUE_MOVE;
		}
		if (Getkeyboardpress(DIK_S))
		{
			g_aPlayer.move.y -= VALUE_MOVE;
		}
		if (Getkeyboardpress(DIK_A))
		{
			g_aPlayer.move.x += VALUE_MOVE;
		}
	}
	/*位置更新*/
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	/*慣性*/
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x)*RATE_MOVE;
	g_aPlayer.move.y += (0.0f - g_aPlayer.move.y)*RATE_MOVE;

	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない

	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x + (-POLYGON_SIZE_X / 2), g_aPlayer.pos.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + (POLYGON_SIZE_X / 2), g_aPlayer.pos.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x + (-POLYGON_SIZE_X / 2), g_aPlayer.pos.y + (POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + (POLYGON_SIZE_X / 2), g_aPlayer.pos.y + (POLYGON_SIZE_Y / 2), 0.0f);
	//頂点データをアンロックする7
	g_pVtxBuffPolygon->Unlock();
	//g_nCounterAnim++;//カウンター計算

}
//描画処理
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}
PLAYER *GatPlayer(void)
{
	return &g_aPlayer;
}

void HitPlayer(int nDamage)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	/*ライフを減らす*/
	g_aPlayer.nLife -= nDamage;

	if (g_aPlayer.nLife <= 0)
	{/*ライフが０になったとき*/
		SetExplosion(g_aPlayer.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
		g_aPlayer.dDisp = false;
		g_aPlayer.state = PLAYERSTATE_DEATH;//死亡状態に移行
		g_aPlayer.nCountState = 60;
		///*頂点カラーの設定*/
		//pVtx[0].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		//pVtx[1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		//pVtx[2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		//pVtx[3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}
	else
	{/*ダメージ状態カウンター状態に移行*/
		g_aPlayer.state = PLAYERSTATE_DAMAGE;//ダメージ状態に移行
		g_aPlayer.nCountState = 5;
		/*頂点カラーの設定*/
		pVtx[0].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}
	/*頂点データをアンロックする*/
	g_pVtxBuffPolygon->Unlock();
}
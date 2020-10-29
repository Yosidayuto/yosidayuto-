#pragma once
#ifndef _MAIN_H
#define _MAIN_H
#include"main.h"

#define POLYGON_POS_X (100)
#define POLYGON_POS_Y (100)
#define POLYGON_SIZE_X (50)
#define POLYGON_SIZE_Y (50)

#define RATE_MOVE (0.2f)
//マクロ定義
#define VALUE_MOVE (0.5f)//ポリゴンの移動量

/*プレイヤーの状態*/
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL = 0,	//通常
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nLife;				//ライフ
	PLAYERSTATE state;		//状態
	int nCountState;		//状態カウンター
	bool dDisp;				//表示切替
	int nBulletType;		//弾の強化
	int nBomb;				//ボム
}PLAYER;

void InintPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
PLAYER *GatPlayer(void);
void HitPlayer(int nDamage);
#endif
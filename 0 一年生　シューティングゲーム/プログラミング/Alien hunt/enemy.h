#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define _CRT_SECURE_NO_WARNINGS
/*マクロ定義*/
#define MAX_ENEMY (128)//敵の最大数
#define MAX_ENEMYSIZ (50)//敵のサイズ
#define MOVE_ENEMY (0.5f)//敵の移動

//インクルードファイル
#include"main.h"

/*構造体定義*/
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//通状

	ENEMYSTATE_DAMAGE,//ダメージ

	ENEMYSTATE_MAX,
}ENEMYSTATE;
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	ENEMYSTATE state;//状態
	int nLife;
	int nCounterState;
	D3DXCOLOR col;
	int nType;//種類
	bool bUse;//使用しているかどうか
}ENEMY;

/*プロトタイプ宣言*/
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
ENEMY *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
#endif
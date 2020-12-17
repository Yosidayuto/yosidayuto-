#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#
#define BULLET_SIZE_X (20)
#define BULLET_SIZE_Y (20)

#include"main.h"
/*弾の種類*/
typedef enum
{
	BULLETTYPE_PLAYE = 0,//プレイヤーの弾
	BULLETTYPE_ENEMY,//敵の弾
	BULLETTYPE_MAX
}BULLETTYPE;

/*プロトタイプ宣言*/
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos/*発射位置*/, D3DXVECTOR3 move/*移動量*/, BULLETTYPE type, int nLife, D3DXCOLOR col);
#endif

#pragma once
#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#define _CRT_SECURE_NO_WARNINGS
#define MAX_EXPLOSION (50)
/*インクルードファイル*/
#include"main.h"
/*プロトタイプ宣言*/
void InitExplosion(void);
void UninitExplosion(void);
void UpdaExplosion(void);
void DraawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos/*発射位置*/, D3DXCOLOR col/*移動量*/);

#endif
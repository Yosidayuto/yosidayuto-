#pragma once
#ifndef _ITEM_H
#define _ITEM_H

/*インクルードファイル*/
#include"main.h"

#define MAX_ITEM_SIZ (50)

/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//カラー
	int nType;			//種類
	bool bUse;			//使用しているかどうか
}ITEM;

/*プロトタイプ宣言*/
void InitItem(void);
void UninitItem(void);
void UpdaItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos,D3DXVECTOR3 move/*移動量*/, D3DXCOLOR col);



#endif

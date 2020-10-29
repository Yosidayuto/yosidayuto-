#pragma once
#ifndef  ITEM_H_
#define  ITEM_H_
#include"main.h"
#define ITEM_SIZE (20)
#define MAX_ITEM (100)
/*構造体*/
typedef enum
{
	TITLE_TYPE_0 = 0,
	TITLE_TYPE_1,
	TITLE_TYPE_2,
	TITLE_TYPE_3,
	TITLE_TYPE_MAX,
} ITEM_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXVECTOR3 dir;	//回転情報
	D3DXMATRIX mtxWorld;//行列計算
	int nType;			//アイテムの種類
	bool use;			//使用判定
}ITEM;

/*プロトタイプ宣言*/
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void SetItem(D3DXVECTOR3 pos,int nType);
void DrawItem(void);
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
#endif
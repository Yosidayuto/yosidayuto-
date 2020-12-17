#pragma once
#ifndef  BACKGROUND_H_
#define  BACKGROUND_H_

#include"main.h"
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXVECTOR3 rot;	//回転情報
	D3DXVECTOR3 size;	//サイズ情報
	D3DXMATRIX mtxWorld;//行列計算用
	LPD3DXMESH pMeshBlock;//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatBlock;//マテリアル情報へのポインタ
	DWORD nNumMatBlock;//マテリアつ情報の数
	bool bsed;			//使用判定
}BACKGROUND;
/*プロトタイプ宣言*/
void InitBackground(void);
void UninitBackground(void);
void UpdateBackground(void);
void DrawBackground(void);
void SetBackground(D3DXVECTOR3 pos);

#endif
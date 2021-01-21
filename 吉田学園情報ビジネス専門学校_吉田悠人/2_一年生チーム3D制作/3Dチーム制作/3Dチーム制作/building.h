#pragma once
#ifndef  BUILDING_H_
#define  BUILDING_H_

#include"main.h"
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXVECTOR3 rot;	//回転情報
	D3DXVECTOR3 size;	//サイズ情報

	D3DXMATRIX mtxWorld;//行列計算用
	LPD3DXMESH pMeshBuilding;//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatBuilding;//マテリアル情報へのポインタ
	DWORD nNumMatBuilding;//マテリアつ情報の数

	bool used;			//使用判定
}BUILDING;
/*プロトタイプ宣言*/
void InitBuilding(void);
void UninitBuilding(void);
void UpdateBuilding(void);
void DrawBuilding(void);
void SetBuilding(D3DXVECTOR3 pos, D3DXVECTOR3 size);
bool CollisionBuilding(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif
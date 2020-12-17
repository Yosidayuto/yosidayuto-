#ifndef  GOAl_H
#define  GOAl_H

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
	bool buse;			//使用判定
}GOAl;
/*プロトタイプ宣言*/
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif
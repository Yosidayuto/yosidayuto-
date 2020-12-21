#ifndef  BLOCK_H_
#define  BLOCK_H_

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
	bool used;			//使用判定
}BLOCK;
/*プロトタイプ宣言*/
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif
#ifndef  BLOCK_H
#define  BLOCK_H

#include"main.h"

#define MAX_BLOCK (100)
/*構造体*/
typedef struct
{
	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
}SEARCH_BOX;
typedef struct
{
	D3DXVECTOR3			pos;			//位置情報
	D3DXVECTOR3			posold;			//位置の古い情報
	D3DXVECTOR3			rot;			//回転情報
	D3DXVECTOR3			size;			//サイズ情報

	D3DXMATRIX			mtxWorld;		//行列計算用
	LPD3DXMESH			pMeshBlock;		//メッシュ情報へのポインタ
	LPD3DXBUFFER		pBuffMatBlock;	//マテリアル情報へのポインタ
	DWORD				nNumMatBlock;	//マテリアつ情報の数
	SEARCH_BOX			box;
	bool				used;			//使用判定
}BLOCK;
/*プロトタイプ宣言*/
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool CollisionBlockEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool ColRayBox(D3DXVECTOR3* pos, D3DXVECTOR3* dir, SEARCH_BOX* border, D3DXMATRIX* mat, float& output, D3DXVECTOR3* colPos = 0);
BLOCK*GetBlock();
#endif
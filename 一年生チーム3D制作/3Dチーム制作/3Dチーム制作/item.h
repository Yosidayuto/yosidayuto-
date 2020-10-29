#ifndef  ITEM_H_
#define  ITEM_H_
#include"main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEM_SIZE (20)
#define MAX_ITEM (30)
//****************************************************************************
/*構造体*/
//****************************************************************************
typedef enum
{
	TITLE_TYPE_0 = 0,	//メインアイテム
	TITLE_TYPE_1,		//アイテム大
	TITLE_TYPE_2,		//アイテム中
	TITLE_TYPE_3,		//アイテム小
	TITLE_TYPE_MAX,
} ITEM_TYPE;
typedef struct
{
	LPDIRECT3DTEXTURE9	pTextureModel[100];//ポリゴンのテクスチャ
	LPD3DXBUFFER		pBuffMat;			//マテリアル情報へのポインタ
	DWORD				nNumMat;			//マテリアル情報の数
	LPD3DXMESH			pMesh;				//メッシュ情報へのポインタ
	D3DXMATRIX			mtxWorld;			//行列計算用
}MODEL_ITEM;
typedef struct
{
	D3DXVECTOR3			pos;				//位置情報
	D3DXVECTOR3			movePos;			//移動量
	D3DXVECTOR3			dir;				//回転情報
	D3DXMATRIX			mtxWorld;			//行列計算
	double				vx = 0.0, vy;		//加速度
	int					nType;				//アイテムの種類

	bool				buse;				//使用判定
	//float				fDist;				//地面の距離
	//BOOL				Hit;				//地面に当たったか
	MODEL_ITEM			ItemParts[TITLE_TYPE_MAX];
}ITEM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 dir , int nType);
void DrawItem(void);
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
ITEM*GetItem();

#endif
#ifndef  MAP_H_
#define  MAP_H_

#include"main.h"

/*構造体*/
/*パーツごとの情報*/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture[256];//ポリゴンのテクスチャ
	LPD3DXMESH Mesh;		//メッシュ情報へのポインタ
	LPD3DXBUFFER BuffMat;	//マテリアル情報へのポインタ
	DWORD NumMat;			//マテリアル情報の数
	D3DXMATRIX mtxWorld;	//行列計算用
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;		//ブロックの当たり判定
	D3DXVECTOR3 rot;		//向き
	BOOL Hit;				//当たり判定
	float fDist;

}MAP;
/*プロトタイプ宣言*/
void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);
MAP*GetMap();

#endif
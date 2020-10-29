#ifndef  LINE_H
#define  LINE_H
#include"main.h"
#define MAX_LINE (100)
#define LINE_X (500)
#define LINE_Y (300)

/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXVECTOR3 rot;	//回転情報
	D3DXMATRIX mtxWorld;//行列計算
	bool buse;			//使用判定
}LINE;
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXCOLOR col;		//カラー
}VERTEX_POINT;
#define FVF_VERTEX_POINT (D3DFVF_XYZ | D3DFVF_DIFFUSE)

void InitLine(void);
void UninitLine(void);
void UpdateLine(void);
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos, D3DXCOLOR color);//位置と方向
void DrawLine(void);
#endif
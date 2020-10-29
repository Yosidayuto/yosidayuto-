#ifndef  BILLBOARD_H_
#define  BILLBOARD_H_
#include"main.h"

#define BILLBOARD_SIZE (5)
#define MAX_BILLBOARD (100)
/*構造体*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXVECTOR3 dir;	//回転情報
	D3DXVECTOR3 size;	//大きさ
	D3DXMATRIX mtxWorld;//行列計算
	bool buse;			//使用判定
}BILLBOARD;

/*プロトタイプ宣言*/
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir);
void DrawBillboard(void);
BILLBOARD*GetBillboard();

#endif
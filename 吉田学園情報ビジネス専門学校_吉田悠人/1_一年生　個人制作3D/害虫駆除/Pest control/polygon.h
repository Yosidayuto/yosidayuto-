#ifndef  POLYGON_H_
#define  POLYGON_H_

#define POLYGON_SAZE (5000)
#define POLYGON_MAX (1)
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報
	D3DXVECTOR3 size;	//大きさ情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXMATRIX mtxWorld;//行列計算

	bool used;			//使用判定
}POLGON;

void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
bool CollisionPolygon(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif
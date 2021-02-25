#ifndef  POLYGON_H_
#define  POLYGON_H_

#define POLYGON_SAZE (5000)
#define POLYGON_MAX (1)
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXVECTOR3 size;	//�傫�����
	D3DXVECTOR3 rot;	//�������
	D3DXMATRIX mtxWorld;//�s��v�Z

	bool used;			//�g�p����
}POLGON;

void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
bool CollisionPolygon(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif
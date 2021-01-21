#ifndef  LINE_H
#define  LINE_H
#include"main.h"
#define MAX_LINE (100)
#define LINE_X (500)
#define LINE_Y (300)

/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXVECTOR3 rot;	//��]���
	D3DXMATRIX mtxWorld;//�s��v�Z
	bool buse;			//�g�p����
}LINE;
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXCOLOR col;		//�J���[
}VERTEX_POINT;
#define FVF_VERTEX_POINT (D3DFVF_XYZ | D3DFVF_DIFFUSE)

void InitLine(void);
void UninitLine(void);
void UpdateLine(void);
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos, D3DXCOLOR color);//�ʒu�ƕ���
void DrawLine(void);
#endif
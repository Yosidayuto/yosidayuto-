#ifndef  BILLBOARD_H_
#define  BILLBOARD_H_
#include"main.h"

#define BILLBOARD_SIZE (5)
#define MAX_BILLBOARD (100)
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���
	D3DXVECTOR3 dir;	//��]���
	D3DXVECTOR3 size;	//�傫��
	D3DXMATRIX mtxWorld;//�s��v�Z
	bool buse;			//�g�p����
}BILLBOARD;

/*�v���g�^�C�v�錾*/
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir);
void DrawBillboard(void);
BILLBOARD*GetBillboard();

#endif
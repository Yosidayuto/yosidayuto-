#ifndef  LIFE_H
#define  LIFE_H

#define LIFE_SION_Y (50)
#define LIFE_SION_X (30)

#define MAX_LIFE (5*4-1)//�X�R�A�p�l���̍ő吔
#include"main.h"
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nCntLife;
}LIFE;

void InintLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos);
#endif
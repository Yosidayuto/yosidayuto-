#ifndef _EFFECT_H_
#define _EFFECT_H_
#include"main.h"

#define EFFECT_SIZE (15)

/*�v���g�^�C�v�錾*/
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos/*���ˈʒu*/, D3DXCOLOR col,float fRadius, int nLife);
#endif

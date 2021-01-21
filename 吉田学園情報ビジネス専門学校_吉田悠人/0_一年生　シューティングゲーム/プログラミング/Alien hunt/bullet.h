#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#
#define BULLET_SIZE_X (20)
#define BULLET_SIZE_Y (20)

#include"main.h"
/*�e�̎��*/
typedef enum
{
	BULLETTYPE_PLAYE = 0,//�v���C���[�̒e
	BULLETTYPE_ENEMY,//�G�̒e
	BULLETTYPE_MAX
}BULLETTYPE;

/*�v���g�^�C�v�錾*/
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos/*���ˈʒu*/, D3DXVECTOR3 move/*�ړ���*/, BULLETTYPE type, int nLife, D3DXCOLOR col);
#endif

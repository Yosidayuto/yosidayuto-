#pragma once
#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#define _CRT_SECURE_NO_WARNINGS
#define MAX_EXPLOSION (50)
/*�C���N���[�h�t�@�C��*/
#include"main.h"
/*�v���g�^�C�v�錾*/
void InitExplosion(void);
void UninitExplosion(void);
void UpdaExplosion(void);
void DraawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos/*���ˈʒu*/, D3DXCOLOR col/*�ړ���*/);

#endif
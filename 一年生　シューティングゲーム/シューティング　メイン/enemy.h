#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define _CRT_SECURE_NO_WARNINGS
/*�}�N����`*/
#define MAX_ENEMY (128)//�G�̍ő吔
#define MAX_ENEMYSIZ (50)//�G�̃T�C�Y
#define MOVE_ENEMY (0.5f)//�G�̈ړ�

//�C���N���[�h�t�@�C��
#include"main.h"

/*�\���̒�`*/
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//�ʏ�

	ENEMYSTATE_DAMAGE,//�_���[�W

	ENEMYSTATE_MAX,
}ENEMYSTATE;
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	ENEMYSTATE state;//���
	int nLife;
	int nCounterState;
	D3DXCOLOR col;
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
}ENEMY;

/*�v���g�^�C�v�錾*/
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
ENEMY *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
#endif
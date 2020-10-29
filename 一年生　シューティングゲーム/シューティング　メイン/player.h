#pragma once
#ifndef _MAIN_H
#define _MAIN_H
#include"main.h"

#define POLYGON_POS_X (100)
#define POLYGON_POS_Y (100)
#define POLYGON_SIZE_X (50)
#define POLYGON_SIZE_Y (50)

#define RATE_MOVE (0.2f)
//�}�N����`
#define VALUE_MOVE (0.5f)//�|���S���̈ړ���

/*�v���C���[�̏��*/
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL = 0,	//�ʏ�
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;
/*�\����*/
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nLife;				//���C�t
	PLAYERSTATE state;		//���
	int nCountState;		//��ԃJ�E���^�[
	bool dDisp;				//�\���ؑ�
	int nBulletType;		//�e�̋���
	int nBomb;				//�{��
}PLAYER;

void InintPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
PLAYER *GatPlayer(void);
void HitPlayer(int nDamage);
#endif
#ifndef  ENEMY_H_
#define  ENEMY_H_
/*-----------------*/
#include"main.h"
/*-----------------*/
#define MAX_ENEMY 30
#define MAX_SIZE1 12
/*-----------------*/
/*�\����*/
/*��ԏ����\����*/
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//�ʏ�
	ENEMYSTATE_DAMAGE,//�_���[�W
	ENEMYSTATE_MAX,
}ENEMYSTATE;

typedef enum
{
	ENEMY_PARTS0 = 0,
	ENEMY_PARTS1,
	ENEMY_PARTS2,
	ENEMY_PARTS3,
	ENEMY_PARTS_MAX,
} ENEMY_PARTS;

typedef struct
{
	LPD3DXMESH pMesh;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;			//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;	//�s��v�Z�p
	LPDIRECT3DTEXTURE9 pTextureModel[100];//�|���S���̃e�N�X�`��
}MODEL_ENEMY;
typedef struct
{
	int nLife;				//�̗�
	int nType;				//�G�l�~�[�̎��
	int nCounterState;		//�_���[�W��Ԃ̏����J�E���g
	ENEMYSTATE state;		//�G�l�~�[�̏��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�u���b�N�̓����蔻��
	D3DXVECTOR3 movePos;	//�ړ���
	D3DXVECTOR3 size;		//�傫��
	D3DXVECTOR3 rot;		//��]
	D3DXVECTOR3 rotDest;	//�ڕW�̊p�x
	D3DXCOLOR col;			//�J���[
	float fAngle;			//�v���C���[�ւ̊p�x
	float fRot;				//�i�ފp�x
	double vx = 0.0f, vy;	//�����x
	D3DXMATRIX mtxWorld;	//�s��v�Z�p
	bool use = false;		//�g���Ă��邩
	MODEL_ENEMY enemyParts[ENEMY_PARTS_MAX];	//�G�l�~�[�̎��
	float fDist;			//�n�ʂ܂ł̋���
	BOOL Hit;				//�n�ʂɓ���������
}ENEMY;
/*�v���g�^�C�v�錾*/
void InitEnemy(void);
void UninitEnemy(void);	
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(int Type, D3DXVECTOR3 pos);
void HitEnemy(int nDamage,int nCntEnemy);
ENEMY*GetEnemy();
#endif
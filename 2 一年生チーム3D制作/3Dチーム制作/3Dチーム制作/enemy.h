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
	ENEMYSTATE_TRACKING,//�ǔ�
	ENEMYSTATE_DAMAGE,//�_���[�W
	ENEMYSTATE_MAX,
}ENEMYSTATE;
/*�G�l�~�[�p�[�c*/
typedef enum
{
	ENEMY_PARTS0 = 0,
	ENEMY_PARTS1,
	ENEMY_PARTS2,
	ENEMY_PARTS3,
	ENEMY_PARTS4,
	ENEMY_PARTS5,
	ENEMY_PARTS6,
	ENEMY_PARTS7,
	ENEMY_PARTS8,
	ENEMY_PARTS9,
	ENEMY_PARTS10,
	ENEMY_PARTS_MAX,
} ENEMY_PARTS;
/*�G�l�~�[�̃p�[�c���*/
typedef struct
{
	LPD3DXMESH			pMesh;				//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		pBuffMat;			//�}�e���A�����ւ̃|�C���^
	DWORD				nNumMat;			//�}�e���A�����̐�
	LPDIRECT3DTEXTURE9	pTextureModel[50];	//�|���S���̃e�N�X�`��
	D3DXVECTOR3			pos;				//�ʒu���
	D3DXVECTOR3			rot;				//��]���
	D3DXVECTOR3			rotAnime;			//�A�j���̊p�x
	D3DXVECTOR3			posAnime;			//�A�j���̈ړ���
	D3DXVECTOR3			moverotAnime;		//�A�j���̊p�x
	D3DXVECTOR3			moveposAnime;		//�A�j���̈ړ���

	D3DXMATRIX			mtxWorld;			//�s��v�Z
	D3DXMATRIX			mtxWorldAnime;		//�s��v�Z

}MODEL_ENEMY;
/*�G�l�~�[�̎��씻��*/
typedef struct
{

	D3DXVECTOR3		SearchRot;
	float			fdistance;
	float			fRot;
	bool			bSearch;
}ENEMY_SEARCH;
/*�G�l�~�[�̃}�b�v�����蔻��*/
typedef struct
{
	D3DXVECTOR3 directionMap;					//���肷�����
	BOOL		WallHit;						//����̌���
	float		WallDistance;					//���肵�����̂Ƃ̋���
}ENEMY_MAP;
/*�G�l�~�[�̏��*/
typedef struct
{
	int				nLife;							//�̗�
	int				nType;							//�G�l�~�[�̎��
	int				nCounterState;					//�_���[�W��Ԃ̏����J�E���g
	ENEMYSTATE		state;							//�G�l�~�[�̏��
	D3DXVECTOR3		pos;							//�ʒu
	D3DXVECTOR3		posOld;							//�u���b�N�̓����蔻��
	D3DXVECTOR3		movePos;						//�ړ���
	D3DXVECTOR3		size;							//�傫��
	D3DXVECTOR3		rot;							//��]
	D3DXVECTOR3		rotDest;						//�ڕW�̊p�x
	D3DXCOLOR		col;							//�J���[
	D3DXVECTOR3		startPos;						//����X�^�[�g�ʒu
	D3DXVECTOR3		endPos;							//����I���ʒu
	float			fAngle;							//�ڕW�ւ̈ʒu
	float			fRot;							//�i�ފp�x
	float			fcol_t;							//�ڐ��̏Փˊ��o
	int				x;
	double			vx = 0.0f, vy;					//�����x
	D3DXMATRIX		mtxWorld;						//�s��v�Z�p
	bool			buse = false;					//�g���Ă��邩
	int				nPos;							//����X�C�b�`
	MODEL_ENEMY		enemyParts[ENEMY_PARTS_MAX];	//�G�l�~�[�̎��
	ENEMY_SEARCH	enemySearch;					//�G�l�~�[�̎���
}ENEMY;
/*�v���g�^�C�v�錾*/
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(int Type, D3DXVECTOR3 pos, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos);
void HitEnemy(int nDamage, int nCntEnemy);
ENEMY*GetEnemy();
void SearchEnemy();
#endif
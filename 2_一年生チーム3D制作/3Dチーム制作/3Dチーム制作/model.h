#ifndef  MODEL_H
#define  MODEL_H

#include"item.h"
#include"main.h"
#include"map.h"
#define MOTION_ANIMATION_NUM 5	//�A�j���[�V������
#define MOTION_KEYSET_MAX 5		//�L�[�Z�b�g�ő吔
//****************************************************************************
/*�\����*/
//****************************************************************************
/*�v���C���[�̃p�[�c*/
typedef enum
{
	MODEL_LABEL_Parts0 = 0,
	MODEL_LABEL_Parts1,
	MODEL_LABEL_Parts2,
	MODEL_LABEL_Parts3,
	MODEL_LABEL_Parts4,
	MODEL_LABEL_Parts5,
	MODEL_LABEL_Parts6,
	MODEL_LABEL_Parts7,
	MODEL_LABEL_Parts8,
	MODEL_LABEL_Parts9,
	MODEL_LABEL_Parts10,
	MODEL_LABEL_MAX,
} MODEL_LABEL;
/*�A�j���[�V�����L�[���*/
typedef struct
{
	D3DXVECTOR3		pos;						//�ʒu
	D3DXVECTOR3		rot;						//��]
	D3DXMATRIX		mtxWorldAnime;			//�s��v�Z

}AnimationKey;	
/*�A�j���[�V�����L�[�Z�b�g���*/
typedef struct
{
	int				frame;						//�L�[�t���[����
	AnimationKey	key[MODEL_LABEL_MAX];		//�L�[�Z�b�g�Ɋ܂ރL�[���
}AnimationKeySet;
/*�A�j���[�V�������*/
typedef struct
{
	bool			isLoop;						//���[�V�������[�v�ݒ�
	int				keyNum;						//�L�[��
	AnimationKeySet keySet[MOTION_KEYSET_MAX];	//�A�j���[�V�����Ɋ܂ރL�[�Z�b�g���
}Animation;

/*�v���C���[�̏��*/
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL = 0,	//�ʏ�
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_MAX
}PLAYER_STATE;
/*�v���C���[�̃}�b�v�����蔻��*/
typedef struct
{
	D3DXVECTOR3 directionMap;	//���肷�����
	BOOL		WallHit;		//����̌���
	float		WallDistance;	//���肵�����̂Ƃ̋���
}PLAYER_MAP;
/*�p�[�c�̏��*/
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

}MODEL;
/*�v���C���[�̏��*/
typedef struct
{
	D3DXVECTOR3		pos;							//�ʒu
	D3DXVECTOR3		posOld;							//�u���b�N�̓����蔻��
	D3DXVECTOR3		movePos;						//�ړ���
	D3DXVECTOR3		rot;							//��]
	D3DXVECTOR3		rotDest;						//�ڕW�̊p�x
	D3DXMATRIX		mtxWorld;						//�s��v�Z�p
	PLAYER_STATE	state;							//���
	//double		vx = 0.0, vy;					//�����x
	float			fAngle;
	bool			bItem[MAX_ITEM][TITLE_TYPE_MAX];//�v���C���[�̎����Ă���A�C�e��
	int				nLife[MAX_ITEM][TITLE_TYPE_MAX];//�A�C�e���i��
	int				nDamage;						//�_���[�W����
	int				x,y,z;							//�e�L�X�g
	
	bool			bGoal;							//�S�[���X�C�b�`
	MODEL			modelParts[MODEL_LABEL_MAX];	//�v���C���[���\������p�[�c�Q
	PLAYER_MAP		MapProcess[DIRECTION_PROCESS];	//�n�ʂɓ���������
}PLAYER;
//****************************************************************************
/*�v���g�^�C�v�錾*/
//****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(bool bDamage);
PLAYER*GetPlayer();

#endif
#ifndef  MODEL_H_
#define  MODEL_H_

#include"main.h"
#define MOTION_ANIMATION_NUMMODEL 5	//�A�j���[�V������
#define MOTION_KEYSET_MAXMODEL 5		//�L�[�Z�b�g�ő吔

/*�\����*/
/*�v���C���[�̏��*/
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL = 0,	//�ʏ�
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_MAX
}PLAYER_STATE;
/*�p�[�c�̊K�w�\��*/
typedef enum
{
	MODEL_LABEL_Parts0 = 0,		

	MODEL_LABEL_MAX,
} MODEL_LABEL;
/*�A�j���[�V�����L�[���*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//��]
}AnimationKeyMODEL;
/*�A�j���[�V�����L�[�Z�b�g���*/
typedef struct
{
	int frame;							//�L�[�t���[����
	AnimationKeyMODEL key[MODEL_LABEL_MAX];	//�L�[�Z�b�g�Ɋ܂ރL�[���
}AnimationKeySetMODEL;
/*�A�j���[�V�������*/
typedef struct
{
	bool isLoop;	//���[�V�������[�v�ݒ�
	int keyNum;		//�L�[��
	AnimationKeySetMODEL keySet[MOTION_KEYSET_MAXMODEL];//�A�j���[�V�����Ɋ܂ރL�[�Z�b�g���
}AnimationMODEL;

/*�p�[�c���Ƃ̏��*/
typedef struct
{
	LPD3DXMESH pMesh;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;			//�}�e���A�����̐�
	LPDIRECT3DTEXTURE9 pTextureModel[250];//�|���S���̃e�N�X�`��
	D3DXVECTOR3 pos;		//�ʒu���
	D3DXVECTOR3 rot;		//��]���
	D3DXMATRIX mtxWorld;	//�s��v�Z
	char pFilename;			// �t�@�C����
	int nldxModelParent;	//�e�q���f���̃C���f�b�N�X
	D3DXVECTOR3 rotAnime;	//�A�j���̊p�x
	D3DXVECTOR3 posAnime;	//�A�j���̈ړ���
}MODEL;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�u���b�N�̓����蔻��
	D3DXVECTOR3 movePos;	//�ړ���
	D3DXVECTOR3 rot;		//��]
	D3DXVECTOR3 rotDest;	//�ڕW�̊p�x
	D3DXMATRIX mtxWorld;	//�s��v�Z�p
	PLAYER_STATE state;		//���
	double vx = 0.0f, vy;	//�����x
	float fDist;			//�n�ʂ̋���
	int nLife;				//�v���C���[�̗�
	int nMagic;				//�}�W�b�N�X�C�b�`
	int nDamage;			//�_���[�W����
	MODEL modelParts[MODEL_LABEL_MAX];	//�v���C���[���\������p�[�c�Q
	float fAngle;			//�_���[�W���󂯂����̂̂�����
	BOOL Hit;				//�n�ʂɓ���������
}PLAYER;	
/*�v���g�^�C�v�錾*/
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void HitModel(int nDamage,int nEnemy,int nHit);
PLAYER*GetPlayer();

#endif
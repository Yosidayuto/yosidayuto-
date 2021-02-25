#ifndef  BOOS_H_
#define  BOOS_H_

#include"main.h"

#define MOTION_ANIMATION_NUM 5	//�A�j���[�V������
#define MOTION_KEYSET_MAX 5		//�L�[�Z�b�g�ő吔
/*�\����*/
/*�p�[�c�̊K�w�\��*/
typedef enum
{
	BOOS_PARTS_Parts0 = 0,
	BOOS_PARTS_Parts1,
	BOOS_PARTS_Parts2,
	BOOS_PARTS_Parts3,
	BOOS_PARTS_Parts4,
	BOOS_PARTS_MAX,
} BOOS_PARTS_FILE;
/*�A�j���[�V�����L�[���*/
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//��]
}AnimationKey;
/*�A�j���[�V�����L�[�Z�b�g���*/
typedef struct
{
	int frame;							//�L�[�t���[����
	AnimationKey key[BOOS_PARTS_MAX];	//�L�[�Z�b�g�Ɋ܂ރL�[���
}AnimationKeySet;
/*�A�j���[�V�������*/
typedef struct
{
	bool isLoop;	//���[�V�������[�v�ݒ�
	int keyNum;		//�L�[��
	AnimationKeySet keySet [MOTION_KEYSET_MAX];//�A�j���[�V�����Ɋ܂ރL�[�Z�b�g���
}Animation;
/*�{�X�̏��*/
typedef enum
{
	BOOS_STATE_NORMAL=0,		//�ʏ�
	BOOS_STATE_DAMAGE,		//�_���[�W
	BOOS_STATE_DEATH,		//���S���
	BOOS_STATE_MAX
}BOOS_STATE;
/*�s���p�^�[��*/
typedef enum
{
	BOOS_PATTERN_0 = 0,	
	BOOS_PATTERN_1,		
	BOOS_PATTERN_2,		
	BOOS_PATTERN_3,
	BOOS_PATTERN_MAX
}BOOS_PATTERN;
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
	D3DXVECTOR3 rotAnime;	//�A�j���̊p�x
	D3DXVECTOR3 posAnime;	//�A�j���̈ړ���
	int nldxModelParent;	//�e�q���f���̃C���f�b�N�X
}BOOS_PARTS;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 movePos;	//�ړ���
	D3DXVECTOR3 rot;		//��]
	D3DXVECTOR3 rotDest;	//�ڕW�̊p�x
	D3DXMATRIX mtxWorld;	//�s��v�Z�p
	BOOS_STATE state;		//���
	BOOS_PATTERN pattern;	//�s��
	int nLife;				//�{�X�̗�
	int nDamage;			//�_���[�W����
	float fRot;				//�i�ފp�x

	BOOS_PARTS modelParts[BOOS_PARTS_MAX];	//�v���C���[���\������p�[�c�Q
}BOOS;
/*�v���g�^�C�v�錾*/
void InitBoos(void);
void UninitBoos(void);
void UpdateBoos(void);
void DrawBoos(void);
void HitBoos(int nDamage,int nMagicType);
BOOS*GetBoos();

#endif
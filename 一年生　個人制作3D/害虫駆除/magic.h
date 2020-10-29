#ifndef  MAGIC_H_
#define  MAGIC_H_
/*-----------------*/
#include"main.h"
/*-----------------*/
#define MAX_MAGIC 30
#define MAX_SIZE1 12
/*-----------------*/
/*�\����*/

typedef enum
{
	MAGIC_PARTS0 = 0,
	MAGIC_PARTS1,
	MAGIC_PARTS2,
	MAGIC_PARTS3,
	MAGIC_PARTS_MAX,
} MAGIC_PARTS;

typedef struct
{
	LPD3DXMESH pMesh;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;			//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;	//�s��v�Z�p
	LPDIRECT3DTEXTURE9 pTextureModel[100];//�|���S���̃e�N�X�`��

}MODEL_MAGIC;
typedef struct
{
	int nType;				//���@�̎��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 movePos;	//�ړ���
	D3DXVECTOR3 size;		//�傫��
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 dir;		//����
	float fAngle;			
	float fRot;				//�i�ފp�x
	D3DXMATRIX mtxWorld;	//�s��v�Z�p
	bool bUse = false;		//�g���Ă��邩
	MODEL_MAGIC enemyParts[MAGIC_PARTS_MAX];	//���@�̎��X�t�@�C��
}MAGIC;
/*�v���g�^�C�v�錾*/
void InitMagic(void);
void UninitMagic(void);
void UpdateMagic(void);
void DrawMagic(void);
void SetMagic(int Type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 dir);
MAGIC*GetMagic();
#endif
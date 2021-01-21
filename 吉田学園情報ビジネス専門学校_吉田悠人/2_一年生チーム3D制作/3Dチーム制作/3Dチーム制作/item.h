#ifndef  ITEM_H_
#define  ITEM_H_
#include"main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM_SIZE (20)
#define MAX_ITEM (30)
//****************************************************************************
/*�\����*/
//****************************************************************************
typedef enum
{
	TITLE_TYPE_0 = 0,	//���C���A�C�e��
	TITLE_TYPE_1,		//�A�C�e����
	TITLE_TYPE_2,		//�A�C�e����
	TITLE_TYPE_3,		//�A�C�e����
	TITLE_TYPE_MAX,
} ITEM_TYPE;
typedef struct
{
	LPDIRECT3DTEXTURE9	pTextureModel[100];//�|���S���̃e�N�X�`��
	LPD3DXBUFFER		pBuffMat;			//�}�e���A�����ւ̃|�C���^
	DWORD				nNumMat;			//�}�e���A�����̐�
	LPD3DXMESH			pMesh;				//���b�V�����ւ̃|�C���^
	D3DXMATRIX			mtxWorld;			//�s��v�Z�p
}MODEL_ITEM;
typedef struct
{
	D3DXVECTOR3			pos;				//�ʒu���
	D3DXVECTOR3			movePos;			//�ړ���
	D3DXVECTOR3			dir;				//��]���
	D3DXMATRIX			mtxWorld;			//�s��v�Z
	double				vx = 0.0, vy;		//�����x
	int					nType;				//�A�C�e���̎��

	bool				buse;				//�g�p����
	//float				fDist;				//�n�ʂ̋���
	//BOOL				Hit;				//�n�ʂɓ���������
	MODEL_ITEM			ItemParts[TITLE_TYPE_MAX];
}ITEM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 dir , int nType);
void DrawItem(void);
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
ITEM*GetItem();

#endif
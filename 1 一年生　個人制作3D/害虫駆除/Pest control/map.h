#ifndef  MAP_H_
#define  MAP_H_

#include"main.h"

/*�\����*/
/*�p�[�c���Ƃ̏��*/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture[256];//�|���S���̃e�N�X�`��
	LPD3DXMESH Mesh;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER BuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD NumMat;			//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;	//�s��v�Z�p
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�u���b�N�̓����蔻��
	D3DXVECTOR3 rot;		//����
	BOOL Hit;				//�����蔻��
	float fDist;

}MAP;
/*�v���g�^�C�v�錾*/
void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);
MAP*GetMap();

#endif
#ifndef  CAMERA_H_
#define  CAMERA_H_

#include"main.h"
typedef struct
{
	D3DXVECTOR3 posV;//�J�����̍��W
	D3DXVECTOR3 posR;//�����_
	D3DXVECTOR3 vecU;//������x�N�g��
	D3DXMATRIX mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X
	
	D3DXVECTOR3 rotDest;//�J�����̖ړI����
	D3DXVECTOR3 rot;//�����擾
	float fDistance;//���_-�����_�̋���
	float fmove;		//�J�����̈ړ���

	D3DXVECTOR3 posVDest;//�J�����̍��W�i�ڕW�l�j
	D3DXVECTOR3 posRDest;//�����_�i�ڕW�l�j
}CAMERA;
/*�v���g�^�C�v�錾*/
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
#endif
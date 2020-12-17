#pragma once
//�C���N���[�h�t�@�C��
#ifndef  _POLYGON_H_
#define  _POLYGON_H_

#include<Windows.h>
#define DIRECTINPUT_VERSION (0x0800) 
#include<dinput.h>
#include"XAudio2.h"		//�T�E���h����
#include"d3dx9.h"
//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v

//�}�N����`
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)


#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//���W�E�@���E�J���[�E�e�N�X�`��
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define NUM_VERTEX (4)//���_��
#define NUM_POLYGON (2)//�|���S����




//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);

/*���[�h�̎��*/
typedef enum
{
	MODE_TITLE = 0,		//�^�C�g�����
	MODE_TUTORIAL,		//�`���[�g���A�����
	MODE_GAME,			//�Q�[�����
	MODE_GAMEOVER,		//�Q�[���I�[�o�[���
	MODE_RESULE,		//���U���g���
	MODE_MAX,
}MODE;
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 nor;//�@���x�N�g��
	D3DCOLOR	col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_3D;
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��v�W���i�P�D�O���ŌŒ�j
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);


#endif



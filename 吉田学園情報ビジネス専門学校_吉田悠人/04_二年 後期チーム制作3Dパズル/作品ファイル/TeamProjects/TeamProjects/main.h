//=============================================================================
//
// ���C������ [main.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
//#undef _DEBUG
//=============================================================================
//DirectInput�̃o�[�W�����ݒ�
//=============================================================================
#define DIRECTINPUT_VERSION (0x0800)
#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include <dinput.h>
#include <time.h>
#include <windows.h>
#include "d3dx9.h"

//=============================================================================
//���C�u�����̃����N
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")    //�V�X�e�������擾
#pragma comment(lib, "dinput8.lib")

//=============================================================================
//�}�N����`
//=============================================================================

#define SCREEN_WIDTH (1280)															//��ʂ̉𑜓x�iX����)
#define SCREEN_HEIGHT (720)															//��ʂ̉𑜓x�iY�����j
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				//2D�p
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3D�p
#define NUM_POLYGON (2)
#define NUM_VERTEX	(4)
#define CLASS_NAME	"AppClass"   // �E�C���h�E�̃N���X��
//#define PRIORITY_MAX (4)         // �`��D��x�̍ő�l

//=============================================================================
//�\���̒�`
//=============================================================================

//���C���p
typedef struct
{
    D3DXVECTOR3 pos;
    D3DCOLOR col;    //���_�J���[

} VERTEX_POINT;

//2D�p
typedef struct
{
    D3DXVECTOR3 pos;
    float rhw;          //���W�ϊ��p�W��(1.0f�Œ�)
    D3DCOLOR col;       //���_�J���[
    D3DXVECTOR2 tex;    //�e�N�X�`�����W
} VERTEX_2D;

//3D�p
typedef struct
{
    D3DXVECTOR3 pos;
    D3DXVECTOR3 nor;
    D3DCOLOR col;
    D3DXVECTOR2 tex;
} VERTEX_3D;

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================


#endif

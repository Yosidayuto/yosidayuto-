//=============================================================================
//
// ���C������ [main.h]
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800) //�x���Ώ��p

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <WinSock2.h>
#include <windows.h>
#include "d3dx9.h"
#include <stdio.h>

#include "xaudio2.h"
#include <thread>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	WINDOW_POS_X	(0)						// �E�B���h�E�����l(��)
#define	WINDOW_POS_Y	(0)						// �E�B���h�E�����l(�c)
#define SCREEN_WIDTH	(1280)					// �E�C���h�E�T�C�Y(��)
#define SCREEN_HEIGHT	(720)					// �E�C���h�E�T�C�Y(�c)
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)		// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)		// �E�C���h�E�̒��S�x���W
#define TEXTURE_WIDTH	(50)					// �e�N�X�`���T�C�Y(�c)
#define TEXTURE_HEIGHT	(50)					// �e�N�X�`���T�C�Y(��)
#define NUM_VERTEX      (4)						// ���_��
#define NUM_POLYGON		(2)						// �|���S����
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//���_�t�H�[�}�b�g(���_���W[2D]/���_�J���[/�e�N�X�`�����W)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int FPS(void);

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;


#endif







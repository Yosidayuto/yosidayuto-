#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNNGS

//�C���N���[�h�t�@�C��
#include"main.h"
//�C���v�b�g�N���X
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void)=0;
protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;	//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput;	//Directlnput�I�u�W�F�N�g�̃|�C���^
};


#endif
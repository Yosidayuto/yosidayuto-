//=============================================================================
//
// �C���v�b�g���� [input.cpp]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CInput
{
public:
	CInput();				//�R���X�g���N�^
	virtual ~CInput();		//�f�X�g���N�^	

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	virtual void	Uninit(void);							// �I������
	virtual void	Update(void)=0;							// �X�V����
protected:
	LPDIRECTINPUTDEVICE8	m_pDevice;	//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
	static LPDIRECTINPUT8	m_pInput;	//Directlnput�I�u�W�F�N�g�̃|�C���^
};


#endif
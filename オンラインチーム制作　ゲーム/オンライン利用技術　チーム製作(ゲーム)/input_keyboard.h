//=============================================================================
//
// �L�[�{�[�h���� [inputkeyboard.h]
// Author : �U�J �����Y
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX (256)	//�L�[�̐�

//*****************************************************************************
// �L�[�{�[�h�N���X
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// �R���X�g���N�^
	~CInputKeyboard();								// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	bool GetKeyPress(int nKey);						// �v���X��Ԃ��擾
	bool GetKeyTrigger(int nKey);					// �g���K�[��Ԃ��擾
	bool GetKeyRelease(int nKey);					// �����[�X��Ԃ��擾

private:
	BYTE m_akeyState[NUM_KEY_MAX];					// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_akeyStateTrigger[NUM_KEY_MAX];			// �L�[�{�[�h�̃g���K�[���[�N
	BYTE m_akeyStateRelease[NUM_KEY_MAX];			// �L�[�{�[�h�̃g���K�[���[�N


};



#endif // !_INPUT_KEYBOARD_H_






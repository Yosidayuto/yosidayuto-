//=============================================================================
//
// �L�[�{�[�h���͏��� [inputkeyboard.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "input.h"
#include "main.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_KEY_MAX (256)    //�L�[�{�[�h�̍ő吔

//=============================================================================
// �N���X��`
//=============================================================================
class CInputKeyboard : public CInput
{
public:
    CInputKeyboard();	// �R���X�g���N�^
	~CInputKeyboard();	// �f�X�g���N�^
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
    void	Uninit(void);							// �I���I������
    void	Update(void);							// �X�V����

    bool GetKeyPress(int nkey);						// �L�[���͏󋵎擾
    bool GetKeyTrigger(int nkey);					// �g���K�[�L�[���͏󋵎擾
    bool GetKeyRelease(int nkey);					// �����[�X�L�[���͏󋵎擾

private:
    BYTE m_aState[NUM_KEY_MAX];			// �L�[���͕ۑ�
    BYTE m_aStateTrigger[NUM_KEY_MAX];	// �g���K�[�L�[���͕ۑ�
    BYTE m_aStateRelease[NUM_KEY_MAX];	// �����[�X�L�[���͕ۑ�

};

#endif

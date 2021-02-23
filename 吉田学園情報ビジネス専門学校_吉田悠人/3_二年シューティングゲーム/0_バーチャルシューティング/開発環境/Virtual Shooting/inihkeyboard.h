//=============================================================================
//
// �L�[�{�[�h���� [inihkeyboard.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"input.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_KEY_MAX (256)						//�L�[�̍ő吔

//=============================================================================
// �N���X��`
//=============================================================================
class CInihKeyboard :public CInput
{
public:
	CInihKeyboard();
	~CInihKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Uninit(void);
	void	Update(void);

	bool GetKeyPress(int nKey);			//�v�b�V���Q�b�^�[
	bool GetKeyPressTrigger(int nKey);	//�v�b�V���g���K�[�Q�b�^�[
	bool GetKeyPressRelease(int nKey);	//�v�b�V�������[�X�Q�b�^�[
private:
	BYTE m_akeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aKesStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���
};

#endif
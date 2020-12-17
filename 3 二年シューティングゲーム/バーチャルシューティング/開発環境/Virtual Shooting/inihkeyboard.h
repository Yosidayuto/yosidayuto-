#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#define NUM_KEY_MAX (256)						//�L�[�̍ő吔
//---------------------------------------------------
//�C���N���[�h�t�@�C��
//---------------------------------------------------
#include"main.h"
#include"input.h"
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CInihKeyboard :public CInput
{
public:
	CInihKeyboard();
	~CInihKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetKeyPress(int nKey);
	bool GetKeyPressTrigger(int nKey);
	bool GetKeyPressRelease(int nKey);
private:
	BYTE m_akeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aKesStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���
};

#endif
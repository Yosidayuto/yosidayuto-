#ifndef _INPUT_MOUSE_H_
#define _INPUT_MOUSE_H_

#define NUM_CLICK_MAX (3)						//�L�[�̍ő吔

//=============================================================================
//�t���O
//=============================================================================
#define MOUSE_POS_TYPE
#undef MOUSE_POS_TYPE

//=============================================================================
// �w�b�_�t�@�C��
//=============================================================================
#include"main.h"
#include "input.h"

//=============================================================================
// �N���X
//=============================================================================
class CInhMouse : public CInput
{
public:
	CInhMouse();
	~CInhMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE GetMousePos(void);
#else 
	POINT		GetMousePos(void);
#endif


	bool GetClick(int nClick);
	bool GetClickTrigger(int nClick);
	bool GetClickRelease(int nClick);
private:
	DIMOUSESTATE m_aClickState;			//�}�E�X�̓��͏�񃏁[�N
	DIMOUSESTATE m_aClickTrigger;		//�}�E�X�̃g���K�[���
	DIMOUSESTATE m_aClickRelease;		//�}�E�X�̃����[�X���
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE m_aMousePos;			//�}�E�X�̈ړ���
#else 
	POINT posMouse;						//�}�E�X�̍��W
	HWND hPointerpos;					//�E�B���h�E�̃}�E�X�|�C���^�[�̍��W
#endif



};



#endif
//=============================================================================
//
//	�}�E�X����[input mouse.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

#define NUM_CLICK_MAX (3)						//�L�[�̍ő吔

//=============================================================================
//�t���O
//=============================================================================
#define MOUSE_POS_TYPE
#undef MOUSE_POS_TYPE

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include "input.h"
//=============================================================================
//�O���錾
//=============================================================================
typedef enum	//�N���b�N���
{
	CLICK_LEFT = 0,	//���N���b�N
	CLICK_RIGHT,	//�E�N���b�N
	CLICK_WHEEL,	//�}�E�X�z�C�[��
	CLICK_MAX
}CLICK_TYPE;

//=============================================================================
// �N���X��`
//=============================================================================
class CInihMouse :public CInput
{
public:
	CInihMouse();
	~CInihMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Uninit(void);
	void	Update(void);
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE GetMousePos(void);
#else 
	POINT	GetMousePos(void);
#endif

	bool	GetClick(int nClick);			// �N���b�N����
	bool	GetClickTrigger(int nClick);	// �N���b�N�g���K�[����
	bool	GetClickRelease(int nClick);	// �N���b�N�����[�X����
private:
	DIMOUSESTATE m_aClickState;		//�}�E�X�̓��͏�񃏁[�N
	DIMOUSESTATE m_aClickTrigger;	//�}�E�X�̃g���K�[���
	DIMOUSESTATE m_aClickRelease;	//�}�E�X�̃����[�X���
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE m_aMousePos;		//�}�E�X�̈ړ���
#else 
	POINT	posMouse;				//�}�E�X�̍��W
	HWND	hPointerpos;			//�E�B���h�E�̃}�E�X�|�C���^�[�̍��W
#endif



};



#endif
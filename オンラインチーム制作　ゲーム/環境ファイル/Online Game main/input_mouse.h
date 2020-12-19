//=============================================================================
//
// �}�E�X���� [input_mouse.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _INPUT_MOUSE_H_
#define _INPUT_MOUSE_H_

#define NUM_CLICK_MAX (3)						//�L�[�̍ő吔

//=============================================================================
//�t���O
//=============================================================================
//�}�E�X�̃|�C���^�[�擾�̕ύX
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
	CInhMouse();									// �R���X�g���N�^
	~CInhMouse();									// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE GetMousePos(void);					// �}�E�X�|�C���^�[�̈ړ���
#else 
	POINT		GetMousePos(void);					// �}�E�X�|�C���^�[�̈ʒu
#endif
	bool GetClick(int nClick);						// �v���X��Ԃ��擾
	bool GetClickTrigger(int nClick);				// �g���K�[��Ԃ��擾
	bool GetClickRelease(int nClick);				// �����[�X��Ԃ��擾
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
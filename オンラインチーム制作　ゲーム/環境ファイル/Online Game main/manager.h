//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �U�J �����Y�@�g�c�I�l
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "renderer.h"
#include "input_keyboard.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CInputKeyboard;
class CPolygon;
class CInhMouse;
class CTitle;
class CWait;
class CGame;
class CResult;
class CFade;
class CCommunication;
class CSound;
class CLoad;
//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CManager
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_LOAD,
		MODE_GAME,
		MODE_RESULT,
		MODE_END
	}MODE;
	CManager();													// �R���X�g���N�^
	~CManager();												// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	static CRenderer *GetRenderer(void);						// �����_�����O�̎擾
	static CInputKeyboard *Getkeyboard(void);					// �L�[�{�[�h�̎擾
	static CInhMouse *GetMouse(void);							// �}�E�X�̎擾
	static CPolygon *GetPolygon(void);							// �|���S���i���o�[�̎擾
	static void SetMode(MODE mode);								// ���[�h�ؑ�
	static MODE GetMode(void);									// ���[�h�̎擾
	static CFade *GetFade(void);								// �t�F�[�h�̎擾
	static CCommunication*GetCommunication(void);				// �ʐM�̎擾		
	static CSound *GetSound(void);								// �T�E���h�̎擾

private:

	static CRenderer *m_pRenderer;								// �����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;					// �L�[�{�[�h�̃|�C���^
	static CPolygon *m_pPolygon;								// �|���S���i���o�[�̃|�C���^
	static CInhMouse *m_pInputMouse;							// �}�E�X�̃|�C���^
	static CTitle *m_pTitle;									// �^�C�g���̃|�C���^
	static CLoad *m_pLoad;										// ���[�h�̃|�C���^
	static CGame *m_pGame;										// �Q�[���̃|�C���^
	static CResult *m_pResult;									// ���U���g�̃|�C���^
	static MODE m_mode;											// ���[�h�̕ϐ�
	static CFade *m_pFade;										// �t�F�[�h�̃|�C���^
	static CCommunication *pCommunication;						// �ʐM�̃|�C���^
	static CSound *m_pSound;									// �T�E���h�̃|�C���^
};




#endif









//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CFade;
class CInput;
class CSound;
class CCamera;
class CTitle;
class CGame;
class CPause;
class CResource;
//=============================================================================
//�N���X��`
//=============================================================================
class CManager
{
public:

	typedef enum //���[�h�^�C�v
	{
		MODE_TITLE = 0,		// �^�C�g��
		MODE_GAME,			// �Q�[��
		MODE_MAX
	} MODE;

	CManager();     //�R���X�g���N�^
	~CManager();    //�f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);	// �������֐�
	void	Uninit(void);										// �I���֐�
	void	Update(void);										// �X�V�֐�
	void	Draw(void);											// �`��֐�
	
	static CRenderer*	GetRenderer(void);			// �����_���Q�b�^�[
	static CResource*	GetResource(void);			// ���\�[�X�Q�b�^�[
	static CInput*		GetInputKey(void);			// �L�[�{�[�h�擾
	static CInput*		GetInputMou(void);			// �}�E�X�擾
	static CInput*		GetInputController(void);	// �R���g���[���[�擾
	static CCamera*		GetCamera(void);			// �J�����擾
	static CFade*		GetFadeout(void) { return m_pFade; }// �t�F�[�h�̎擾
	static CSound*		GetSound(void);						//�T�E���h�̎擾
	static CPause*		GetPause(void) { return m_pPause; }	// �|�[�Y�̎擾
	static void SetMode(MODE mode);					// ���[�h�ؑ�
	static MODE GetMode(void);						// ���[�h�擾

	static void BindCamera(CCamera* pCamera);		// �J�����ݒ�
	
	void		PauseStart(void);					// �|�[�Y�X�^�[�g

private:

    static CRenderer*	m_pRenderer;		// �����_���̃|�C���^
    static MODE			m_mode;				// ���[�h�̕ϐ�
	static CInput*		m_pInputKey;		// �L�[�{�[�h�̃|�C���^
	static CInput*		m_pInputMou;		// �}�E�X�̃|�C���^
	static CInput*		m_pInputController;	// �R���g���[���[�̃|�C���^
	static CCamera*		m_pCamera;			// �J�����̃|�C���^
	static CFade*		m_pFade;			// �t�F�[�h�|�C���^
	static CSound*		m_pSound;			// �T�E���h�̃|�C���^
	static CTitle*		m_pTitle;			// �^�C�g���̃|�C���^
	static CGame*		m_pGame;			// �Q�[���̃|�C���^
	static CPause*		m_pPause;			// �|�[�Y�|�C���^
	static CResource*	m_Resource;			// ���\�[�X�}�l�[�W���[�|�C���^
	
};

#endif

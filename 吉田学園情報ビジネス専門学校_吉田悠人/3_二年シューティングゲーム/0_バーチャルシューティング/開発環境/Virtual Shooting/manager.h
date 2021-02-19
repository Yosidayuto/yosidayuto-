//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"
#include "game.h"

//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CInihKeyboard;
class CInihMouse;
class CSound;
class CPause;
class CScore;
class CScene;
class CFade;
class CGame;
class CSelect;
class CPlayerData;
class CTitle;
class CTutorial;
typedef enum	//�Q�[�����[�h
{
	GAME_MODE_NONE = 0,
	GAME_MODE_TITLE,		//�^�C�g��
	GAME_MODE_TUTORIAL,		//�`���[�g���A��
	GAME_MODE_SELECT,		//�Z���N�g
	GAME_MODE_STAGE,		//�X�e�[�W
	GAME_MODE_CLEAR,		//�N���A
	GAME_MODE_MAX,
}GAME_MODE;

//=============================================================================
// �N���X��`
//=============================================================================
class CManager
{
public:
	CManager();		//�R���X�g���N�^
	~CManager();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);	// ����������
	void	Uninit(void);										// �I������
	void	Update(void);										// �X�V����
	void	Draw(void);											// �`�揈��
																   
	static void SetMode(GAME_MODE mode);						// �Q�[�����[�h�Z�b�g
	static void	SetScore(int nScore) { m_nScore = nScore; };	// �X�R�A�Z�b�^�[
	static void SetPlayer(CPlayerData* Player);						// �v���C���[�Z�b�^�[

	static int				GetScore(void);		//�X�R�A�擾
	static CPlayerData*		GetPlayer(void);	//�v���C���[�擾

	static CRenderer		*GetRenderer(void);	// �����_�����O�擾
	static CInihKeyboard	*GetKeyboard(void);	// �L�[�{�[�h�擾
	static CInihMouse		*GetMouse(void);	// �}�E�X�擾
	static CSound			*GetSound(void);	// �T�E���h�擾
	static CFade			*GetFade(void);		// �t�F�[�h�A�E�g�擾
private:
	void LoadFile(void);						// �t�@�C�����[�h�֐�
	void UnLoadFile(void);						// �t�@�C���A�����[�h�֐�

	static CRenderer		*m_pRenderer;	// �����_�����O�N���X
	static CInihKeyboard	*m_pInput;		// �C���v�b�g�i�L�[�{�[�h�j�N���X
	static CInihMouse		*m_pInihMouse;	// �C���v�b�g�i�}�E�X�j�N���X
	static CSound			*m_pSound;		// �T�E���h�N���X
	static CScene			*m_pScene;		// �V�[���N���X
	static CFade			*m_pFade;		// �t�F�C�h�A�E�g�N���X

	static CPlayerData*		m_pPlayerData;	// �v���C���[�N���X�N���X
	static int				m_nScore;		// �X�R�A�ۑ���
	static CGame*			m_pGame;		// �Q�[���|�C���^

	static CSelect*			m_pSelect;		// �Z���N�g����
	static GAME_MODE		m_Mode;			// �Q�[�����[�h
	static CTitle*			m_pTitle;		// �^�C�g���|�C���^
	static CTutorial*		m_pTutorial;	// �`���[�g���A���|�C���^
};



#endif
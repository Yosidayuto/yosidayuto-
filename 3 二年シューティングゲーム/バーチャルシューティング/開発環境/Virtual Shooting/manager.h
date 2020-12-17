#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "player.h"
#include "scene.h"

//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define GAME_WIDTH 780

//------------------------------------
//�O�u����
//------------------------------------
class CRenderer;
class CInihKeyboard;
class CInihMouse;
class CSound;
class CPause;
class CTitle;
class CScore;
class CScene;
class CFade;
class CGame;
class CSelect;
class CPlayer;
class CTutorial;
//------------------------------------
//�N���X����
//------------------------------------
class CManager
{
public:
	CManager();		//�R���X�g���N�^
	~CManager();	//�f�X�g���N�^

	typedef enum	//�Q�[�����[�h
	{
		GAME_MODE_NONE = 0,
		GAME_MODE_FADE,			//�t�F�C�h
		GAME_MODE_TITLE,		//�^�C�g��
		GAME_MODE_TUTORIAL,		//�`���[�g���A��
		GAME_MODE_SELECT,		//�Z���N�g
		GAME_MODE_STAGE,		//�X�e�[�W
		GAME_MODE_CLEAR,		//�N���A
		GAME_MODE_MAX,
	}GAME_MODE;


	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);	//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void Draw(void);					//�`�揈��
	static void SetMode(GAME_MODE mode);		//�Q�[�����[�h�Z�b�g

	static CRenderer		*GetRenderer(void);		//�����_�����O�擾
	static CInihKeyboard	*GetKeyboard(void);		//�L�[�{�[�h�擾
	static CInihMouse		*GetMouse(void);		//�}�E�X�擾
	static CSound			*GetSound(void);		//�T�E���h�擾
	static CFade			*GetFade(void);			//�t�F�[�h�A�E�g�擾

	static int				GetScore(void);		//�X�R�A�擾
	static void				SetScore(int nScore) { m_nScore = nScore; };

	static int				GetPlayer(int nPlayerData);		//�v���C���[�擾
	static void				SetPlayer(int nLife,int nSpeed);
	static CPlayer::WEAPON_MODE GetWeapon(int nWeaponData) {return m_Player.m_nWeapon[nWeaponData];};
	static void				SetWeapon(CPlayer::WEAPON_MODE nWeaponData1, CPlayer::WEAPON_MODE nWeaponData2) ;
	//static int				GetStage(void) { return m_StageType; };
private:
	static CRenderer		*m_pRenderer;			//�����_�����O�N���X
	static CInihKeyboard	*m_pInput;				//�C���v�b�g�i�L�[�{�[�h�j�N���X
	static CInihMouse		*m_pInihMouse;			//�C���v�b�g�i�}�E�X�j�N���X
	static CSound			*m_pSound;				//�T�E���h�N���X
	static CScene			*m_pScene;				//�V�[���N���X
	static CTitle			*m_pTitle;				//�^�C�g���N���X
	static CFade			*m_pFade;				//�t�F�C�h�A�E�g�N���X
	static CTutorial		*m_pTutorial;			//�^�C�g���N���X

	typedef struct
	{
		int				m_nLife;
		int				m_nSpeed;
		CPlayer::WEAPON_MODE m_nWeapon[MAX_WEAPON];
	}PLAYER_DATA;
	 
	static PLAYER_DATA		m_Player;				//�v���C���[�f�[�^
	static int				m_nScore;				//�X�R�A�ۑ���
	static CGame			*m_pGame;				//�Q�[������
	static CSelect			*m_pSelect;				//�Z���N�g����
	static GAME_MODE		m_Mode;					//�Q�[�����[�h
	
};



#endif
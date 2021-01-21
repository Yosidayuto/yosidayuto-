//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"		
#include "renderer.h"		
#include "scene2d.h"		
#include "scene.h"			
#include "input.h"			
#include "inihkeyboard.h"	
#include "inputmouse.h"		
#include "sound.h"			
#include "score.h"			
#include "number.h"			
#include "fade.h"			
#include "ui.h"				
#include "game.h"			
#include "select.h"			
#include "text.h"			
#include "window.h"			
#include "player.h"			
#include "button.h"			
#include "clear.h"			
#include "telop_bar.h"		
#include "mouse pointer.h"	
#include "telop_text.h"		
#include "title bg.h"
#include "title.h"
#include "tutorial bg.h"
#include "tutorial.h"
#include "select bg.h"
#include "weapon_UI.h"
#include "start button.h"
#include "button p.h"
#include "life button.h"
#include "life ui.h"
//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CRenderer *CManager::m_pRenderer	= NULL;
CInihKeyboard *CManager::m_pInput	= NULL;
CInihMouse *CManager::m_pInihMouse	= NULL;
CSound *CManager::m_pSound			= NULL;
GAME_MODE CManager::m_Mode			= GAME_MODE_TITLE;
CScene *CManager::m_pScene			= NULL;
CFade *CManager::m_pFade			= NULL;
CGame *CManager::m_pGame			= NULL;
CSelect *CManager::m_pSelect		= NULL;
int CManager::m_nScore				= 10000;
CManager::PLAYER_DATA CManager::m_Player =
{ 0,0,{ WEAPONS_MODE_BUTTOL , WEAPONS_MODE_NONE } };
CTitle *CManager::m_pTitle			= NULL;
CTutorial *CManager::m_pTutorial	= NULL;
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
//�������֐�
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�C���v�b�g(�L�[�{�[�h)����
	m_pInput = new CInihKeyboard;
	m_pInput->Init(hInstance, hWnd);
	
	//�C���v�b�g(�}�E�X)����
	m_pInihMouse = new CInihMouse;
	m_pInihMouse->Init(hInstance, hWnd);
	
	//�����_�����O����
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�t�F�C�h�A�E�g����
	m_pFade = new CFade;
	m_pFade->Init();

	//�T�E���h����
	m_pSound = new CSound;
	m_pSound->Init(hWnd);
	//�^�C�g������
	m_pTitle	= new CTitle;
	//�`���[�g���A������
	m_pTutorial	= new CTutorial;
	//�Z���N�g����
	m_pSelect	= new CSelect;
	//�Q�[������
	m_pGame		= new CGame;
	//�t�@�C�����[�h
	LoadFile();

	//�I�u�W�F�N�g�N���X����
	m_pFade->SetFade(m_Mode);
	return S_OK;
}

//=============================================================================
//�I���֐�
//=============================================================================
void CManager::Uninit(void)
{
	//�V�[���̏I��
	CScene::ReleaseAll();

	//�L�[�{�[�h�j��
	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;

	}
	//�}�E�X�j��
	if (m_pInihMouse != NULL)
	{
		m_pInihMouse->Uninit();
		delete m_pInihMouse;
		m_pInihMouse = NULL;

	}
	//�T�E���h�j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//�t�F�[�h�A�E�g�j��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	//�����_�����O�N���X�̔j��
	if (m_pRenderer != NULL)	//���������m�ۂ���Ă��邩
	{
		//�����_�����O �I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�t�@�C���A�����[�h����
	UnLoadFile();
}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CManager::Update()
{
	// �L�[�{�[�h�X�V (�ŏ��ɍs��)
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}

	// �}�E�X�X�V
	if (m_pInihMouse != NULL)
	{
		m_pInihMouse->Update();		
	}

	// �����_�����O�X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();		
	}

	// �t�F�[�h�A�E�g�X�V����
	if (m_pFade != NULL)
	{
		m_pFade->Update();			
	}

	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTitle != NULL)
		{
			m_pTutorial->Update();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Update();
		}
		break;
	case GAME_MODE_STAGE:
		if (m_pSelect != NULL)
		{
			m_pGame->Update();
		}
		break;
	}

}

//=============================================================================
//�`�揈��
//=============================================================================
void CManager::Draw(void)
{

	//�����_���̕`��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
//�Q�[�����[�h�Z�b�g����
//=============================================================================
void CManager::SetMode(GAME_MODE mode)
{
	//�I������
	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			//�^�C�g���V�[���j��
			m_pTitle->Uninit();
		}

		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			//�Z���N�g�V�[���j��
			m_pSelect->Uninit();
		}

		break;
	case GAME_MODE_STAGE:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
		}
		//�V�[���j��
		CScene::ReleaseAll();
		//�T�E���h��~
		m_pSound->Stop();
		break;
	case GAME_MODE_CLEAR:
		m_Player = { 0,0,{ WEAPONS_MODE_BUTTOL , WEAPONS_MODE_NONE } };
		m_nScore = 10000;
		//�V�[���j��
		CScene::ReleaseAll();
		//�T�E���h��~
		m_pSound->Stop();
		break;
	}

	m_Mode = mode;

	//����������
	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			//�^�C�g������������
			m_pTitle->Init();
		}
		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			//�`���[�g���A������������
			m_pTutorial->Init();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			//�Z���N�g����������
			m_pSelect->Init();
		}
		break;
	case GAME_MODE_STAGE:
		if (m_pGame != NULL)
		{
			//�Q�[����������
			m_pGame->Init();
		}
		break;
	case GAME_MODE_CLEAR:
		//�Q�[���N���A
		CClear::Create();
		//�T�E���h�Đ�
		m_pSound->Play(CSound::LABEL_SE_RESULT);
		break;
	}
}

CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInihKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

CInihMouse * CManager::GetMouse(void)
{
	return m_pInihMouse;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

CFade * CManager::GetFade(void)
{
	return m_pFade;
}

int  CManager::GetScore(void)
{
	return m_nScore;
}

int CManager::GetPlayer(int nPlayerData)
{
	if (nPlayerData == 0)
	{
		return m_Player.m_nLife;
	}
	else
	{
		return m_Player.m_nSpeed;
	}
}

//=============================================================================
// �t�@�C�����[�h�֐�
//=============================================================================
void CManager::LoadFile(void)
{
	//�e�N�X�`���̓ǂݍ���
	CClear::Load();			
	CNumber::Load();		
	CUi::Load();			
	CText::Load();			
	CWindow::Load();		
	CButton::Load();		
	CTelopBer::Load();		
	CTelopText::Load();		
	CPointer::Load();		
	CTitleBg::Load();
	CTutorialBg::Load();
	CSelectBg::Load();		
	CWeapon_Ui::Load();
	CStartButton::Load();
	CButtonp::Load();
	CLifeButton::Load();
	CLifeUi::Load();
}

//=============================================================================
// �t�@�C���A�����[�h�֐�
//=============================================================================
void CManager::UnLoadFile(void)
{
	//�e�N�X�`���̔j��
	CClear::Unload();			
	CButton::Unload();			
	CNumber::Unload();			
	CUi::Unload();				
	CText::Unload();			
	CWindow::Unload();			
	CTelopBer::Unload();		
	CTelopText::Unload();		
	CPointer::Unload();			
	CTitleBg::Unload();
	CTutorialBg::Unload();
	CSelectBg::Unload();
	CWeapon_Ui::Unload();
	CStartButton::Unload();
	CButtonp::Unload();
	CLifeButton::Unload();
	CLifeUi::Unload();

}

void CManager::SetPlayer(int nLife, int nSpeed)
{
	m_Player.m_nLife = nLife;
	m_Player.m_nSpeed = nSpeed;
}

void CManager::SetWeapon(WEAPON_MODE nWeaponData1, WEAPON_MODE nWeaponData2)
{
	m_Player.m_nWeapon[0] = nWeaponData1;
	m_Player.m_nWeapon[1] = nWeaponData2;
}





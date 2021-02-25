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
#include "load.h"
#include "fade.h"			
#include "game.h"			
#include "select.h"			
#include "clear.h"			
#include "telop.h"		
#include "mouse pointer.h"	
#include "title bg.h"
#include "title.h"
#include "tutorial bg.h"
#include "tutorial.h"
#include "select bg.h"
#include "life ui.h"
#include "life tank.h"
#include "weapon manager.h"
#include "button manager.h"
#include "player data.h"
#include "result bg.h"
#include "stage.h"
#include "stage_1.h"
#include "stage_2.h"
#include "stage_3.h"
#include "score bar.h"
#include "boss base.h"
#include "boss effect base.h"
#include <thread>

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CRenderer *CManager::m_pRenderer	 = NULL;
CInihKeyboard *CManager::m_pInput	 = NULL;
CInihMouse *CManager::m_pInihMouse	 = NULL;
CSound *CManager::m_pSound			 = NULL;
GAME_MODE CManager::m_Mode			 = GAME_MODE_LOAD;
CScene *CManager::m_pScene			 = NULL;
CFade *CManager::m_pFade			 = NULL;
int CManager::m_nScore				 = 10000;
CPlayerData *CManager::m_pPlayerData = NULL;
CGame* CManager::m_pGame			 = NULL;
CTitle* CManager::m_pTitle			 = NULL;
CSelect* CManager::m_pSelect		 = NULL;
CTutorial* CManager::m_pTutorial	 = NULL;
CLoad* CManager::m_pLoad			 = NULL;
bool CManager::m_bLoad				 = false;
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
	m_pGame = new CGame;
	//���[�h���
	m_pLoad = new CLoad;
	//���[�h��ʃ��[�h
	CLoad::Load();
	LoadFile();
	////�t�@�C�����[�h(�}���`�X���b�h)
	//std::thread thLoad(LoadFile);
	////�}���`�X���b�h�����邩
	//if (thLoad.joinable())
	//{
	//	//�}���`�X���b�h�������
	//	thLoad.detach();
	//}
	////�I�u�W�F�N�g�N���X����
	//m_pFade->SetFade(m_Mode);

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
	//�^�C�g���j��
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;
	}
	//�`���[�g���A���j��
	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;
	}
	//�Z���N�g�j��
	if (m_pSelect != NULL)
	{
		m_pSelect->Uninit();
		delete m_pSelect;
		m_pSelect = NULL;
	}
	//�Q�[���j��
	if (m_pGame != NULL)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
	}
	//���[�h�j��
	if (m_pLoad != NULL)
	{
		m_pLoad->Uninit();
		delete m_pLoad;
		m_pLoad = NULL;
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

	//��ʂ��Ƃ̃A�b�v�f�[�g
	switch (m_Mode)
	{
	case GAME_MODE_LOAD:
		//���[�h���I����Ă��邩
		if (m_bLoad == false)
		{
			if (m_pLoad != NULL)
			{
				m_pLoad->Update();
			}
		}
		else
		{
			//m_Load��true�̎�
			m_pFade->SetFade(GAME_MODE_TITLE);
		}
		break;
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
		if (m_pGame != NULL)
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
	//std::lock_guard<std::mutex> lock(m_mtx_);
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
	case GAME_MODE_LOAD:
		if (m_pLoad != NULL)
		{
			//���[�h�j��
			m_pLoad->Uninit();
		}
		break;
	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			//�^�C�g���V�[���j��
			m_pTitle->Uninit();
			//�v���C���[����
			m_pPlayerData = CPlayerData::Create();
		}

		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			//�`���[�g���A���V�[���̔j��
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
		break;
	case GAME_MODE_CLEAR:
		m_nScore = 10000;
		break;
	}

	//�T�E���h��~
	m_pSound->Stop();
	//���[�h�ύX����
	m_Mode = mode;

	//����������
	switch (m_Mode)
	{
	case GAME_MODE_LOAD:
		if (m_pLoad != NULL)
		{
			//���[�h��ʏ�����
			m_pLoad->Init();
		}
		break;
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
			m_pSelect->SetStage(m_pGame->GetStageType());
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
		//�v���C���[�̃f�[�^�j��
		m_pPlayerData->Uninit();
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

//=============================================================================
// �v���C���[�擾
//=============================================================================
CPlayerData* CManager::GetPlayer(void)
{
	return m_pPlayerData;
}

//=============================================================================
// �t�@�C�����[�h�֐�
//=============================================================================
void CManager::LoadFile(void)
{
	//�e�N�X�`���̓ǂݍ���
	CClear::Load();			
	CNumber::Load();		
	CTelop::Load();		
	CPointer::Load();		
	CTitleBg::Load();
	CTutorialBg::Load();
	CSelectBg::Load();		
	CLifeUi::Load();
	CWeaponManager::Load();
	CButtonManager::Load();
	CGame::Load();
	CResultBg::Load();
	CScoreBar::Load();
	CBossBase::Load();
	CBossEffectBase::Load();
	CLifeTank::Load();
	//�e�L�X�g�ǂݍ���
	CStage::LoadFile();
	m_bLoad = true;

}

//=============================================================================
// �t�@�C���A�����[�h�֐�
//=============================================================================
void CManager::UnLoadFile(void)
{
	//�e�N�X�`���̔j��
	CClear::Unload();			
	CNumber::Unload();			
	CTelop::Unload();		
	CPointer::Unload();			
	CTitleBg::Unload();
	CTutorialBg::Unload();
	CSelectBg::Unload();
	CLifeUi::Unload();
	CWeaponManager::Unload();
	CButtonManager::Unload();
	CGame::Unload();
	CResultBg::Unload();
	CScoreBar::Unload();
	CBossBase::Unload();
	CBossEffectBase::Unload();
	CLifeTank::Unload();
	CLoad::Unload();

}

//=============================================================================
// �v���C���[�f�[�^�Z�b�^�[�֐�
//=============================================================================
void CManager::SetPlayer(CPlayerData* Player)
{
	m_pPlayerData = Player;
}





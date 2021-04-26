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
#include "light.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "sound.h"
#include "fade.h"
#include "camera.h"
#include "title.h"
#include "game.h"
#include "inputmouse.h"
#include "pause.h"
#include "child.h"

#include "resource manager.h"
#include "player.h"
//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CRenderer*		CManager::m_pRenderer			= NULL;
CFade*			CManager::m_pFade				= NULL;
CManager::MODE	CManager::m_mode				= MODE_TITLE;
CSound*			CManager::m_pSound				= NULL;
CInput*			CManager::m_pInputKey			= NULL;
CInput*			CManager::m_pInputMou			= NULL;
CInput*			CManager::m_pInputController	= NULL;
CCamera*		CManager::m_pCamera				= NULL;
CTitle*			CManager::m_pTitle				= NULL;
CGame*			CManager::m_pGame				= NULL;
CPause*			CManager::m_pPause				= NULL;
CResource*		CManager::m_Resource			= NULL;
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
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	//�����_���𐶐�
    HRESULT hResult = NULL;
    m_pRenderer     = new CRenderer;

	//�����_����������
	if (m_pRenderer != NULL)
	{
		hResult = m_pRenderer->Init(hWnd, bWindow);
	}

	//���C�g�̐���
    CLight* pLight	= NULL;						
    pLight			= new CLight;	
	//���C�g�̏�����
	if (pLight != NULL)
	{
		pLight->Init();
	}

	//�L�[�{�[�h����
    m_pInputKey = new CInputKeyboard;		
	if (m_pInputKey != NULL)
	{
		m_pInputKey->Init(hInstance, hWnd);
	}

	//�}�E�X����
	m_pInputMou = new CInputMouse;
	if (m_pInputMou != NULL)
	{
		m_pInputMou->Init(hInstance, hWnd);
	}

	//�R���g���[���[����
	m_pInputController = new CInputJoyStick;
	if (m_pInputController != NULL)
	{
		if (m_pInputController->Init(hInstance, hWnd) == E_FAIL)
		{
			m_pInputController = NULL;
		}
	}

    //�T�E���h�̐���
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		//�T�E���h�̏�����
		m_pSound->Init(hWnd);
	}

	//�t�F�[�h����
	m_pFade = CFade::Create();
	
	//�|�[�Y����
	m_pPause = new CPause;

	//�t�@�C���ǂݍ���
	m_Resource = new CResource;
	//���\�[�X�ǂݍ���
	m_Resource->Init();

    //LoadFile();				
	
	//�������m��
	m_pTitle	= new CTitle;	//�^�C�g��
	m_pGame		= new CGame;	//�Q�[��
	
	m_pFade->SetBlackout(m_mode);
	return hResult;
}

//=============================================================================
//�I���֐�
//=============================================================================
void CManager::Uninit(void)
{
    //�V�[���̏I��
    CObject::ReleaseAll();

    //�t�F�[�h�I��
    if(m_pFade != NULL)
    {
		m_pFade->Uninit();
        delete m_pFade;
		m_pFade = NULL;
    }
	//�|�[�Y�I��
	if (m_pPause!=NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;

	}
    //�L�[�{�[�h���͂̏I��
	if (m_pInputKey != NULL)
	{
		m_pInputKey->Uninit();
		delete m_pInputKey;
		m_pInputKey = NULL;
	}
	
	//�}�E�X���͂̏I��
	if (m_pInputMou != NULL)
	{
		m_pInputMou->Uninit();
		delete m_pInputMou;
		m_pInputMou = NULL;
	}

	//�R���g���[���[���͂̏I��
	if (m_pInputController != NULL)
	{
		m_pInputController->Uninit();
		delete m_pInputController;
		m_pInputController = NULL;
	}
	//�J�����̏I��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

    //�����_���̏I��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//���\�[�X�̏I������
	if (m_Resource != NULL)
	{
		m_Resource->Uninit();
		delete m_Resource;
		m_Resource = NULL;
	}
    
	//�T�E���h�̔j��
    if(m_pSound != NULL)
    {
		//�T�E���h�̒�~
		m_pSound->StopSound();

        m_pSound->Uninit();
        delete m_pSound;
        m_pSound = NULL;
    }

}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CManager::Update(void)
{
    //�L�[�{�[�h���͂̍X�V
    if(m_pInputKey != NULL)
    {
        m_pInputKey->Update();
    }

	//�}�E�X���͂̍X�V
    if(m_pInputMou != NULL)
    {
        m_pInputMou->Update();
    }

	//�R���g���[�����͂̍X�V
	if (m_pInputController != NULL)
	{
		m_pInputController->Update();
	}

	//�����_���̍X�V
	if (m_pRenderer != NULL&&!m_pPause->GetPause())
	{
		m_pRenderer->Update();
	}

    //�t�F�[�h�X�V
    if(m_pFade != NULL)
    {
		m_pFade->Update();
    }

	//�|�[�Y��Ԃ�
	if (m_pPause->GetPause())		//�|�[�Y�Ȃ�
	{
		//�|�[�Y�X�V
		m_pPause->Update();
	}
	else						//�|�[�Y�łȂ��Ȃ�
	{
		//��ʂ��Ƃ̍X�V
		switch (m_mode)
		{
		case MODE_TITLE:	//�^�C�g��
			if (m_pTitle != NULL)
			{
				m_pTitle->Update();
			}
			break;
		case MODE_GAME:		//�Q�[��
			if (m_pGame != NULL)
			{
				m_pGame->Update();
				//�|�[�Y����
				PauseStart();
			}
			break;
		}

	}
}

//=============================================================================
//�`��֐�
//=============================================================================
void CManager::Draw(void)
{
	//���[�h����
    switch(m_mode)
    {
        case MODE_TITLE:	//�^�C�g��
			if (m_pTitle != NULL)
			{
				m_pTitle->Draw();
			}
			break;
		case MODE_GAME:		//�Q�[��
			if (m_pGame != NULL)
			{
				m_pGame->Draw();
			}
			break;
    }

    //�����_���̕`��
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Draw();
    }
}

//=============================================================================
//�Q�b�^�[�֐�
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

CResource * CManager::GetResource(void)
{
	return m_Resource;
}

CInput* CManager::GetInputKey(void)
{
    return m_pInputKey;
}

CInput* CManager::GetInputMou(void)
{
    return m_pInputMou;
}

CInput * CManager::GetInputController(void)
{
	return m_pInputController;
}

CCamera* CManager::GetCamera(void)
{
    return m_pCamera;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

void CManager::BindCamera(CCamera* pCamera)
{
	m_pCamera = pCamera;
	CChild::Load();
}

//=============================================================================
//���[�h�ؑ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	//�|�[�Y�I��
	m_pPause->Delete();
    //�I������
    switch(m_mode)
    {
        case MODE_TITLE:	//�^�C�g��	
			if (m_pTitle != NULL)
			{
				m_pTitle->Uninit();
			}
            break;
		case MODE_GAME:		//�Q�[��
			if (m_pGame != NULL)
			{
				m_pGame->Uninit();
			}
			break;
    }

	//���[�h�ؑ�
	m_mode = mode;

    switch(m_mode)
    {
        case MODE_TITLE:	//�^�C�g��
			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
			}
            break;
		case MODE_GAME:		//�Q�[��
			if (m_pGame != NULL)
			{
				m_pGame->Init();
			}
			break;
    }
}

//=============================================================================
// �|�[�Y���[�h�X�^�[�g
//=============================================================================
void CManager::PauseStart(void)
{
	//�R���g���[���[���͎擾
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	//���͊m�F�X�C�b�`
	bool bJoyStick = false;
	
	//�R���g���[���[���͊m�F
	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_SELECT))
		{
			bJoyStick = true;
		}
	}

	//�|�[�Y��ʐ���
	if (!m_pPause->GetPause() &&((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_P)|| bJoyStick)
	{
		m_pPause->Init();
	}
}


//=============================================================================
// ���[�h�擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
    return m_mode;
}

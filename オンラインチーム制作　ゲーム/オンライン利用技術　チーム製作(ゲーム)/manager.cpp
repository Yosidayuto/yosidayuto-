//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �U�J �����Y
//
//=============================================================================
#include "manager.h"
#include "scene2d.h"
#include "polygon.h"
#include "tooth.h"
#include "bg.h"
#include "input_mouse.h"
#include "mouse_pointer.h"
#include "clean.h"
#include "fade.h"
#include "title.h"
#include "wait.h"
#include "game.h"
#include "result.h"
#include "communication.h"
#include "turn wait.h"
#include "ui.h"
#include "death.h"
#include "sound.h"
#include "die screen.h"
#include "load.h"
//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CPolygon *CManager::m_pPolygon = NULL;
CInhMouse *CManager::m_pInputMouse = NULL;
CTitle *CManager::m_pTitle = NULL;
CLoad *CManager::m_pLoad = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_mode = {};
CCommunication *CManager::pCommunication=NULL;
CSound *CManager::m_pSound = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_mode = MODE_TITLE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�ڑ�����
	WSADATA wsaData;
	//winsock�̏�����
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		//�������ł��Ȃ�������
		printf("�������Ɏ��s���܂���\n");

		return 1;
	}


	//�����_���[����
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h����
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�}�E�X����
	m_pInputMouse = new CInhMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	//�T�E���h����
	m_pSound = new CSound;
	m_pSound->Init(hWnd);


	//�e�N�X�`������
	CUi::Load();
	CTurnWait::Load();
	CTooth::Load();
	CClean::Load();
	CBg::Load();
	CPointer::Load();
	CTitle::Load();
	CWait::Load();
	CResult::Load();
	CDeath::Load();
	CDieScreen::Load();
	//�t�F�[�h����
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));


	SetMode(MODE_TITLE);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g��j��
	CScene::ReleaseAll();

	//�e�N�X�`���j��
	CUi::Unload();
	CTurnWait::Unload();
	CTooth::Unload();
	CClean::Unload();
	CBg::Unload();
	CPointer::Unload();
	CTitle::Unload();
	CWait::Unload();
	CResult::Unload();
	CDeath::Unload();
	CDieScreen::Unload();
	//�T�E���h�I��
	if (m_pSound != NULL)
	{
		//�I������
		m_pSound->Uninit();

		//�C���X�^���X�j��
		delete m_pSound;
		m_pSound = NULL;
	}

	//�t�F�[�h�I��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = NULL;
	}

	//�ʐM�I��
	if (pCommunication != NULL)
	{
		pCommunication->Uninit();
		delete pCommunication;
		pCommunication = NULL;
	}

	//�L�[�{�[�h�I��
	if (m_pInputKeyboard != NULL)
	{
		//�I������
		m_pInputKeyboard->Uninit();

		//�C���X�^���X�j��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�}�E�X�I��
	if (m_pInputMouse != NULL)
	{
		//�I������
		m_pInputMouse->Uninit();

		//�C���X�^���X�j��
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//�����_���[�I��
	if (m_pRenderer != NULL)
	{
		//�I������
		m_pRenderer->Uninit();

		//�C���X�^���X�j��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	//���͏����X�V(�L�[�{�[�h)
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//���͏����X�V(�}�E�X)
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	//�����_���[�X�V
	if (m_pRenderer != NULL)
	{
		//�X�V����
		m_pRenderer->Update();
	}

	//�t�F�[�h�X�V
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE://�^�C�g����ʂ̏I������
		if (m_pInputKeyboard->GetKeyTrigger(DIK_RETURN))
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);				//���艹

			m_pFade->SetFade(MODE_LOAD);
		}
		break;
	case MODE_LOAD://���[�h��ʂ̏I������
		if (CCommunication::GetbRecv()==true)
		{

			m_pFade->SetFade(MODE_GAME);
		}
		break;
	case MODE_GAME://�Q�[����ʂ̏I������
		if (m_pInputKeyboard->GetKeyTrigger(DIK_RETURN))
		{
			m_pFade->SetFade(MODE_RESULT);
		}
		break;

	case MODE_RESULT://���U���g��ʂ̏I������
		if (m_pInputKeyboard->GetKeyTrigger(DIK_RETURN))
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);		//���艹
																		
			m_pFade->SetFade(MODE_TITLE);						//�t�F�C�h
		}
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//�`�揈��
		m_pRenderer->Draw();
	}
}

//=============================================================================
// �����_�����O���擾
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// �L�[�{�[�h���擾
//=============================================================================
CInputKeyboard * CManager::Getkeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// �}�E�X���擾
//=============================================================================
CInhMouse * CManager::GetMouse(void)
{
	return m_pInputMouse;
}

//=============================================================================
// �|���S���i���o�[�擾
//=============================================================================
CPolygon * CManager::GetPolygon(void)
{
	return m_pPolygon;
}

//=============================================================================
// �T�E���h���擾
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// ���[�h�ؑ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pSound->Stop();				//�T�E���h��~
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
		}
		break;
	case MODE_LOAD:
		m_pSound->Stop();				//�T�E���h��~

		if (m_pLoad != NULL)
		{
			m_pLoad->Uninit();
		}
		break;

	case MODE_GAME:
		m_pSound->Stop();				//�T�E���h��~
		if (pCommunication != NULL)		//�ʐM�I��
		{
			pCommunication->Uninit();
			delete pCommunication;
			pCommunication = NULL;
		}


		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
		}

		break;

	case MODE_RESULT:
		m_pSound->Stop();				//�T�E���h��~

		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
		}
		break;
	}

	CScene::ReleaseAll();

	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE://�^�C�g����ʂ̏�����
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		m_pTitle->Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		break;
	case MODE_LOAD:	//���[�h���
		m_pSound->Play(CSound::SOUND_LABEL_BGM_LOAD);
		m_pLoad->Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		pCommunication = CCommunication::Create();
		break;

	case MODE_GAME://�Q�[����ʂ̏�����
		m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		pCommunication->SetbRecv();
		m_pGame->Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		break;

	case MODE_RESULT:
		m_pSound->Play(CSound::SOUND_LABEL_BGM_RESULT);
		m_pSound->Play(CSound::SOUND_LABEL_SE_WINNER);

		m_pResult->Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		break;
	}
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// �̎擾
//=============================================================================
CCommunication * CManager::GetCommunication(void)
{
	return pCommunication;
}


//=============================================================================
//
//	�^�C�g���{�^���}�l�[�W���[[button title.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "pause button manager.h"
#include "renderer.h"
#include "manager.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"
#include "button.h"
#include "start button.h"
#include "end button.h"
#include "restart button.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CPauseButtonManager::CPauseButtonManager()
{
	ZeroMemory(m_pButton, sizeof(m_pButton));
	m_bStick = false;
	m_nButtonSelect = 0;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CPauseButtonManager::~CPauseButtonManager()
{
}


//=============================================================================
// ��������
//=============================================================================
CPauseButtonManager * CPauseButtonManager::Create(void)
{
	CPauseButtonManager* pPauseButtonManager = NULL;
	pPauseButtonManager = new CPauseButtonManager;
	
	//NULL�`�F�b�N
	if (pPauseButtonManager != NULL)
	{
		//����������
		pPauseButtonManager->Init();
	}
	return pPauseButtonManager;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPauseButtonManager::Init(void)
{
	//���ꂼ��̃{�^������
	m_pButton[BUTTON_TYPE_START]	= CStartButton::Create(D3DXVECTOR3((float)(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 150, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	m_pButton[BUTTON_TYPE_RESTART]	= CRestartButton::Create(D3DXVECTOR3 ((float)(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	m_pButton[BUTTON_TYPE_END]		= CEndButton::Create(D3DXVECTOR3((float)(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 150, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPauseButtonManager::Uninit(void)
{
	for (int nButton = 0; nButton<BUTTON_TYPE_MAX; nButton++)
	{
		if (m_pButton[nButton] != NULL)
		{
			m_pButton[nButton]->Uninit();
			m_pButton[nButton] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CPauseButtonManager::Update(void)
{
	//�A�b�v�f�[�g����
	for (int nButton = 0; nButton < BUTTON_TYPE_MAX; nButton++)
	{
		if (m_pButton[nButton] != NULL)
		{
			m_pButton[nButton]->Update();
		}
	}

	//�I�������{�^���̏���
	Over();

	//�{�^���I������
	Select();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPauseButtonManager::Draw(void)
{

}

//=============================================================================
// �I������
//=============================================================================
void CPauseButtonManager::Select(void)
{
	//�L�[�{�[�h���͎擾
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();

	// �R���g���[���[�\���L�[�̒l�̎擾
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	WORD joyCross = CROSS_KEY_NEUTRAL;
	if (pJoyInput != NULL) joyCross = (WORD)pJoyInput->GetJoyStick().rgdwPOV[0];


	//���͂�����Ă��邩
	if (!m_bStick)
	{
		//�X�^�[�g�{�^���I��
		if (joyCross == CROSS_KEY_UP || pInputKey->GetKeyTrigger(DIK_W))
		{
			m_nButtonSelect -= 1;
			m_bStick = true;

			//BGM�̍Đ�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_CHOICE);
		}
		//�I���{�^���I��
		if (joyCross == CROSS_KEY_DOWN || pInputKey->GetKeyTrigger(DIK_S))
		{
			m_nButtonSelect += 1;
			m_bStick = true;

			//BGM�̍Đ�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_CHOICE);
		}
	}
	else if(m_bStick)
	{
		if (joyCross == CROSS_KEY_NEUTRAL)
		{
			m_bStick = false;
		}
	}


	//�I�����̃��[�v
	if (m_nButtonSelect>=BUTTON_TYPE_MAX)
	{
		//�߂�
		m_nButtonSelect = 0;
	}
	if (m_nButtonSelect<BUTTON_TYPE_START)
	{
		//�߂�
		m_nButtonSelect = BUTTON_TYPE_MAX - 1;
	}
}
//=============================================================================
// �I�������{�^���̏���
//=============================================================================
void CPauseButtonManager::Over(void)
{
	for (int nButton = 0; nButton < BUTTON_TYPE_MAX; nButton++)
	{
		if (m_pButton[nButton] != NULL)
		{
			//���݂̑I�����Ă���{�^�����ǂ���
			if (nButton == m_nButtonSelect)
			{
				//�I�����Ă���{�^��
				m_pButton[nButton]->Over();
			}
			else
			{
				//�I�����Ă��Ȃ��{�^��
				m_pButton[nButton]->Out();
			}

		}
	}
}

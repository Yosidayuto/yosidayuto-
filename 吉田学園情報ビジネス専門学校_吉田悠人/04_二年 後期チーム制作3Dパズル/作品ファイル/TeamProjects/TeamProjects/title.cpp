//=============================================================================
//
// �^�C�g�� [title.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "title.h"
#include "manager.h"
#include "object.h"
#include "camera.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "fade.h"
#include "stage1.h"
#include "sound.h"
#include "title logo.h"
#include "sea.h"
#include "press button ui.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLE_LOGO_POS_X	(SCREEN_WIDTH / 2)	// ���S��X�ʒu
#define TITLE_LOGO_POS_Y	(280.0f)			// ���S��Y�ʒu		
#define TITLE_LOGO_SIZE_X	(1400.0f)			// ���S��X�T�C�Y
#define TITLE_LOGO_SIZE_Y	(680.0f)			// ���S��Y�T�C�Y
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pStage	 = NULL;
	m_pCamera	 = NULL;
	m_pTitleLoge = NULL;
	m_bFlag		 = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// �C�̐���
	CSea::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 0.002f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -60.0f, 0.0f), 0.005f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), 0.008f, CSea::TYPE_NORMAL);

	//�J�����̃������m��
	m_pCamera = new CCamera;

	//�J�����̏���������
	if (m_pCamera != NULL)
	{
		m_pCamera->Init(D3DXVECTOR3(-275, 0.0f, 300.0f));
	}

	//�^�C�g�����S����
	m_pTitleLoge = CTitleLoge::Create(D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y,0.0f), D3DXVECTOR3(TITLE_LOGO_SIZE_X, TITLE_LOGO_SIZE_Y, 0.0f));

	//�t�F�[�h�����Ă��Ȃ�
	m_bFlag = false;

	//�{�^��UI
	CPressUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), D3DXVECTOR3(500.0f, 100.0f, 0.0f));


	//�X�e�[�W�̃������m��
	m_pStage = new CStage1;
	//�X�e�[�W�̏���������
	if (m_pStage != NULL)
	{
		m_pStage->TitleMapCreate();
	}

	//BGM�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�J�����I��
	if (m_pCamera != NULL)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//BGM�̏I��
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);

	CObject::ReleaseAll();
}


//=============================================================================
// �`��֐�
//=============================================================================
void CTitle::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	//�J�����̍X�V
	if (m_pCamera != NULL)
	{
		m_pCamera->TitleMove();
		m_pCamera->Update();
	}

	//�L�[�{�[�h���͂̎擾
	CInputKeyboard* pInput = (CInputKeyboard*)CManager::GetInputKey();
	//�t�F�[�h�̃|�C���^�擾
	CFade* pBlackout = CManager::GetFadeout();
	//�R���g���[���[���͎擾
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	//���͊m�F�X�C�b�`
	bool bJoyStick = false;
	//�R���g���[���[���͊m�F
	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_START)) bJoyStick = true;

	}

	//�t�F�[�h�����Ă��邩&�t�F�[�h��
	if (m_bFlag == false && pBlackout->GetFade() <= CFade::FADE_NONE)
	{
		//�{�^���������ꂽ��
		if (pInput->GetKeyTrigger(DIK_RETURN)|| bJoyStick)
		{
			//�t�F�[�h�����Ă���
			m_bFlag = true;

			//�V�[���ړ�����
			pBlackout->SetBlackout(CManager::MODE_GAME);

			//BGM�̍Đ�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_DECISION);
		}
	}
}
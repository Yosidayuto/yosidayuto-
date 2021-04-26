//=============================================================================
//
//	�X�^�[�g�{�^��[start button.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "start button.h"
#include "renderer.h"
#include "resource manager.h"
#include "manager.h"
#include "pause.h"
#include "sound.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStartButton::CStartButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStartButton::~CStartButton()
{
}

//=============================================================================
// ��������
//=============================================================================
CStartButton * CStartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CStartButton *pStartButton = NULL;
	pStartButton = new CStartButton;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pStartButton->m_nTexture);

	//NULL�`�F�b�N
	if (pStartButton != NULL)
	{
		//�ʒu�ݒ�
		pStartButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pStartButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//�e�N�X�`���ݒ�
		pStartButton->BindTexture(Texture);
		//����������
		pStartButton->Init();
	}
	return pStartButton;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStartButton::Init(void)
{
	CButton::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStartButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CStartButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CStartButton::Draw(void)
{
	CButton::Draw();
}


//=============================================================================
// �v�b�V�����菈��
//=============================================================================
void CStartButton::Push()
{
	//�L�[���͎擾
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();
	//�|�[�Y�擾
	CPause* pPause = CManager::GetPause();
	// �R���g���[���[���͂̎擾
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	bool bpush = false;
	
	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_A))bpush = true;
	}
	
	//�X�e�B�b�N����
	if (bpush || pInputKey->GetKeyTrigger(DIK_RETURN))
	{
		//�|�[�Y�I��
		pPause->Delete();
		//BGM�̍Đ�
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_DECISION);
	}
}


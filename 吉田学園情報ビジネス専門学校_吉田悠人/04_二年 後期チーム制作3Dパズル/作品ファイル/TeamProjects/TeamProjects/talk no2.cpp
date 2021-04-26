//=============================================================================
//
//	�Z���tNo2 [talk no2.cpp]
//	Author:���� �r�H
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "talk_base.h"
#include "resource manager.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "talk no2.h"
#include "tutorial.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TALK_APPEAR (420)	//�o�����Ă��鎞��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkNo2::CTalkNo2(int nPriorit)
{
	m_bTutorial = false;
	m_pTutorial = nullptr;
}

//=============================================================================
// ��������
//=============================================================================
CTalkNo2 * CTalkNo2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTalkNo2* pTalkNo2 = nullptr;
	pTalkNo2 = new CTalkNo2;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo2->m_nTexture);

	//NULL�`�F�b�N
	if (pTalkNo2 != nullptr)
	{
		//�ʒu�ݒ�
		pTalkNo2->SetPos(pos);
		//�T�C�Y�ݒ�
		pTalkNo2->SetSize(size);
		//�e�N�X�`���ݒ�
		pTalkNo2->BindTexture(Texture);
		//����������
		pTalkNo2->Init();
	}
	return pTalkNo2;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTalkNo2::Init(void)
{
	//�o�����Ă��鎞�ԃZ�b�g
	SetAppear(TALK_APPEAR);
	//�t�F�[�h�󋵐ݒ�
	SetFade(FADE_IN);

	//����������
	CTalkbase::Init();
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTalkNo2::Update(void)
{
	CTalkbase::Update();
}

//=============================================================================
// �g�[�N����
//=============================================================================
void CTalkNo2::Talk(void)
{
	//�L�[�{�[�h���͎擾
	CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();
	//�R���g���[���[���͎擾
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	//���͊m�F�X�C�b�`
	bool bJoyStick = false;
	//�R���g���[���[���͊m�F
	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_A)) bJoyStick = true;

	}

	//�t���O�������Ă��Ȃ���
	if (m_bTutorial == false)
	{
		//�J�E���g�A�b�v
		m_nTalkCount++;

		//�J�E���g�̐��l�����ɒB������ || �L�[����������||�{�^������������
		if (m_nTalkCount >= TALK_APPEAR || pKeyInput->GetKeyTrigger(DIK_SPACE) || bJoyStick)
		{
			//�J�E���g������
			m_nTalkCount = 0;
			
			//�`���[�g���A������
			if (m_pTutorial == nullptr)
			{
				m_pTutorial = CTutorial::Create();
			}

			m_bTutorial = true;
		}
	}

	//�t���O����������
	else if (m_bTutorial == true)
	{
		//�L�[����������||�{�^������������
		if (pKeyInput->GetKeyTrigger(DIK_SPACE)|| bJoyStick)
		{
			//NULL�`�F�b�N
			if (m_pTutorial != nullptr)
			{
				//�I������
				m_pTutorial->TutorialUninit();
				m_pTutorial = nullptr;
			}

			//���ߏ󋵂�ݒ�
			m_Fade = FADE_OUT;
		}
	}
}

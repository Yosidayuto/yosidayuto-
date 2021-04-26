//=============================================================================
//
//	�Z���tNo12 [talk no12.cpp]
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
#include "talk no12.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TALK_APPEAR (220)	//�o�����Ă��鎞��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkNo12::CTalkNo12(int nPriorit)
{

}

//=============================================================================
// ��������
//=============================================================================
CTalkNo12 * CTalkNo12::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTalkNo12* pTalkNo12 = nullptr;
	pTalkNo12 = new CTalkNo12;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo12->m_nTexture);

	if (pTalkNo12 != nullptr)
	{
		//�ʒu�ݒ�
		pTalkNo12->SetPos(pos);
		//�T�C�Y�ݒ�
		pTalkNo12->SetSize(size);
		//�e�N�X�`���ݒ�
		pTalkNo12->BindTexture(Texture);
		//����������
		pTalkNo12->Init();
	}
	return pTalkNo12;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTalkNo12::Init(void)
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
void CTalkNo12::Update(void)
{
	CTalkbase::Update();
}

//=============================================================================
// �g�[�N�����ɐi�߂�֐�
//=============================================================================
void CTalkNo12::Talk(void)
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

	//�J�E���g�A�b�v
	m_nTalkCount++;

	//�J�E���g�����ɒB������ || �L�[����������||�{�^������������
	if (m_nTalkCount >= TALK_APPEAR || pKeyInput->GetKeyTrigger(DIK_SPACE) || bJoyStick)
	{
		//�t�F�[�h�󋵐ݒ�
		m_Fade = FADE_OUT;

		//�J�E���g������
		m_nTalkCount = 0;
	}

}

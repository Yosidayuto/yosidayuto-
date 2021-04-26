//=============================================================================
//
//	�Z���t�e�N���X [talk_bass.cpp]
//	Author:���� �r�H
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "talk_base.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_PATH_TALK_1 "Data/Texture/talk_bass/serifu1.png"
#define TEXTURE_PATH_TALK_2 "Data/Texture/talk_bass/serifu2.png"
#define TEXTURE_PATH_TALK_3 "Data/Texture/talk_bass/serifu3.png"
#define TEXTURE_PATH_TALK_4 "Data/Texture/talk_bass/serifu4.png"
#define TEXTURE_PATH_TALK_5 "Data/Texture/talk_bass/serifu5.png"
#define TEXTURE_PATH_TALK_6 "Data/Texture/talk_bass/serifu6.png"
#define TEXTURE_PATH_TALK_7 "Data/Texture/talk_bass/serifu7.png"
#define TEXTURE_PATH_TALK_8 "Data/Texture/talk_bass/serifu8.png"
#define TEXTURE_PATH_TALK_9 "Data/Texture/talk_bass/serifu9.png"
#define TEXTURE_PATH_TALK_10 "Data/Texture/talk_bass/serifu10.png"
#define TEXTURE_PATH_TALK_11 "Data/Texture/talk_bass/serifu11.png"
#define TEXTURE_PATH_TALK_12 "Data/Texture/talk_bass/serifu12.png"

#define FADE_RATE 0.03f

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkbase::CTalkbase(int nPriorit) :CUi(nPriorit)
{
	m_Fade		 = FADE_NONE;
	m_bTalkEnd	 = false;
	m_col		 = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nAppear	 = 0;
	m_nTalkCount = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTalkbase::~CTalkbase()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTalkbase::Init(void)
{

	//�J���[�Z�b�g
	SetCol(m_col);
	//����������
	CUi::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTalkbase::Uninit(void)
{
	CUi::Uninit();

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTalkbase::Update(void)
{
	CUi::Update();
	//�g�[�N����
	Talk();
	//�t�F�[�h�C���E�A�E�g�̏���
	Blackout();
}

//=============================================================================
// �g�[�N�����ɐi�߂�֐�
//=============================================================================
void CTalkbase::Talk(void)
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
	if (m_nTalkCount >= m_nAppear || pKeyInput->GetKeyTrigger(DIK_SPACE)|| bJoyStick)
	{
		//�t�F�[�h�󋵐ݒ�
		m_Fade = FADE_OUT;
	
		//�J�E���g������
		m_nTalkCount = 0;
	}

}

//=============================================================================
// �Ó]�̐ݒ�
//=============================================================================
void CTalkbase::Blackout(void)
{
	//�t�F�[�h�A�E�g��
	if (m_Fade == FADE_OUT)
	{
		//����
		m_col.a -= FADE_RATE;

		//��������
		if (m_col.a <= 0.0f)
		{
			//������
			m_col.a = 0.0f;
			m_Fade = FADE_NONE;
			m_bTalkEnd = true;
		}
	}
	// �t�F�[�h�C����
	else if (m_Fade == FADE_IN)
	{
		//�s������
		m_col.a += FADE_RATE;

		//�o���d�؂�����
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
		}

	}

	//�J���[�Z�b�g
	SetCol(m_col);

}

//=============================================================================
// �o�����ԃZ�b�^�[
//=============================================================================
void CTalkbase::SetAppear(int nAppear)
{
	m_nAppear = nAppear;
}

//=============================================================================
// �o�����ԃQ�b�^�[
//=============================================================================
int CTalkbase::GetAppear(void)
{
	return m_nAppear;
}

//=============================================================================
// �t�F�[�h��ԃZ�b�^�[
//=============================================================================
void CTalkbase::SetFade(TALK_FADE FadeStatus)
{
	m_Fade = FadeStatus;
}

//=============================================================================
// �t�F�[�h��ԃQ�b�^�[
//=============================================================================
CTalkbase::TALK_FADE CTalkbase::GetFade(void)
{
	return m_Fade;
}

//=============================================================================
// �I���t���O�Q�b�^�[
//=============================================================================
bool CTalkbase::GetTalkEnd(void)
{
	return m_bTalkEnd;
}





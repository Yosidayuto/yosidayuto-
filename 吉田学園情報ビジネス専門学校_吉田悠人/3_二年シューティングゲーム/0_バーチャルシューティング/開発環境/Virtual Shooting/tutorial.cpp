//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "tutorial.h"
#include "sound.h"
#include "fade.h"
#include "inputmouse.h"
#include "tutorial bg.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	m_pTutorialBg = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	CSound*	pSound = CManager::GetSound();	//�T�E���h�擾

	//�`���[�g���A������
	m_pTutorialBg = CTutorialBg::Create();

	//�����܂�
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	//�T�E���h�擾
	CSound*	pSound = CManager::GetSound();
	//�T�E���h��~
	pSound->Stop();
	//�V�[���j��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	CSound*		pSound	= CManager::GetSound();	//�T�E���h�擾
	CInihMouse*	pMouse	= CManager::GetMouse();	//�}�E�X�擾
	CFade*		pFade	= CManager::GetFade();	//�t�F�[�h�擾	
	static int	nCount	= 0;					//�N���b�N�J�E���g
			
	//�}�E�X�����N���b�N
	if (pMouse->GetClickTrigger(0) == true)
	{
		nCount++;
		if (nCount>3)
		{
			pFade->SetFade(GAME_MODE_SELECT);
			nCount = 0;
		}
		else
		{
			//NULL�`�F�b�N
			if (pSound != NULL)
			{
				//SE�Đ�
				pSound->Play(CSound::LABEL_SE_CLICK);
			}
			//NULL�`�F�b�N
			if (m_pTutorialBg != NULL)
			{
				m_pTutorialBg->TextureMove(true);
			}

		}
	}
	//�}�E�X���E�N���b�N
	else if (pMouse->GetClickTrigger(1) == true)
	{
		//�N���b�N�J�E���g
		nCount--;
		if (nCount<0)
		{
			nCount=0;
		}
		else
		{
			//NULL�`�F�b�N
			if (pSound != NULL)
			{
				//SE�Đ�
				pSound->Play(CSound::LABEL_SE_CLICK);
			}
			//NULL�`�F�b�N
			if (m_pTutorialBg != NULL)
			{
				m_pTutorialBg->TextureMove(false);
			}

		}
	}

}

//=============================================================================
// �`��֐�
//=============================================================================
void CTutorial::Draw(void)
{
}

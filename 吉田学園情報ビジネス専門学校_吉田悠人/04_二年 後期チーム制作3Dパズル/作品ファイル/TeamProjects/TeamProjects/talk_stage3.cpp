//=============================================================================
//
//	�g�[�N�X�e�[�W3 [talk_stage3.cpp]
//	Author : ����@�r�H
//
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "talk_stage3.h"
#include "manager.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "talk_base.h"
#include "talk no9.h"
#include "talk no10.h"
#include "talk no11.h"
#include "talk no12.h"
#include "fade.h"
#include "player.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkStage3::CTalkStage3(int nPriority) :CTalkStageBese(nPriority)
{
	pTalk = nullptr;
	TalkData = TALK_9;
}

//=============================================================================
// �Z���t�̐���
//=============================================================================
CTalkStage3 * CTalkStage3::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �������̊m��
	CTalkStage3 * pTalk = NULL;
	pTalk = new CTalkStage3;
	if (pTalk != NULL)
	{
		// ���W��set
		pTalk->SetPos(pos);
		// �T�C�Y��set
		pTalk->SetSize(size);
		// ����������
		pTalk->Init();
	}

	return pTalk;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTalkStage3::Update(void)
{
	//�t�F�[�h�擾
	CFade* pFade = CManager::GetFadeout();


	//NULL�`�F�b�N
	if (pTalk != nullptr)
	{
		//�g�[�N���I����Ă��邩
		if (pTalk->GetTalkEnd())
		{
			pTalk->Uninit();
			pTalk = nullptr;
			//�v���C���[�̐���������
			if (TalkData == TALK_9)
			{
				CPlayer::GetPlayer()->SetAction(false);
			}

			//�g�[�N�f�[�^��i�߂�
			TalkData = (TALK_DATA)(1 + TalkData);
		}
		return;
	}
	switch (TalkData)
	{
	case TALK_9:
		//�v���C���[�̐�����������
		CPlayer::GetPlayer()->SetAction(true);
		
		//�g�[�N����
		pTalk = CTalkNo9::Create(GetPos(), Getsize());
		break;

	case TALK_10:
		//�g�[�N����
		pTalk = CTalkNo10::Create(GetPos(), Getsize());
		break;

	case TALK_11:
		//�g�[�N����
		pTalk = CTalkNo11::Create(GetPos(), Getsize());
		break;

	case TALK_12:
		//�g�[�N����
		pTalk = CTalkNo12::Create(GetPos(), Getsize());
		break;

	case TALK_MAX:
		//�g�[�N����
		pFade->SetBlackout(CManager::MODE_TITLE);
		break;

	}

}

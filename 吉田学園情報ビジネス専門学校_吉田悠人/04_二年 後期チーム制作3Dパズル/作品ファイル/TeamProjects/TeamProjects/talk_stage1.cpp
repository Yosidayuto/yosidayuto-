//=============================================================================
//
//	talk�w�b�_ [talk_stage1.cpp]
//	Author : ����@�r�H
//
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "talk_stage1.h"
#include "manager.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "tutorial.h"
#include "talk_base.h"
#include "player.h"
#include "talk no1.h"
#include "talk no2.h"
#include "talk no3.h"
#include "talk no4.h"
#include "talk no5.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkStage1::CTalkStage1(int nPriority):CTalkStageBese(nPriority)
{
	pTalk		= nullptr;
	TalkData	= TALK_1;
}

//=============================================================================
// �����֐�
//=============================================================================
CTalkStage1 * CTalkStage1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �������̊m��
	CTalkStage1 * pTalk = NULL;
	pTalk = new CTalkStage1;

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
void CTalkStage1::Update(void)
{
	//�L�[�{�[�h���͎擾
	CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();

	//NULL�`�F�b�N
	if (pTalk != nullptr)
	{
		//�g�[�N���I����Ă��邩
		if (pTalk->GetTalkEnd())
		{
			pTalk->Uninit();
			pTalk = nullptr;

			//�v���C���[�̐���������
			if (TalkData == TALK_2)
			{
				CPlayer::GetPlayer()->SetAction(false);
			}
			//�g�[�N�f�[�^��i�߂�
			TalkData = (TALK_DATA)(1 + TalkData);
		}
		return;
	}

	//����pTalk��nullptr�������琶��
	switch (TalkData)
	{
	case TALK_1:
		//�v���C���[�̐�����������
		CPlayer::GetPlayer()->SetAction(true);
		//�g�[�N����
		pTalk = CTalkNo1::Create(GetPos(), Getsize());
		break;
	case TALK_2:
		//�g�[�N����
		pTalk = CTalkNo2::Create(GetPos(), Getsize());
		break;
	case TALK_3:
		//�g�[�N����
		pTalk = CTalkNo3::Create(GetPos(), Getsize());
		break;
	case TALK_4:
		//�g�[�N����
		pTalk = CTalkNo4::Create(GetPos(), Getsize());
		break;
	case TALK_5:
		//�g�[�N����
		pTalk = CTalkNo5::Create(GetPos(), Getsize());
		break;

	}
}


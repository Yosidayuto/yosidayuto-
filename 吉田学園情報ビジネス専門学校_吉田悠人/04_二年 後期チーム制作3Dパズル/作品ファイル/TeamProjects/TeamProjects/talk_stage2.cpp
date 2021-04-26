//=============================================================================
//
//	talk�w�b�_ [talk_stage2.cpp]
//	Author : ����@�r�H
//
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "talk_stage2.h"
#include "manager.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "talk_base.h"
#include "talk no6.h"
#include "talk no7.h"
#include "talk no8.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkStage2::CTalkStage2(int nPriority) :CTalkStageBese(nPriority)
{
	pTalk = nullptr;
	TalkData = TALK_6;
}


//=============================================================================
// �Z���t�̐���
//=============================================================================
CTalkStage2 * CTalkStage2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �������̊m��
	CTalkStage2 * pTalk = NULL;
	pTalk = new CTalkStage2;
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
void CTalkStage2::Update(void)
{
	//NULL�`�F�b�N
	if (pTalk != nullptr)
	{
		//�g�[�N���I����Ă��邩
		if (pTalk->GetTalkEnd())
		{
			pTalk->Uninit();
			pTalk = nullptr;
			//�v���C���[�̐���������
			if (TalkData == TALK_6)
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
	case TALK_6:
		//�v���C���[�̐�����������
		CPlayer::GetPlayer()->SetAction(true);

		//�g�[�N����
		pTalk = CTalkNo6::Create(GetPos(), Getsize());
		break;
	case TALK_7:
		//�g�[�N����
		pTalk = CTalkNo7::Create(GetPos(), Getsize());
		break;
	case TALK_8:
		//�g�[�N����
		pTalk = CTalkNo8::Create(GetPos(), Getsize());
		break;
	}

}

//=============================================================================
//
//	�Z���tNo3 [talk no3.cpp]
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
#include "talk no3.h"
#include "tutorial.h"
#include "player.h"
#include "child.h"

//=============================================================================
// �}�N����`
//=============================================================================
//#define TALK_APPEAR (420)	//�o�����Ă��鎞��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkNo3::CTalkNo3(int nPriorit)
{
	m_bTutorial = false;
	m_pTutorial = nullptr;
	m_pChild = nullptr;
}

//=============================================================================
// ��������
//=============================================================================
CTalkNo3 * CTalkNo3::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTalkNo3* pTalkNo3 = nullptr;
	pTalkNo3 = new CTalkNo3;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo3->m_nTexture);

	//NULL�`�F�b�N
	if (pTalkNo3 != nullptr)
	{
		//�ʒu�ݒ�
		pTalkNo3->SetPos(pos);
		//�T�C�Y�ݒ�
		pTalkNo3->SetSize(size);
		//�e�N�X�`���ݒ�
		pTalkNo3->BindTexture(Texture);
		//����������
		pTalkNo3->Init();
	}
	return pTalkNo3;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTalkNo3::Init(void)
{
	//�o�����Ă��鎞�ԃZ�b�g
	SetAppear(0);
	//�t�F�[�h�󋵐ݒ�
	SetFade(FADE_IN);

	//����������
	CTalkbase::Init();
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTalkNo3::Update(void)
{
	CTalkbase::Update();
}

//=============================================================================
// �g�[�N����
//=============================================================================
void CTalkNo3::Talk(void)
{
	//�q��(�v���C���[�̂������Ă�u���b�N)�|�C���^����
	CChild * pChild = (CChild*)(GetTop()[PRIORITY_OBJECT_CHILD]);
	while (pChild != NULL)
	{
		//�����ɂ������Ă���
		if (pChild->GetIsActive())
		{
			//���ߏ󋵂�ݒ�
			m_Fade = FADE_OUT;
		}
		pChild = (CChild*)(pChild->GetNext());
	}
}


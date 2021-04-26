//=============================================================================
//
//	�Z���tNo4 [talk no4.cpp]
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
#include "talk no4.h"
#include "child.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkNo4::CTalkNo4(int nPriorit)
{
}

//=============================================================================
// ��������
//=============================================================================
CTalkNo4 * CTalkNo4::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTalkNo4* pTalkNo4 = nullptr;
	pTalkNo4 = new CTalkNo4;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo4->m_nTexture);

	//NULL�`�F�b�N
	if (pTalkNo4 != nullptr)
	{
		//�ʒu�ݒ�
		pTalkNo4->SetPos(pos);
		//�T�C�Y�ݒ�
		pTalkNo4->SetSize(size);
		//�e�N�X�`���ݒ�
		pTalkNo4->BindTexture(Texture);
		//����������
		pTalkNo4->Init();
	}
	return pTalkNo4;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTalkNo4::Init(void)
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
void CTalkNo4::Update(void)
{
	CTalkbase::Update();
}

//=============================================================================
// �g�[�N����
//=============================================================================
void CTalkNo4::Talk(void)
{
	//�q��(�v���C���[�̂������Ă�u���b�N)�|�C���^����
	CChild * pChild = (CChild*)(GetTop()[PRIORITY_OBJECT_CHILD]);
	while (pChild != NULL)
	{
		//�����ɂ������Ă���
		if (!pChild->GetIsActive())
		{
			//���ߏ󋵂�ݒ�
			m_Fade = FADE_OUT;
		}
		pChild = (CChild*)(pChild->GetNext());
	}
}

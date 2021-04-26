//=============================================================================
//
//	�Z���tNo11 [talk No11.cpp]
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
#include "talk no11.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkNo11::CTalkNo11(int nPriorit)
{
}

//=============================================================================
// ��������
//=============================================================================
CTalkNo11 * CTalkNo11::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTalkNo11* pTalkNo11 = nullptr;
	pTalkNo11 = new CTalkNo11;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo11->m_nTexture);

	//NULL�`�F�b�N
	if (pTalkNo11 != nullptr)
	{
		//�ʒu�ݒ�
		pTalkNo11->SetPos(pos);
		//�T�C�Y�ݒ�
		pTalkNo11->SetSize(size);
		//�e�N�X�`���ݒ�
		pTalkNo11->BindTexture(Texture);
		//����������
		pTalkNo11->Init();
	}
	return pTalkNo11;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTalkNo11::Init(void)
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
void CTalkNo11::Update(void)
{
	CTalkbase::Update();
}

//=============================================================================
// �g�[�N����
//=============================================================================
void CTalkNo11::Talk(void)
{
	//��
	int nCountItem = 0;
	//�I�u�W�F�N�g�擾�p
	CObject* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����I�u�W�F�N�g�̃|�C���^
	CObject* pNext = NULL;
	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}


	//�I�u�W�F�N�g�T��
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�̃^�C�v���A�C�e���Ȃ�
				if (pNext->GetObjType() == OBJTYPE_ITEM)
				{
					nCountItem++;
				}

				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();
			}
		}
	}

	//�A�C�e������̎�
	if (nCountItem == 0)
	{
		//���ߏ󋵂�ݒ�
		m_Fade = FADE_OUT;
	}

}

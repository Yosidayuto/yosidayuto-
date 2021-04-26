//=============================================================================
//
//	�Z���tNo10 [talk No10.cpp]
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
#include "talk no10.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkNo10::CTalkNo10(int nPriorit)
{
}

//=============================================================================
// ��������
//=============================================================================
CTalkNo10 * CTalkNo10::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTalkNo10* pTalkNo10 = nullptr;
	pTalkNo10 = new CTalkNo10;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo10->m_nTexture);

	//NULL�`�F�b�N
	if (pTalkNo10 != nullptr)
	{
		//�ʒu�ݒ�
		pTalkNo10->SetPos(pos);
		//�T�C�Y�ݒ�
		pTalkNo10->SetSize(size);
		//�e�N�X�`���ݒ�
		pTalkNo10->BindTexture(Texture);
		//����������
		pTalkNo10->Init();
	}
	return pTalkNo10;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTalkNo10::Init(void)
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
void CTalkNo10::Update(void)
{
	CTalkbase::Update();
}

//=============================================================================
// �g�[�N����
//=============================================================================
void CTalkNo10::Talk(void)
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
	if (nCountItem == 1)
	{
		//���ߏ󋵂�ݒ�
		m_Fade = FADE_OUT;
	}

}

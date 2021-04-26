//=============================================================================
//
//	�Z���tNo5 [talk no5.cpp]
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
#include "talk no6.h"
#include "child.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TALK_APPEAR (360)	//�o�����Ă��鎞��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTalkNo6::CTalkNo6(int nPriorit)
{
}

//=============================================================================
// ��������
//=============================================================================
CTalkNo6 * CTalkNo6::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTalkNo6* pTalkNo6 = nullptr;
	pTalkNo6 = new CTalkNo6;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo6->m_nTexture);

	//NULL�`�F�b�N
	if (pTalkNo6 != nullptr)
	{
		//�ʒu�ݒ�
		pTalkNo6->SetPos(pos);
		//�T�C�Y�ݒ�
		pTalkNo6->SetSize(size);
		//�e�N�X�`���ݒ�
		pTalkNo6->BindTexture(Texture);
		//����������
		pTalkNo6->Init();
	}
	return pTalkNo6;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTalkNo6::Init(void)
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
void CTalkNo6::Update(void)
{
	CTalkbase::Update();
}


//=============================================================================
//
//	�^�C�g�����S[title logo.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "title logo.h"
#include "resource manager.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleLoge::CTitleLoge(int nPriority) :CUi(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleLoge::~CTitleLoge()
{
}


//=============================================================================
// ��������
//=============================================================================
CTitleLoge * CTitleLoge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTitleLoge *pTitleLoge = NULL;
	pTitleLoge = new CTitleLoge;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTitleLoge->m_nTexture);

	//NULL�`�F�b�N
	if (pTitleLoge != NULL)
	{
		//�ʒu�ݒ�
		pTitleLoge->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pTitleLoge->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//�e�N�X�`���ݒ�
		pTitleLoge->BindTexture(Texture);
		//����������
		pTitleLoge->Init();
	}
	return pTitleLoge;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitleLoge::Init(void)
{
	CUi::Init();
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitleLoge::Update(void)
{
	CUi::Update();
}

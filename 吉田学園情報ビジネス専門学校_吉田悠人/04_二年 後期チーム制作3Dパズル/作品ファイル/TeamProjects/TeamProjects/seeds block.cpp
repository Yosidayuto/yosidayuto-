//=============================================================================
//
// ��u���b�N [seeds block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "seeds block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSeedsBlock::CSeedsBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSeedsBlock::~CSeedsBlock()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CSeedsBlock * CSeedsBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CSeedsBlock* pSeedsBlock = NULL;
	pSeedsBlock = new CSeedsBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSeedsBlock->m_nModel);

	//NULL�`�F�b�N
	if (pSeedsBlock != NULL)
	{
		//�ʒu�ݒ�
		pSeedsBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//�����ݒ�
		pSeedsBlock->SetRotation(rot);
		//�J���[�ݒ�
		pSeedsBlock->SetScale(size);
		//���f���ݒ�
		pSeedsBlock->SetModelData(Model);
		//����������
		pSeedsBlock->Init();
	}

	return pSeedsBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CSeedsBlock::Init(void)
{
	CItemBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CSeedsBlock::Uninit(void)
{
	CItemBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CSeedsBlock::Update(void)
{
	CItemBlockBase::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CSeedsBlock::Draw(void)
{
	CItemBlockBase::Draw();
}

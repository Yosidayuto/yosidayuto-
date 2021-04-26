//=============================================================================
//
// ��u���b�N [sprout block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "sprout block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSproutBlock::CSproutBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSproutBlock::~CSproutBlock()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CSproutBlock * CSproutBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CSproutBlock* pSproutBlock = NULL;
	pSproutBlock = new CSproutBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSproutBlock->m_nModel);

	//NULL�`�F�b�N
	if (pSproutBlock != NULL)
	{
		//�ʒu�ݒ�
		pSproutBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//�����ݒ�
		pSproutBlock->SetRotation(rot);
		//�J���[�ݒ�
		pSproutBlock->SetScale(size);
		//���f���ݒ�
		pSproutBlock->SetModelData(Model);
		//����������
		pSproutBlock->Init();
	}

	return pSproutBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CSproutBlock::Init(void)
{
	CTileBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CSproutBlock::Uninit(void)
{
	CTileBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CSproutBlock::Update(void)
{
	CTileBlockBase::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CSproutBlock::Draw(void)
{
	CTileBlockBase::Draw();

}


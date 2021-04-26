//=============================================================================
//
// �����S�u���b�N [apple block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "apple block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAppleBlock::CAppleBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CAppleBlock::~CAppleBlock()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CAppleBlock * CAppleBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CAppleBlock* pAppleBlock = NULL;
	pAppleBlock = new CAppleBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pAppleBlock->m_nModel);

	//NULL�`�F�b�N
	if (pAppleBlock != NULL)
	{
		//�ʒu�ݒ�
		pAppleBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//�����ݒ�
		pAppleBlock->SetRotation(rot);
		//�J���[�ݒ�
		pAppleBlock->SetScale(size);
		//���f���ݒ�
		pAppleBlock->SetModelData(Model);
		//����������
		pAppleBlock->Init();
	}

	return pAppleBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CAppleBlock::Init(void)
{
	CItemBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CAppleBlock::Uninit(void)
{
	CItemBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CAppleBlock::Update(void)
{
	CItemBlockBase::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CAppleBlock::Draw(void)
{
	CItemBlockBase::Draw();
}

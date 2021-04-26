//=============================================================================
//
// �r���u���b�N [building block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "building block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBuildingBlock::CBuildingBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBuildingBlock::~CBuildingBlock()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CBuildingBlock * CBuildingBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CBuildingBlock* pBuildingBlock = NULL;
	pBuildingBlock = new CBuildingBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pBuildingBlock->m_nModel);

	//NULL�`�F�b�N
	if (pBuildingBlock != NULL)
	{
		//�ʒu�ݒ�
		pBuildingBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//�����ݒ�
		pBuildingBlock->SetRotation(rot);
		//�J���[�ݒ�
		pBuildingBlock->SetScale(size);
		//���f���ݒ�
		pBuildingBlock->SetModelData(Model);
		//����������
		pBuildingBlock->Init();
	}

	return pBuildingBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBuildingBlock::Init(void)
{
	CHindranceBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBuildingBlock::Uninit(void)
{
	CHindranceBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBuildingBlock::Update(void)
{
	CHindranceBlockBase::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CBuildingBlock::Draw(void)
{
	CHindranceBlockBase::Draw();

}

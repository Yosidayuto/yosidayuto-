//=============================================================================
//
// �r���i����j�u���b�N [building break block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "building break block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBuildingBreakBlock::CBuildingBreakBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBuildingBreakBlock::~CBuildingBreakBlock()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CBuildingBreakBlock * CBuildingBreakBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CBuildingBreakBlock* pBuildingBreakBlock = NULL;
	pBuildingBreakBlock = new CBuildingBreakBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pBuildingBreakBlock->m_nModel);

	//NULL�`�F�b�N
	if (pBuildingBreakBlock != NULL)
	{
		//�ʒu�ݒ�
		pBuildingBreakBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//�����ݒ�
		pBuildingBreakBlock->SetRotation(rot);
		//�J���[�ݒ�
		pBuildingBreakBlock->SetScale(size);
		//���f���ݒ�
		pBuildingBreakBlock->SetModelData(Model);
		//����������
		pBuildingBreakBlock->Init();
	}

	return pBuildingBreakBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBuildingBreakBlock::Init(void)
{
	CHindranceBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBuildingBreakBlock::Uninit(void)
{
	CHindranceBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBuildingBreakBlock::Update(void)
{
	CHindranceBlockBase::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CBuildingBreakBlock::Draw(void)
{
	CHindranceBlockBase::Draw();

}

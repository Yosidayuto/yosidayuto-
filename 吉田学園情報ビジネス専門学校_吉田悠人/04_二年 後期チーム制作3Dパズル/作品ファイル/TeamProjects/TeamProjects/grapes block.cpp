//=============================================================================
//
// �u�h�E�u���b�N [grapes block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "grapes block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGrapesBlock::CGrapesBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGrapesBlock::~CGrapesBlock()
{
}


//=============================================================================
// �����֐�
//=============================================================================
CGrapesBlock * CGrapesBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CGrapesBlock* pGrapesBlock = NULL;
	pGrapesBlock = new CGrapesBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pGrapesBlock->m_nModel);


	//NULL�`�F�b�N
	if (pGrapesBlock != NULL)
	{
		//�ʒu�ݒ�
		pGrapesBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//�����ݒ�
		pGrapesBlock->SetRotation(rot);
		//�J���[�ݒ�
		pGrapesBlock->SetScale(size);
		//���f���ݒ�
		pGrapesBlock->SetModelData(Model);
		//����������
		pGrapesBlock->Init();
	}

	return pGrapesBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CGrapesBlock::Init(void)
{
	CItemBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CGrapesBlock::Uninit(void)
{
	CItemBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CGrapesBlock::Update(void)
{
	CItemBlockBase::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CGrapesBlock::Draw(void)
{
	CItemBlockBase::Draw();
}

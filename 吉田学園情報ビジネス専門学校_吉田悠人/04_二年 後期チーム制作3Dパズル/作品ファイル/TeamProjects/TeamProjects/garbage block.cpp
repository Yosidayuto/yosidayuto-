//=============================================================================
//
// �S�~�u���b�N [garbage block.h]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "garbage block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGarbageBlock::CGarbageBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGarbageBlock::~CGarbageBlock()
{
}


//=============================================================================
// �����֐�
//=============================================================================
CGarbageBlock * CGarbageBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CGarbageBlock* pGarbageBlock = NULL;
	pGarbageBlock = new CGarbageBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pGarbageBlock->m_nModel);

	//NULL�`�F�b�N
	if (pGarbageBlock != NULL)
	{
		//�ʒu�ݒ�
		pGarbageBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//�����ݒ�
		pGarbageBlock->SetRotation(rot);
		//�J���[�ݒ�
		pGarbageBlock->SetScale(size);
		//���f���ݒ�
		pGarbageBlock->SetModelData(Model);
		//����������
		pGarbageBlock->Init();
	}

	return pGarbageBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CGarbageBlock::Init(void)
{
	CItemBlockBase::Init();

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CGarbageBlock::Uninit(void)
{
	CItemBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CGarbageBlock::Update(void)
{
	CItemBlockBase::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CGarbageBlock::Draw(void)
{
	CItemBlockBase::Draw();
}

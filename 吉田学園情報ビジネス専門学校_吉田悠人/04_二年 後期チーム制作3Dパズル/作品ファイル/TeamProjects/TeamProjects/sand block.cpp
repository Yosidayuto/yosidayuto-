//=============================================================================
//
// ���u���b�N [sand block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "sand block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSandBlock::CSandBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSandBlock::~CSandBlock()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CSandBlock * CSandBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CSandBlock* pSandBlock = NULL;
	pSandBlock = new CSandBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSandBlock->m_nModel);

	//NULL�`�F�b�N
	if (pSandBlock != NULL)
	{
		//�ʒu�ݒ�
		pSandBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//�����ݒ�
		pSandBlock->SetRotation(rot);
		//�J���[�ݒ�
		pSandBlock->SetScale(size);
		//���f���ݒ�
		pSandBlock->SetModelData(Model);
		//����������
		pSandBlock->Init();
	}

	return pSandBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CSandBlock::Init(void)
{
	CTileBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CSandBlock::Uninit(void)
{
	CTileBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CSandBlock::Update(void)
{
	CTileBlockBase::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CSandBlock::Draw(void)
{
	CTileBlockBase::Draw();

}

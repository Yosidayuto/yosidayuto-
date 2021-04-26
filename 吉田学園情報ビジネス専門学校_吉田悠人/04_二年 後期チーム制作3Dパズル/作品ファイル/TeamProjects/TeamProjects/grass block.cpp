//=============================================================================
//
// ���u���b�N���� [grass block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "grass block.h"
#include "manager.h"
#include "resource manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGrassBlock::CGrassBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGrassBlock::~CGrassBlock()
{
}


//=============================================================================
// �����֐�
//=============================================================================
CGrassBlock * CGrassBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CGrassBlock* pTileBlock = NULL;
	pTileBlock = new CGrassBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pTileBlock->m_nModel);

	//NULL�`�F�b�N
	if (pTileBlock != NULL)
	{
		//�ʒu�ݒ�
		pTileBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//�����ݒ�
		pTileBlock->SetRotation(rot);
		//�J���[�ݒ�
		pTileBlock->SetScale(size);
		//���f���ݒ�
		pTileBlock->SetModelData(Model);
		//����������
		pTileBlock->Init();
	}

	return pTileBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CGrassBlock::Init(void)
{
	CTileBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CGrassBlock::Uninit(void)
{
	CTileBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CGrassBlock::Update(void)
{
	CTileBlockBase::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CGrassBlock::Draw(void)
{
	CTileBlockBase::Draw();

}


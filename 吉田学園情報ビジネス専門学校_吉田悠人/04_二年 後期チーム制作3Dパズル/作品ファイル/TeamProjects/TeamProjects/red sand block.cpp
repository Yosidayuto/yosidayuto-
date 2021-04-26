//=============================================================================
//
// �ԍ��u���b�N [red sand block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "red sand block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRedSandBlock::CRedSandBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRedSandBlock::~CRedSandBlock()
{
}


//=============================================================================
// �����֐�
//=============================================================================
CRedSandBlock * CRedSandBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CRedSandBlock* pRedSandBlock = NULL;
	pRedSandBlock = new CRedSandBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pRedSandBlock->m_nModel);

	//NULL�`�F�b�N
	if (pRedSandBlock != NULL)
	{
		
		//�ʒu�ݒ�
		pRedSandBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//�����ݒ�
		pRedSandBlock->SetRotation(rot);
		//�J���[�ݒ�
		pRedSandBlock->SetScale(size);
		//���f���ݒ�
		pRedSandBlock->SetModelData(Model);
		//����������
		pRedSandBlock->Init();
	}

	return pRedSandBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CRedSandBlock::Init(void)
{
	CTileBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CRedSandBlock::Uninit(void)
{
	CTileBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CRedSandBlock::Update(void)
{
	CTileBlockBase::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CRedSandBlock::Draw(void)
{
	CTileBlockBase::Draw();
}
//=============================================================================
//
// �ו��u���b�N [luggage block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "luggage block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define LUGGAGE_HEIGHT (-25.0f)	//��������

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLuggageBlock::CLuggageBlock()
{
	bGoal = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLuggageBlock::~CLuggageBlock()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CLuggageBlock * CLuggageBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CGame::MAP_TYPE MapType, bool Goal)
{
	//�������m��
	CLuggageBlock* pLuggageBlock = NULL;
	pLuggageBlock = new CLuggageBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pLuggageBlock->m_nModel);

	//NULL�`�F�b�N
	if (pLuggageBlock != NULL)
	{
		//�ʒu�ݒ�
		pLuggageBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + LUGGAGE_HEIGHT, pos.z));
		//�����ݒ�
		pLuggageBlock->SetRotation(rot);
		//�J���[�ݒ�
		pLuggageBlock->SetScale(size);
		//�}�b�v�ݒ�
		pLuggageBlock->SetMapType(MapType);
		//���f���ݒ�
		pLuggageBlock->SetModelData(Model);
		//�S�[���@�\�ݒ�
		pLuggageBlock->SetGoal(Goal);
		//����������
		pLuggageBlock->Init();
	}

	return pLuggageBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CLuggageBlock::Init(void)
{
	CGoalBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CLuggageBlock::Uninit(void)
{
	CGoalBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CLuggageBlock::Update(void)
{
	CGoalBlockBase::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CLuggageBlock::Draw(void)
{
	CGoalBlockBase::Draw();

}

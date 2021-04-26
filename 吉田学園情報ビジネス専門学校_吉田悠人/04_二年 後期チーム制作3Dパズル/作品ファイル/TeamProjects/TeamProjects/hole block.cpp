//=============================================================================
//
// ���u���b�N [sand block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "hole block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"
#include "fade.h"
#include "sprout block.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHoleBlock::CHoleBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHoleBlock::~CHoleBlock()
{
}


//=============================================================================
// �����֐�
//=============================================================================
CHoleBlock * CHoleBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CGame::MAP_TYPE MapType)
{
	//�������m��
	CHoleBlock* pHoleBlock = NULL;
	pHoleBlock = new CHoleBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pHoleBlock->m_nModel);

	//NULL�`�F�b�N
	if (pHoleBlock != NULL)
	{
		//�ʒu�ݒ�
		pHoleBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//�����ݒ�
		pHoleBlock->SetRotation(rot);
		//�J���[�ݒ�
		pHoleBlock->SetScale(size);
		//�}�b�v�ݒ�
		pHoleBlock->SetMapType(MapType);
		//���f���ݒ�
		pHoleBlock->SetModelData(Model);
		//����������
		pHoleBlock->Init();
	}

	return pHoleBlock;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CHoleBlock::Init(void)
{
	CGoalBlockBase::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CHoleBlock::Uninit(void)
{
	CGoalBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CHoleBlock::Update(void)
{
	CGoalBlockBase::Update();
	GoalCollision();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CHoleBlock::Draw(void)
{
	CGoalBlockBase::Draw();
}

//=============================================================================
// �S�[�������֐�
//=============================================================================
void CHoleBlock::Goal(void)
{
	//�t�F�[�h�擾
	CFade*	pFade = CManager::GetFadeout();
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	//�p�[�e�B�N������
	
	//�I������
	CHoleBlock::Uninit();

	//��u���b�N����
	CSproutBlock::Create(D3DXVECTOR3(pos.x, 0, pos.z), GetRotation(), GetScale());

	//�A�C�e�����Ȃ���
	if (ItemSearch())
	{
		//�X�e�[�W�̃t�F�[�h
		if (GetMapType() < CGame::MAP_TYPE_3)
		{
			//���̃X�e�[�W�Ƀt�F�[�h
			pFade->SetWhiteout(CGame::MAP_TYPE(GetMapType() + 1));

		}
	}

}


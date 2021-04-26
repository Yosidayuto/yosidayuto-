//=============================================================================
//
// �S�[���u���b�N�x�[�X [goal block base.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "goal block base.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"
#include "child.h"
#include "item block base.h"
#include "fade.h"
#include "player.h"
#include "particle.h"
#include "inputcontroller.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGoalBlockBase::CGoalBlockBase()
{
	SetObjType(OBJTYPE_GOAL);
	m_MapType	= CGame::MAP_TYPE_1;
	m_bGoal		= true;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGoalBlockBase::~CGoalBlockBase()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CGoalBlockBase::Init(void)
{
	CBlockBase::Init();
	SetPriority(PRIORITY_OBJECT_TILE);
	GetModel()->SetPriority(PRIORITY_OBJECT_TILE);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CGoalBlockBase::Uninit(void)
{
	CBlockBase::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CGoalBlockBase::Update(void)
{
	CBlockBase::Update();

	if (m_bGoal)
	{
		GoalCollision();
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CGoalBlockBase::Draw(void)
{
	CBlockBase::Draw();
}

//=============================================================================
// �S�[���̓����蔻��֐�
//=============================================================================
void CGoalBlockBase::GoalCollision(void)
{
	//���݂̈ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	CParticle*pParticle = NULL;
	CChild * pChild = dynamic_cast<CChild*>(GetTop()[PRIORITY_OBJECT_CHILD]);

	while (pChild != NULL)
	{
		if (pChild->GetIsActive())
		{
			// ���[���h���W�̎擾
			CModel::MODELDATA modelData = pChild->GetModel()->GetModelData();
			D3DXVECTOR3 worldPos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);

			//�͈͂ɓ����(Y���͍�����+�ƌ덷���Ȃ������߂�+1)
			if (pos.x + GOAL_RANGE>worldPos.x
				&&pos.x - GOAL_RANGE<worldPos.x
				&&pos.y + GOAL_RANGE*2.0f+1>worldPos.y
				&&pos.z + GOAL_RANGE>worldPos.z
				&&pos.z - GOAL_RANGE<worldPos.z)
			{	

				for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
				{
					//�p�[�e�B�N���̏���
					pParticle = CParticle::Cretae(pos, worldPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CParticle::PARTICLE_TYPE_2);
				}

				//�S�[������
				Goal();
				// �R���g���[���[�\���L�[�̒l�̎擾
				CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
				pJoyInput->SetVibration(0);

				//�v���C���[�̃S�[���ɓ����������̏���
				CPlayer::GetPlayer()->Goal();
			}
		}
		//���̃|�C���^���擾
		pChild = dynamic_cast<CChild*>(pChild->GetNext());
	}

}

//=============================================================================
// �A�C�e���T�[�`�֐�
//=============================================================================
bool CGoalBlockBase::ItemSearch(void)
{
	CItemBlockBase * pItem = dynamic_cast<CItemBlockBase*>(GetTop()[PRIORITY_OBJECT_ITEM]);

	while (pItem != NULL)
	{
		return false;
	}
	
	return true;
}

//=============================================================================
// �S�[�������֐�
//=============================================================================
void CGoalBlockBase::Goal(void)
{
	//�t�F�[�h�擾
	CFade*	pFade = CManager::GetFadeout();

	//�A�C�e�����Ȃ���
	if (ItemSearch())
	{
		//�X�e�[�W�̃t�F�[�h
		if (m_MapType < CGame::MAP_TYPE_3)
		{
			//���̃X�e�[�W�Ƀt�F�[�h
			pFade->SetWhiteout(CGame::MAP_TYPE(m_MapType+1));
		}
	}
}

//=============================================================================
// �}�b�v�Z�b�^�[
//=============================================================================
void CGoalBlockBase::SetMapType(CGame::MAP_TYPE MapType)
{
	m_MapType = MapType;
}

//=============================================================================
// �}�b�v�Q�b�g
//=============================================================================
CGame::MAP_TYPE CGoalBlockBase::GetMapType(void)
{
	return m_MapType;
}

//=============================================================================
// �S�[���@�\�Z�b�^�[
//=============================================================================
void CGoalBlockBase::SetGoal(bool bGoal)
{
	m_bGoal = bGoal;
}


//=============================================================================
// �S�[���@�\�Q�b�^�[
//=============================================================================
bool CGoalBlockBase::GetGoal(void)
{
	return m_bGoal;
}

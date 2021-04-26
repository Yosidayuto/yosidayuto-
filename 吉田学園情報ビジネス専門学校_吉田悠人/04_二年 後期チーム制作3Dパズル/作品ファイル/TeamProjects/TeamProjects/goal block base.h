//=============================================================================
//
// �S�[���u���b�N�x�[�X [goal block base.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _GOAL_BLOCK_BASE_H_
#define _GOAL_BLOCK_BASE_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
#include "block base.h"
#include "game.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define GOAL_HEIGHT (25.0f)	//�S�[���u���b�N�̍���
#define GOAL_RANGE	(25.0f)	//�S�[������̑傫��
//=============================================================================
// �O���錾
//=============================================================================
class CModel;
class CParticle;
//=============================================================================
// �N���X��`
//=============================================================================
class CGoalBlockBase : public CBlockBase
{
public:
	CGoalBlockBase();
	~CGoalBlockBase();
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void	GoalCollision(void);	// �S�[���̓����蔻�菈��
	bool	ItemSearch(void);		// �A�C�e���T�[�`�֐�
	virtual void Goal(void);		// �S�[������

	void			SetMapType(CGame::MAP_TYPE MapType);	// �}�b�v�Z�b�^�[
	CGame::MAP_TYPE	GetMapType(void);						// �}�b�v�Q�b�g
	void			SetGoal(bool bGoal);					// �S�[���@�\�Z�b�^�[
	bool			GetGoal(void);							// �S�[���@�\�Q�b�^�[
private:

	bool			m_bGoal;		//�S�[���@�\�������Ă��邩
	CGame::MAP_TYPE	m_MapType;		//���݂̃}�b�v�擾

};
#endif
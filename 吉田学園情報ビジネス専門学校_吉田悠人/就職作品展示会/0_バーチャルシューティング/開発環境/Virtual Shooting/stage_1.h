//=============================================================================
//
// �X�e�[�W1���� [stage_1.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _STAGE_1_H_
#define _STAGE_1_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "stage.h"
//=============================================================================
//�O���錾
//=============================================================================
class CEnemy;

//=============================================================================
// �N���X��`
//=============================================================================
class CStage1 :public CStage
{
public:

	CStage1();	//�R���X�g���N�^
	~CStage1();	//�f�X�g���N�^
	static CStage1*	Create(void);	//��������

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			StageMode(void);// �G�l�~�[�̃X�|�[�����[�h

private:
	typedef enum	//�G�l�~�[�̏o�����[�h
	{
		ENEMY_CREATE_NONE = 0,
		ENEMY_CREATE_1,		//�t�F�[�Y�P
		ENEMY_CREATE_2,		//�t�F�[�Y�Q
		ENEMY_CREATE_3,		//�t�F�[�Y�R
		ENEMY_CREATE_4,		//�t�F�[�Y�S
		ENEMY_CREATE_5,		//�t�F�[�Y5
		ENEMY_CREATE_6,		//�t�F�[�Y6
		ENEMY_CREATE_7,		//�t�F�[�Y7
		ENEMY_CREATE_8,		//�t�F�[�Y8
		ENEMY_CREATE_9,		//�t�F�[�Y9
		ENEMY_CREATE_MAX,
	}STAGE_1_ENEMY;

	STAGE_1_ENEMY	m_EnemyCreate;	//�G�l�~�[�̏o�����[�h
};


#endif
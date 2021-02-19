//=============================================================================
//
// �X�e�[�W���� [stage.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "game.h"
#include "enemy base.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ENEMY (200)	//�ő�G�l�~�[��
#define MAX_STAGE (3)	//�ő�X�e�[�W��
//=============================================================================
//�O���錾
//=============================================================================
class CEnemy;
class CEnemyBase;

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
}STAGE_ENEMY;

typedef struct	//�G�l�~�[�̈ړ����
{
	D3DXVECTOR3		pos;		//�ʒu
	float			fSpeed;		//�X�s�[�h
} MOVE_DATA;

typedef struct	//�G�l�~�[���
{
	MOVE_DATA	moveData[ENEMY_POINTER];	//�ړ����
	ENEMY_TYPE	EnemyType;					//�G�l�~�[�^�C�v
} SPAWN_DATA;

typedef struct	//�t�F�[�Y���
{
	SPAWN_DATA	EnemySpawn[MAX_ENEMY];
} PHASE_DATA;


//=============================================================================
// �N���X��`
//=============================================================================
class CStage
{
public:

	CStage();	//�R���X�g���N�^
	~CStage();	//�f�X�g���N�^

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Result(STAGE_TYPE stage);	// ���U���g
	void			SetEnemyCount(int nConut);	// �G�l�~�[�J�E���g�Z�b�g
	void			EnemeyCreate(void);			// �G�l�~�[�N���G�C�g
	static void		LoadFile(void);				// ���[�h�t�@�C��
	virtual void	StageMode(void) = 0;		// �G�l�~�[�̃X�|�[�����[�h

private:
	int					m_nCountEnemy;							// �G�l�~�[�o���܂ł̃J�E���g
	static PHASE_DATA	m_Enemy[ENEMY_CREATE_MAX][MAX_STAGE];	// �X�e�[�W�̃G�l�~�[�o���f�[�^
	static char*		pFileName[STAGE_TYPE_MAX];				// �t�@�C���l�[��
};
#endif
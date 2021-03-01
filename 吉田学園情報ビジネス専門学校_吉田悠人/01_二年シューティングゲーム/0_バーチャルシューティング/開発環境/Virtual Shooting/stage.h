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
class CBossBase;
class CEnemyBase;
class CScore;

typedef enum	//�G�l�~�[�̏o�����[�h
{
	ENEMY_CREATE_NULL = -1,	//�������
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

typedef struct	//�G�l�~�[�f�[�^
{
	ENEMY_TYPE				EnemyType;			// �^�C�v
	ENEMY_MOVE_PATTERN		EnemyMovePattern;	// �s���p�^�[��
	ENEMY_ATTACK_PATTERN	EnemyAttack;		// �U���p�^�[��
	int						nSpwan;				// �o���܂ł̎���
	int						nActionTime;		// �A�N�V�����^�C��
	int						nAttackTime;		// �U���܂ł̃^�C��
	int						nReturnTime;		// �߂�܂ł̃^�C��
	D3DXVECTOR3				pos;				// �ŏ��̏o���ʒu
	float					fSpeed;				// �X�s�[�h
	int						nLife;				// �̗�
}ENEMY_DATA;

typedef struct	//�t�F�[�Y���
{
	ENEMY_DATA	EnemySpawn[MAX_ENEMY];			// �G�l�~�[�f�[�^
	int			nEnemyCount;					// �ő�G�l�~�[��
	int			nPhaseCount;					// ���̃t�F�[�Y�܂ł̎���
} PHASE_DATA;

typedef struct //�X�e�[�W���
{
	PHASE_DATA	Phase[ENEMY_CREATE_MAX];		// �t�F�[�Y���
	int			nCountPhase;					// �ő�t�F�[�Y
}STAGE_DATA;


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
	void			WarningCreate(void);				// �{�X�o�����o����
	void			Result(STAGE_TYPE stage);			// ���U���g
	void			SetEnemyCount(int nConut);			// �G�l�~�[�J�E���g�Z�b�g
	void			SetScore(CScore* pScore);			// �X�R�A�|�C���^�Z�b�^�[
	void			EnemeyCreate(void);					// �G�l�~�[�N���G�C�g
	static void		LoadEnemyData(void);				// �G�N�Z������G�l�~�[�f�[�^�擾
	virtual void	StageMode(void) = 0;				// �G�l�~�[�̃X�|�[�����[�h
	STAGE_DATA		GetStageEnemy(STAGE_TYPE stage);	// �X�e�[�W�G�l�~�[�f�[�^�Q�b�^�[
	bool			BossSearch(void);					// �{�X�����邩
private:
	int					m_nCountEnemy;				// �G�l�~�[�o���܂ł̃J�E���g
	static STAGE_DATA	m_Stage[STAGE_TYPE_MAX];	// �X�e�[�W�̃G�l�~�[�o���f�[�^
	static char*		pFileName[STAGE_TYPE_MAX];	// �t�@�C���l�[��
	CScore*				m_pScore;					// �X�R�A�|�C���^
	ENEMY_DATA			m_Enemy[MAX_ENEMY];			// �G�l�~�[�f�[�^�ۑ�

};
#endif
//=============================================================================
//
// �G�l�~�[�x�[�X���� [enemy base.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define ENEMY_POINTER (5)	//�G�l�~�[�̍ő�ړ��|�C���^
//=============================================================================
//�O���錾
//=============================================================================
class CShotsBase;
typedef enum						//�G�l�~�[�^�C�v
{
	ENEMY_TYPE_1 = 0,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
	ENEMY_TYPE_4,
	ENEMY_TYPE_MAX
}ENEMY_TYPE;

typedef enum						//�G�l�~�[�s���p�^�[��
{
	ENEMY_MOVE_RETURN = 0,			//U�^�[��
	ENEMY_MOVE_STRAIGHT,			//���i
	ENEMY_MOVE_RIGHT,				//�E�ɋȂ���
	ENEMY_MOVE_LEFT,				//���ɋȂ���
	ENEMY_MOVE_RIGHT_SLIDE,			//�E�Ɍ������ĉ��ړ�
	ENEMY_MOVE_LEFT_SLIDE,			//���Ɍ������ĉ��ړ�
	ENEMY_MOVE_MAX,
}ENEMY_MOVE_PATTERN;

typedef enum						//�G�l�~�[�p�^�[��
{
	BULLET_PATTERN_NONE = 0,		//NULL
	BULLET_PATTERN_SHOTS,			//�ʏ�V���b�g
	BULLET_PATTERN_SPIRAL,			//�����V���b�g
	BULLET_PATTERN_MAX				
}ENEMY_ATTACK_PATTERN;

//=============================================================================
// �N���X��`
//=============================================================================
class CEnemyBase :public CScene2d
{
public:

	CEnemyBase(int nPriorit = PRIORITY_OBJECT_1);	//�R���X�g���N�^
	~CEnemyBase();									//�f�X�g���N�^	

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��

	HRESULT Init(void);				// ����������
	void	Uninit(void);			// �I������
	void	Update(void);			// �X�V����
	void	Draw(void);				// �`�揈��
	void	StatasManage(void);		// ��ԊǗ�
	void	Damage(int nDamage);	// �_���[�W����
	void	Hit(void);				// �����蔻��
	void	Move(void);				// �ړ�����
	void	Rotate(void);			// ��]����
	void	Bullet(void);			// �V���b�g����

	void		SetMovePattern(ENEMY_MOVE_PATTERN MovePattern);			// �s���p�^�[���Z�b�^�[
	void		SetAttackPattern(ENEMY_ATTACK_PATTERN AttackPaattern);	// �U���p�^�[���Z�b�^�[
	void		SetInTime(int nInTime);			// �o�����ԃZ�b�^�[
	void		SetActionTime(int nActionTime);	// �s�����ԃZ�b�^�[
	void		SetAttackTime(int nAttackTime);	// �U�����ԃZ�b�^�[
	void		SetOutTime(int nOutTime);		// �A�Ҏ��ԃZ�b�^�[

	void		SetLife(int nLife);				// ���C�t�Z�b�^�[
	int			GetLife(void);					// ���C�t�Q�b�^�[
	void		SetScore(int nScore);			// �X�R�A�Z�b�^�[
	int			GetScore(void);					// �X�R�A�Q�b�^�[
	void		SetSpeed(float nSpeed);			// �X�s�[�h�Z�b�^�[
	float		GetSpeed(void);					// �X�s�[�h�Q�b�^�[

private:
	typedef enum				// �G�l�~�[�̏��
	{
		STATS_MODE_NORMAL = 0,	// �ʏ���
		STATS_MODE_DAMAGE,		// �_���[�W���
		STATS_MODE_DEATH		// ��
	}STATS_MODE;

	ENEMY_MOVE_PATTERN		m_MovePattern;				// �ړ��p�^�[��	
	ENEMY_ATTACK_PATTERN	m_Shots;					// �V���b�g�^�C�v

	int					m_nInTime;						// ��ʂɓ����Ă���܂�
	int					m_nActionTime;					// �s�����N�����܂ł̃^�C��
	int					m_nAttackTime;					// �U���܂ł̎���
	int					m_nOutTime;						// �A�҃^�C��
	int					m_nCount;						// �J�E���g
	int					m_nLife;						// �G�l�~�[�̃��C�t
	float				m_fSpped;						// �G�l�~�[�X�s�[�h

	STATS_MODE			m_Stats;						// �G�l�~�[�̏��
	bool				m_bAttack;						// �U��������
	int					m_Score;						// �X�R�A
	CShotsBase*			m_pShotsBase;					// �V���b�g�|�C���^
	float				m_fRot;							// ��]�p�x

};
#endif
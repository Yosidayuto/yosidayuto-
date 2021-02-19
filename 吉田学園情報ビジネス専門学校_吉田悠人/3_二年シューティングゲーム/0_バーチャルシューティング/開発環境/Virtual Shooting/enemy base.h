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
	ENEMY_TYPE_4
}ENEMY_TYPE;
typedef enum						//�G�l�~�[�p�^�[��
{
	BULLET_PATTERN_NONE = 0,		//NULL
	BULLET_PATTERN_SHOTS,			//�ʏ�V���b�g
	BULLET_PATTERN_SPIRAL,			//�����V���b�g
	BULLET_PATTERN_MAX				//�}�b�N�X
}ENEMY_PATTERN;

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

	void		SetMove(D3DXVECTOR3 move);	// �ړ��ʃZ�b�^�[
	D3DXVECTOR3	GetMove(void);				// �ړ��ʃQ�b�^�[
	void		SetLife(int nLife);			// ���C�t�Z�b�^�[
	int			GetLife(void);				// ���C�t�Q�b�^�[
	void		SetScore(int nScore);		// �X�R�A�Z�b�^�[
	int			GetScore(void);				// �X�R�A�Q�b�^�[
	void		SetMovePointer(D3DXVECTOR3 pointer, int nPointer);	//�ړ��ʒu�Z�b�g
	void			SetPattern(ENEMY_PATTERN type);				//�U���p�^�[���Z�b�^�[
	ENEMY_PATTERN	GetPattern(void);								//�U���p�^�[���Q�b�^�[
private:
	typedef enum	// �G�l�~�[�̏��
	{
		STATS_MODE_NORMAL = 0,	// �ʏ���
		STATS_MODE_DAMAGE,		// �_���[�W���
		STATS_MODE_DEATH		// ��
	}STATS_MODE;

	STATS_MODE			m_Stats;						// �G�l�~�[�̏��
	ENEMY_PATTERN		m_Shots;						// �V���b�g�^�C�v
	D3DXVECTOR3			m_move;							// �ړ���
	int					m_Score;						// �X�R�A
	int					m_nLife;						// �G�l�~�[�̃��C�t
	int					m_nPointer;						// �|�C���^
	D3DXVECTOR3			m_movePointer[ENEMY_POINTER];	// �ړ��n�_�|�C���^�[
	bool				m_bAttack;						// �U��������
	CShotsBase*			m_pShotsBase;					// �V���b�g�|�C���^
};
#endif
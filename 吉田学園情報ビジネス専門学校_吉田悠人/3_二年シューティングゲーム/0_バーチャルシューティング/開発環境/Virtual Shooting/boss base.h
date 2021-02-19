//=============================================================================
//
// �{�X�x�[�X���� [boss base.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _BOSS_BASE_H_
#define _BOSS_BASE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
//�O���錾
//=============================================================================
class CShotsBase;

typedef enum						//�G�l�~�[�^�C�v
{
	BOSS_TYPE_1 = 0,
	BOSS_TYPE_2,
	BOSS_TYPE_3,
	BOSS_TYPE_4
}BOSS_TYPE;
typedef enum						//�G�l�~�[�p�^�[��
{
	BOSS_PATTERN_NONE = 0,		//NULL
	BOSS_PATTERN_SHOTS,			//�ʏ�V���b�g
	BOSS_PATTERN_BUCKSHOT,		//�U�e�V���b�g
	BOSS_PATTERN_All_DIR,		//�S���ʃV���b�g
	BOSS_PATTERN_SPLIT,			//����V���b�g
	BOSS_PATTERN_SPIRAL,		//�����V���b�g
	BOSS_PATTERN_MAX			//�}�b�N�X
}BOSS_PATTERN;

//=============================================================================
// �N���X��`
//=============================================================================
class CBossBase :public CScene2d
{
public:
	CBossBase(int nPriorit = PRIORITY_OBJECT_1);	//�R���X�g���N�^
	~CBossBase();									//�f�X�g���N�^	

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��

	HRESULT Init(void);				// ����������
	void	Uninit(void);			// �I������
	void	Update(void);			// �X�V����
	void	Draw(void);				// �`�揈��
	void	StatasManage(void);		// ��ԊǗ�
	void	Damage(int nDamage);	// �_���[�W����
	void	Hit(void);				// �����蔻��
	void	Bullet(void);			// �{�X�̃V���b�g����
	bool	CoolTime(void);			// �U�����̃N�[���^�C��

	void		SetCoolTime(int nCoolTime);	// �N�[���^�C���Z�b�^�[
	int			GetCoolTime(void);			// �N�[���^�C���Q�b�^�[
	void		SetLife(int nLife);			// ���C�t�Z�b�^�[
	int			GetLife(void);				// ���C�t�Q�b�^�[
	void		SetScore(int nScore);		// �X�R�A�Z�b�^�[
	int			GetScore(void);				// �X�R�A�Q�b�^�[
	void			SetPattern(BOSS_PATTERN type);				//�U���p�^�[���Z�b�^�[
	BOSS_PATTERN	GetPattern(void);								//�U���p�^�[���Q�b�^�[
private:
	typedef enum	// �G�l�~�[�̏��
	{
		STATS_MODE_NORMAL = 0,	// �ʏ���
		STATS_MODE_DAMAGE,		// �_���[�W���
		STATS_MODE_DEATH		// ��
	}STATS_MODE;

	STATS_MODE			m_Stats;			// �G�l�~�[�̏��
	BOSS_PATTERN		m_Shots;			// �V���b�g�^�C�v
	
	int					m_Score;			// �X�R�A
	int					m_nLife;			// �G�l�~�[�̃��C�t
	int					m_nCoolTime;		// �U�����̃N�[���^�C��
	int					m_nLimitCoolTime;	// �N�[���^�C���̍ő�l
	CShotsBase*			m_pShots;			// �V���b�g�|�C���^
};
#endif
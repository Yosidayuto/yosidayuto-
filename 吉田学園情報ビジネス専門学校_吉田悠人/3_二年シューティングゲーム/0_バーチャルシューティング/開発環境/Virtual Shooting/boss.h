//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_BOSS_BULLET (200)	//�ő�o���b�g��

//=============================================================================
//�O���錾
//=============================================================================
class CBossAnime;
class CBulletBase;
//=============================================================================
// �N���X��`
//=============================================================================
class CBoss :public CScene2d
{
public:

	CBoss(int nPriorit = PRIORITY_OBJECT_0);	//�R���X�g���N�^
	~CBoss();					//�f�X�g���N�^	
	typedef enum  //�{�X���
	{
		BOSS_TYPE_1 = 0,
		BOSS_TYPE_2,
		BOSS_TYPE_3,
		BOSS_TYPE_MAX
	}BOSS_TYPE;

	typedef enum	//�{�X�p�^�[��
	{
		BOSS_PATTERN_NONE = 0,	//NULL
		BOSS_PATTERN_STRAIGHT,	//���i
		BOSS_PATTERN_CROSS,		//����
		BOSS_PATTERN_CORNER,	//�Ȃ���
		BOSS_PATTERN_SIDE,		//���ړ�
		BOSS_PATTERN_U_TURN,	//U�^�[��
		BOSS_PATTERN_ROUND_TRIP,//����
		BOSS_PATTERN_MAX		//�}�b�N�X
	}BOSS_PATTERN;
	typedef enum	//�G�l�~�[�p�^�[��
	{
		BULLET_PATTERN_NONE = 0,		//NULL
		BULLET_PATTERN_SHOTS,			//�ʏ�V���b�g
		BULLET_PATTERN_HOMING,			//�ǔ��V���b�g
		BULLET_PATTERN_BUCKSHOT,		//�U�e�V���b�g
		BULLET_PATTERN_SPIRAL,			//�����V���b�g
		BULLET_PATTERN_All_DIR,			//�S���ʃV���b�g
		BULLET_PATTERN_SPLIT,			//����V���b�g
		BULLET_PATTERN_HOMING2,			//�ǔ��V���b�g2
		BULLET_PATTERN_MAX				//�}�b�N�X
	}BOSS_PATTERN_BULLET;


	static HRESULT	Load(void);				//�e�N�X�`���ǂݍ���
	static void		Unload(void);			//�e�N�X�`���̔j��
	static CBoss*	Create(D3DXVECTOR3 Pos, BOSS_TYPE  nType, D3DXVECTOR3 size);//��������

	HRESULT			Init(void);				//����������
	void			Uninit(void);			//�I������
	void			Update(void);			//�X�V����
	void			Draw(void);				//�`�揈��
	void			Damage(int nDamage);	//�_���[�W����
	static bool		GetEnemyNumber(void) { return m_bDie; };	//�G�l�~�[�����񂾂��Q�b�g
private:
	typedef enum	//�G�l�~�[�̏��
	{
		STATS_MODE_NONE = 0,	//NULL
		STATS_MODE_NORMAL,		//�ʏ���
		STATS_MODE_DAMAGE,		//�_���[�W���
		STATS_MODE_DEATH		//��
	}STATS_MODE;

	STATS_MODE		m_Stats;				//�{�X�̏��
	void			StatasManage(void);		//��ԊǗ�

	void		Rotate(void);												//��]����
	void		Bullet(BOSS_PATTERN_BULLET BulletMode, D3DXVECTOR3 Pos);	//�o���b�g����
	D3DXVECTOR3	Tracking(float fSpeed, D3DXVECTOR3 Pos);					//�ǔ�����
	D3DXVECTOR3 Random(float fSpeed);										//�����_������
	float		Spiral(void);												//��������
	void		Hit(D3DXVECTOR3 Pos);										//�����蔻��
		
	static TEXTURE_DATA			m_TextureData[BOSS_TYPE_MAX];	//�e�N�X�`���f�[�^
	D3DXVECTOR3					m_pos;							//�{�X���W
	D3DXVECTOR3					m_move;							//�{�X�̈ړ���
	D3DXVECTOR3					m_size;							//�{�X�̃T�C�Y
	BOSS_TYPE					m_Type;							//�{�X�̃^�C�v
	BOSS_PATTERN_BULLET			m_BulletType;					//�{�X�̍U���p�^�[��
	int							m_nLife;						//�{�X�̃��C�t
	static int					m_EnemyNumber;					//�{�X�̑���
	int							m_PatternCount;					//�p�^�[���̃J�E���g
	bool						m_bBulletMode;					//�U�����I�������
	int							m_nBulletCoolTime;				//�U���̃N�[���^�C��
	static bool					m_bDie;							//�����Ă��邩�ǂ���
	int							nConutBullet[MAX_BOSS_BULLET];	//�o���b�g��
	D3DXVECTOR3					m_rot[MAX_BOSS_BULLET];			//�G�l�~�[�̌���
	bool						m_bBullet[MAX_BOSS_BULLET];		//�g�p���Ă��邩
	CBossAnime					*m_BossAnime;					//�{�X�̃A�j���[�V�����N���X
	CBulletBase					*m_pBullet;						//�o���b�g�N���X

};
#endif

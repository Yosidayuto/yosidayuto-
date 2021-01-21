#ifndef _ENEMY_H_
#define _ENEMY_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"
#include"scene2d.h"
#include "player.h"
//----------------------------------
//�}�N����`
//----------------------------------
#define MAX_ENEMY_BULLET 200
//----------------------------------------------
//�N���X
//----------------------------------------------
class CEnemy:public CScene2d
{
public:

	CEnemy(int nPriorit=3);			//�R���X�g���N�^
	~CEnemy();						//�f�X�g���N�^	
	typedef enum  //�G�l�~�[���
	{
		ENEMY_TYPE_1 = 0,
		ENEMY_TYPE_2,
		ENEMY_TYPE_3,
		ENEMY_TYPE_4,
		ENEMY_TYPE_MAX
	}ENEMY_TYPE;

	typedef enum	//�G�l�~�[�p�^�[��
	{
		PATTERN_MODE_NONE = 0,	//NULL
		PATTERN_MODE_STRAIGHT,	//���i
		PATTERN_MODE_CROSS,		//����
		PATTERN_MODE_CORNER,	//�Ȃ���
		PATTERN_MODE_SIDE,		//���ړ�
		PATTERN_MODE_U_TURN,	//U�^�[��
		PATTERN_MODE_ROUND_TRIP,//����
		PATTERN_MODE_STOP,		//�X�g�b�v
		PATTERN_MODE_MAX		//�}�b�N�X
	}PATTERN_MODE;
	typedef enum	//�G�l�~�[�p�^�[��
	{
		BULLET_PATTERN_NONE = 0,		//NULL
		BULLET_PATTERN_SHOTS,			//�ʏ�V���b�g
		BULLET_PATTERN_HOMING,			//�ǔ��V���b�g
		BULLET_PATTERN_BUCKSHOT,		//�U�e�V���b�g
		BULLET_PATTERN_SPIRAL,			//�����V���b�g
		BULLET_PATTERN_All_DIR,			//�S���ʃV���b�g
		BULLET_PATTERN_MAX				//�}�b�N�X
	}BULLET_PATTERN;


	static CEnemy*	Create(D3DXVECTOR3 Pos, ENEMY_TYPE  nType, 
		PATTERN_MODE nPattern,int nCountPattern=0,
		BULLET_PATTERN BulletMode = BULLET_PATTERN_NONE,
		D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE / 2, PLAYER_SIZE / 2, 0.0f));//��������
	static HRESULT	Load(void);				//�e�N�X�`���ǂݍ���
	static void		Unload(void);			//�e�N�X�`���̔j��

	HRESULT			Init(void);						//����������
	void			Uninit(void);					//�I������
	void			Update(void);					//�X�V����
	void			Draw(void);						//�`�揈��
	void			SetTexture(ENEMY_TYPE nType);	//�e�N�X�`���̐ݒ�
	void			Damage(int nDamage);			//�_���[�W����
private:
	typedef enum	//�G�l�~�[�̏��
	{
		STATS_MODE_NONE = 0,	//NULL
		STATS_MODE_NORMAL,		//�ʏ���
		STATS_MODE_DAMAGE,		//�_���[�W���
		STATS_MODE_DEATH		//��
	}STATS_MODE;

	STATS_MODE		m_Stats;				//�G�l�~�[�̏��
	void			StatasManage(void);		//��ԊǗ�

	void		Rotate(void);								//��]����
	void		Bullet(BULLET_PATTERN BulletMode);			//�o���b�g����
	D3DXVECTOR3	Tracking(float fSpeed);						//�ǔ�����
	D3DXVECTOR3 Random(float fSpeed);						//�����_������
	float Spiral(void);						//��������
	void		Move(D3DXVECTOR3 pos);						//�ړ�����									//�ړ�����
	void		Hit(D3DXVECTOR3 Pos);								//�����蔻��
	static char					*pTexture[ENEMY_TYPE_MAX];	//�e�L�X�g��
	static LPDIRECT3DTEXTURE9	m_Texture[ENEMY_TYPE_MAX];	//�e�N�X�`���̃|�C���^
	D3DXVECTOR3					m_pos;						//�G�l�~�[���W
	D3DXVECTOR3					m_move;						//�G�l�~�[�̈ړ���
	D3DXVECTOR3					m_size;						//�G�l�~�[�̃T�C�Y
	ENEMY_TYPE					m_Type;						//�G�l�~�[�̃^�C�v
	PATTERN_MODE				m_Pattern;					//�G�l�~�[�̍s���p�^�[��
	BULLET_PATTERN				m_BulletMode;				//�o���b�g���[�h
	int							m_nLife;					//�G�l�~�[�̃��C�t
	int							m_nScore;					//�G�l�~�[�̃X�R�A
	int							m_PatternCount;				//�p�^�[���̃J�E���g
	
	int							nConutBullet[MAX_ENEMY_BULLET];	//�o���b�g��
	D3DXVECTOR3					m_rot[MAX_ENEMY_BULLET];	//�G�l�~�[�̌���
	bool						m_bBullet[MAX_ENEMY_BULLET];

};
#endif

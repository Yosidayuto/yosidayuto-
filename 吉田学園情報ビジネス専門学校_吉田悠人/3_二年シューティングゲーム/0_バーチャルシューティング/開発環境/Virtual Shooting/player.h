//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_WEAPON		 (2)	// �v���C���[�̍ő啐����
#define PLAYER_SIZE		 (100)	// �v���C���[�̃T�C�Y

#define PLAYER_LIFE		 (3)	// �������C�t
#define PLAYER_MAX_LIFE  (8)	// �ő僉�C�t
#define PLAYER_LIFE_UP	 (PLAYER_MAX_LIFE-PLAYER_LIFE)			// �ő僉�C�t������

#define PLAYER_SPEED	 (4.0f)	// �����X�s�[�h
#define PLAYER_MAX_SPEED (9.0f)	// �ő�X�s�[�h
#define PLAYER_SPEED_UP	 ((int)(PLAYER_MAX_SPEED-PLAYER_SPEED))	// �X�s�[�h������
//=============================================================================
//�O���錾
//=============================================================================
class CLife;

typedef enum	//�v���C���[�̕���
{
	WEAPONS_MODE_NONE = 0,	//NULL
	WEAPONS_MODE_BUTTOL,	//�o���b�g
	WEAPONS_MODE_LASER,		//���[�U�[
	WEAPONS_MODE_HOMING,	//�z�[�~���O
	WEAPONS_MODE_MAX
}WEAPON_TYPE;

typedef enum	//�v���C���[�̏��
{
	STATS_MODE_NONE = 0,	//NULL
	STATS_MODE_NORMAL,		//�ʏ���
	STATS_MODE_DAMAGE,		//�_���[�W���
	STATS_MODE_DEATH		//��
}STATS_MODE;

typedef struct	//�v���C���[�̕���
{
	WEAPON_TYPE Left;
	WEAPON_TYPE Right;
}WEAPON_DATA;

//=============================================================================
// �N���X��`
//=============================================================================
class CPlayer :public CScene2d
{
public:
	CPlayer(int nPriorit = PRIORITY_OBJECT_0);	//�R���X�g���N�^
	~CPlayer();									//�f�X�g���N�^	

	static CPlayer*	Create(D3DXVECTOR3 Pos);	//��������

	static void		Unload(void);	// �e�N�X�`���̔j��
	static HRESULT	Load(void);		// �e�N�X�`���ǂݍ���
									   
	HRESULT	Init(void);				// ����������
	void	Uninit(void);			// �I������
	void	Update(void);			// �X�V����
	void	Draw(void);				// �`�揈��
	void	Damage(int nDamage);	// �_���[�W����
	
	void	SetLife(int nLife);				// ���C�t�Z�b�^�[
	void	SetSpeed(float fSpeed);			// �X�s�[�h�Z�b�^�[
	void	SetWeapon(WEAPON_DATA wepon);	// �E�F�|���Z�b�^�[

	int			GetLife(void);		// ���C�t�Q�b�^�[
	float		GetSpeed(void);		// �X�s�[�h�Q�b�^�[
	WEAPON_DATA GetWeapon(void);	// �E�F�|���Q�b�^�[	

private:

	void	StatasManage(void);		// ��ԊǗ�����
	void	Move(void);				// �ړ�����
	void	Weapon(void);			// �U�����̕�������

	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
	STATS_MODE			Stats;			// �v���C���[�̏��
	int					m_nLife;		// ���C�t
	CLife*				pLife;			// ���C�t�|�C���^
	float				m_fSpeed;		// �X�s�[�h
	WEAPON_DATA			m_Weapon;		// ����������
	int					m_nAttackCount[MAX_WEAPON];	// �U���܂ł̃J�E���g
};
#endif
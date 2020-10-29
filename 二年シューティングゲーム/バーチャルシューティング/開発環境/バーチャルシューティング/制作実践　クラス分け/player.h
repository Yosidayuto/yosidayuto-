#ifndef _PLAYER_H_
#define _PLAYER_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"
#include"scene2d.h"
//------------------------------------
//�O�u����
//------------------------------------
#define MAX_WEAPON 2
//------------------------------------
//�O�u����
//------------------------------------
class CLife;
//----------------------------------------------
//�N���X
//----------------------------------------------
class CPlayer :public CScene2d
{
public:
	CPlayer(int nPriorit = 4);			//�R���X�g���N�^
	~CPlayer();			//�f�X�g���N�^	
	typedef enum	//�v���C���[�̕���
	{
		WEAPONS_MODE_NONE = 0,	//NULL
		WEAPONS_MODE_BUTTOL,	//�o���b�g
		WEAPONS_MODE_LASER,		//���[�U�[
		WEAPONS_MODE_HOMING,	//�z�[�~���O
		WEAPONS_MODE_MAX
	}WEAPON_MODE;

	static CPlayer*	Create(D3DXVECTOR3 Pos);	//��������
	static void		Unload(void);		//�e�N�X�`���̔j��
	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	
	HRESULT			Init(void);				//����������
	void			Uninit(void);			//�I������
	void			Update(void);			//�X�V����
	void			Draw(void);				//�`�揈��
	void			Set(D3DXVECTOR3 Pos);	//�ݒu�ʒu
	void			Damage(int nDamage);	//�_���[�W����
	int				GetLife(void) { return m_nLife; };//���C�t�Q�b�g
	float			GetSpeed(void) { return m_fSpeed; };//�X�s�[�h�Q�b�g
private:
	void			StatasManage(void);		//��ԊǗ�����
	D3DXVECTOR3		MoveLimit(D3DXVECTOR3 pos, float fAngle);		//�ړ���������
	void			Weapon(D3DXVECTOR3 pos, int nWeapon);
	typedef enum	//�v���C���[�̏��
	{
		STATS_MODE_NONE = 0,	//NULL
		STATS_MODE_NORMAL,		//�ʏ���
		STATS_MODE_DAMAGE,		//�_���[�W���
		STATS_MODE_DEATH		//��
	}STATS_MODE;

	STATS_MODE					Stats;		//�v���C���[�̏��

	static D3DXVECTOR3			posMove;	//�ړ���
	static LPDIRECT3DTEXTURE9	m_pTexture;	//�e�N�X�`���̃|�C���^
	static int					m_nLife;	//���C�t
	static float				m_fSpeed;	//�X�s�[�h
	static WEAPON_MODE			m_Weapon[MAX_WEAPON];//����������
	CLife						*pLife;		//���C�t�|�C���^
	int							nDamageTime;//�_���[�W��Ԃ̖��G����
	int							nCountWeapon[MAX_WEAPON];
};
#endif
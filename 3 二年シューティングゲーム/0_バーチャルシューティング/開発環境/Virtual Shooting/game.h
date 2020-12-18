#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
//------------------------------------
//�}�N����`
//------------------------------------
#define MAX_STAGE 1		//�X�e�[�W��
#define MAX_ENEMY 10	//��ʂɉf��G�l�~�[��
//------------------------------------
//�O�u����
//------------------------------------
class CLife;
class CPlayer;
class CEnemy;
class CBg;
class CScore;
//------------------------------------
//�N���X����
//------------------------------------
class CGame :public CScene
{
public:
	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^
	typedef enum
	{
		STAGE_TYPE_1 = 0,
		STAGE_TYPE_2,
		STAGE_TYPE_3,
		STAGE_TYPE_MAX
	}STAGE_TYPE;


	static CGame*	Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��
	static CLife	*GetLife(void);	//���C�t�擾
	static CScore	*GetScore(void);//�Q�b�g�X�R�A
	static STAGE_TYPE SetStage(void) { return m_StageType; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
private:
	void			EnemeyCreate(void);	//�G�l�~�[�N���G�C�g
	void			StageMode(void);
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
		ENEMY_CREATE_MAX,	//�t�F�[�Y
	}ENEMY_CREATE;
	ENEMY_CREATE	m_EnemyCreate;	//�G�l�~�[�̏o�����[�h
	int				m_nCountEnemy;	//�G�l�~�[�o���܂ł̃J�E���g


	static CLife	*m_Life;				//���C�t�N���X
	static	CPlayer			*m_pPlayer;				//�v���C���[�N���X
	CBg				*m_pBg;					//�w�i�N���X
	static CScore	*m_Score;				//�X�R�A�N���X
	static STAGE_TYPE m_StageType;
};


#endif
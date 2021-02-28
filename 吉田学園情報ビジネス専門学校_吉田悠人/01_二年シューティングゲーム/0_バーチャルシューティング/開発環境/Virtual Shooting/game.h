//=============================================================================
//
// �Q�[������ [game.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//�}�N����`
//=============================================================================
#define STAGE_POS (780)		//�X�e�[�W���S
#define STAGE_SIZE (800)	//�X�e�[�W��X�T�C�Y
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene.h"
//=============================================================================
//�O���錾
//=============================================================================
class CPlayer;
class CScore;
class CStage;
class CGameBgManager;
class CGamePointer;
typedef enum //�X�e�[�W�^�C�v
{
	STAGE_TYPE_1 = 0,	//1�X�e�[�W
	STAGE_TYPE_2,		//2�X�e�[�W
	STAGE_TYPE_3,		//3�X�e�[�W
	STAGE_TYPE_MAX
}STAGE_TYPE;

//=============================================================================
// �N���X��`
//=============================================================================
class CGame 
{
public:
	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^

	static HRESULT	Load(void);		// �e�N�X�`���ǂݍ���
	static void		Unload(void);	// �e�N�X�`���̔j��

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
	static CScore*			GetScore(void);	// �X�R�A�Q�b�^�[
	STAGE_TYPE			GetStageType(void);	// �X�e�[�W�^�C�v�Q�b�^�[
	static void			SetStageType(STAGE_TYPE stage);
	static CPlayer*		GetPlayer(void);
private:
	CGameBgManager*		m_pGameBgManager;	// �Q�[���X�e�[�W�w�i�|�C���^
	CStage*				m_pStage;			// �X�e�[�W�|�C���^
	CGamePointer*		m_pGamePointer;		// �}�E�X�|�C���^�[�̃|�C���^
	static CPlayer*		m_pPlayer;			// �v���C���[�|�C���^
	static CScore*		m_Score;			// �X�R�A�|�C���^
	static STAGE_TYPE	m_StageType;		// �X�e�[�W�^�C�v
};


#endif
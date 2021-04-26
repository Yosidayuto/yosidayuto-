//=============================================================================
//
// �Q�[�� [game.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define SQUARE_SIZE (50)	//�P�}�X�c���̃T�C�Y

//=============================================================================
//  �O���錾
//=============================================================================
class CCamera;
class CPlayer;
class CTalk;
class CStageNumber;
class CStageBase;
//=============================================================================
// �N���X��`
//=============================================================================
class CGame
{
public:
	typedef enum	//�}�b�v���
	{
		MAP_TYPE_1 = 0,
		MAP_TYPE_2,
		MAP_TYPE_3,
		MAP_TYPE_MAX
	}MAP_TYPE;

	CGame();
	~CGame();

	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	void	Uninit(void);

	static void	SetMapMode(MAP_TYPE MapMode);	//�}�b�v���[�h�Z�b�^�[
	static MAP_TYPE GetMapMode(void);			//�}�b�v���[�h�Q�b�^�[z

private:
	CCamera*		m_pCamera;			// �J���|�C���^
	CTalk*			m_pTalk;			// ��bUI
	CStageNumber*	m_pStageNumber;		// �X�e�[�W�i���o�[UI
	static MAP_TYPE	m_MapMode;			// �}�b�v�f�[�^
	static CStageBase*	m_pStage_1;		// �X�e�[�W1�|�C���^
	static CStageBase*	m_pStage_2;		// �X�e�[�W2�|�C���^
	static CStageBase*	m_pStage_3;		// �X�e�[�W3�|�C���^

};
#endif

//=============================================================================
//
// �X�e�[�W [stage base.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _STAGE_BASE_H_
#define _STAGE_BASE_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_STAGE_SIZE_X	(50)	//�ő�u���b�N��
#define MAX_STAGE_SIZE_Y	(50)	//�ő�X�e�[�W�T�C�Y
#define MAX_STAGE_COUNT		(3)		//�ő�X�e�[�W��

//=============================================================================
//  �O���錾
//=============================================================================
class CPlayer;

typedef struct //��s�̃u���b�N���
{
	int			nBlockType[MAX_STAGE_SIZE_X];	//�u���b�N�f�[�^
	int			nStageSizeX;					//���̍s�̃u���b�N��
}BLOCK_DATA;

typedef struct	//�X�e�[�W���
{
	BLOCK_DATA	BlockData[MAX_STAGE_SIZE_Y];	//�u���b�N
	int			nStageSizeY;					//�u���b�N�̗�
}MAP_DATA;

//=============================================================================
// �N���X��`
//=============================================================================
class CStageBase
{
public:

	CStageBase();
	virtual ~CStageBase();
	virtual HRESULT Init(void) = 0;
	virtual void	Uninit(void) = 0;
	virtual void	Draw(void) = 0;
	virtual void	Update(void) = 0;
	
	virtual void	MapCreate(void) = 0;	//�}�b�v�̐���
private:
};
#endif

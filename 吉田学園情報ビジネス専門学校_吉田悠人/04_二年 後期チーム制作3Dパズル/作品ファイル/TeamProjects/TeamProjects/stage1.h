//=============================================================================
//
// �X�e�[�W_1 [stage1.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _STAGE_1_H_
#define _STAGE_1_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
#include "stage base.h"
#include "stagenumber.h"
#include "talk_stage1.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CStage1 :public CStageBase
{
public:
	typedef enum	//�G�l�~�[�̏o�����[�h
	{
		BLOCK_TYPE_NONE = 0,				//�Ȃ�
		BLOCK_TYPE_START,					//�X�^�[�g�n�_
		BLOCK_TYPE_GOAL,					//�S�[���n�_
		BLOCK_TYPE_TILE_RED_SAMD,			//�ԍ��u���b�N
		BLOCK_TYPE_HINDRANCE_BUILDING_1,	//�r��
		BLOCK_TYPE_HINDRANCE_BUILDING_2,	//�r��(����)
		BLOCK_TYPE_ITEM_GARBAGE,			//�S�~�u���b�N
	}BLOCK_TYPE;

	CStage1();
	~CStage1();
	static void	Load(void);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	MapCreate(void);		//�}�b�v�̐���
	void	TitleMapCreate(void);	//�^�C�g���\���p�}�b�v�̐���

	static CTalkStage1* GetTalkStage1(void);

private:
	static char*		m_pFileName;	// �t�@�C���l�[��
	static MAP_DATA		m_pMapData;
	static CTalkStage1*		m_pTalkStage1;
};
#endif
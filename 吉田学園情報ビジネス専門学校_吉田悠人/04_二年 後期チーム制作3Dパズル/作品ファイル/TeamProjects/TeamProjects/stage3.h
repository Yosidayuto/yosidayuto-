//=============================================================================
//
// �X�e�[�W_3 [stage3.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _STAGE_3_H_
#define _STAGE_3_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
#include "stage base.h"
#include "talk_stage3.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CStage3 :public CStageBase
{
public:
	typedef enum	//�G�l�~�[�̏o�����[�h
	{
		BLOCK_TYPE_NONE = 0,				//�Ȃ�
		BLOCK_TYPE_START,					//�X�^�[�g�n�_
		BLOCK_TYPE_GOAL,					//�S�[���n�_
		BLOCK_TYPE_TILE_GRASS,				//���u���b�N
		BLOCK_TYPE_HINDRANCE_BIG_TREE,		//�j�t��(�傫��)
		BLOCK_TYPE_HINDRANCE_SMALL_TREE,	//�j�t��(������)
		BLOCK_TYPE_ITEM_APPLE,				//�����S�u���b�N
		BLOCK_TYPE_ITEM_ORANGES,			//�I�����W�u���b�N
		BLOCK_TYPE_ITEM_GRAPES,				//�u�h�E�u���b�N
		BLOCK_TYPE_ITEM_WATERMELON,			//�X�C�J�u���b�N
	}BLOCK_TYPE;

	CStage3();
	~CStage3();
	static void	Load(void);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	MapCreate(void);	//�}�b�v�̐���

	static CTalkStage3* GetTalkStage3(void);

private:
	static char*			m_pFileName;	// �t�@�C���l�[��
	static MAP_DATA			m_pMapData;
	static CTalkStage3*		m_pTalkStage3;
};
#endif
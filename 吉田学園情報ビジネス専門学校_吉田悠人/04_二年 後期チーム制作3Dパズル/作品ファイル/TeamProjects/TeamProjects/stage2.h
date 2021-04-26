//=============================================================================
//
// �X�e�[�W_2 [stage2.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _STAGE_2_H_
#define _STAGE_2_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
#include "stage base.h"
#include "talk_stage2.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CStage2 :public CStageBase
{
public:
	typedef enum	//�G�l�~�[�̏o�����[�h
	{
		BLOCK_TYPE_NONE = 0,			//�Ȃ�
		BLOCK_TYPE_START,				//�X�^�[�g�n�_
		BLOCK_TYPE_GOAL,				//�S�[���n�_
		BLOCK_TYPE_TILE_SAMD,			//���u���b�N
		BLOCK_TYPE_TILE_SPROUT,			//��u���b�N
		BLOCK_TYPE_ITEM_SEEDS,			//��u���b�N
		BLOCK_TYPE_ITEM_CUBE,			//���u���b�N
		BLOCK_TYPE_ITEM_SAMD_WALL,		//���ǃu���b�N
	}BLOCK_TYPE;

	CStage2();
	~CStage2();
	static void	Load(void);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	MapCreate(void);	//�}�b�v�̐���

	static CTalkStage2* GetTalkStage2(void);

private:
	static char*			m_pFileName;	// �t�@�C���l�[��
	static MAP_DATA			m_pMapData;
	static CTalkStage2*		m_pTalkStage2;
};
#endif
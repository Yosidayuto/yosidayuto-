//=============================================================================
//
//	�g�[�N�X�e�[�W1 [talk_stage1.h]
//	Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TALK_STAGE1_H_
#define _TALK_STAGE1_H_

//====================================
//�C���N���[�h
//====================================
#include "main.h"
#include "talk_stage_base.h"

//====================================
//�O���錾
//====================================
class CTutorial;
class CTalkbase;
//====================================
// �N���X��`
//====================================
class CTalkStage1:public CTalkStageBese
{
public:
	// ��bUI�̎��
	typedef enum
	{
		TALK_NONE = -1,
		TALK_1,
		TALK_2,
		TALK_3,
		TALK_4,
		TALK_5,
		TALK_MAX
	}TALK_DATA;



	CTalkStage1(int nPriorit = PRIORITY_UI_0);
	static CTalkStage1 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void	Update(void);

private:
	CTalkbase* pTalk;	//�g�[�N1�̃|�C���^
	TALK_DATA TalkData;	//�g�[�N�f�[�^
};
#endif // !_UI_H_

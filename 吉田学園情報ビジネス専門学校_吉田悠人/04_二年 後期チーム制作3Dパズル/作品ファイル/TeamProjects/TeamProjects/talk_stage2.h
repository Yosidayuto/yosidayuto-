//=============================================================================
//
//	�g�[�N�X�e�[�W2 [talk_stage2.h]
//	Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TALK_STAGE2_H_
#define _TALK_STAGE2_H_

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
class CTalkStage2 :public CTalkStageBese
{
public:
	// ��bUI�̎��
	typedef enum
	{
		TALK_NONE = -1,
		TALK_6,
		TALK_7,
		TALK_8,
		TALK_MAX
	}TALK_DATA;



	CTalkStage2(int nPriorit = PRIORITY_UI_0);
	static CTalkStage2 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void	Update(void);

private:
	CTalkbase* pTalk;	//�g�[�N�̃|�C���^
	TALK_DATA TalkData;	//�g�[�N�f�[�^
};
#endif // !_UI_H_

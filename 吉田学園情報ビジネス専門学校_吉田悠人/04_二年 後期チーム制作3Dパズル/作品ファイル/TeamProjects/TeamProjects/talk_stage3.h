//=============================================================================
//
//	�g�[�N�X�e�[�W3 [talk_stage3.h]
//	Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TALK_STAGE3_H_
#define _TALK_STAGE3_H_

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
class CTalkStage3 :public CTalkStageBese
{
public:
	// ��bUI�̎��
	typedef enum
	{
		TALK_NONE = -1,
		TALK_9,
		TALK_10,
		TALK_11,
		TALK_12,
		TALK_MAX
	}TALK_DATA;



	CTalkStage3(int nPriorit = PRIORITY_UI_0);
	static CTalkStage3 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void	Update(void);

private:
	CTalkbase* pTalk;	//�g�[�N�̃|�C���^
	TALK_DATA TalkData;	//�g�[�N�f�[�^
};
#endif // !_UI_H_

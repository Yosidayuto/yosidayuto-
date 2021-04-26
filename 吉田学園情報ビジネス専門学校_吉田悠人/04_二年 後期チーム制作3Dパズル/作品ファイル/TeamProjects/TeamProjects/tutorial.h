//=============================================================================
//
//	�`���[�g���A�� [tutorial.h]
//	Author : ��؁@����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//====================================
//�C���N���[�h
//====================================
#include "main.h"
#include "ui.h"

//====================================
// �N���X��`
//====================================

//UI�N���X
class CTutorial : public CUi
{
public:
	CTutorial(int nPriorit = PRIORITY_UI_0);
	~CTutorial();

	static CTutorial *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TutorialUninit(void);
private:
	CObject2D* m_pObject2d;
	const int m_nTexture = 30;			// �e�N�X�`���ԍ�

};
#endif // !_UI_H_
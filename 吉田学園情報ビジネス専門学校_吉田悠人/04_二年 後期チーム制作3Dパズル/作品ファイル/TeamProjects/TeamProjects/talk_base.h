//=============================================================================
//
//	�Z���t�e�N���X[talk_bass.h]
//	Author:����@�r�H
//
//=============================================================================

// ��d�C���N���[�h�h�~
#ifndef _TALK_BASS_H_
#define _TALK_BASS_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "ui.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CTalkbase :public CUi
{
public:

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}TALK_FADE;

	CTalkbase(int nPriorit = PRIORITY_UI_0);	// �R���X�g���N�^
	~CTalkbase();								// �f�X�g���N�^

	HRESULT		Init(void);				// ����������
	void		Uninit(void);			// �I������
	void		Update(void);			// �X�V����

	virtual void Talk(void);			// �g�[�N�����ɐi�߂�֐�
	void		Blackout(void);			// �t�F�[�h�C���E�A�E�g�̏���

	void		SetAppear(int nAppear);			// �o�����ԃZ�b�^�[
	int			GetAppear(void);				// �o�����ԃQ�b�^�[
	void		SetFade(TALK_FADE FadeStatus);	// �t�F�[�h��ԃZ�b�^�[
	TALK_FADE	GetFade(void);					// �t�F�[�h��ԃQ�b�^�[
	bool		GetTalkEnd(void);				// �I�����Ă��邩

private:
	D3DXCOLOR		m_col;			// �J���[
	bool			m_bTalkEnd;		// �I�����Ă��邩
	int				m_nAppear;		// �o������

protected:
	TALK_FADE					m_Fade;					// �����̓��ߏ�
	int							m_nTalkCount;			// �����܂ł̃J�E���g

};
#endif

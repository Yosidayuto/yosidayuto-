//=============================================================================
//
//  �|�[�Y�{�^���}�l�[�W���[[pause button manager.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _PAUSE_BUTTON_MANAGER_H_
#define _PAUSE_BUTTON_MANAGER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_BUTTON (2)
//=============================================================================
//�O���錾
//=============================================================================
class CButton;

typedef enum	//�{�^���̎��
{
	BUTTON_TYPE_START = 0,	//�ĊJ
	BUTTON_TYPE_RESTART,	//���X�^�[�g
	BUTTON_TYPE_END,		//�I��
	BUTTON_TYPE_MAX
}BUTTON_TYPE;
//=============================================================================
// �N���X��`
//=============================================================================
class CPauseButtonManager :public CObject
{
public:
	CPauseButtonManager();	//�R���X�g���N�^
	~CPauseButtonManager();	//�f�X�g���N�^

	static CPauseButtonManager*	Create(void);

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
	void			Select(void);	// �I������
	void			Over(void);		// �I�������{�^���̏���
private:
	CButton*		m_pButton[BUTTON_TYPE_MAX];	// �{�^���|�C���^
	int				m_nButtonSelect;			// �I�����Ă���{�^��
	bool			m_bStick;					// �X�e�B�b�N
};
#endif

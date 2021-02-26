//=============================================================================
//
//	�{�^��[button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _BUTTONP_H_
#define _BUTTONP_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "inputmouse.h"
#include "scene2d.h"

//=============================================================================
//�O���錾
//=============================================================================
typedef enum  //�{�^���e�N�X�`�����
{
	BUTTON_STATE_NORMAL =0,
	BUTTON_STATE_PUSH,
	BUTTON_STATE_MAX
}BUTTON_STATE;

//=============================================================================
// �N���X��`
//=============================================================================
class CButton :public CScene2d
{
public:

	CButton(int nPriorit = PRIORITY_UI_0);	// �R���X�g���N�^
	~CButton();								// �f�X�g���N�^
	static HRESULT	Load(void);
	static void		Unload(void);

	HRESULT		Init(void);				// ����������
	void		Uninit(void);			// �I������
	void		Update(void);			// �X�V����
	void		Draw(void);				// �`�揈��
	bool		Hit(void);				// �����蔻��
	
	virtual void MouseOver(void) = 0;	// �}�E�X�I�[�o�[����
	virtual void Push(void) = 0;		// �v�b�V�����菈��

private:
	static TEXTURE_DATA	m_TextureData[BUTTON_STATE_MAX];	//�e�N�X�`���f�[�^
	CScene2d*			m_pScene2d;					//�I�u�W�F�N�g�|�C���^
	
};
#endif

//=============================================================================
//
//	�{�^���}�l�[�W���[[button manager.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _BUTTON_MANAGER_H_
#define _BUTTON_MANAGER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_BUTTON (6)
//=============================================================================
//�O���錾
//=============================================================================
class CButton;

typedef enum	//�{�^���̎��
{
	BUTTON_TYPE_START = 0,	//�X�^�[�g
	BUTTON_TYPE_LIFE,		//���C�t
	BUTTON_TYPE_SPEED,		//�X�s�[�h
	BUTTON_TYPE_BUTTOL,		//�o���b�g
	BUTTON_TYPE_LASER,		//���[�U�[
	BUTTON_TYPE_HOMING,		//�z�[�~���O
	BUTTON_TYPE_MAX
}BUTTON_TYPE;
//=============================================================================
// �N���X��`
//=============================================================================
class CButtonManager :public CScene
{
public:
	CButtonManager();	//�R���X�g���N�^
	~CButtonManager();	//�f�X�g���N�^

	static HRESULT			Load(void);		
	static void				Unload(void);
	static CButtonManager*	Create(void);

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��

	void			MouseOut(void);	// �e���b�v�̐ؑ�
private:
	CButton*		m_pButton[BUTTON_TYPE_MAX];	// �{�^���|�C���^

};
#endif

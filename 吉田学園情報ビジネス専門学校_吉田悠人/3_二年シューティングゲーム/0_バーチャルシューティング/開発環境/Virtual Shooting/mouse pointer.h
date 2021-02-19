//=============================================================================
//
// �}�E�X�|�C���^�[ [mouse pointer.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _MOUSE_POINTER_H_
#define _MOUSE_POINTER_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "scene2D.h"


//=============================================================================
// �N���X��`
//=============================================================================
class CPointer : public CScene2d
{
public:

	CPointer(int nPriorit = PRIORITY_UI_3);			// �R���X�g���N�^
	~CPointer();									// �f�X�g���N�^
	static HRESULT	 Load(void);					// �e�N�X�`���ǂݍ���
	static void		 Unload(void);					// �e�N�X�`���j��
	HRESULT Init(void);								// ����������
	void	Uninit(void);							// �I������
	void	Update(void);							// �X�V����
	void	Draw(void);								// �`�揈��
	void	MouseMove(void);						// �}�E�X�Ǐ]����
private:

};



#endif // !_POLYGON_H_

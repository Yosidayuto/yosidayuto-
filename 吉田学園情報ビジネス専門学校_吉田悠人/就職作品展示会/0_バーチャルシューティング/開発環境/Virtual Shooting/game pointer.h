//=============================================================================
//
// �Q�[���̃}�E�X�|�C���^�[ [game pointer.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _GAME_POINTER_H_
#define _GAME_POINTER_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "mouse pointer.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CGamePointer : public CPointer
{
public:

	CGamePointer();							// �R���X�g���N�^
	~CGamePointer();						// �f�X�g���N�^
	static HRESULT			Load(void);		// �e�N�X�`���ǂݍ���
	static void				Unload(void);	// �e�N�X�`���j��
	static CGamePointer*	Create(void);	// �쐬����
	HRESULT Init(void);						// ����������
	void	Uninit(void);					// �I������
	void	Update(void);					// �X�V����
	void	Draw(void);						// �`�揈��

private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^
};
#endif // !_POLYGON_H_

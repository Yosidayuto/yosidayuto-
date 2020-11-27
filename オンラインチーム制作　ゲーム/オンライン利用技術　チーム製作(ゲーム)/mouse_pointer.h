#ifndef _MOUSE_POINTER_H_
#define _MOUSE_POINTER_H_


#define MOUSE_POINTER "data/TEXTURE/brush1.png"	// �e�N�X�`���p�X

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�E�X�|�C���^�[�N���X
//*****************************************************************************
class CPointer : public CScene2D
{
public:
	CPointer();										// �R���X�g���N�^
	~CPointer();									// �f�X�g���N�^
	static HRESULT Load(void);						// �e�N�X�`���ǂݍ���
	static void Unload(void);						// �e�N�X�`���j��

	static CPointer *Create(void);					// �쐬����

	HRESULT Init(void);								// ����������
	void	Uninit(void);							// �I������
	void	Update(void);							// �X�V����
	void	Draw(void);								// �`�揈��

private:


	static LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^

	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_size;								// �T�C�Y

};



#endif // !_POLYGON_H_

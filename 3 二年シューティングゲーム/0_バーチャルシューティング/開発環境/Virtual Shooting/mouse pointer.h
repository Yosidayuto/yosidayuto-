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
class CPointer : public CScene2d
{
public:
	typedef enum  //�}�E�X�|�C���^�[���
	{
		POINTER_TYPE_SELECR = 0,
		POINTER_TYPE_GAME,
		POINTER_TYPE_MAX
	}POINTER_TYPE;

	CPointer(int nPriorit = 5);										// �R���X�g���N�^
	~CPointer();									// �f�X�g���N�^
	static HRESULT Load(void);						// �e�N�X�`���ǂݍ���
	static void Unload(void);						// �e�N�X�`���j��

	static CPointer *Create(POINTER_TYPE Type);					// �쐬����

	HRESULT Init(POINTER_TYPE Type);								// ����������
	void	Uninit(void);							// �I������
	void	Update(void);							// �X�V����
	void	Draw(void);								// �`�揈��

private:


	static LPDIRECT3DTEXTURE9	m_pTexture[POINTER_TYPE_MAX];	// �e�N�X�`���̃|�C���^
	static char					*pTexture[POINTER_TYPE_MAX];	// �e�L�X�g��

	POINTER_TYPE				m_Type;							// �^�C�v
	D3DXVECTOR3					m_pos;							// �ʒu
	D3DXVECTOR3					m_size;							// �T�C�Y

};



#endif // !_POLYGON_H_

#ifndef _DIE_SCREEN_H_
#define _DIE_SCREEN_H_
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DIE_SCREEN "data/TEXTURE/die_001.png"// �|���S���̃e�N�X�`���p�X

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �|���S���N���X
//*****************************************************************************
class CDieScreen : public CScene2D
{
public:
	CDieScreen();													// �R���X�g���N�^
	~CDieScreen();													// �f�X�g���N�^
	static HRESULT Load(void);									// �e�N�X�`���ǂݍ���
	static void Unload(void);									// �e�N�X�`���j��
	static CDieScreen *Create(void);	// �쐬����

	HRESULT Init(void);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;						// �e�N�X�`���̃|�C���^
};




#endif // !_DIE_SCREEN_H_




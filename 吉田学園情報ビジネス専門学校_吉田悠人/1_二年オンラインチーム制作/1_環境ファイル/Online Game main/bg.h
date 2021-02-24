//=============================================================================
//
// �w�i�̏��� [bg.h]
// Author : �U�J �����Y
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE		(4)								// �e�N�X�`���̍ő吔
#define BG1_TEXTURE		"data/TEXTURE/bg001.png"		// �w�i1�̃e�N�X�`���p�X
#define BG2_TEXTURE		"data/TEXTURE/wani_body001.png"	// �w�i2�̃e�N�X�`���p�X
#define BG3_TEXTURE		"data/TEXTURE/wani_head001.png"	// �w�i3�̃e�N�X�`���p�X
#define BG4_TEXTURE		"data/TEXTURE/wani_eye001.png"	// �w�i4�̃e�N�X�`���p�X


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// �w�i�N���X
//*****************************************************************************
class CBg : public CScene
{
public:
	CBg();													// �R���X�g���N�^
	~CBg();													// �f�X�g���N�^
	static HRESULT Load(void);								// �e�N�X�`���ǂݍ���
	static void Unload(void);								// �e�N�X�`���j��
	static CBg *Create(D3DXVECTOR3 size);					// �쐬����
	HRESULT Init(D3DXVECTOR3 size);							// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];		// �e�N�X�`���̃|�C���^
	CScene2D *m_apScene2D[MAX_TEXTURE];						// Scene2D�̃|�C���^
	D3DXVECTOR3 m_pos;										// �w�i�̈ʒu
};




#endif // !_BG_H_






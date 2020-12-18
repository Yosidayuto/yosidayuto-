//=============================================================================
//
// ���̃e�N�X�`������ [tooth.h]
// Author : �U�J �����Y
//
//=============================================================================
#ifndef _TOOTH_H_
#define _TOOTH_H_


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_TEXTURE	"data/TEXTURE/teeth001.png"// �|���S���̃e�N�X�`���p�X
#define MAX_POLYGON_TEX	(25)

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �|���S���N���X
//*****************************************************************************
class CTooth : public CScene2D
{
public:
	CTooth();													// �R���X�g���N�^
	~CTooth();													// �f�X�g���N�^
	static HRESULT Load(void);									// �e�N�X�`���ǂݍ���
	static void Unload(void);									// �e�N�X�`���j��
	static CTooth *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �쐬����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	void Color(void);											// �J���[�ύX
	void SetRotation(float fAngle);								// �e�N�X�`����]

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;						// �e�N�X�`���̃|�C���^

	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3 m_size;											// �T�C�Y
};




#endif // !_TOOTH_H_




//=============================================================================
//
//	���C�t�^���N[life tank.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _LIFE_ICON_H_
#define _LIFE_ICON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "texture.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CLifeTank :public CTexture
{
public:
	CLifeTank();	//�R���X�g���N�^
	~CLifeTank();	//�f�X�g���N�^

	static HRESULT		Load(void);
	static void			Unload(void);
	static CLifeTank*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
private:
	static TEXTURE_ICON	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif

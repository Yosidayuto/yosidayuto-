//=============================================================================
//
//	�z�[�~���O�A�C�R��[homing icon.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _HOMING_ICON_H_
#define _HOMING_ICON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "texture.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CHomingIcon :public CTexture
{
public:
	CHomingIcon();	//�R���X�g���N�^
	~CHomingIcon();	//�f�X�g���N�^

	static HRESULT			Load(void);
	static void				Unload(void);
	static CHomingIcon*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
private:
	static TEXTURE_ICON	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif

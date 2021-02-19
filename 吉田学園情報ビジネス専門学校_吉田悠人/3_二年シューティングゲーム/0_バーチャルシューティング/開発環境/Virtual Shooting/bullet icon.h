//=============================================================================
//
//	�o���b�g�A�C�R��[bullet icon.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _BULLET_ICON_H_
#define _BULLET_ICON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "texture.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBulletIcon :public CTexture
{
public:
	CBulletIcon();	//�R���X�g���N�^
	~CBulletIcon();	//�f�X�g���N�^

	static HRESULT			Load(void);
	static void				Unload(void);
	static CBulletIcon*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
private:
	static TEXTURE_ICON	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif

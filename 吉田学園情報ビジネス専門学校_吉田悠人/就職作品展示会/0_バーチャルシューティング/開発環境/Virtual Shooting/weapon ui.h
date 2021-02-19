//=============================================================================
//
//	�E�F�|��UI[weapon ui.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _WEAPON_UI_H_
#define _WEAPON_UI_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "player.h"
//=============================================================================
//�O���錾
//=============================================================================
class CTexture;

//=============================================================================
// �N���X��`
//=============================================================================
class CWeaponUi :public CScene2d
{
public:

	CWeaponUi(int nPriorit = PRIORITY_UI_1);	// �R���X�g���N�^
	~CWeaponUi();								// �f�X�g���N�^

	static HRESULT		Load(void);
	static void			Unload(void);
	static CWeaponUi*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT		Init(void);		// ����������
	void		Uninit(void);	// �I������
	void		Update(void);	// �X�V����
	void		Draw(void);		// �`�揈��
	
	WEAPON_TYPE GetIconType(void);				// �^�C�v�Z�b�^�[
	void		TypeChange(WEAPON_TYPE Type);	// �A�C�R���̐ؑց@
private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
	WEAPON_TYPE			m_IconType;		// �A�C�R���^�C�v
	CTexture*			m_pWeaponIcon;	// �A�C�R���|�C���^
};
#endif

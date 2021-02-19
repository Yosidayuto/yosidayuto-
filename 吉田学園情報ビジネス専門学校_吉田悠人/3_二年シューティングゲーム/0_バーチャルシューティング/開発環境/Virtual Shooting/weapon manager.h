//=============================================================================
//
//	�E�F�|���}�l�[�W���[[weapon manager.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _WEAPON_MANAGER_H_
#define _WEAPON_MANAGER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "texture.h"
#include "player.h"
//=============================================================================
//�O���錾
//=============================================================================
class CWeaponUi;

//=============================================================================
// �N���X��`
//=============================================================================
class CWeaponManager:public CScene
{
public:
	CWeaponManager();	//�R���X�g���N�^
	~CWeaponManager();	//�f�X�g���N�^

	static HRESULT			Load(void);
	static void				Unload(void);
	static CWeaponManager*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
private:
	CWeaponUi*		m_pWeaponUi[MAX_WEAPON];	// �E�F�|��UI�|�C���^
	D3DXVECTOR3		m_pos;						// �ʒu
	D3DXVECTOR3		m_size;						// �T�C�Y
};
#endif

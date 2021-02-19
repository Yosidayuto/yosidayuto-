//=============================================================================
//
//	�v���C���[�f�[�^[player data.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _PLAYER_DATA_H_
#define _PLAYER_DATA_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "player.h"

//=============================================================================
//�O���錾
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CPlayerData
{
public:
	CPlayerData();	// �R���X�g���N�^
	~CPlayerData();	// �f�X�g���N�^

	void		Uninit(void);					// �I������

	void		SetLifeData(int nLife);				// ���C�t�f�[�^�Z�b�^�[
	void		SetSpeedData(float fSpeed);			// �X�s�[�h�f�[�^�Z�b�^�[
	void		SetWeaponData(WEAPON_DATA wepon);	// �E�F�|���f�[�^�Z�b�^�[

	int			GetLifeData(void);					// ���C�t�f�[�^�Q�b�^�[
	float		GetSpeedData(void);					// �X�s�[�h�f�[�^�Q�b�^�[
	WEAPON_DATA GetWeaponData(void);				// �E�F�|���f�[�^�Q�b�^�[	

private:
	int					m_nLifeData;		// ���C�t�f�[�^
	float				m_fSpeedData;		// �X�s�[�h�f�[�^
	WEAPON_DATA			m_WeaponData;		// �����������f�[�^
};
#endif

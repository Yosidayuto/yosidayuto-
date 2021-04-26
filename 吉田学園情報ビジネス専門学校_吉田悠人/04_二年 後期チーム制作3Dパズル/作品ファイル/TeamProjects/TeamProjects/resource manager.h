//=============================================================================
//
// ���\�[�X�}�l�[�W���[ [reource manager.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "model.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CResource
{
public:

	CResource();
	~CResource();

	HRESULT Init(void);
	void	Uninit(void);
	LPDIRECT3DTEXTURE9	TextureLoad(int nTexture);	// �e�N�X�`�����[�h
	void	TextureUnLoad(void);					// �e�N�X�`���A�����[�h
	void	TextureFail(void);						// �e�N�X�`���ǂݍ��݃t�@�C��
	CModel::MODELDATA ModelLoad(int nModel);		// ���f�����[�h
	void	ModelUnLoad(void);						// ���f���A�����[�h
	void	XFail(void);							// X�t�@�C���ǂݍ��݃t�@�C��

private:
	char				m_pcTextureName[256];	// �t�@�C���̖��O

	int*				m_npTexture;			// �e�N�X�`���ԍ�
	int					m_nMaxTexture;			// �e�N�X�`���̑���
	LPDIRECT3DTEXTURE9*	m_pTexture;				// �e�N�X�`���ւ̃|�C���^

	int*				m_npModel;				// ���f���ԍ�
	int					m_nMaxModel;			// ���f���̑���
	CModel::MODELDATA*	m_pModel;			// ���f���ւ̃|�C���^

};
#endif

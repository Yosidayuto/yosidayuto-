//=============================================================================
//
// �`���C���h [child.h]
// Author : ���V ����
//
//=============================================================================
#ifndef _CHILD_H_
#define _CHILD_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
#include "object3d.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================
class CModel;

//=============================================================================
// �N���X��`
//=============================================================================
class CChild : public CObject3D
{
public:
	CChild();
	~CChild();
	static HRESULT	Load(void);
	static void		Unload(void);
	static CChild*	Create(CModel* modelPearent ,D3DXVECTOR3 rot, D3DXVECTOR3 size = D3DXVECTOR3(1.0f, 1.0f, 1.0f));//����:�e���f��,��],�T�C�Y
	HRESULT Init(void);   // ����������
	void	Uninit(void); // �I������
	void	Update(void); // �X�V����
	void	Draw(void);   // �`�揈��

	//void FadeTalk(void);

	CModel* GetModel(void) { return m_model; }	 // ���f���̎擾
	bool GetIsActive(void) { return m_bActive; } // �L���t���O�̎擾����

private:
	void CollisionItem(void);				// �A�C�e���Ƃ̂���������
	
	CModel* m_modelPearent;                 // �e���f��
	CModel* m_model;		                // ���f���|�C���^
	bool m_bActive;                         // �L���t���O
	static CModel::MODELDATA m_modeldata;	// ���f���f�[�^
	bool m_bFlag;
};
#endif
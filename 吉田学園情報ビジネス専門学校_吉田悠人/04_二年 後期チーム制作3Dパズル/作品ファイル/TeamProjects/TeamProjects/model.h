//=============================================================================
//
//	���f���f�[�^����[model.h]
//	Author:�g�c�I�l
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object3d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_MATERIAL (30)
//=============================================================================
//�N���X��`
//=============================================================================
class CModel : public CObject3D
{
public:

	typedef struct
	{
		LPD3DXBUFFER pBuffMat;                        // �}�e���A�����ւ̃|�C���^
		DWORD nNumMat;                                // �}�e���A�����̐�
		LPD3DXMESH pMesh;                             // ���b�V�����ւ̃|�C���^
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // �e�N�X�`���ւ̃|�C���^
		D3DXMATRIX mtxWorld;                          // �A�j���[�V�������
	} MODELDATA;

    CModel();
    virtual ~CModel();
    virtual HRESULT Init(void);
    virtual void	Uninit(void);
    virtual void	Update(void);
    virtual void	Draw(void);
    
	MODELDATA	GetModelData(void);				//���f���f�[�^�Q�b�^�[
	void		SetModelData(MODELDATA Model);	//���f���f�[�^�Z�b�^�[

private:
    MODELDATA m_ModelData;		//���f���f�[�^
    CObject* m_pParentObject;	//
};
#endif

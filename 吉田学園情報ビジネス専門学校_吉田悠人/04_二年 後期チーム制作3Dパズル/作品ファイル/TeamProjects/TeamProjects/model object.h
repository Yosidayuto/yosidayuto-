//=============================================================================
//
//	�I�u�W�F�N�g���f��[model object.h]
//	Author:�g�c�I�l
//
//=============================================================================
#ifndef _MODEL_OBJECT_H_
#define _MODEL_OBJECT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "model.h"

//=============================================================================
//�N���X��`
//=============================================================================
class CModelObject : public CModel
{
public:

	CModelObject();
	virtual ~CModelObject();
	static CModelObject* Create(MODELDATA Data,CObject* pParentObject, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	MODELDATA m_ModelData;

};
#endif

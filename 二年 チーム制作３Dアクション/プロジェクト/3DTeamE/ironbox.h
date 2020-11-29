//=============================================================================
//
// �S�� [ironbox.h]
// Author : ��K������
//
//=============================================================================
#ifndef _IRONBOX_H_
#define _IRONBOX_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CIronBox : public CObject
{
public:
	CIronBox();
	~CIronBox();
	static HRESULT Load(void);
	static void Unload(void);
	static CIronBox* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
private:
	static CModel::MODELDATA m_modeldata;
	static D3DXMATERIAL *m_pMat;
	CModel* m_pModel;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
};
#endif
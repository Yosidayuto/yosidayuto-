//=============================================================================
//
// ���C������ [line.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _LINE_H_
#define _LINE_H_
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
class CLine :public CObject
{
public:
	CLine();
	~CLine();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetStartPosition(D3DXVECTOR3 pos);
	void SetEndPosition(D3DXVECTOR3 pos);

	void SetRotation(D3DXVECTOR3 rot);
	void SetCol(D3DCOLOR col);
	D3DXMATRIX GetWorld(void) { return m_StartWorld; };
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	static CModel::MODELDATA m_modeldata;
	static D3DXMATERIAL *m_pMat;
	D3DXMATRIX m_mtxWorld; //�s��v�Z�p
	D3DXMATRIX m_StartWorld; //�s��v�Z�p

	D3DXVECTOR3 m_Startpos;
	D3DXVECTOR3 m_Endpos;

	D3DXVECTOR3 m_rot;
	D3DCOLOR m_col;

};
#endif
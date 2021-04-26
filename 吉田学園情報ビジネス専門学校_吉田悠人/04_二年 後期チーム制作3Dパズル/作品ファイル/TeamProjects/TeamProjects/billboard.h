//=============================================================================
//
// �r���{�[�h [billboard.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CBillboard :public CObject
{
public:
	CBillboard();
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);									// �ʒu�Z�b�^�[
	void SetSize(D3DXVECTOR3 size);										// �T�C�Y�Z�b�^�[
	void SetRot(D3DXVECTOR3 rot);										// �T�C�Y�Z�b�^�[
	void SetColor(D3DXCOLOR col);										// �J���[�Z�b�^�[
	void SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2);	// �e�N�X�`���Z�b�^�[
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// �o�C���h�e�N�X�`��

	D3DXVECTOR3 GetPosition(void) { return m_pos; }						//�ʒu�Q�b�^�[
	D3DXVECTOR3 GetSize(void) { return m_size; }						//�T�C�Y�Q�b�^�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//�T�C�Y�Q�b�^�[
	D3DXCOLOR GetColor(void) { return m_col; }							//�J���[�Q�b�^�[

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;	//�s��v�Z�p
	
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_size;	// �T�C�Y
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXCOLOR	m_col;	// �J���[
	float m_fTexX;		// �e�N�X�`���ʒuX
	float m_fTexY;		// �e�N�X�`���ʒuY
	float m_fTexX2;		// �e�N�X�`���ʒuX2
	float m_fTexY2;		// �e�N�X�`���ʒuY2
};
#endif
//=============================================================================
//
// �|���S��2D���� [scene2d.h]
// Author : �U�J �����Y
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X(�h��)
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D();												// �R���X�g���N�^
	~CScene2D();											// �f�X�g���N�^
	static CScene2D *Create(D3DXVECTOR3 size);				// �쐬����
	HRESULT Init(D3DXVECTOR3 size);							// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	void SetPosition(D3DXVECTOR3 pos);						// �ݒu����

	D3DXVECTOR3 GetPosition(void);							// �ʒu���擾
	void SetTexPosition(int nCount, float nPattern);		// �e�N�X�`�����W�擾
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);			// �e�N�X�`���̊��蓖��
	void SetCol(D3DXCOLOR col);								// �J���[�Z�b�g
	void SetRotate(float fAngle);							// �p�x���
	void SetAnimation(float nPattern, int nMaxAnimation);	// �A�j���[�V�������
	void SetSize(D3DXVECTOR3 size);                         // �T�C�Y���

private:
	LPDIRECT3DTEXTURE9		m_pTexture;						// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;							// �|���S���̈ʒu
	D3DXVECTOR3				m_size;							// �|���S���̃T�C�Y

	float m_fAngle;											// �p�x
	float m_fAngle1;										// �p�x
	float m_fDiagonal;										// ��]���a
	float m_fChange;										// �g��k���ϊ�
	float m_fAdd;											// �����ς�
	float m_fAngleChane;									// ���]
};





#endif // !_SCENE2D_H_








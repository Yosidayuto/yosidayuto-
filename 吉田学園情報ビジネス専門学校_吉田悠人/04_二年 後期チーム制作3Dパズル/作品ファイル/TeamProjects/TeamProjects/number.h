//=============================================================================
//
// �i���o�[ [number.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef  _NUMBER_H_
#define  _NUMBER_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CNumber
{
public:

	CNumber();		// �R���X�g���N�^
	~CNumber();		// �f�X�g���N�^

	static CNumber*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ��������
	static HRESULT	Load(void);			// �e�N�X�`���ǂݍ���
	static void		Unload(void);		// �e�N�X�`���̔j��

	HRESULT Init(void);					// ����������
	void	Uninit(void);				// �I������
	void	Update(void);				// �X�V����
	void	Draw(void);					// �`�揈��
										   
	void	SetNumber(int nNumber);		// �\�����l�ݒ�
	void	SetPos(D3DXVECTOR3 pos);	// �ʒu�Z�b�^�[
	void	SetSize(D3DXVECTOR3 size);	// �T�C�Y�Z�b�^�[
	void	ColChange(D3DXCOLOR col);	// �J���[�`�F���W

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	static char*				m_cFileName;	// �t�@�C����
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;			// �ʒu
	D3DXVECTOR3					m_size;			// �T�C�Y
};




#endif